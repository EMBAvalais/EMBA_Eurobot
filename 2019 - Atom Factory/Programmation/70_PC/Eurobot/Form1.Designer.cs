namespace Eurobot
{
    partial class Form1
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.srlPort_RS = new System.IO.Ports.SerialPort(this.components);
            this.tlStrCon_Main = new System.Windows.Forms.ToolStripContainer();
            this.staStr_Status = new System.Windows.Forms.StatusStrip();
            this.tlStrStaLbl_State = new System.Windows.Forms.ToolStripStatusLabel();
            this.tlStrStaLbl_Spring = new System.Windows.Forms.ToolStripStatusLabel();
            this.staStrLbl_Position = new System.Windows.Forms.ToolStripStatusLabel();
            this.spCon_Horizontal = new System.Windows.Forms.SplitContainer();
            this.spCon_Vertical = new System.Windows.Forms.SplitContainer();
            this.tlStrCon_Com = new System.Windows.Forms.ToolStripContainer();
            this.spCon_Communication = new System.Windows.Forms.SplitContainer();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txt_PosX = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.txt_PosY = new System.Windows.Forms.TextBox();
            this.btn_InitPosition = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.txtPrincAdr = new System.Windows.Forms.TextBox();
            this.txt_Angle = new System.Windows.Forms.TextBox();
            this.spCon_Communication1 = new System.Windows.Forms.SplitContainer();
            this.cbBoardToSend = new System.Windows.Forms.ComboBox();
            this.rTxt_Sent = new System.Windows.Forms.RichTextBox();
            this.txt_Send = new System.Windows.Forms.TextBox();
            this.rTxt_Received = new System.Windows.Forms.RichTextBox();
            this.btn_Clear = new System.Windows.Forms.Button();
            this.buffPan_Carte = new Eurobot.BufferedPanel();
            this.tabCtr_Main = new System.Windows.Forms.TabControl();
            this.tabPg_Objectifs = new System.Windows.Forms.TabPage();
            this.dataGV_Objectifs = new System.Windows.Forms.DataGridView();
            this.tabPg_Zones = new System.Windows.Forms.TabPage();
            this.dataGV_Zones = new System.Windows.Forms.DataGridView();
            this.col_ZoneNumero = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_ZoneX1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_ZoneY1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_ZoneX2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_ZoneY2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_ZoneX3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_ZoneY3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_ZoneX4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_ZoneY4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.imgLst_Tab = new System.Windows.Forms.ImageList(this.components);
            this.mnu_Main = new System.Windows.Forms.MenuStrip();
            this.tlStrMnuItm_EEPROM = new System.Windows.Forms.ToolStripMenuItem();
            this.eraseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_Objectifs = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_ObjectifsSend = new System.Windows.Forms.ToolStripMenuItem();
            this.cartePrincipaleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lireToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrSep_Objectifs1 = new System.Windows.Forms.ToolStripSeparator();
            this.tlStrMnuItm_ObjectifsNew = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_ObjectifsOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_ObjectifsSave = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_ObjectifsSaveAs = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrSep_Objectifs2 = new System.Windows.Forms.ToolStripSeparator();
            this.tlStrMnuItm_SymmetryX = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_SymmetryY = new System.Windows.Forms.ToolStripMenuItem();
            this.roboteQToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_RS232 = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_PortState = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_OptionsRS = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_COM1 = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_COM2 = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_COM3 = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_COM4 = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_COM5 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.tlStrMnuItm_COMPerso = new System.Windows.Forms.ToolStripTextBox();
            this.tlStrMnuItm_COMx = new System.Windows.Forms.ToolStripMenuItem();
            this.settingsToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_Zones = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_ZonesSend = new System.Windows.Forms.ToolStripMenuItem();
            this.lireToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrSep_Zones = new System.Windows.Forms.ToolStripSeparator();
            this.tlStrMnuItm_ZonesNew = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_ZonesOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_ZonesSave = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_ZonesSaveAs = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.tmr_Update = new System.Windows.Forms.Timer(this.components);
            this.Objectifs = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_ObjectifNumero = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_ObjectifPositionX = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_ObjectifPositionY = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_TypeObj = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_AvAr = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_CoteTourn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_VitMax = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_ObjectifToDo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col_PrecAngle = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.a = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.tlStrCon_Main.BottomToolStripPanel.SuspendLayout();
            this.tlStrCon_Main.ContentPanel.SuspendLayout();
            this.tlStrCon_Main.TopToolStripPanel.SuspendLayout();
            this.tlStrCon_Main.SuspendLayout();
            this.staStr_Status.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.spCon_Horizontal)).BeginInit();
            this.spCon_Horizontal.Panel1.SuspendLayout();
            this.spCon_Horizontal.Panel2.SuspendLayout();
            this.spCon_Horizontal.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.spCon_Vertical)).BeginInit();
            this.spCon_Vertical.Panel1.SuspendLayout();
            this.spCon_Vertical.Panel2.SuspendLayout();
            this.spCon_Vertical.SuspendLayout();
            this.tlStrCon_Com.ContentPanel.SuspendLayout();
            this.tlStrCon_Com.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.spCon_Communication)).BeginInit();
            this.spCon_Communication.Panel1.SuspendLayout();
            this.spCon_Communication.Panel2.SuspendLayout();
            this.spCon_Communication.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.spCon_Communication1)).BeginInit();
            this.spCon_Communication1.Panel1.SuspendLayout();
            this.spCon_Communication1.Panel2.SuspendLayout();
            this.spCon_Communication1.SuspendLayout();
            this.tabCtr_Main.SuspendLayout();
            this.tabPg_Objectifs.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGV_Objectifs)).BeginInit();
            this.tabPg_Zones.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGV_Zones)).BeginInit();
            this.mnu_Main.SuspendLayout();
            this.SuspendLayout();
            // 
            // srlPort_RS
            // 
            this.srlPort_RS.BaudRate = 115200;
            this.srlPort_RS.RtsEnable = true;
            this.srlPort_RS.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // tlStrCon_Main
            // 
            // 
            // tlStrCon_Main.BottomToolStripPanel
            // 
            this.tlStrCon_Main.BottomToolStripPanel.BackColor = System.Drawing.Color.Transparent;
            this.tlStrCon_Main.BottomToolStripPanel.Controls.Add(this.staStr_Status);
            // 
            // tlStrCon_Main.ContentPanel
            // 
            this.tlStrCon_Main.ContentPanel.BackColor = System.Drawing.Color.Silver;
            this.tlStrCon_Main.ContentPanel.Controls.Add(this.spCon_Horizontal);
            this.tlStrCon_Main.ContentPanel.Size = new System.Drawing.Size(1002, 520);
            this.tlStrCon_Main.Dock = System.Windows.Forms.DockStyle.Fill;
            // 
            // tlStrCon_Main.LeftToolStripPanel
            // 
            this.tlStrCon_Main.LeftToolStripPanel.BackColor = System.Drawing.Color.Transparent;
            this.tlStrCon_Main.LeftToolStripPanelVisible = false;
            this.tlStrCon_Main.Location = new System.Drawing.Point(0, 0);
            this.tlStrCon_Main.Margin = new System.Windows.Forms.Padding(0);
            this.tlStrCon_Main.Name = "tlStrCon_Main";
            // 
            // tlStrCon_Main.RightToolStripPanel
            // 
            this.tlStrCon_Main.RightToolStripPanel.BackColor = System.Drawing.Color.Transparent;
            this.tlStrCon_Main.RightToolStripPanelVisible = false;
            this.tlStrCon_Main.Size = new System.Drawing.Size(1002, 566);
            this.tlStrCon_Main.TabIndex = 1;
            this.tlStrCon_Main.Text = "toolStripContainer1";
            // 
            // tlStrCon_Main.TopToolStripPanel
            // 
            this.tlStrCon_Main.TopToolStripPanel.BackColor = System.Drawing.Color.Transparent;
            this.tlStrCon_Main.TopToolStripPanel.Controls.Add(this.mnu_Main);
            // 
            // staStr_Status
            // 
            this.staStr_Status.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(104)))), ((int)(((byte)(33)))), ((int)(((byte)(122)))));
            this.staStr_Status.Dock = System.Windows.Forms.DockStyle.None;
            this.staStr_Status.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tlStrStaLbl_State,
            this.tlStrStaLbl_Spring,
            this.staStrLbl_Position});
            this.staStr_Status.Location = new System.Drawing.Point(0, 0);
            this.staStr_Status.Name = "staStr_Status";
            this.staStr_Status.Size = new System.Drawing.Size(1002, 22);
            this.staStr_Status.TabIndex = 3;
            this.staStr_Status.Text = "statusStrip1";
            // 
            // tlStrStaLbl_State
            // 
            this.tlStrStaLbl_State.BackColor = System.Drawing.Color.Transparent;
            this.tlStrStaLbl_State.ForeColor = System.Drawing.Color.White;
            this.tlStrStaLbl_State.Name = "tlStrStaLbl_State";
            this.tlStrStaLbl_State.Size = new System.Drawing.Size(198, 17);
            this.tlStrStaLbl_State.Text = "État de la connexion : [COM1] fermé";
            // 
            // tlStrStaLbl_Spring
            // 
            this.tlStrStaLbl_Spring.Name = "tlStrStaLbl_Spring";
            this.tlStrStaLbl_Spring.Size = new System.Drawing.Size(789, 17);
            this.tlStrStaLbl_Spring.Spring = true;
            // 
            // staStrLbl_Position
            // 
            this.staStrLbl_Position.ForeColor = System.Drawing.Color.White;
            this.staStrLbl_Position.Name = "staStrLbl_Position";
            this.staStrLbl_Position.Size = new System.Drawing.Size(59, 17);
            this.staStrLbl_Position.Text = "Position : ";
            this.staStrLbl_Position.Visible = false;
            // 
            // spCon_Horizontal
            // 
            this.spCon_Horizontal.Dock = System.Windows.Forms.DockStyle.Fill;
            this.spCon_Horizontal.Location = new System.Drawing.Point(0, 0);
            this.spCon_Horizontal.Margin = new System.Windows.Forms.Padding(2);
            this.spCon_Horizontal.Name = "spCon_Horizontal";
            this.spCon_Horizontal.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // spCon_Horizontal.Panel1
            // 
            this.spCon_Horizontal.Panel1.Controls.Add(this.spCon_Vertical);
            // 
            // spCon_Horizontal.Panel2
            // 
            this.spCon_Horizontal.Panel2.Controls.Add(this.tabCtr_Main);
            this.spCon_Horizontal.Size = new System.Drawing.Size(1002, 520);
            this.spCon_Horizontal.SplitterDistance = 386;
            this.spCon_Horizontal.SplitterWidth = 3;
            this.spCon_Horizontal.TabIndex = 2;
            // 
            // spCon_Vertical
            // 
            this.spCon_Vertical.Dock = System.Windows.Forms.DockStyle.Fill;
            this.spCon_Vertical.Location = new System.Drawing.Point(0, 0);
            this.spCon_Vertical.Margin = new System.Windows.Forms.Padding(2);
            this.spCon_Vertical.Name = "spCon_Vertical";
            // 
            // spCon_Vertical.Panel1
            // 
            this.spCon_Vertical.Panel1.Controls.Add(this.tlStrCon_Com);
            // 
            // spCon_Vertical.Panel2
            // 
            this.spCon_Vertical.Panel2.Controls.Add(this.buffPan_Carte);
            this.spCon_Vertical.Size = new System.Drawing.Size(1002, 386);
            this.spCon_Vertical.SplitterDistance = 405;
            this.spCon_Vertical.SplitterWidth = 3;
            this.spCon_Vertical.TabIndex = 0;
            // 
            // tlStrCon_Com
            // 
            // 
            // tlStrCon_Com.BottomToolStripPanel
            // 
            this.tlStrCon_Com.BottomToolStripPanel.BackColor = System.Drawing.Color.Transparent;
            // 
            // tlStrCon_Com.ContentPanel
            // 
            this.tlStrCon_Com.ContentPanel.Controls.Add(this.spCon_Communication);
            this.tlStrCon_Com.ContentPanel.Margin = new System.Windows.Forms.Padding(2);
            this.tlStrCon_Com.ContentPanel.Size = new System.Drawing.Size(405, 361);
            this.tlStrCon_Com.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tlStrCon_Com.Location = new System.Drawing.Point(0, 0);
            this.tlStrCon_Com.Margin = new System.Windows.Forms.Padding(2);
            this.tlStrCon_Com.Name = "tlStrCon_Com";
            this.tlStrCon_Com.Size = new System.Drawing.Size(405, 386);
            this.tlStrCon_Com.TabIndex = 22;
            this.tlStrCon_Com.Text = "toolStripContainer1";
            // 
            // spCon_Communication
            // 
            this.spCon_Communication.BackColor = System.Drawing.Color.Transparent;
            this.spCon_Communication.Dock = System.Windows.Forms.DockStyle.Fill;
            this.spCon_Communication.IsSplitterFixed = true;
            this.spCon_Communication.Location = new System.Drawing.Point(0, 0);
            this.spCon_Communication.Name = "spCon_Communication";
            this.spCon_Communication.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // spCon_Communication.Panel1
            // 
            this.spCon_Communication.Panel1.BackColor = System.Drawing.Color.Transparent;
            this.spCon_Communication.Panel1.Controls.Add(this.groupBox1);
            // 
            // spCon_Communication.Panel2
            // 
            this.spCon_Communication.Panel2.Controls.Add(this.spCon_Communication1);
            this.spCon_Communication.Size = new System.Drawing.Size(405, 361);
            this.spCon_Communication.SplitterDistance = 200;
            this.spCon_Communication.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Gainsboro;
            this.groupBox1.Controls.Add(this.txt_PosX);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.txt_PosY);
            this.groupBox1.Controls.Add(this.btn_InitPosition);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.txtPrincAdr);
            this.groupBox1.Controls.Add(this.txt_Angle);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(0);
            this.groupBox1.Size = new System.Drawing.Size(405, 266);
            this.groupBox1.TabIndex = 58;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Carte Principale";
            // 
            // txt_PosX
            // 
            this.txt_PosX.Location = new System.Drawing.Point(29, 79);
            this.txt_PosX.Name = "txt_PosX";
            this.txt_PosX.Size = new System.Drawing.Size(75, 20);
            this.txt_PosX.TabIndex = 9;
            this.txt_PosX.Text = "50";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(54, 42);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(185, 16);
            this.label1.TabIndex = 53;
            this.label1.Text = "X                  Y                Phi";
            // 
            // txt_PosY
            // 
            this.txt_PosY.Location = new System.Drawing.Point(110, 79);
            this.txt_PosY.Name = "txt_PosY";
            this.txt_PosY.Size = new System.Drawing.Size(75, 20);
            this.txt_PosY.TabIndex = 10;
            this.txt_PosY.Text = "1800";
            // 
            // btn_InitPosition
            // 
            this.btn_InitPosition.Location = new System.Drawing.Point(344, 68);
            this.btn_InitPosition.Name = "btn_InitPosition";
            this.btn_InitPosition.Size = new System.Drawing.Size(75, 40);
            this.btn_InitPosition.TabIndex = 36;
            this.btn_InitPosition.Text = "Init Position";
            this.btn_InitPosition.UseVisualStyleBackColor = true;
            this.btn_InitPosition.Click += new System.EventHandler(this.btn_InitPosition_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(276, 41);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 13);
            this.label2.TabIndex = 59;
            this.label2.Text = "Adresse :";
            // 
            // txtPrincAdr
            // 
            this.txtPrincAdr.Location = new System.Drawing.Point(344, 41);
            this.txtPrincAdr.Name = "txtPrincAdr";
            this.txtPrincAdr.Size = new System.Drawing.Size(66, 20);
            this.txtPrincAdr.TabIndex = 58;
            this.txtPrincAdr.Text = "2";
            this.txtPrincAdr.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtPrincAdr.Leave += new System.EventHandler(this.txtPrincAdr_Leave);
            // 
            // txt_Angle
            // 
            this.txt_Angle.Location = new System.Drawing.Point(191, 79);
            this.txt_Angle.Name = "txt_Angle";
            this.txt_Angle.Size = new System.Drawing.Size(75, 20);
            this.txt_Angle.TabIndex = 11;
            this.txt_Angle.Text = "0";
            // 
            // spCon_Communication1
            // 
            this.spCon_Communication1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.spCon_Communication1.IsSplitterFixed = true;
            this.spCon_Communication1.Location = new System.Drawing.Point(0, 0);
            this.spCon_Communication1.Name = "spCon_Communication1";
            // 
            // spCon_Communication1.Panel1
            // 
            this.spCon_Communication1.Panel1.Controls.Add(this.cbBoardToSend);
            this.spCon_Communication1.Panel1.Controls.Add(this.rTxt_Sent);
            this.spCon_Communication1.Panel1.Controls.Add(this.txt_Send);
            // 
            // spCon_Communication1.Panel2
            // 
            this.spCon_Communication1.Panel2.Controls.Add(this.rTxt_Received);
            this.spCon_Communication1.Panel2.Controls.Add(this.btn_Clear);
            this.spCon_Communication1.Size = new System.Drawing.Size(405, 157);
            this.spCon_Communication1.SplitterDistance = 200;
            this.spCon_Communication1.TabIndex = 0;
            // 
            // cbBoardToSend
            // 
            this.cbBoardToSend.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.cbBoardToSend.FormattingEnabled = true;
            this.cbBoardToSend.Items.AddRange(new object[] {
            "Carte Principale",
            "Driver Moteur"});
            this.cbBoardToSend.Location = new System.Drawing.Point(0, 109);
            this.cbBoardToSend.Name = "cbBoardToSend";
            this.cbBoardToSend.Size = new System.Drawing.Size(200, 21);
            this.cbBoardToSend.TabIndex = 59;
            this.cbBoardToSend.Text = "Carte Principale";
            // 
            // rTxt_Sent
            // 
            this.rTxt_Sent.Dock = System.Windows.Forms.DockStyle.Fill;
            this.rTxt_Sent.Font = new System.Drawing.Font("Lucida Sans Unicode", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rTxt_Sent.Location = new System.Drawing.Point(0, 0);
            this.rTxt_Sent.Name = "rTxt_Sent";
            this.rTxt_Sent.Size = new System.Drawing.Size(200, 130);
            this.rTxt_Sent.TabIndex = 0;
            this.rTxt_Sent.Text = "";
            this.rTxt_Sent.Enter += new System.EventHandler(this.rTxt_Sent_Enter);
            // 
            // txt_Send
            // 
            this.txt_Send.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.txt_Send.Font = new System.Drawing.Font("Lucida Sans Unicode", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txt_Send.Location = new System.Drawing.Point(0, 130);
            this.txt_Send.Name = "txt_Send";
            this.txt_Send.Size = new System.Drawing.Size(200, 27);
            this.txt_Send.TabIndex = 2;
            this.txt_Send.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txt_Send_KeyDown);
            // 
            // rTxt_Received
            // 
            this.rTxt_Received.Dock = System.Windows.Forms.DockStyle.Fill;
            this.rTxt_Received.Font = new System.Drawing.Font("Lucida Sans Unicode", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rTxt_Received.Location = new System.Drawing.Point(0, 0);
            this.rTxt_Received.Name = "rTxt_Received";
            this.rTxt_Received.Size = new System.Drawing.Size(201, 136);
            this.rTxt_Received.TabIndex = 0;
            this.rTxt_Received.Text = "";
            // 
            // btn_Clear
            // 
            this.btn_Clear.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.btn_Clear.Location = new System.Drawing.Point(0, 136);
            this.btn_Clear.Name = "btn_Clear";
            this.btn_Clear.Size = new System.Drawing.Size(201, 21);
            this.btn_Clear.TabIndex = 4;
            this.btn_Clear.Text = "Effacer";
            this.btn_Clear.UseVisualStyleBackColor = true;
            this.btn_Clear.Click += new System.EventHandler(this.btn_Clear_Click);
            // 
            // buffPan_Carte
            // 
            this.buffPan_Carte.BackColor = System.Drawing.Color.Gainsboro;
            this.buffPan_Carte.Dock = System.Windows.Forms.DockStyle.Fill;
            this.buffPan_Carte.Location = new System.Drawing.Point(0, 0);
            this.buffPan_Carte.Name = "buffPan_Carte";
            this.buffPan_Carte.Size = new System.Drawing.Size(594, 386);
            this.buffPan_Carte.TabIndex = 0;
            this.buffPan_Carte.Paint += new System.Windows.Forms.PaintEventHandler(this.bufferedPanel1_Paint);
            this.buffPan_Carte.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bufferedPanel1_MouseDown);
            this.buffPan_Carte.MouseMove += new System.Windows.Forms.MouseEventHandler(this.bufferedPanel1_MouseMove);
            this.buffPan_Carte.MouseUp += new System.Windows.Forms.MouseEventHandler(this.bufferedPanel1_MouseUp);
            // 
            // tabCtr_Main
            // 
            this.tabCtr_Main.Controls.Add(this.tabPg_Objectifs);
            this.tabCtr_Main.Controls.Add(this.tabPg_Zones);
            this.tabCtr_Main.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabCtr_Main.ImageList = this.imgLst_Tab;
            this.tabCtr_Main.Location = new System.Drawing.Point(0, 0);
            this.tabCtr_Main.Name = "tabCtr_Main";
            this.tabCtr_Main.SelectedIndex = 0;
            this.tabCtr_Main.Size = new System.Drawing.Size(1002, 131);
            this.tabCtr_Main.TabIndex = 0;
            // 
            // tabPg_Objectifs
            // 
            this.tabPg_Objectifs.Controls.Add(this.dataGV_Objectifs);
            this.tabPg_Objectifs.ImageKey = "objectif.png";
            this.tabPg_Objectifs.Location = new System.Drawing.Point(4, 23);
            this.tabPg_Objectifs.Name = "tabPg_Objectifs";
            this.tabPg_Objectifs.Padding = new System.Windows.Forms.Padding(3);
            this.tabPg_Objectifs.Size = new System.Drawing.Size(994, 104);
            this.tabPg_Objectifs.TabIndex = 1;
            this.tabPg_Objectifs.Text = "Objectifs";
            this.tabPg_Objectifs.UseVisualStyleBackColor = true;
            // 
            // dataGV_Objectifs
            // 
            this.dataGV_Objectifs.AllowDrop = true;
            this.dataGV_Objectifs.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGV_Objectifs.BackgroundColor = System.Drawing.SystemColors.ControlLight;
            this.dataGV_Objectifs.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGV_Objectifs.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Objectifs,
            this.col_ObjectifNumero,
            this.col_ObjectifPositionX,
            this.col_ObjectifPositionY,
            this.col_TypeObj,
            this.col_AvAr,
            this.col_CoteTourn,
            this.col_VitMax,
            this.col_ObjectifToDo,
            this.col_PrecAngle,
            this.Column1,
            this.Column2,
            this.Column3,
            this.a});
            this.dataGV_Objectifs.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGV_Objectifs.Location = new System.Drawing.Point(3, 3);
            this.dataGV_Objectifs.Name = "dataGV_Objectifs";
            this.dataGV_Objectifs.Size = new System.Drawing.Size(988, 98);
            this.dataGV_Objectifs.TabIndex = 1;
            // 
            // tabPg_Zones
            // 
            this.tabPg_Zones.Controls.Add(this.dataGV_Zones);
            this.tabPg_Zones.ImageKey = "zone.png";
            this.tabPg_Zones.Location = new System.Drawing.Point(4, 23);
            this.tabPg_Zones.Name = "tabPg_Zones";
            this.tabPg_Zones.Padding = new System.Windows.Forms.Padding(3);
            this.tabPg_Zones.Size = new System.Drawing.Size(780, 53);
            this.tabPg_Zones.TabIndex = 4;
            this.tabPg_Zones.Text = "Zones interdites";
            this.tabPg_Zones.UseVisualStyleBackColor = true;
            // 
            // dataGV_Zones
            // 
            this.dataGV_Zones.AllowDrop = true;
            this.dataGV_Zones.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGV_Zones.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGV_Zones.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.col_ZoneNumero,
            this.col_ZoneX1,
            this.col_ZoneY1,
            this.col_ZoneX2,
            this.col_ZoneY2,
            this.col_ZoneX3,
            this.col_ZoneY3,
            this.col_ZoneX4,
            this.col_ZoneY4});
            this.dataGV_Zones.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGV_Zones.Location = new System.Drawing.Point(3, 3);
            this.dataGV_Zones.Name = "dataGV_Zones";
            this.dataGV_Zones.Size = new System.Drawing.Size(774, 47);
            this.dataGV_Zones.TabIndex = 0;
            // 
            // col_ZoneNumero
            // 
            this.col_ZoneNumero.HeaderText = "Numéro";
            this.col_ZoneNumero.Name = "col_ZoneNumero";
            // 
            // col_ZoneX1
            // 
            this.col_ZoneX1.HeaderText = "X1";
            this.col_ZoneX1.Name = "col_ZoneX1";
            // 
            // col_ZoneY1
            // 
            this.col_ZoneY1.HeaderText = "Y1";
            this.col_ZoneY1.Name = "col_ZoneY1";
            // 
            // col_ZoneX2
            // 
            this.col_ZoneX2.HeaderText = "X2";
            this.col_ZoneX2.Name = "col_ZoneX2";
            // 
            // col_ZoneY2
            // 
            this.col_ZoneY2.HeaderText = "Y2";
            this.col_ZoneY2.Name = "col_ZoneY2";
            // 
            // col_ZoneX3
            // 
            this.col_ZoneX3.HeaderText = "X3";
            this.col_ZoneX3.Name = "col_ZoneX3";
            // 
            // col_ZoneY3
            // 
            this.col_ZoneY3.HeaderText = "Y3";
            this.col_ZoneY3.Name = "col_ZoneY3";
            // 
            // col_ZoneX4
            // 
            this.col_ZoneX4.HeaderText = "X4";
            this.col_ZoneX4.Name = "col_ZoneX4";
            // 
            // col_ZoneY4
            // 
            this.col_ZoneY4.HeaderText = "Y4";
            this.col_ZoneY4.Name = "col_ZoneY4";
            // 
            // imgLst_Tab
            // 
            this.imgLst_Tab.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imgLst_Tab.ImageStream")));
            this.imgLst_Tab.TransparentColor = System.Drawing.Color.White;
            this.imgLst_Tab.Images.SetKeyName(0, "objectif.png");
            this.imgLst_Tab.Images.SetKeyName(1, "zone.png");
            // 
            // mnu_Main
            // 
            this.mnu_Main.AutoSize = false;
            this.mnu_Main.BackColor = System.Drawing.Color.SkyBlue;
            this.mnu_Main.Dock = System.Windows.Forms.DockStyle.None;
            this.mnu_Main.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tlStrMnuItm_EEPROM,
            this.tlStrMnuItm_Objectifs,
            this.roboteQToolStripMenuItem,
            this.tlStrMnuItm_RS232,
            this.tlStrMnuItm_Zones,
            this.toolStripMenuItem1});
            this.mnu_Main.Location = new System.Drawing.Point(0, 0);
            this.mnu_Main.Name = "mnu_Main";
            this.mnu_Main.Size = new System.Drawing.Size(1002, 24);
            this.mnu_Main.TabIndex = 0;
            this.mnu_Main.Text = "menuStrip1";
            // 
            // tlStrMnuItm_EEPROM
            // 
            this.tlStrMnuItm_EEPROM.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.eraseToolStripMenuItem});
            this.tlStrMnuItm_EEPROM.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_EEPROM.Image")));
            this.tlStrMnuItm_EEPROM.Name = "tlStrMnuItm_EEPROM";
            this.tlStrMnuItm_EEPROM.Size = new System.Drawing.Size(81, 20);
            this.tlStrMnuItm_EEPROM.Text = "EEPROM";
            // 
            // eraseToolStripMenuItem
            // 
            this.eraseToolStripMenuItem.Name = "eraseToolStripMenuItem";
            this.eraseToolStripMenuItem.Size = new System.Drawing.Size(145, 22);
            this.eraseToolStripMenuItem.Text = "erase eeprom";
            this.eraseToolStripMenuItem.Click += new System.EventHandler(this.eraseToolStripMenuItem_Click);
            // 
            // tlStrMnuItm_Objectifs
            // 
            this.tlStrMnuItm_Objectifs.BackColor = System.Drawing.Color.Transparent;
            this.tlStrMnuItm_Objectifs.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tlStrMnuItm_ObjectifsSend,
            this.lireToolStripMenuItem,
            this.tlStrSep_Objectifs1,
            this.tlStrMnuItm_ObjectifsNew,
            this.tlStrMnuItm_ObjectifsOpen,
            this.tlStrMnuItm_ObjectifsSave,
            this.tlStrMnuItm_ObjectifsSaveAs,
            this.tlStrSep_Objectifs2,
            this.tlStrMnuItm_SymmetryX,
            this.tlStrMnuItm_SymmetryY});
            this.tlStrMnuItm_Objectifs.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tlStrMnuItm_Objectifs.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_Objectifs.Image")));
            this.tlStrMnuItm_Objectifs.Name = "tlStrMnuItm_Objectifs";
            this.tlStrMnuItm_Objectifs.Size = new System.Drawing.Size(82, 20);
            this.tlStrMnuItm_Objectifs.Text = "Objectifs";
            // 
            // tlStrMnuItm_ObjectifsSend
            // 
            this.tlStrMnuItm_ObjectifsSend.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cartePrincipaleToolStripMenuItem});
            this.tlStrMnuItm_ObjectifsSend.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.tlStrMnuItm_ObjectifsSend.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_ObjectifsSend.Image")));
            this.tlStrMnuItm_ObjectifsSend.Name = "tlStrMnuItm_ObjectifsSend";
            this.tlStrMnuItm_ObjectifsSend.Size = new System.Drawing.Size(166, 22);
            this.tlStrMnuItm_ObjectifsSend.Text = "Envoyer";
            // 
            // cartePrincipaleToolStripMenuItem
            // 
            this.cartePrincipaleToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("cartePrincipaleToolStripMenuItem.Image")));
            this.cartePrincipaleToolStripMenuItem.Name = "cartePrincipaleToolStripMenuItem";
            this.cartePrincipaleToolStripMenuItem.Size = new System.Drawing.Size(157, 22);
            this.cartePrincipaleToolStripMenuItem.Text = "Carte Principale";
            this.cartePrincipaleToolStripMenuItem.Click += new System.EventHandler(this.cartePrincipaleToolStripMenuItem_Click);
            // 
            // lireToolStripMenuItem
            // 
            this.lireToolStripMenuItem.Enabled = false;
            this.lireToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("lireToolStripMenuItem.Image")));
            this.lireToolStripMenuItem.Name = "lireToolStripMenuItem";
            this.lireToolStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.lireToolStripMenuItem.Text = "Lire";
            // 
            // tlStrSep_Objectifs1
            // 
            this.tlStrSep_Objectifs1.Name = "tlStrSep_Objectifs1";
            this.tlStrSep_Objectifs1.Size = new System.Drawing.Size(163, 6);
            // 
            // tlStrMnuItm_ObjectifsNew
            // 
            this.tlStrMnuItm_ObjectifsNew.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.tlStrMnuItm_ObjectifsNew.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_ObjectifsNew.Image")));
            this.tlStrMnuItm_ObjectifsNew.Name = "tlStrMnuItm_ObjectifsNew";
            this.tlStrMnuItm_ObjectifsNew.Size = new System.Drawing.Size(166, 22);
            this.tlStrMnuItm_ObjectifsNew.Text = "Nouveau";
            this.tlStrMnuItm_ObjectifsNew.Click += new System.EventHandler(this.tlStrMnuItm_ObjectifsNew_Click);
            // 
            // tlStrMnuItm_ObjectifsOpen
            // 
            this.tlStrMnuItm_ObjectifsOpen.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.tlStrMnuItm_ObjectifsOpen.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_ObjectifsOpen.Image")));
            this.tlStrMnuItm_ObjectifsOpen.Name = "tlStrMnuItm_ObjectifsOpen";
            this.tlStrMnuItm_ObjectifsOpen.Size = new System.Drawing.Size(166, 22);
            this.tlStrMnuItm_ObjectifsOpen.Text = "Ouvrir";
            // 
            // tlStrMnuItm_ObjectifsSave
            // 
            this.tlStrMnuItm_ObjectifsSave.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.tlStrMnuItm_ObjectifsSave.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_ObjectifsSave.Image")));
            this.tlStrMnuItm_ObjectifsSave.Name = "tlStrMnuItm_ObjectifsSave";
            this.tlStrMnuItm_ObjectifsSave.Size = new System.Drawing.Size(166, 22);
            this.tlStrMnuItm_ObjectifsSave.Text = "Enregistrer";
            // 
            // tlStrMnuItm_ObjectifsSaveAs
            // 
            this.tlStrMnuItm_ObjectifsSaveAs.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.tlStrMnuItm_ObjectifsSaveAs.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_ObjectifsSaveAs.Image")));
            this.tlStrMnuItm_ObjectifsSaveAs.Name = "tlStrMnuItm_ObjectifsSaveAs";
            this.tlStrMnuItm_ObjectifsSaveAs.Size = new System.Drawing.Size(166, 22);
            this.tlStrMnuItm_ObjectifsSaveAs.Text = "Enregistrer sous...";
            // 
            // tlStrSep_Objectifs2
            // 
            this.tlStrSep_Objectifs2.Name = "tlStrSep_Objectifs2";
            this.tlStrSep_Objectifs2.Size = new System.Drawing.Size(163, 6);
            // 
            // tlStrMnuItm_SymmetryX
            // 
            this.tlStrMnuItm_SymmetryX.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_SymmetryX.Image")));
            this.tlStrMnuItm_SymmetryX.Name = "tlStrMnuItm_SymmetryX";
            this.tlStrMnuItm_SymmetryX.Size = new System.Drawing.Size(166, 22);
            this.tlStrMnuItm_SymmetryX.Text = "Symétrie en X";
            this.tlStrMnuItm_SymmetryX.Click += new System.EventHandler(this.tlStrMnuItm_SymmetryX_Click);
            // 
            // tlStrMnuItm_SymmetryY
            // 
            this.tlStrMnuItm_SymmetryY.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_SymmetryY.Image")));
            this.tlStrMnuItm_SymmetryY.Name = "tlStrMnuItm_SymmetryY";
            this.tlStrMnuItm_SymmetryY.Size = new System.Drawing.Size(166, 22);
            this.tlStrMnuItm_SymmetryY.Text = "Symétrie en Y";
            this.tlStrMnuItm_SymmetryY.Click += new System.EventHandler(this.tlStrMnuItm_SymmetryY_Click);
            // 
            // roboteQToolStripMenuItem
            // 
            this.roboteQToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("roboteQToolStripMenuItem.Image")));
            this.roboteQToolStripMenuItem.Name = "roboteQToolStripMenuItem";
            this.roboteQToolStripMenuItem.Size = new System.Drawing.Size(82, 20);
            this.roboteQToolStripMenuItem.Text = "RoboteQ";
            this.roboteQToolStripMenuItem.Click += new System.EventHandler(this.roboteQToolStripMenuItem_Click);
            // 
            // tlStrMnuItm_RS232
            // 
            this.tlStrMnuItm_RS232.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tlStrMnuItm_PortState,
            this.tlStrMnuItm_OptionsRS,
            this.settingsToolStripMenuItem2});
            this.tlStrMnuItm_RS232.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_RS232.Image")));
            this.tlStrMnuItm_RS232.Name = "tlStrMnuItm_RS232";
            this.tlStrMnuItm_RS232.Size = new System.Drawing.Size(71, 20);
            this.tlStrMnuItm_RS232.Text = "RS-232";
            // 
            // tlStrMnuItm_PortState
            // 
            this.tlStrMnuItm_PortState.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_PortState.Image")));
            this.tlStrMnuItm_PortState.Name = "tlStrMnuItm_PortState";
            this.tlStrMnuItm_PortState.Size = new System.Drawing.Size(181, 22);
            this.tlStrMnuItm_PortState.Text = "Ouvrir le port COM1";
            this.tlStrMnuItm_PortState.Click += new System.EventHandler(this.tlStrMnuItm_PortState_Click);
            // 
            // tlStrMnuItm_OptionsRS
            // 
            this.tlStrMnuItm_OptionsRS.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tlStrMnuItm_COM1,
            this.tlStrMnuItm_COM2,
            this.tlStrMnuItm_COM3,
            this.tlStrMnuItm_COM4,
            this.tlStrMnuItm_COM5,
            this.toolStripSeparator1,
            this.tlStrMnuItm_COMPerso,
            this.tlStrMnuItm_COMx});
            this.tlStrMnuItm_OptionsRS.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_OptionsRS.Image")));
            this.tlStrMnuItm_OptionsRS.Name = "tlStrMnuItm_OptionsRS";
            this.tlStrMnuItm_OptionsRS.Size = new System.Drawing.Size(181, 22);
            this.tlStrMnuItm_OptionsRS.Text = "Port";
            // 
            // tlStrMnuItm_COM1
            // 
            this.tlStrMnuItm_COM1.Checked = true;
            this.tlStrMnuItm_COM1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.tlStrMnuItm_COM1.Name = "tlStrMnuItm_COM1";
            this.tlStrMnuItm_COM1.Size = new System.Drawing.Size(160, 22);
            this.tlStrMnuItm_COM1.Text = "COM1";
            this.tlStrMnuItm_COM1.Click += new System.EventHandler(this.tlStrMnuItm_COM1_Click);
            // 
            // tlStrMnuItm_COM2
            // 
            this.tlStrMnuItm_COM2.Name = "tlStrMnuItm_COM2";
            this.tlStrMnuItm_COM2.Size = new System.Drawing.Size(160, 22);
            this.tlStrMnuItm_COM2.Text = "COM2";
            this.tlStrMnuItm_COM2.Click += new System.EventHandler(this.tlStrMnuItm_COM2_Click);
            // 
            // tlStrMnuItm_COM3
            // 
            this.tlStrMnuItm_COM3.Name = "tlStrMnuItm_COM3";
            this.tlStrMnuItm_COM3.Size = new System.Drawing.Size(160, 22);
            this.tlStrMnuItm_COM3.Text = "COM3";
            this.tlStrMnuItm_COM3.Click += new System.EventHandler(this.tlStrMnuItm_COM3_Click);
            // 
            // tlStrMnuItm_COM4
            // 
            this.tlStrMnuItm_COM4.Name = "tlStrMnuItm_COM4";
            this.tlStrMnuItm_COM4.Size = new System.Drawing.Size(160, 22);
            this.tlStrMnuItm_COM4.Text = "COM4";
            this.tlStrMnuItm_COM4.Click += new System.EventHandler(this.tlStrMnuItm_COM4_Click);
            // 
            // tlStrMnuItm_COM5
            // 
            this.tlStrMnuItm_COM5.Name = "tlStrMnuItm_COM5";
            this.tlStrMnuItm_COM5.Size = new System.Drawing.Size(160, 22);
            this.tlStrMnuItm_COM5.Text = "COM5";
            this.tlStrMnuItm_COM5.Click += new System.EventHandler(this.cOM5ToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(157, 6);
            // 
            // tlStrMnuItm_COMPerso
            // 
            this.tlStrMnuItm_COMPerso.Name = "tlStrMnuItm_COMPerso";
            this.tlStrMnuItm_COMPerso.Size = new System.Drawing.Size(100, 23);
            this.tlStrMnuItm_COMPerso.Text = "COMx";
            // 
            // tlStrMnuItm_COMx
            // 
            this.tlStrMnuItm_COMx.Name = "tlStrMnuItm_COMx";
            this.tlStrMnuItm_COMx.Size = new System.Drawing.Size(160, 22);
            this.tlStrMnuItm_COMx.Text = "Ouvrir COMx";
            this.tlStrMnuItm_COMx.Click += new System.EventHandler(this.tlStrMnuItm_COMx_Click);
            // 
            // settingsToolStripMenuItem2
            // 
            this.settingsToolStripMenuItem2.Enabled = false;
            this.settingsToolStripMenuItem2.Image = ((System.Drawing.Image)(resources.GetObject("settingsToolStripMenuItem2.Image")));
            this.settingsToolStripMenuItem2.Name = "settingsToolStripMenuItem2";
            this.settingsToolStripMenuItem2.Size = new System.Drawing.Size(181, 22);
            this.settingsToolStripMenuItem2.Text = "Settings";
            // 
            // tlStrMnuItm_Zones
            // 
            this.tlStrMnuItm_Zones.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tlStrMnuItm_ZonesSend,
            this.lireToolStripMenuItem1,
            this.tlStrSep_Zones,
            this.tlStrMnuItm_ZonesNew,
            this.tlStrMnuItm_ZonesOpen,
            this.tlStrMnuItm_ZonesSave,
            this.tlStrMnuItm_ZonesSaveAs});
            this.tlStrMnuItm_Zones.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_Zones.Image")));
            this.tlStrMnuItm_Zones.Name = "tlStrMnuItm_Zones";
            this.tlStrMnuItm_Zones.Size = new System.Drawing.Size(119, 20);
            this.tlStrMnuItm_Zones.Text = "Zones interdites";
            // 
            // tlStrMnuItm_ZonesSend
            // 
            this.tlStrMnuItm_ZonesSend.DoubleClickEnabled = true;
            this.tlStrMnuItm_ZonesSend.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_ZonesSend.Image")));
            this.tlStrMnuItm_ZonesSend.Name = "tlStrMnuItm_ZonesSend";
            this.tlStrMnuItm_ZonesSend.Size = new System.Drawing.Size(166, 22);
            this.tlStrMnuItm_ZonesSend.Text = "Envoyer";
            this.tlStrMnuItm_ZonesSend.Click += new System.EventHandler(this.tlStrMnuItm_ZonesSend_Click);
            // 
            // lireToolStripMenuItem1
            // 
            this.lireToolStripMenuItem1.Enabled = false;
            this.lireToolStripMenuItem1.Image = ((System.Drawing.Image)(resources.GetObject("lireToolStripMenuItem1.Image")));
            this.lireToolStripMenuItem1.Name = "lireToolStripMenuItem1";
            this.lireToolStripMenuItem1.Size = new System.Drawing.Size(166, 22);
            this.lireToolStripMenuItem1.Text = "Lire";
            // 
            // tlStrSep_Zones
            // 
            this.tlStrSep_Zones.Name = "tlStrSep_Zones";
            this.tlStrSep_Zones.Size = new System.Drawing.Size(163, 6);
            // 
            // tlStrMnuItm_ZonesNew
            // 
            this.tlStrMnuItm_ZonesNew.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_ZonesNew.Image")));
            this.tlStrMnuItm_ZonesNew.Name = "tlStrMnuItm_ZonesNew";
            this.tlStrMnuItm_ZonesNew.Size = new System.Drawing.Size(166, 22);
            this.tlStrMnuItm_ZonesNew.Text = "Nouveau";
            this.tlStrMnuItm_ZonesNew.Click += new System.EventHandler(this.tlStrMnuItm_ZonesNew_Click);
            // 
            // tlStrMnuItm_ZonesOpen
            // 
            this.tlStrMnuItm_ZonesOpen.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_ZonesOpen.Image")));
            this.tlStrMnuItm_ZonesOpen.Name = "tlStrMnuItm_ZonesOpen";
            this.tlStrMnuItm_ZonesOpen.Size = new System.Drawing.Size(166, 22);
            this.tlStrMnuItm_ZonesOpen.Text = "Ouvrir";
            // 
            // tlStrMnuItm_ZonesSave
            // 
            this.tlStrMnuItm_ZonesSave.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_ZonesSave.Image")));
            this.tlStrMnuItm_ZonesSave.Name = "tlStrMnuItm_ZonesSave";
            this.tlStrMnuItm_ZonesSave.Size = new System.Drawing.Size(166, 22);
            this.tlStrMnuItm_ZonesSave.Text = "Enregistrer";
            // 
            // tlStrMnuItm_ZonesSaveAs
            // 
            this.tlStrMnuItm_ZonesSaveAs.Image = ((System.Drawing.Image)(resources.GetObject("tlStrMnuItm_ZonesSaveAs.Image")));
            this.tlStrMnuItm_ZonesSaveAs.Name = "tlStrMnuItm_ZonesSaveAs";
            this.tlStrMnuItm_ZonesSaveAs.Size = new System.Drawing.Size(166, 22);
            this.tlStrMnuItm_ZonesSaveAs.Text = "Enregistrer sous...";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(24, 20);
            this.toolStripMenuItem1.Text = "?";
            this.toolStripMenuItem1.Click += new System.EventHandler(this.toolStripMenuItem1_Click);
            // 
            // tmr_Update
            // 
            this.tmr_Update.Enabled = true;
            this.tmr_Update.Interval = 500;
            this.tmr_Update.Tick += new System.EventHandler(this.timer_update_Tick);
            // 
            // Objectifs
            // 
            this.Objectifs.HeaderText = "Objectifs";
            this.Objectifs.Name = "Objectifs";
            // 
            // col_ObjectifNumero
            // 
            this.col_ObjectifNumero.HeaderText = "Point";
            this.col_ObjectifNumero.Name = "col_ObjectifNumero";
            this.col_ObjectifNumero.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            // 
            // col_ObjectifPositionX
            // 
            this.col_ObjectifPositionX.HeaderText = "Position X [mm]";
            this.col_ObjectifPositionX.Name = "col_ObjectifPositionX";
            // 
            // col_ObjectifPositionY
            // 
            this.col_ObjectifPositionY.HeaderText = "Position Y [mm]";
            this.col_ObjectifPositionY.Name = "col_ObjectifPositionY";
            // 
            // col_TypeObj
            // 
            this.col_TypeObj.HeaderText = "Type de déplacement";
            this.col_TypeObj.Name = "col_TypeObj";
            // 
            // col_AvAr
            // 
            this.col_AvAr.HeaderText = "Avance (0) / Recule (1)";
            this.col_AvAr.Name = "col_AvAr";
            // 
            // col_CoteTourn
            // 
            this.col_CoteTourn.HeaderText = "Tourner (0/auto, 1/g, 2/d)";
            this.col_CoteTourn.Name = "col_CoteTourn";
            // 
            // col_VitMax
            // 
            this.col_VitMax.HeaderText = "Vitesse Maximum";
            this.col_VitMax.Name = "col_VitMax";
            this.col_VitMax.ToolTipText = "20";
            // 
            // col_ObjectifToDo
            // 
            this.col_ObjectifToDo.HeaderText = "Objectif à Réaliser (Carte Principale)";
            this.col_ObjectifToDo.Name = "col_ObjectifToDo";
            // 
            // col_PrecAngle
            // 
            this.col_PrecAngle.HeaderText = "Point (comm/0, g/1,d/2)";
            this.col_PrecAngle.Name = "col_PrecAngle";
            // 
            // Column1
            // 
            this.Column1.HeaderText = "Pondération objectifs";
            this.Column1.Name = "Column1";
            // 
            // Column2
            // 
            this.Column2.HeaderText = "Obj end(1/end)";
            this.Column2.Name = "Column2";
            // 
            // Column3
            // 
            this.Column3.HeaderText = "Next obj( 0/next, 2/obj2....)";
            this.Column3.Name = "Column3";
            // 
            // a
            // 
            this.a.HeaderText = "Obj Redondant (1/y, 0/n)";
            this.a.Name = "a";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1002, 566);
            this.Controls.Add(this.tlStrCon_Main);
            this.DoubleBuffered = true;
            this.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximumSize = new System.Drawing.Size(5000, 5000);
            this.MinimumSize = new System.Drawing.Size(804, 405);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Eurobot - Programme de configuration";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tlStrCon_Main.BottomToolStripPanel.ResumeLayout(false);
            this.tlStrCon_Main.BottomToolStripPanel.PerformLayout();
            this.tlStrCon_Main.ContentPanel.ResumeLayout(false);
            this.tlStrCon_Main.TopToolStripPanel.ResumeLayout(false);
            this.tlStrCon_Main.ResumeLayout(false);
            this.tlStrCon_Main.PerformLayout();
            this.staStr_Status.ResumeLayout(false);
            this.staStr_Status.PerformLayout();
            this.spCon_Horizontal.Panel1.ResumeLayout(false);
            this.spCon_Horizontal.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.spCon_Horizontal)).EndInit();
            this.spCon_Horizontal.ResumeLayout(false);
            this.spCon_Vertical.Panel1.ResumeLayout(false);
            this.spCon_Vertical.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.spCon_Vertical)).EndInit();
            this.spCon_Vertical.ResumeLayout(false);
            this.tlStrCon_Com.ContentPanel.ResumeLayout(false);
            this.tlStrCon_Com.ResumeLayout(false);
            this.tlStrCon_Com.PerformLayout();
            this.spCon_Communication.Panel1.ResumeLayout(false);
            this.spCon_Communication.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.spCon_Communication)).EndInit();
            this.spCon_Communication.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.spCon_Communication1.Panel1.ResumeLayout(false);
            this.spCon_Communication1.Panel1.PerformLayout();
            this.spCon_Communication1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.spCon_Communication1)).EndInit();
            this.spCon_Communication1.ResumeLayout(false);
            this.tabCtr_Main.ResumeLayout(false);
            this.tabPg_Objectifs.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGV_Objectifs)).EndInit();
            this.tabPg_Zones.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGV_Zones)).EndInit();
            this.mnu_Main.ResumeLayout(false);
            this.mnu_Main.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ToolStripContainer tlStrCon_Main;
        private System.Windows.Forms.TabControl tabCtr_Main;
        private System.Windows.Forms.TabPage tabPg_Objectifs;
        private System.Windows.Forms.DataGridView dataGV_Objectifs;
        private System.Windows.Forms.TabPage tabPg_Zones;
        private System.Windows.Forms.DataGridView dataGV_Zones;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_ZoneNumero;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_ZoneX1;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_ZoneY1;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_ZoneX2;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_ZoneY2;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_ZoneX3;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_ZoneY3;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_ZoneX4;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_ZoneY4;
        private System.Windows.Forms.SplitContainer spCon_Communication;
        private System.Windows.Forms.TextBox txt_Angle;
        private System.Windows.Forms.TextBox txt_PosY;
        private System.Windows.Forms.TextBox txt_PosX;
        private System.Windows.Forms.Button btn_Clear;
        private System.Windows.Forms.TextBox txt_Send;
        private System.Windows.Forms.SplitContainer spCon_Communication1;
        private System.Windows.Forms.RichTextBox rTxt_Received;
        private System.Windows.Forms.SplitContainer spCon_Horizontal;
        private System.Windows.Forms.SplitContainer spCon_Vertical;
        private BufferedPanel buffPan_Carte;
        private System.Windows.Forms.ToolStripContainer tlStrCon_Com;
        private System.Windows.Forms.MenuStrip mnu_Main;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_Objectifs;
        private System.Windows.Forms.ImageList imgLst_Tab;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_ObjectifsOpen;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_ObjectifsSave;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_ObjectifsSaveAs;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_RS232;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_PortState;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_OptionsRS;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_Zones;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_ZonesOpen;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_ZonesSave;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_ZonesSaveAs;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_ObjectifsNew;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_ZonesNew;
        private System.Windows.Forms.ToolStripSeparator tlStrSep_Objectifs1;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_ZonesSend;
        private System.Windows.Forms.ToolStripSeparator tlStrSep_Zones;
        private System.Windows.Forms.StatusStrip staStr_Status;
        private System.Windows.Forms.ToolStripStatusLabel tlStrStaLbl_State;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_COM1;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_COM2;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_COM3;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_COM4;
        private System.Windows.Forms.ToolStripStatusLabel staStrLbl_Position;
        private System.Windows.Forms.ToolStripStatusLabel tlStrStaLbl_Spring;
        private System.Windows.Forms.Button btn_InitPosition;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_SymmetryX;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_SymmetryY;
        private System.Windows.Forms.ToolStripSeparator tlStrSep_Objectifs2;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_EEPROM;
        public System.Windows.Forms.Timer tmr_Update;
        public System.IO.Ports.SerialPort srlPort_RS;
        public System.Windows.Forms.RichTextBox rTxt_Sent;
        private System.Windows.Forms.ToolStripMenuItem roboteQToolStripMenuItem;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ToolStripMenuItem lireToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem lireToolStripMenuItem1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtPrincAdr;
        private System.Windows.Forms.ComboBox cbBoardToSend;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_COM5;
        private System.Windows.Forms.ToolStripMenuItem settingsToolStripMenuItem2;
        private System.Windows.Forms.ToolStripTextBox tlStrMnuItm_COMPerso;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_COMx;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_ObjectifsSend;
        private System.Windows.Forms.ToolStripMenuItem cartePrincipaleToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem eraseToolStripMenuItem;
        private System.Windows.Forms.DataGridViewTextBoxColumn Objectifs;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_ObjectifNumero;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_ObjectifPositionX;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_ObjectifPositionY;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_TypeObj;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_AvAr;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_CoteTourn;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_VitMax;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_ObjectifToDo;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_PrecAngle;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column2;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column3;
        private System.Windows.Forms.DataGridViewTextBoxColumn a;
    }
}

