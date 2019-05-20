using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows;
using System.Media;
using System.Threading;

namespace Eurobot
{
    public partial class Form1 : Form
    {
        UpgradedDataGrid principal_objectifs;
        UpgradedDataGrid principal_zonesInt;

        Color borderColor = Color.FromArgb(0, 122, 204);
        //Color.FromArgb(104, 33, 122); Violet
        //Color.FromArgb(90, 200, 40);  Vert
        //Color.FromArgb(220, 91, 0);   Orange
        //Color.FromArgb(0, 122, 204);  Bleu

        // Tableau de l'historique pour la barre d'envoi
        public int[] Data = new int[256];
        public int reiceive_ok = 0;
        int i;
        string[] sendHistory = new string[25];
        int sendHistoryPos = 0;
        int sendHistoryMax = 1;
        char STX = '\u0002', ETX = '\u0003', CR = '\u0015';
        public string PrincipaleAdr = "2";
        public string DriverAdr = "1";
        bool DriverMotIsBrake = false, CartePrincIsStopped = false;
        bool BoardIsConnected = false;

        RoboteQ fRoboteQ;
        public Form1()
        {
            InitializeComponent();

            this.TransparencyKey = Color.Blue;
            this.BackColor = Color.Blue;
            this.DoubleBuffered = true;
            
            staStrLbl_Position.Alignment = ToolStripItemAlignment.Left;
            staStr_Status.BackColor = borderColor;
            
            principal_objectifs = new UpgradedDataGrid(dataGV_Objectifs);
            principal_objectifs.AddSaveHandler(tlStrMnuItm_ObjectifsSaveAs, tlStrMnuItm_ObjectifsSave, tlStrMnuItm_ObjectifsOpen);

            principal_zonesInt = new UpgradedDataGrid(dataGV_Zones);
            principal_zonesInt.AddSaveHandler(tlStrMnuItm_ZonesSaveAs, tlStrMnuItm_ZonesSave, tlStrMnuItm_ZonesOpen);
                
        }

        //Permet d'éviter l'effet de scintillement sur la carte
        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams cp = base.CreateParams;
                cp.ExStyle |= 0x02000000;  // Turn on WS_EX_COMPOSITED
                return cp;
            }
        }

        // Au chargement de la fenêtre
        private void Form1_Load(object sender, EventArgs e)
        {
            // On définit la taille des splitter
            spCon_Horizontal.SplitterDistance = spCon_Horizontal.Height / 15*10;
            spCon_Vertical.SplitterDistance = spCon_Vertical.Width / 19*10;
            spCon_Communication.SplitterDistance = spCon_Vertical.Height / 2;
            spCon_Communication1.SplitterDistance = spCon_Communication.Width / 2;
         }

        // Fonction d'envoi RS232
        public void SendDataRS(string data, bool ToDisplay=true)
        {
            tmr_Update.Enabled = false;
            // Calcul des hash et compute les données
            int i;
            // Les valeurs de base des Hash correspondent au premier espace après STX
            int Hash1 = 0x20, Hash2=0x20;
            // Hash les données
            for(i=0;i<data.Length;i++)
            {
                Hash1 = (Hash1 + data[i]) % 0x100;
                Hash2 = ((Hash2 + data[i]) * (i + 2)) % 0x100;
            }
            // Ajoute l'espace traité en plus
            Hash1 = (Hash1 + ' ') % 0x100;
            Hash2 = ((Hash2 + ' ') * (i + 2)) % 0x100;
            // Passage en byte
            byte H1 = (byte)Hash1, H2 = (byte)(Hash2);
            // Le caractère ETX est réservé pour la fin de tableau, il ne peut donc pas être utilisé pour le hash
            if (H1 == ETX||H1==CR) H1++;
            if (H2 == ETX||H2==CR) H2++;
                // Compute
            data = STX + " " + (char)(H1) + " " + (char)(H2) + " " + data + " " + ETX;

            char[] cMess = data.ToCharArray();
            byte[] bMess = new byte[cMess.Length];
            for (int b = 0; b < cMess.Length; b++)
                bMess[b] = (byte)cMess[b];
            // Essaie d'envoyer
            try
            {
                srlPort_RS.Write(bMess,0,bMess.Length);
                if (ToDisplay == true)
                {
                    // Affichage dans la RichTextBox des caractères envoyés
                    rTxt_Sent.Text += data + "\r";
                    // Descend la scroll bar en bas quand le texte dépasse
                    rTxt_Sent.SelectionStart = rTxt_Sent.Text.Length;
                    rTxt_Sent.ScrollToCaret();
                }
            }
            catch (Exception)
            {
                MessageBox.Show("Vérifiez le port "+srlPort_RS.PortName, "Échec de l'envoi");
            }

            tmr_Update.Enabled = true;
        }

        // Fonction de réception RS232
        public void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            System.IO.Ports.SerialPort sp = (System.IO.Ports.SerialPort)sender;
           
            int charRead = 0;
            if (fRoboteQ.receive_PID == 1)
            {
                while (sp.BytesToRead > 0)
                {
                    charRead = sp.ReadChar();
                    if (charRead != 6 && charRead != 0 && charRead != 21)
                    {
                        Data[i] = charRead;
                        i++;
                        if (charRead == 13)
                        {
                            reiceive_ok = 1;
                           fRoboteQ.Affiche_PID();
                           i = 0;
                        }
                    }
                }
            }
            else
            {
                if (this.rTxt_Received.InvokeRequired)
                {
                    AddTextCallback d = new AddTextCallback(AddText);
                    this.Invoke(d, new object[] { sp.ReadExisting() });

                }
                else
                {
                    AddText(sp.ReadExisting());
                }
            }
            
        }

        delegate void AddTextCallback(string text);

        private void AddText(string text)
        {
            text = String.Join('@' + Environment.NewLine, text.Split('@'));

            if (text.Contains((char)12))
            {
                text = text.Split((char)(12))[1];
                rTxt_Received.Text = "";
            }
            if (text.Contains("1")) BoardIsConnected = true;
            // Ajoute le texte dans la RichTextBox
            rTxt_Received.Text = rTxt_Received.Text + text;
            // Descend la scroll bar en bas quand le texte dépasse
            rTxt_Received.SelectionStart = rTxt_Received.Text.Length;
            rTxt_Received.ScrollToCaret();
        }


        private static Image carte = Image.FromFile("table.png");
        int map_Height = 0;
        int map_Width = 0;
        int map_PositionX = 0;
        int map_PositionY = 0;

        private Point ConvertPositionToMap(Point position)
        {
            int x, y;
            x = ((position.X - map_PositionX) * 3000) / map_Width;
            y = 2000-((position.Y - map_PositionY) * 2000) / map_Height;

            return new Point(x,y);
        }

        private Point ConvertPositionToScreen(Point position)
        {
            int x = ((position.X * map_Width) / 3000) + map_PositionX;
            int y = (((2000*map_Height)-(position.Y * map_Height)) / 2000) + map_PositionY;
            return new Point(x, y);
        }

        int IsMouseDown = 0;
        int MouseDownSelected = 0;

        Bitmap dragBit = new Bitmap(30, 30);

        private void bufferedPanel1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            Int32 num_obj;

            if (buffPan_Carte.Size.Height * 3 < buffPan_Carte.Size.Width * 2)
            {
                map_Height = buffPan_Carte.Size.Height - 20;
                map_Width = (int)((buffPan_Carte.Size.Height - 20) * 1.5);
            }
            else
            {
                map_Height = (int)((buffPan_Carte.Size.Width - 20) / 1.5);
                map_Width = buffPan_Carte.Size.Width - 20;
            }

            map_PositionX = (buffPan_Carte.Size.Width - map_Width) / 2;
            map_PositionY = (buffPan_Carte.Size.Height - map_Height) / 2;

            g.DrawImage(carte, new Rectangle(map_PositionX, map_PositionY, map_Width, map_Height));

            System.Drawing.Drawing2D.HatchBrush mybrush = new System.Drawing.Drawing2D.HatchBrush(System.Drawing.Drawing2D.HatchStyle.BackwardDiagonal, Color.Black, Color.Transparent);

            for (int i = 0; i < dataGV_Zones.Rows.Count - 1; i++)
            {
                try
                {
                    Point[] points = {ConvertPositionToScreen(new Point(Convert.ToInt32(dataGV_Zones.Rows[i].Cells[1].Value), Convert.ToInt32(dataGV_Zones.Rows[i].Cells[2].Value))),
                                 ConvertPositionToScreen(new Point(Convert.ToInt32(dataGV_Zones.Rows[i].Cells[3].Value), Convert.ToInt32(dataGV_Zones.Rows[i].Cells[4].Value))),
                                 ConvertPositionToScreen(new Point(Convert.ToInt32(dataGV_Zones.Rows[i].Cells[5].Value), Convert.ToInt32(dataGV_Zones.Rows[i].Cells[6].Value))),
                                 ConvertPositionToScreen(new Point(Convert.ToInt32(dataGV_Zones.Rows[i].Cells[7].Value), Convert.ToInt32(dataGV_Zones.Rows[i].Cells[8].Value)))
                                 };

                    g.FillPolygon(mybrush, points);
                    g.DrawPolygon(new Pen(Color.Black), points);
                }
                catch (Exception) { }

                
            }

            for (int i = 0; i < dataGV_Objectifs.Rows.Count - 1; i++)
            {
                StringFormat sf = new StringFormat();
                sf.Alignment = StringAlignment.Center;
                sf.LineAlignment = StringAlignment.Center;

                int value_x = 0, value_y = 0;

                try {
                    value_x = Convert.ToInt32(dataGV_Objectifs.Rows[i].Cells[2].Value);
                }
                catch (Exception) {
                    value_x = 0;
                }

                try {
                    value_y = Convert.ToInt32(dataGV_Objectifs.Rows[i].Cells[3].Value);
                }
                catch (Exception) {
                    value_y = 0;
                }

                string valueText = "";

                try {
                    valueText = dataGV_Objectifs.Rows[i].Cells[1].Value.ToString();
                }
                catch (Exception) {
                    valueText = "";
                }
                try{
                    num_obj =Convert.ToInt32(dataGV_Objectifs.Rows[i].Cells[0].Value);
                }
                catch(Exception) {
                        num_obj = 0;
                }
                switch(num_obj)
                {
                    case 1 :
                    g.FillEllipse(new SolidBrush(Color.FromArgb(0, 122, 204)), new Rectangle(
                        ConvertPositionToScreen(new Point(value_x, value_y)).X - 11,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y - 11,
                        22, 22));
                    g.DrawEllipse(new Pen(new SolidBrush(Color.Black)), new Rectangle(
                        ConvertPositionToScreen(new Point(value_x, value_y)).X - 11,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y - 11,
                        22, 22));

                    g.DrawString(valueText, new Font("Segoe UI", 11, FontStyle.Bold), new SolidBrush(Color.Black),
                        ConvertPositionToScreen(new Point(value_x, value_y)).X,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y, sf);
                    break;

                    case 2:
                    g.FillEllipse(new SolidBrush(Color.FromArgb(127, 255, 0)), new Rectangle(
                        ConvertPositionToScreen(new Point(value_x, value_y)).X - 11,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y - 11,
                        22, 22));
                    g.DrawEllipse(new Pen(new SolidBrush(Color.Black)), new Rectangle(
                        ConvertPositionToScreen(new Point(value_x, value_y)).X - 11,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y - 11,
                        22, 22));

                    g.DrawString(valueText, new Font("Segoe UI", 11, FontStyle.Bold), new SolidBrush(Color.Black),
                        ConvertPositionToScreen(new Point(value_x, value_y)).X,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y, sf);
                    break;

                    case 3:
                    g.FillEllipse(new SolidBrush(Color.FromArgb(255, 140, 0)), new Rectangle(
                        ConvertPositionToScreen(new Point(value_x, value_y)).X - 11,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y - 11,
                        22, 22));
                    g.DrawEllipse(new Pen(new SolidBrush(Color.Black)), new Rectangle(
                        ConvertPositionToScreen(new Point(value_x, value_y)).X - 11,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y - 11,
                        22, 22));

                    g.DrawString(valueText, new Font("Segoe UI", 11, FontStyle.Bold), new SolidBrush(Color.Black),
                        ConvertPositionToScreen(new Point(value_x, value_y)).X,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y, sf);
                    break;

                    case 4:
                    g.FillEllipse(new SolidBrush(Color.FromArgb(255, 255, 0)), new Rectangle(
                        ConvertPositionToScreen(new Point(value_x, value_y)).X - 11,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y - 11,
                        22, 22));
                    g.DrawEllipse(new Pen(new SolidBrush(Color.Black)), new Rectangle(
                        ConvertPositionToScreen(new Point(value_x, value_y)).X - 11,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y - 11,
                        22, 22));

                    g.DrawString(valueText, new Font("Segoe UI", 11, FontStyle.Bold), new SolidBrush(Color.Black),
                        ConvertPositionToScreen(new Point(value_x, value_y)).X,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y, sf);
                    break;

                    case 5:
                    g.FillEllipse(new SolidBrush(Color.FromArgb(255, 0, 0)), new Rectangle(
                        ConvertPositionToScreen(new Point(value_x, value_y)).X - 11,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y - 11,
                        22, 22));
                    g.DrawEllipse(new Pen(new SolidBrush(Color.Black)), new Rectangle(
                        ConvertPositionToScreen(new Point(value_x, value_y)).X - 11,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y - 11,
                        22, 22));

                    g.DrawString(valueText, new Font("Segoe UI", 11, FontStyle.Bold), new SolidBrush(Color.Black),
                        ConvertPositionToScreen(new Point(value_x, value_y)).X,
                        ConvertPositionToScreen(new Point(value_x, value_y)).Y, sf);
                    break;

                    default:
                        g.FillEllipse(new SolidBrush(Color.FromArgb(255, 255, 255)), new Rectangle(
                            ConvertPositionToScreen(new Point(value_x, value_y)).X - 11,
                            ConvertPositionToScreen(new Point(value_x, value_y)).Y - 11,
                            22, 22));
                        g.DrawEllipse(new Pen(new SolidBrush(Color.Black)), new Rectangle(
                            ConvertPositionToScreen(new Point(value_x, value_y)).X - 11,
                            ConvertPositionToScreen(new Point(value_x, value_y)).Y - 11,
                            22, 22));

                        g.DrawString(valueText, new Font("Segoe UI", 11, FontStyle.Bold), new SolidBrush(Color.Black),
                            ConvertPositionToScreen(new Point(value_x, value_y)).X,
                            ConvertPositionToScreen(new Point(value_x, value_y)).Y, sf);
                    break;

                }
            }

            // Dessine un cadre
            g.DrawLine(new Pen(borderColor), 0, 0, 0, buffPan_Carte.Size.Height);
            g.DrawLine(new Pen(borderColor), 0, 0, buffPan_Carte.Size.Width, 0);
            g.DrawLine(new Pen(borderColor), buffPan_Carte.Size.Width - 1, buffPan_Carte.Size.Height - 1, 0, buffPan_Carte.Size.Height - 1);
            g.DrawLine(new Pen(borderColor), buffPan_Carte.Size.Width - 1, buffPan_Carte.Size.Height - 1, buffPan_Carte.Size.Width - 1, 0);
            g.DrawLine(new Pen(borderColor), 1, 1, 1, buffPan_Carte.Size.Height);
            g.DrawLine(new Pen(borderColor), 1, 1, buffPan_Carte.Size.Width, 1);
            g.DrawLine(new Pen(borderColor), buffPan_Carte.Size.Width - 2, buffPan_Carte.Size.Height - 2, 1, buffPan_Carte.Size.Height - 2);
            g.DrawLine(new Pen(borderColor), buffPan_Carte.Size.Width - 2, buffPan_Carte.Size.Height - 2, buffPan_Carte.Size.Width - 2, 1);
            //*/
        }

        /// <summary>
        /// Se déclenche en cas d'appui sur une touche d'appui de la souris
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void bufferedPanel1_MouseDown(object sender, MouseEventArgs e)
        {
            MouseEventArgs MouseE = e;

            //Si on est en train d'appuyer sur la touche shift
            if (e.Button == System.Windows.Forms.MouseButtons.Left && (Control.ModifierKeys & Keys.Shift) == Keys.Shift)
            {
                //On récupère la position de la souris
                int PositionX = ConvertPositionToMap(e.Location).X;
                int PositionY = ConvertPositionToMap(e.Location).Y;

                dataGV_Zones.Rows.Insert(dataGV_Zones.Rows.Count - 1, 1);
                dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[0].Value = (dataGV_Zones.Rows.Count - 1).ToString();
                dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[1].Value = ConvertPositionToMap(new Point(MouseE.X, MouseE.Y)).X;
                dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[2].Value = ConvertPositionToMap(new Point(MouseE.X, MouseE.Y)).Y;
                dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[7].Value = ConvertPositionToMap(new Point(MouseE.X, MouseE.Y)).X;
                dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[4].Value = ConvertPositionToMap(new Point(MouseE.X, MouseE.Y)).Y;

                IsMouseDown = 6;
            }
            //Si c'est uniquement un clic gauche, soit si la souris se trouve au dessus d'un objectif, alors on le déplace
            //Sinon si il n'y a aucune coordonée en dessous, alors on en place une
            else if(e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                //On récupère la position de la souris
                int PositionX = ConvertPositionToMap(e.Location).X;
                int PositionY = ConvertPositionToMap(e.Location).Y;

                //On parcours le tableau pour vérifier qu'il y a un rond à cette position
                for (int i = dataGV_Objectifs.Rows.Count - 2; i >= 0; i--)
                {
                    int value_x = 0, value_y = 0;
                    Point position = ConvertPositionToMap(new Point(e.X, e.Y));

                    //évite les erreurs en cas de valeur incorrecte dans la case
                    try {
                        value_x = Convert.ToInt32(dataGV_Objectifs.Rows[i].Cells[2].Value);
                    }
                    catch (Exception) {
                        value_x = 0;
                    }

                    try {
                        value_y = Convert.ToInt32(dataGV_Objectifs.Rows[i].Cells[3].Value);
                    }
                    catch (Exception) {
                        value_y = 0;
                    }

                    //Pour s'adapter à la taille de l'affichage
                    int marge = (11 * 3000) / map_Width;

                    if (position.X < value_x + marge && position.X > value_x - marge && position.Y > value_y - marge && position.Y < value_y + marge)
                    {
                        MouseMove_last = ConvertPositionToScreen(new Point(value_x, value_y));
                        IsMouseDown = 1;
                        MouseDownSelected = i;
                        return;
                    }
                }

                //On parcours le tableau pour vérifier si il y a une zone interdite à cet endroit
                for (int i = dataGV_Zones.Rows.Count - 2; i >= 0; i--)
                {
                    int value_x = 0, value_y = 0;
                    Point position = ConvertPositionToMap(new Point(e.X, e.Y));

                    for (int j = 0; j < 4; j++)
                    {
                        //évite les erreurs en cas de valeur incorrecte dans la case
                        try
                        {
                            value_x = Convert.ToInt32(dataGV_Zones.Rows[i].Cells[j*2 + 1].Value);
                        }
                        catch (Exception)
                        {
                            value_x = 0;
                        }

                        try
                        {
                            value_y = Convert.ToInt32(dataGV_Zones.Rows[i].Cells[j*2 + 2].Value);
                        }
                        catch (Exception)
                        {
                            value_y = 0;
                        }

                        //Pour s'adapter à la taille de l'affichage
                        int marge = (7 * 3000) / map_Width;

                        if (position.X < value_x + marge && position.X > value_x - marge && position.Y > value_y - marge && position.Y < value_y + marge)
                        {
                            MouseMove_last = ConvertPositionToScreen(new Point(value_x, value_y));
                            IsMouseDown = 2 + j;
                            MouseDownSelected = i;
                            return;
                        }
                    }
                }

                dataGV_Objectifs.Rows.Insert(dataGV_Objectifs.Rows.Count - 1, 1);
                dataGV_Objectifs.Rows[dataGV_Objectifs.Rows.Count - 2].Cells[1].Value = (dataGV_Objectifs.Rows.Count - 1).ToString();
                dataGV_Objectifs.Rows[dataGV_Objectifs.Rows.Count - 2].Cells[2].Value = ConvertPositionToMap(new Point(MouseE.X, MouseE.Y)).X;
                dataGV_Objectifs.Rows[dataGV_Objectifs.Rows.Count - 2].Cells[3].Value = ConvertPositionToMap(new Point(MouseE.X, MouseE.Y)).Y;

                Rectangle changedArea = new Rectangle(e.X - 15, e.Y - 15, 30, 30);
                buffPan_Carte.Invalidate(changedArea);
            }
            //Si on fait un clic droit, alors on vérifie si il y a un objectif à cet endroit, et si oui on le supprime
            else if (MouseE.Button == System.Windows.Forms.MouseButtons.Right)
            {
                //Parcourt le tableau des objectifs
                for (int i = dataGV_Objectifs.Rows.Count - 2; i >= 0; i--)
                {
                    int value_x = 0, value_y = 0;
                    Point position = ConvertPositionToMap(new Point(MouseE.X, MouseE.Y));

                    //évite les erreurs en cas de valeur incorrecte dans la case
                    try {
                        value_x = Convert.ToInt32(dataGV_Objectifs.Rows[i].Cells[2].Value);
                    }
                    catch (Exception) {
                        value_x = 0;
                    }

                    try {
                        value_y = Convert.ToInt32(dataGV_Objectifs.Rows[i].Cells[3].Value);
                    }
                    catch (Exception) {
                        value_y = 0;
                    }

                    //Pour supprimer selon la taille de l'image
                    int marge = (11 * 3000) / map_Width;

                    //Vérifie qu'il y a un rond
                    if (position.X < value_x + marge && position.X > value_x - marge && position.Y > value_y - marge && position.Y < value_y + marge)
                    {
                        dataGV_Objectifs.Rows.RemoveAt(i);
                        Rectangle changedArea = new Rectangle(ConvertPositionToScreen(new Point(value_x, value_y)).X - 15, ConvertPositionToScreen(new Point(value_x, value_y)).Y - 15, 30, 30);
                        buffPan_Carte.Invalidate(changedArea);
                        return;
                    }
                }
            }
        }

        /// <summary>
        /// Se déclenche lorsque l'on relâche la souris, permet de valider le déplacement d'un objectif
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void bufferedPanel1_MouseUp(object sender, MouseEventArgs e)
        {
            //Si la souris était déjà appuyée (déplacement d'un point), alors on relâche sur la position actuelle
            if(IsMouseDown == 1)
            {
                //Récupère la position
                int PositionX = ConvertPositionToMap(e.Location).X;
                int PositionY = ConvertPositionToMap(e.Location).Y;

                //On déplace la position d'un rond
                dataGV_Objectifs.Rows[MouseDownSelected].Cells[2].Value = PositionX;
                dataGV_Objectifs.Rows[MouseDownSelected].Cells[3].Value = PositionY;

                buffPan_Carte.Invalidate();
                IsMouseDown = 0;
            }
            else if (IsMouseDown > 1 && IsMouseDown < 6)
            {
                //Récupère la position
                int PositionX = ConvertPositionToMap(e.Location).X;
                int PositionY = ConvertPositionToMap(e.Location).Y;

                //On déplace la position d'une zone interdite
                dataGV_Zones.Rows[MouseDownSelected].Cells[(IsMouseDown - 2) * 2 + 1].Value = PositionX;
                dataGV_Zones.Rows[MouseDownSelected].Cells[(IsMouseDown - 2) * 2 + 2].Value = PositionY;

                buffPan_Carte.Invalidate();
                IsMouseDown = 0;
            }
            else if (IsMouseDown == 6)
            {
                //Récupère la position
                int PositionX = ConvertPositionToMap(e.Location).X;
                int PositionY = ConvertPositionToMap(e.Location).Y;

                //On déplace la position d'une zone interdite
                dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[5].Value = PositionX;
                dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[6].Value = PositionY;
                dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[3].Value = PositionX;
                dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[8].Value = PositionY;

                buffPan_Carte.Invalidate();

                IsMouseDown = 0;
            }
        }

        public Point MouseMove_last = new Point(0, 0);

        private void bufferedPanel1_MouseMove(object sender, MouseEventArgs e)
        {
            //Récupère la position
            int PositionX = 0;
            int PositionY = 0;
            // Try-Catch pour éviter une division par 0 dans certains cas au démarrage
            try
            {
                PositionX = ConvertPositionToMap(e.Location).X;
                PositionY = ConvertPositionToMap(e.Location).Y;
            }
            catch (Exception) { }


            //Affiche la position dans la barre de statut au fond
            staStrLbl_Position.Visible = true;
            staStrLbl_Position.Text = "Position : " + PositionX.ToString() + " ; " + PositionY.ToString();

            //Si on déplace un point
            if (IsMouseDown == 1)
            {
                //On déplace la position d'un rond
                dataGV_Objectifs.Rows[MouseDownSelected].Cells[2].Value = PositionX;
                dataGV_Objectifs.Rows[MouseDownSelected].Cells[3].Value = PositionY;

                //Invalide la position de départ, afin de la redessiner
                Rectangle changedArea = new Rectangle(e.X - 15, e.Y - 15, 30, 30);
                buffPan_Carte.Invalidate(changedArea);

                //Invalide la position d'arrivée, afin de la redessiner
                changedArea = new Rectangle(MouseMove_last.X - 15, MouseMove_last.Y - 15, 30, 30);
                buffPan_Carte.Invalidate(changedArea);

                //Sauvegarde la dernière position
                MouseMove_last = e.Location;
            }
            //Si on déplace une zone interdite
            else if (IsMouseDown >= 2 && IsMouseDown < 6)
            {
                try{
                    //Cherche les valeurs min et max
                    int maxX = Math.Max(Math.Max(Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[1].Value), Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[3].Value)),
                                        Math.Max(Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[5].Value), Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[7].Value)));

                    int maxY = Math.Max(Math.Max(Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[2].Value), Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[4].Value)),
                                        Math.Max(Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[6].Value), Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[8].Value)));

                    int minX = Math.Min(Math.Min(Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[1].Value), Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[3].Value)),
                                        Math.Min(Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[5].Value), Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[7].Value)));

                    int minY = Math.Min(Math.Min(Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[2].Value), Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[4].Value)),
                                        Math.Min(Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[6].Value), Convert.ToInt32(dataGV_Zones.Rows[MouseDownSelected].Cells[8].Value)));

                    maxX = Math.Max(maxX, PositionX);
                    maxY = Math.Max(maxY, PositionY);

                    minX = Math.Min(minX, PositionX);
                    minY = Math.Min(minY, PositionY);

                    maxX = ConvertPositionToScreen(new Point(maxX, maxY)).X + 1;
                    maxY = ConvertPositionToScreen(new Point(maxX, maxY)).Y + 1;
                    minX = ConvertPositionToScreen(new Point(minX, minY)).X - 1;
                    minY = ConvertPositionToScreen(new Point(minX, minY)).Y - 1;

                    //Remplace la valeur dans le tableau
                    dataGV_Zones.Rows[MouseDownSelected].Cells[(IsMouseDown - 2) * 2 + 1].Value = PositionX;
                    dataGV_Zones.Rows[MouseDownSelected].Cells[(IsMouseDown - 2) * 2 + 2].Value = PositionY;

                    //Invalide uniquement la zone du cadre
                    Rectangle changedArea = new Rectangle(minX, minY, maxX - minX, maxY - minY);
                    buffPan_Carte.Invalidate(changedArea);
                }
                catch (Exception)
                {
                    dataGV_Zones.Rows[MouseDownSelected].Cells[(IsMouseDown - 2) * 2 + 1].Value = PositionX;
                    dataGV_Zones.Rows[MouseDownSelected].Cells[(IsMouseDown - 2) * 2 + 2].Value = PositionY;

                    buffPan_Carte.Invalidate();
                }

                MouseMove_last = e.Location;
            }
            //Permet d'afficher la zone interdite lors de sa création
            else if (IsMouseDown == 6)
            {
                try
                {
                    //Cherche les valeurs min et max
                    int maxX = Math.Max(Math.Max(Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[1].Value), Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[3].Value)),
                                        Math.Max(Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[5].Value), Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[7].Value)));

                    int maxY = Math.Max(Math.Max(Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[2].Value), Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[4].Value)),
                                        Math.Max(Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[6].Value), Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[8].Value)));

                    int minX = Math.Min(Math.Min(Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[1].Value), Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[3].Value)),
                                        Math.Min(Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[5].Value), Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[7].Value)));

                    int minY = Math.Min(Math.Min(Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[2].Value), Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[4].Value)),
                                        Math.Min(Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[6].Value), Convert.ToInt32(dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[8].Value)));

                    maxX = Math.Max(maxX, PositionX);
                    maxY = Math.Max(maxY, PositionY);

                    minX = Math.Min(minX, PositionX);
                    minY = Math.Min(minY, PositionY);

                    maxX = ConvertPositionToScreen(new Point(maxX, maxY)).X + 1;
                    maxY = ConvertPositionToScreen(new Point(maxX, maxY)).Y + 1;
                    minX = ConvertPositionToScreen(new Point(minX, minY)).X - 1;
                    minY = ConvertPositionToScreen(new Point(minX, minY)).Y - 1;

                    //On déplace la position d'une zone interdite
                    dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[5].Value = PositionX;
                    dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[6].Value = PositionY;
                    dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[3].Value = PositionX;
                    dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[8].Value = PositionY;

                    //Invalide uniquement la zone du cadre
                    Rectangle changedArea = new Rectangle(minX, minY, maxX - minX, maxY - minY);
                    buffPan_Carte.Invalidate(changedArea);
                }
                catch(Exception)
                {
                    //On déplace la position d'une zone interdite
                    dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[5].Value = PositionX;
                    dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[6].Value = PositionY;
                    dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[3].Value = PositionX;
                    dataGV_Zones.Rows[dataGV_Zones.Rows.Count - 2].Cells[8].Value = PositionY;

                    buffPan_Carte.Invalidate();
                }
            }
        }

        // Envoi de commandes à la carte principale
        // Tool Strip Item Start
        private void tlStrMnuItm_Start_Click(object sender, EventArgs e)
        {
            if (CartePrincIsStopped == true)
            {
                SendDataRS(PrincipaleAdr + " 10 1");
                CartePrincIsStopped = false;
            }
            else SendDataRS(PrincipaleAdr + "11 0");
        }

        // Tool Strip Item Stop
        private void tlStrMnuItm_Stop_Click(object sender, EventArgs e)
        {
            SendDataRS(PrincipaleAdr+" 11 1");
            CartePrincIsStopped = true;
        }

        // Tool Strip Item Pause
        private void tlStrMnuItm_Pause_Click(object sender, EventArgs e)
        {
            SendDataRS(PrincipaleAdr + " 10 0");
        }
        
        // Appui sur Enter dans txt_Send pour envoyer
        private void txt_Send_KeyDown(object sender, KeyEventArgs e)
        {
            // Définit à quelle plaque on communique
            string ToComm;
            if (cbBoardToSend.SelectedIndex == 0) ToComm = PrincipaleAdr;
            else ToComm = DriverAdr;

            if (e.KeyCode == Keys.Enter)
            {
                for (int i = 24; i > 1; i--)
			    {
			        sendHistory[i] = sendHistory[i-1];
			    }
                sendHistory[1] = txt_Send.Text;
                sendHistoryPos = 1;
                SendDataRS(ToComm+" "+txt_Send.Text);
                txt_Send.Text = "";
            }

            if (e.KeyCode == Keys.Up)
            {
                txt_Send.Text = sendHistory[sendHistoryPos];
                if (sendHistoryPos < 24)
                {
                    sendHistoryPos++;
                }
                else
                {
                    sendHistoryPos = 24;
                }
            }

            if (e.KeyCode == Keys.Down)
            {
                if (sendHistoryPos > 1)
                {
                    sendHistoryPos--;
                }
                else
                {
                    sendHistoryPos = 0;
                }
                txt_Send.Text = sendHistory[sendHistoryPos];
            }
        }

        // Bouton "Effacer"
        private void btn_Clear_Click(object sender, EventArgs e)
        {
            rTxt_Received.Text = "";
            rTxt_Sent.Text = "";
        }

        // Bouton "Aller à"
        private void btn_GoTo_Click(object sender, EventArgs e)
        {
            int x, y;
            try
            {
                x = Convert.ToInt16(txt_PosX.Text);
                y = Convert.ToInt16(txt_PosY.Text);
                SendDataRS(DriverAdr + " 13 " + x + " " + y);
            }
            catch (Exception)
            {
                MessageBox.Show("La position doit être une valeur entière entre -32768 et 32767", "Valeur entière demandée");
            }
        }

        // Bouton "Init position"
        private void btn_InitPosition_Click(object sender, EventArgs e)
        {
            UInt16 x, y, phi;
            try
            {
                x = Convert.ToUInt16(txt_PosX.Text);
                y = Convert.ToUInt16(txt_PosY.Text);
                phi = Convert.ToUInt16(txt_Angle.Text);
                SendDataRS(PrincipaleAdr + " 12 " + x + " " + y + " " + phi);
            }
            catch (Exception)
            {
                MessageBox.Show("La position doit contenir des valeurs entières entre 0 et "+UInt16.MaxValue.ToString()+".", "Valeur entière demandée");
            }
        }

        // Bouton "Reset principal"
        private void tlStrMnuItm_Reset_Principal_Click(object sender, EventArgs e)
        {
            SendDataRS(PrincipaleAdr+" 2");
        }

        // Bouton "Reset driver"
        private void tlStrMnuItm_Reset_Driver_Click(object sender, EventArgs e)
        {
            SendDataRS(DriverAdr + " 2");
        }

        private void timer_update_Tick(object sender, EventArgs e)
        {
            // Regarde si port ouvert et répond
            if (!srlPort_RS.IsOpen)
            {
                tlStrStaLbl_State.Text = "État de la connexion : [" + srlPort_RS.PortName + "] fermé";
                staStr_Status.BackColor = Color.FromArgb(104, 33, 122);
            }
            else
            {
                    tlStrStaLbl_State.Text = "État de la connexion : [" + srlPort_RS.PortName + "] - Connecté   |   ";
                    staStr_Status.BackColor = Color.FromArgb(0, 122, 204);

                    BoardIsConnected = false;
                    // Regarde si carte principale connectée
                 /*   SendDataRS(PrincipaleAdr + " 1",false); //Envoi le code de demande à la carte
                    Thread.Sleep(20);
                    if (BoardIsConnected) tlStrStaLbl_State.Text += "[CARTE PRINCIPALE] - Connectée   |   ";
                    else tlStrStaLbl_State.Text += "[CARTE PRINCIPALE] - Déconnectée   |   ";
                    BoardIsConnected = false;
                    Thread.Sleep(20);
                    // Regarde si carte driver connectée
                    SendDataRS(DriverAdr+" 1",false); //Envoi le code de demande à la carte
                    Thread.Sleep(20);
                    if (BoardIsConnected) tlStrStaLbl_State.Text += "[CARTE DRIVER] - Connectée   |   ";
                    else tlStrStaLbl_State.Text += "[CARTE DRIVER] - Déconnectée   |   ";
                    BoardIsConnected = false;
                    Thread.Sleep(20);
                    // Regarde si module RoboteQ connecté
                    SendDataRS(DriverAdr+" 3",false); //Envoi le code de demande à la carte
                    Thread.Sleep(20);
                    if (BoardIsConnected) tlStrStaLbl_State.Text += "[ROBOTEQ] - Connecté";
                    else tlStrStaLbl_State.Text += "[ROBOTEQ] - Déconnecté";
                    BoardIsConnected = false;*/
            }
        }

        // Symétrie d'axe X des objectifs
        private void tlStrMnuItm_SymmetryX_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < dataGV_Objectifs.Rows.Count - 1; i++)
            {
                dataGV_Objectifs.Rows[i].Cells[1].Value = 3000 - Convert.ToInt32(dataGV_Objectifs.Rows[i].Cells[1].Value);
            }
        }

        // Symétrie d'axe Y des objectifs
        private void tlStrMnuItm_SymmetryY_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < dataGV_Objectifs.Rows.Count - 1; i++)
            {
                dataGV_Objectifs.Rows[i].Cells[2].Value = 2000 - Convert.ToInt32(dataGV_Objectifs.Rows[i].Cells[2].Value);
            }
        }

        // Envoi des zones interdites
        private void tlStrMnuItm_ZonesSend_Click(object sender, EventArgs e)
        {
            string Data;
            // Envoi objectifs, sauvegarde en ram
            int i;
            for (i = 0; i < dataGV_Zones.Rows.Count - 1; i++)
            {
                Data= " 19 ";
                for (int j = 0; j < dataGV_Zones.Columns.Count; j++)
                {
                    Data += " ";

                    if (dataGV_Zones.Rows[i].Cells[j].Value != null)
                        Data += dataGV_Zones.Rows[i].Cells[j].Value.ToString();
                }
                SendDataRS(PrincipaleAdr + Data);
                Thread.Sleep(100);
              }        
        }

        // Gestion du menu déroulant pour le choix du PORT COM
        private void TryOpenPort(string portName)
        {
            srlPort_RS.Close();
            try
            {
                srlPort_RS.PortName = portName;
                srlPort_RS.Open();
                tlStrMnuItm_PortState.Text = "Fermer le port " + portName;
                tlStrMnuItm_RS232.Image = Image.FromFile("../../../Ressources/close_port.png");
            }
            catch (Exception)
            {
                MessageBox.Show("Échec de l'ouverture du port " + portName, "Erreur");
                tlStrMnuItm_PortState.Text = "Ouvrir le port " + portName;
                tlStrMnuItm_RS232.Image = Image.FromFile("../../../Ressources/open_port.png");
            }
        }
        private void tlStrMnuItm_COM1_Click(object sender, EventArgs e)
        {
            fRoboteQ = new RoboteQ();
            tlStrMnuItm_COM1.Checked = true;
            tlStrMnuItm_COMx.Checked = tlStrMnuItm_COM2.Checked = tlStrMnuItm_COM3.Checked = tlStrMnuItm_COM4.Checked = tlStrMnuItm_COM5.Checked = false;
            TryOpenPort("COM1");
        }
        private void tlStrMnuItm_COM2_Click(object sender, EventArgs e)
        {
            fRoboteQ = new RoboteQ();
            tlStrMnuItm_COM2.Checked = true;
            tlStrMnuItm_COMx.Checked = tlStrMnuItm_COM1.Checked = tlStrMnuItm_COM3.Checked = tlStrMnuItm_COM4.Checked = tlStrMnuItm_COM5.Checked = false;
            TryOpenPort("COM2");
        }
        private void tlStrMnuItm_COM3_Click(object sender, EventArgs e)
        {
            fRoboteQ = new RoboteQ();
            tlStrMnuItm_COM3.Checked = true;
            tlStrMnuItm_COMx.Checked = tlStrMnuItm_COM1.Checked = tlStrMnuItm_COM2.Checked = tlStrMnuItm_COM4.Checked = tlStrMnuItm_COM5.Checked = false;
            TryOpenPort("COM3");
        }
        private void tlStrMnuItm_COM4_Click(object sender, EventArgs e)
        {
            fRoboteQ = new RoboteQ();
            tlStrMnuItm_COM4.Checked = true;
            tlStrMnuItm_COMx.Checked = tlStrMnuItm_COM1.Checked = tlStrMnuItm_COM2.Checked = tlStrMnuItm_COM3.Checked = tlStrMnuItm_COM5.Checked = false;
            TryOpenPort("COM4");
        }
        private void cOM5ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            fRoboteQ = new RoboteQ();
            tlStrMnuItm_COM5.Checked = true;
            tlStrMnuItm_COMx.Checked = tlStrMnuItm_COM1.Checked = tlStrMnuItm_COM2.Checked = tlStrMnuItm_COM3.Checked = tlStrMnuItm_COM4.Checked = false;
            TryOpenPort("COM5");
        }
        private void tlStrMnuItm_COMx_Click(object sender, EventArgs e)
        {
            fRoboteQ = new RoboteQ();
            tlStrMnuItm_COMx.Checked = true;
            tlStrMnuItm_COM1.Checked = tlStrMnuItm_COM2.Checked = tlStrMnuItm_COM3.Checked = tlStrMnuItm_COM4.Checked = tlStrMnuItm_COM5.Checked = false;
            TryOpenPort(tlStrMnuItm_COMPerso.Text);
        }
        // Ouverture et fermeture du port COM
        private void tlStrMnuItm_PortState_Click(object sender, EventArgs e)
        {
            if (srlPort_RS.IsOpen)
            {
                // Si le port est ouvert on le ferme et on met à jour tlStrMnuItm_PortState
                srlPort_RS.Close();
                tlStrMnuItm_RS232.Image = Image.FromFile("../../../Ressources/open_port.png");
                tlStrMnuItm_PortState.Text = "Ouvrir le port " + srlPort_RS.PortName;
            }
            else
            {
                // Si le port est fermé on essaie de l'ouvrir
                TryOpenPort(srlPort_RS.PortName);
            }
        }

        // Lors que rTxt_Sent est sélectionné on place le curseur dans txt_Send pour éviter d'écrire dans la richTextBox
        private void rTxt_Sent_Enter(object sender, EventArgs e)
        {
            txt_Send.Focus();
        }

        // Au clique sur l'item "Nouveau" dans le menu "Objectifs"
        private void tlStrMnuItm_ObjectifsNew_Click(object sender, EventArgs e)
        {
            // On contrôle que le tableau ne soit pas vide
            if (dataGV_Objectifs.Rows.Count > 1)
            {
                // Si c'est le cas, on affiche un message de confirmation
                if ((MessageBox.Show("Voulez-vous vraiment effacer tous les objectifs?", "Effacer tous les objectifs",
                MessageBoxButtons.OKCancel, MessageBoxIcon.Question)) == DialogResult.OK)
                {
                    dataGV_Objectifs.Rows.Clear();
                }
            }
        }

        // Au clique sur l'item "Nouveau" dans le menu "Zones interdites"
        private void tlStrMnuItm_ZonesNew_Click(object sender, EventArgs e)
        {
            // On contrôle que le tableau ne soit pas vide
            if (dataGV_Zones.Rows.Count > 1)
            {
                // Si c'est le cas, on affiche un message de confirmation
                if ((MessageBox.Show("Voulez-vous vraiment effacer toutes les zones interdites?", "Effacer toutes les zones interdites",
                MessageBoxButtons.OKCancel, MessageBoxIcon.Question)) == DialogResult.OK)
                {
                    dataGV_Zones.Rows.Clear();
                }
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            srlPort_RS.Close();
        }

        private void btnTestComm_Click(object sender, EventArgs e)
        {
            SendDataRS(DriverAdr+" 0");
        }

        private void roboteQToolStripMenuItem_Click(object sender, EventArgs e)
        {
            fRoboteQ = new RoboteQ();
            fRoboteQ.Owner = this;
            fRoboteQ.Show();
        }

        private void txtPrincAdr_Leave(object sender, EventArgs e)
        {
            try
            {
                UInt32 Val = Convert.ToUInt32(txtPrincAdr.Text);
                if (Val == Convert.ToUInt32(PrincipaleAdr)) return;
                else
                {
                    if (Val == 3)
                    {
                        MessageBox.Show("L'adresse 3 est réservée et inutilisable.", "Adresse inutilisable");
                        txtPrincAdr.Text = PrincipaleAdr;
                    }
                    else
                    {
                        MessageBox.Show("Adresse modifiée de " + PrincipaleAdr + " en " + Val.ToString(), "Carte Principale"+".", System.Windows.Forms.MessageBoxButtons.OK);
                        PrincipaleAdr = txtPrincAdr.Text;
                    }
                }
            }
            catch (Exception)
            {
                txtPrincAdr.Text = PrincipaleAdr;
                MessageBox.Show("L'adresse doit être une valeur entière entre " + UInt32.MinValue.ToString() + " et " + UInt32.MaxValue.ToString()+".", "Valeur incorrecte");
            }
        }

        private void tlstr_StartDriver_Click(object sender, EventArgs e)
        {
            if (DriverMotIsBrake == false)
            {
                SendDataRS(DriverAdr + " 10 1");
                DriverMotIsBrake = false;
            }
            else SendDataRS(DriverAdr + " 11 0");
        }

        private void tlstr_PauseDriver_Click(object sender, EventArgs e)
        {
            SendDataRS(DriverAdr + " 10 0");
        }

        private void tlstr_StopDriver_Click(object sender, EventArgs e)
        {
            SendDataRS(DriverAdr + " 11 1");
            DriverMotIsBrake = true;
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Random Val = new Random();
            UInt16 Valu = (UInt16)Val.Next(2);
            switch (Valu)
            {
                case 0:
                    SoundPlayer simpleSound = new SoundPlayer("../../../Ressources/ChansonLicornes.wav");
                    simpleSound.Play();
                    break;
                case 1:
                    SoundPlayer simpleSound1 = new SoundPlayer("../../../Ressources/NyanCat.wav");
                    simpleSound1.Play();
                    break;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SendDataRS(DriverAdr + " 1", false);
        }

        private void settingsToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            SettingsDriverMot fSettingsDrivMot = new SettingsDriverMot();
            fSettingsDrivMot.Owner = this;
            fSettingsDrivMot.Show();
        }
        private void eraseToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SendDataRS(PrincipaleAdr + " 25 ");
            Thread.Sleep(100);
        }

        private void cartePrincipaleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Les objectifs se réécrivent automatiquement
            string DataToSend;
            // Envoi objectifs, sauvegarde en ram
            int i;
            for (i = 0; i < dataGV_Objectifs.Rows.Count - 1; i++)
            {
                DataToSend = " 21 ";
                for (int j = 0; j < dataGV_Objectifs.Columns.Count; j++)
                {
                    DataToSend += " ";

                    if (dataGV_Objectifs.Rows[i].Cells[j].Value != null)
                        DataToSend += dataGV_Objectifs.Rows[i].Cells[j].Value.ToString();
                }
                SendDataRS(PrincipaleAdr + DataToSend);
                Thread.Sleep(100);
            }
            // Envoi le nombre d'objectifs à traiter
            SendDataRS(PrincipaleAdr + " 20 " + i.ToString());
            Thread.Sleep(100);
        }


    }
}