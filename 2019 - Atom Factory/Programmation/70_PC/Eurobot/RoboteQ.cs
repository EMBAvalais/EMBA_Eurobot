using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Eurobot
{
    public partial class RoboteQ : Form
    {
        public int receive_PID = 2;

        public RoboteQ()
        {
            InitializeComponent();
            receive_PID = 2;
            // Pour accéder aux éléments de form1, il faut mettre leur propriété "Modifiers" à "Public"
            // et utiliser "Form1 Form1 = (Form1)this.Owner;" pour les évènements
        }
        // Lit les valeurs des PIDs
        public void tlStrMnuItm_readAll_Click(object sender, EventArgs e)
        {
            Form1 Form1 = (Form1)this.Owner;
            receive_PID = 1;
            Form1.SendDataRS("2" + " " + "23");//lis les objectifs  

        }

        // Ecrit les valeurs des PIDs à la plaque
        private void tlStrMnuItm_WriteAll_Click(object sender, EventArgs e)
        {
            Form1 Form1 = (Form1)this.Owner;
            try
            {
                Byte Val = Convert.ToByte(txtKp1.Text);
                Val = Convert.ToByte(txtKi1.Text);
                Val = Convert.ToByte(txtKd1.Text);
                // Envoi
                Form1.SendDataRS("2 " + "24 " + txtKp1.Text.ToString() + " " + txtKi1.Text.ToString() + " " + txtKd1.Text.ToString() + " " + txtKp2.Text.ToString() + " " + txtKi2.Text.ToString() + " " + txtKd2.Text.ToString() + " " + txtACC1.Text.ToString() + " " + txtDEC1.Text.ToString() + " " + txtACC2.Text.ToString() + " " + txtDEC2.Text.ToString());
             }
            catch (Exception ui)
            {
                MessageBox.Show(ui.ToString());
            }
        }
        public void Affiche_PID()
        {
            byte i = 0;
            double kp1,ki1,kd1,kp2,ki2,kd2,ac1,dc1,ac2,dc2;
            i = 0;
            kp1 = 0;
            ki1 = 0;
            kd1 = 0;
            kp2 = 0;
            ki2 = 0;
            kd2 = 0;
            ac1 = 0;
            dc1 = 0;
            ac2 = 0;
            dc2 = 0;

            Form1 Form1 = (Form1)this.Owner;
            if (Form1.reiceive_ok == 1)
            {
                // on a dans le tableau 2 0 : .... --> on veut kp = 20, le : sert à séparer les donnée
                while (Form1.Data[i] != 58) // jusqu'au deux point 
                {
                    kp1 *= 10; // *10 car si on a 2 0 :-> on lira le 2 en premier-->chiffre des dizaines 
                    kp1 += (Form1.Data[i] - 0x30);
                    i++;
                }
                i++;
                while (Form1.Data[i] != 58) // ki 1
                {
                    ki1 *= 10;
                    ki1 += (Form1.Data[i] - 0x30);
                    i++;
                }
                i++;
                while (Form1.Data[i] != 58)// kd 1
                {
                    kd1 *= 10;
                    kd1 += (Form1.Data[i] - 0x30);
                    i++;
                }
                i++;
                while (Form1.Data[i] != 58)//kp 2
                {
                    kp2 *= 10;
                    kp2 += (Form1.Data[i] - 0x30);
                    i++;
                }
                i++;
                while (Form1.Data[i] != 58) // ki 2
                {
                    ki2 *= 10;
                    ki2 += (Form1.Data[i] - 0x30);
                    i++;
                }
                i++;
                while (Form1.Data[i] != 58)// kd 2
                {
                    kd2 *= 10;
                    kd2 += (Form1.Data[i] - 0x30);
                    i++;
                }
                i++;
                while (Form1.Data[i] != 58) // ACC 1
                {
                    ac1 *= 10;
                    ac1 += (Form1.Data[i] - 0x30);
                    i++;
                }
                i++;
                while (Form1.Data[i] != 58) // DEC 1
                {
                    dc1 *= 10;
                    dc1 += (Form1.Data[i] - 0x30);
                    i++;
                }
                i++;
                while (Form1.Data[i] != 58) // ACC 2
                {
                    ac2 *= 10;
                    ac2 += (Form1.Data[i] - 0x30);
                    i++;
                }
                i++;
                while (Form1.Data[i] != 13) //DEC 2
                {
                    dc2 *= 10;
                    dc2+= (Form1.Data[i] - 0x30);
                    i++;
                }

                //affichage
                labelkp1.Invoke(new MethodInvoker(delegate
                {
                    labelkp1.Text = "kp : " + (kp1 / 10).ToString();
                }));
                labelki1.Invoke(new MethodInvoker(delegate
                {
                    labelki1.Text = "ki : " +(ki1 / 10).ToString();
                }));
                labelkd1.Invoke(new MethodInvoker(delegate
                {
                    labelkd1.Text = "kd :  " +(kd1 / 10).ToString();
                }));
                labelkp2.Invoke(new MethodInvoker(delegate
                {
                    labelkp2.Text = "kp : " +(kp2 / 10).ToString();
                }));
                labelki2.Invoke(new MethodInvoker(delegate
                {
                    labelki2.Text = "ki : " +(ki2 / 10).ToString();
                }));
                labelkd2.Invoke(new MethodInvoker(delegate
                {
                    labelkd2.Text = "kd : " + (kd2 / 10).ToString();
                }));
                lblACC1.Invoke(new MethodInvoker(delegate
                {
                    lblACC1.Text = "Ac : "+(ac1 / 10).ToString();
                }));
                lblDCC1.Invoke(new MethodInvoker(delegate
                {
                    lblDCC1.Text = "Dc : "+(dc1 / 10).ToString();
                }));
                lblACC2.Invoke(new MethodInvoker(delegate
                {
                    lblACC2.Text = "Ac : " +(ac2 / 10).ToString();
                }));
                lblDCC2.Invoke(new MethodInvoker(delegate
                {
                    lblDCC2.Text = "Dc : "+(dc2 / 10).ToString();
                }));

                Form1.reiceive_ok = 0;
                receive_PID = 0;
                i = 0;
                
                while (i < 254) // reset le tableau
                {
                    Form1.Data[i] = 0;
                    i++;
                }
                i = 0;
            }

            // Relance une fenêtre vierge
            /* private void tlStrMnuItm_Clear_Click(object sender, EventArgs e)
             {
                 // Relance une nouvelle fenêtre
                 RoboteQ fRoboteQ = new RoboteQ();
                 fRoboteQ.Show();
                 this.Close();
             }*/

        }

   }
}
