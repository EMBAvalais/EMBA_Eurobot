namespace Eurobot
{
    partial class SettingsDriverMot
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SettingsDriverMot));
            this.grpPID = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cbPWMRoboteQ = new System.Windows.Forms.CheckBox();
            this.pnRegVit = new System.Windows.Forms.Panel();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.txtKdRoueD = new System.Windows.Forms.TextBox();
            this.txtIntegLimitRoueD = new System.Windows.Forms.TextBox();
            this.txtKiRoueD = new System.Windows.Forms.TextBox();
            this.txtKpRoueD = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.lblPIDRoueD = new System.Windows.Forms.Label();
            this.txtKdRoueG = new System.Windows.Forms.TextBox();
            this.txtIntegLimitRoueG = new System.Windows.Forms.TextBox();
            this.txtKiRoueG = new System.Windows.Forms.TextBox();
            this.txtKpRoueG = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.lblPIDRoueG = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.txtKdOrient = new System.Windows.Forms.TextBox();
            this.txtIntegLimitOrient = new System.Windows.Forms.TextBox();
            this.txtKiOrient = new System.Windows.Forms.TextBox();
            this.txtKpOrient = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.lblPIDOrient = new System.Windows.Forms.Label();
            this.txtKdDist = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.txtIntegLimitDist = new System.Windows.Forms.TextBox();
            this.txtKiDist = new System.Windows.Forms.TextBox();
            this.txtKpDist = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.lblPIDDist = new System.Windows.Forms.Label();
            this.tlStrMnuItm_readAll = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_WriteAll = new System.Windows.Forms.ToolStripMenuItem();
            this.mnu_Main = new System.Windows.Forms.MenuStrip();
            this.gbRobSettings = new System.Windows.Forms.GroupBox();
            this.lblCaracRobot = new System.Windows.Forms.Label();
            this.txtIICRepeat = new System.Windows.Forms.TextBox();
            this.txtIICWatchdog = new System.Windows.Forms.TextBox();
            this.txtIICAddr = new System.Windows.Forms.TextBox();
            this.txtUARTWatchdog = new System.Windows.Forms.TextBox();
            this.txtUARTRepeat = new System.Windows.Forms.TextBox();
            this.txtUARTAddr = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.txtEntraxe = new System.Windows.Forms.TextBox();
            this.txtDiamEnco = new System.Windows.Forms.TextBox();
            this.txtNbreImpulses = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.cbModealgo = new System.Windows.Forms.ComboBox();
            this.lblLocal = new System.Windows.Forms.Label();
            this.lblAsserv = new System.Windows.Forms.Label();
            this.txtLocaTime = new System.Windows.Forms.TextBox();
            this.label23 = new System.Windows.Forms.Label();
            this.txtCorrRg = new System.Windows.Forms.TextBox();
            this.label22 = new System.Windows.Forms.Label();
            this.txtCorrRd = new System.Windows.Forms.TextBox();
            this.label21 = new System.Windows.Forms.Label();
            this.txtVitMax = new System.Windows.Forms.TextBox();
            this.label19 = new System.Windows.Forms.Label();
            this.txtAccMax = new System.Windows.Forms.TextBox();
            this.txtAsservTime = new System.Windows.Forms.TextBox();
            this.txtMotMin = new System.Windows.Forms.TextBox();
            this.txtCorrCentri = new System.Windows.Forms.TextBox();
            this.txtMotMax = new System.Windows.Forms.TextBox();
            this.grpPID.SuspendLayout();
            this.pnRegVit.SuspendLayout();
            this.mnu_Main.SuspendLayout();
            this.gbRobSettings.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // grpPID
            // 
            this.grpPID.Controls.Add(this.label2);
            this.grpPID.Controls.Add(this.cbPWMRoboteQ);
            this.grpPID.Controls.Add(this.pnRegVit);
            this.grpPID.Controls.Add(this.txtKdOrient);
            this.grpPID.Controls.Add(this.txtIntegLimitOrient);
            this.grpPID.Controls.Add(this.txtKiOrient);
            this.grpPID.Controls.Add(this.txtKpOrient);
            this.grpPID.Controls.Add(this.label6);
            this.grpPID.Controls.Add(this.lblPIDOrient);
            this.grpPID.Controls.Add(this.txtKdDist);
            this.grpPID.Controls.Add(this.label11);
            this.grpPID.Controls.Add(this.txtIntegLimitDist);
            this.grpPID.Controls.Add(this.txtKiDist);
            this.grpPID.Controls.Add(this.txtKpDist);
            this.grpPID.Controls.Add(this.label3);
            this.grpPID.Controls.Add(this.label1);
            this.grpPID.Controls.Add(this.lblPIDDist);
            this.grpPID.Location = new System.Drawing.Point(629, 27);
            this.grpPID.Name = "grpPID";
            this.grpPID.Size = new System.Drawing.Size(298, 667);
            this.grpPID.TabIndex = 0;
            this.grpPID.TabStop = false;
            this.grpPID.Text = "PID\'s";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 209);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(97, 91);
            this.label2.TabIndex = 48;
            this.label2.Text = "Kp (*1\'000\'000) :\r\n\r\nKi (*1\'000\'000) :\r\n\r\nLimite intégral [‰] :\r\n\r\nKd (*1\'000\'000" +
    ") :";
            // 
            // cbPWMRoboteQ
            // 
            this.cbPWMRoboteQ.AutoSize = true;
            this.cbPWMRoboteQ.Location = new System.Drawing.Point(9, 334);
            this.cbPWMRoboteQ.Name = "cbPWMRoboteQ";
            this.cbPWMRoboteQ.Size = new System.Drawing.Size(221, 17);
            this.cbPWMRoboteQ.TabIndex = 47;
            this.cbPWMRoboteQ.Text = "Utilisation des PWMs au lieu de RoboteQ";
            this.cbPWMRoboteQ.UseVisualStyleBackColor = true;
            this.cbPWMRoboteQ.CheckedChanged += new System.EventHandler(this.cbPWMRoboteQ_CheckedChanged);
            // 
            // pnRegVit
            // 
            this.pnRegVit.Controls.Add(this.label5);
            this.pnRegVit.Controls.Add(this.label4);
            this.pnRegVit.Controls.Add(this.txtKdRoueD);
            this.pnRegVit.Controls.Add(this.txtIntegLimitRoueD);
            this.pnRegVit.Controls.Add(this.txtKiRoueD);
            this.pnRegVit.Controls.Add(this.txtKpRoueD);
            this.pnRegVit.Controls.Add(this.label13);
            this.pnRegVit.Controls.Add(this.lblPIDRoueD);
            this.pnRegVit.Controls.Add(this.txtKdRoueG);
            this.pnRegVit.Controls.Add(this.txtIntegLimitRoueG);
            this.pnRegVit.Controls.Add(this.txtKiRoueG);
            this.pnRegVit.Controls.Add(this.txtKpRoueG);
            this.pnRegVit.Controls.Add(this.label18);
            this.pnRegVit.Controls.Add(this.lblPIDRoueG);
            this.pnRegVit.Controls.Add(this.label7);
            this.pnRegVit.Enabled = false;
            this.pnRegVit.Location = new System.Drawing.Point(9, 353);
            this.pnRegVit.Name = "pnRegVit";
            this.pnRegVit.Size = new System.Drawing.Size(285, 306);
            this.pnRegVit.TabIndex = 45;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(3, 203);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(97, 91);
            this.label5.TabIndex = 83;
            this.label5.Text = "Kp (*1\'000\'000) :\r\n\r\nKi (*1\'000\'000) :\r\n\r\nLimite intégral [‰] :\r\n\r\nKd (*1\'000\'000" +
    ") :";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(3, 63);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(97, 91);
            this.label4.TabIndex = 82;
            this.label4.Text = "Kp (*1\'000\'000) :\r\n\r\nKi (*1\'000\'000) :\r\n\r\nLimite intégral [‰] :\r\n\r\nKd (*1\'000\'000" +
    ") :";
            // 
            // txtKdRoueD
            // 
            this.txtKdRoueD.Location = new System.Drawing.Point(105, 277);
            this.txtKdRoueD.Name = "txtKdRoueD";
            this.txtKdRoueD.Size = new System.Drawing.Size(100, 20);
            this.txtKdRoueD.TabIndex = 81;
            this.txtKdRoueD.Text = "0";
            // 
            // txtIntegLimitRoueD
            // 
            this.txtIntegLimitRoueD.Location = new System.Drawing.Point(105, 251);
            this.txtIntegLimitRoueD.Name = "txtIntegLimitRoueD";
            this.txtIntegLimitRoueD.Size = new System.Drawing.Size(100, 20);
            this.txtIntegLimitRoueD.TabIndex = 78;
            this.txtIntegLimitRoueD.Text = "0";
            // 
            // txtKiRoueD
            // 
            this.txtKiRoueD.Location = new System.Drawing.Point(105, 225);
            this.txtKiRoueD.Name = "txtKiRoueD";
            this.txtKiRoueD.Size = new System.Drawing.Size(100, 20);
            this.txtKiRoueD.TabIndex = 77;
            this.txtKiRoueD.Text = "0";
            // 
            // txtKpRoueD
            // 
            this.txtKpRoueD.Location = new System.Drawing.Point(105, 200);
            this.txtKpRoueD.Name = "txtKpRoueD";
            this.txtKpRoueD.Size = new System.Drawing.Size(100, 20);
            this.txtKpRoueD.TabIndex = 76;
            this.txtKpRoueD.Text = "0";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label13.Location = new System.Drawing.Point(102, 177);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(106, 20);
            this.label13.TabIndex = 74;
            this.label13.Text = "Roue Droite";
            // 
            // lblPIDRoueD
            // 
            this.lblPIDRoueD.AutoSize = true;
            this.lblPIDRoueD.Location = new System.Drawing.Point(234, 203);
            this.lblPIDRoueD.Name = "lblPIDRoueD";
            this.lblPIDRoueD.Size = new System.Drawing.Size(42, 91);
            this.lblPIDRoueD.TabIndex = 80;
            this.lblPIDRoueD.Text = "Unread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nUnread";
            // 
            // txtKdRoueG
            // 
            this.txtKdRoueG.Location = new System.Drawing.Point(105, 137);
            this.txtKdRoueG.Name = "txtKdRoueG";
            this.txtKdRoueG.Size = new System.Drawing.Size(100, 20);
            this.txtKdRoueG.TabIndex = 72;
            this.txtKdRoueG.Text = "0";
            // 
            // txtIntegLimitRoueG
            // 
            this.txtIntegLimitRoueG.Location = new System.Drawing.Point(105, 111);
            this.txtIntegLimitRoueG.Name = "txtIntegLimitRoueG";
            this.txtIntegLimitRoueG.Size = new System.Drawing.Size(100, 20);
            this.txtIntegLimitRoueG.TabIndex = 69;
            this.txtIntegLimitRoueG.Text = "0";
            // 
            // txtKiRoueG
            // 
            this.txtKiRoueG.Location = new System.Drawing.Point(105, 85);
            this.txtKiRoueG.Name = "txtKiRoueG";
            this.txtKiRoueG.Size = new System.Drawing.Size(100, 20);
            this.txtKiRoueG.TabIndex = 68;
            this.txtKiRoueG.Text = "0";
            // 
            // txtKpRoueG
            // 
            this.txtKpRoueG.Location = new System.Drawing.Point(105, 60);
            this.txtKpRoueG.Name = "txtKpRoueG";
            this.txtKpRoueG.Size = new System.Drawing.Size(100, 20);
            this.txtKpRoueG.TabIndex = 67;
            this.txtKpRoueG.Text = "0";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label18.Location = new System.Drawing.Point(96, 37);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(120, 20);
            this.label18.TabIndex = 65;
            this.label18.Text = "Roue Gauche";
            // 
            // lblPIDRoueG
            // 
            this.lblPIDRoueG.AutoSize = true;
            this.lblPIDRoueG.Location = new System.Drawing.Point(234, 63);
            this.lblPIDRoueG.Name = "lblPIDRoueG";
            this.lblPIDRoueG.Size = new System.Drawing.Size(42, 91);
            this.lblPIDRoueG.TabIndex = 71;
            this.lblPIDRoueG.Text = "Unread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nUnread";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(2, 3);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(161, 20);
            this.label7.TabIndex = 64;
            this.label7.Text = "Régulation Vitesse";
            // 
            // txtKdOrient
            // 
            this.txtKdOrient.Location = new System.Drawing.Point(109, 283);
            this.txtKdOrient.Name = "txtKdOrient";
            this.txtKdOrient.Size = new System.Drawing.Size(100, 20);
            this.txtKdOrient.TabIndex = 43;
            this.txtKdOrient.Text = "800000";
            // 
            // txtIntegLimitOrient
            // 
            this.txtIntegLimitOrient.Location = new System.Drawing.Point(109, 257);
            this.txtIntegLimitOrient.Name = "txtIntegLimitOrient";
            this.txtIntegLimitOrient.Size = new System.Drawing.Size(100, 20);
            this.txtIntegLimitOrient.TabIndex = 40;
            this.txtIntegLimitOrient.Text = "50";
            // 
            // txtKiOrient
            // 
            this.txtKiOrient.Location = new System.Drawing.Point(109, 231);
            this.txtKiOrient.Name = "txtKiOrient";
            this.txtKiOrient.Size = new System.Drawing.Size(100, 20);
            this.txtKiOrient.TabIndex = 39;
            this.txtKiOrient.Text = "1000";
            // 
            // txtKpOrient
            // 
            this.txtKpOrient.Location = new System.Drawing.Point(109, 206);
            this.txtKpOrient.Name = "txtKpOrient";
            this.txtKpOrient.Size = new System.Drawing.Size(100, 20);
            this.txtKpOrient.TabIndex = 38;
            this.txtKpOrient.Text = "4500";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(111, 183);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(98, 20);
            this.label6.TabIndex = 36;
            this.label6.Text = "Orientation";
            // 
            // lblPIDOrient
            // 
            this.lblPIDOrient.AutoSize = true;
            this.lblPIDOrient.Location = new System.Drawing.Point(243, 209);
            this.lblPIDOrient.Name = "lblPIDOrient";
            this.lblPIDOrient.Size = new System.Drawing.Size(42, 91);
            this.lblPIDOrient.TabIndex = 42;
            this.lblPIDOrient.Text = "Unread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nUnread";
            // 
            // txtKdDist
            // 
            this.txtKdDist.Location = new System.Drawing.Point(109, 143);
            this.txtKdDist.Name = "txtKdDist";
            this.txtKdDist.Size = new System.Drawing.Size(100, 20);
            this.txtKdDist.TabIndex = 34;
            this.txtKdDist.Text = "1500000";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Dock = System.Windows.Forms.DockStyle.Top;
            this.label11.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label11.Location = new System.Drawing.Point(3, 16);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(156, 20);
            this.label11.TabIndex = 32;
            this.label11.Text = "Régulation Polaire";
            // 
            // txtIntegLimitDist
            // 
            this.txtIntegLimitDist.Location = new System.Drawing.Point(109, 117);
            this.txtIntegLimitDist.Name = "txtIntegLimitDist";
            this.txtIntegLimitDist.Size = new System.Drawing.Size(100, 20);
            this.txtIntegLimitDist.TabIndex = 22;
            this.txtIntegLimitDist.Text = "55";
            // 
            // txtKiDist
            // 
            this.txtKiDist.Location = new System.Drawing.Point(109, 91);
            this.txtKiDist.Name = "txtKiDist";
            this.txtKiDist.Size = new System.Drawing.Size(100, 20);
            this.txtKiDist.TabIndex = 21;
            this.txtKiDist.Text = "1600";
            // 
            // txtKpDist
            // 
            this.txtKpDist.Location = new System.Drawing.Point(109, 66);
            this.txtKpDist.Name = "txtKpDist";
            this.txtKpDist.Size = new System.Drawing.Size(100, 20);
            this.txtKpDist.TabIndex = 20;
            this.txtKpDist.Text = "13000";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 69);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(97, 91);
            this.label3.TabIndex = 18;
            this.label3.Text = "Kp (*1\'000\'000) :\r\n\r\nKi (*1\'000\'000) :\r\n\r\nLimite intégral [‰] :\r\n\r\nKd (*1\'000\'000" +
    ") :";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(118, 43);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(80, 20);
            this.label1.TabIndex = 16;
            this.label1.Text = "Distance";
            // 
            // lblPIDDist
            // 
            this.lblPIDDist.AutoSize = true;
            this.lblPIDDist.Location = new System.Drawing.Point(243, 69);
            this.lblPIDDist.Name = "lblPIDDist";
            this.lblPIDDist.Size = new System.Drawing.Size(42, 91);
            this.lblPIDDist.TabIndex = 30;
            this.lblPIDDist.Text = "Unread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nUnread";
            // 
            // tlStrMnuItm_readAll
            // 
            this.tlStrMnuItm_readAll.Enabled = false;
            this.tlStrMnuItm_readAll.Name = "tlStrMnuItm_readAll";
            this.tlStrMnuItm_readAll.Size = new System.Drawing.Size(84, 20);
            this.tlStrMnuItm_readAll.Text = "Read Config";
            // 
            // tlStrMnuItm_WriteAll
            // 
            this.tlStrMnuItm_WriteAll.Name = "tlStrMnuItm_WriteAll";
            this.tlStrMnuItm_WriteAll.Size = new System.Drawing.Size(86, 20);
            this.tlStrMnuItm_WriteAll.Text = "Write Config";
            this.tlStrMnuItm_WriteAll.Click += new System.EventHandler(this.tlStrMnuItm_WriteAll_Click);
            // 
            // mnu_Main
            // 
            this.mnu_Main.AutoSize = false;
            this.mnu_Main.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tlStrMnuItm_readAll,
            this.tlStrMnuItm_WriteAll});
            this.mnu_Main.Location = new System.Drawing.Point(0, 0);
            this.mnu_Main.Name = "mnu_Main";
            this.mnu_Main.Size = new System.Drawing.Size(934, 24);
            this.mnu_Main.TabIndex = 2;
            this.mnu_Main.Text = "menuStrip1";
            // 
            // gbRobSettings
            // 
            this.gbRobSettings.Controls.Add(this.lblCaracRobot);
            this.gbRobSettings.Controls.Add(this.txtIICRepeat);
            this.gbRobSettings.Controls.Add(this.txtIICWatchdog);
            this.gbRobSettings.Controls.Add(this.txtIICAddr);
            this.gbRobSettings.Controls.Add(this.txtUARTWatchdog);
            this.gbRobSettings.Controls.Add(this.txtUARTRepeat);
            this.gbRobSettings.Controls.Add(this.txtUARTAddr);
            this.gbRobSettings.Controls.Add(this.label14);
            this.gbRobSettings.Controls.Add(this.txtEntraxe);
            this.gbRobSettings.Controls.Add(this.txtDiamEnco);
            this.gbRobSettings.Controls.Add(this.txtNbreImpulses);
            this.gbRobSettings.Location = new System.Drawing.Point(3, 27);
            this.gbRobSettings.Name = "gbRobSettings";
            this.gbRobSettings.Size = new System.Drawing.Size(620, 251);
            this.gbRobSettings.TabIndex = 3;
            this.gbRobSettings.TabStop = false;
            this.gbRobSettings.Text = "Caractéristiques du robot";
            // 
            // lblCaracRobot
            // 
            this.lblCaracRobot.AutoSize = true;
            this.lblCaracRobot.Location = new System.Drawing.Point(519, 18);
            this.lblCaracRobot.Name = "lblCaracRobot";
            this.lblCaracRobot.Size = new System.Drawing.Size(42, 221);
            this.lblCaracRobot.TabIndex = 83;
            this.lblCaracRobot.Text = "Unread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nU" +
    "nread";
            // 
            // txtIICRepeat
            // 
            this.txtIICRepeat.Location = new System.Drawing.Point(355, 225);
            this.txtIICRepeat.Name = "txtIICRepeat";
            this.txtIICRepeat.Size = new System.Drawing.Size(100, 20);
            this.txtIICRepeat.TabIndex = 56;
            this.txtIICRepeat.Text = "5";
            // 
            // txtIICWatchdog
            // 
            this.txtIICWatchdog.Location = new System.Drawing.Point(355, 200);
            this.txtIICWatchdog.Name = "txtIICWatchdog";
            this.txtIICWatchdog.Size = new System.Drawing.Size(100, 20);
            this.txtIICWatchdog.TabIndex = 55;
            this.txtIICWatchdog.Text = "20";
            // 
            // txtIICAddr
            // 
            this.txtIICAddr.Location = new System.Drawing.Point(355, 174);
            this.txtIICAddr.Name = "txtIICAddr";
            this.txtIICAddr.Size = new System.Drawing.Size(100, 20);
            this.txtIICAddr.TabIndex = 54;
            this.txtIICAddr.Text = "80";
            // 
            // txtUARTWatchdog
            // 
            this.txtUARTWatchdog.Location = new System.Drawing.Point(355, 122);
            this.txtUARTWatchdog.Name = "txtUARTWatchdog";
            this.txtUARTWatchdog.Size = new System.Drawing.Size(100, 20);
            this.txtUARTWatchdog.TabIndex = 52;
            this.txtUARTWatchdog.Text = "20";
            // 
            // txtUARTRepeat
            // 
            this.txtUARTRepeat.Location = new System.Drawing.Point(355, 148);
            this.txtUARTRepeat.Name = "txtUARTRepeat";
            this.txtUARTRepeat.Size = new System.Drawing.Size(100, 20);
            this.txtUARTRepeat.TabIndex = 53;
            this.txtUARTRepeat.Text = "5";
            // 
            // txtUARTAddr
            // 
            this.txtUARTAddr.Location = new System.Drawing.Point(355, 96);
            this.txtUARTAddr.Name = "txtUARTAddr";
            this.txtUARTAddr.Size = new System.Drawing.Size(100, 20);
            this.txtUARTAddr.TabIndex = 51;
            this.txtUARTAddr.Text = "1";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(6, 21);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(318, 221);
            this.label14.TabIndex = 48;
            this.label14.Text = resources.GetString("label14.Text");
            // 
            // txtEntraxe
            // 
            this.txtEntraxe.Location = new System.Drawing.Point(355, 70);
            this.txtEntraxe.Name = "txtEntraxe";
            this.txtEntraxe.Size = new System.Drawing.Size(100, 20);
            this.txtEntraxe.TabIndex = 50;
            this.txtEntraxe.Text = "325500";
            // 
            // txtDiamEnco
            // 
            this.txtDiamEnco.Location = new System.Drawing.Point(355, 18);
            this.txtDiamEnco.Name = "txtDiamEnco";
            this.txtDiamEnco.Size = new System.Drawing.Size(100, 20);
            this.txtDiamEnco.TabIndex = 48;
            this.txtDiamEnco.Text = "34400";
            // 
            // txtNbreImpulses
            // 
            this.txtNbreImpulses.Location = new System.Drawing.Point(355, 44);
            this.txtNbreImpulses.Name = "txtNbreImpulses";
            this.txtNbreImpulses.Size = new System.Drawing.Size(100, 20);
            this.txtNbreImpulses.TabIndex = 49;
            this.txtNbreImpulses.Text = "5000";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.cbModealgo);
            this.groupBox1.Controls.Add(this.lblLocal);
            this.groupBox1.Controls.Add(this.lblAsserv);
            this.groupBox1.Controls.Add(this.txtLocaTime);
            this.groupBox1.Controls.Add(this.label23);
            this.groupBox1.Controls.Add(this.txtCorrRg);
            this.groupBox1.Controls.Add(this.label22);
            this.groupBox1.Controls.Add(this.txtCorrRd);
            this.groupBox1.Controls.Add(this.label21);
            this.groupBox1.Controls.Add(this.txtVitMax);
            this.groupBox1.Controls.Add(this.label19);
            this.groupBox1.Controls.Add(this.txtAccMax);
            this.groupBox1.Controls.Add(this.txtAsservTime);
            this.groupBox1.Controls.Add(this.txtMotMin);
            this.groupBox1.Controls.Add(this.txtCorrCentri);
            this.groupBox1.Controls.Add(this.txtMotMax);
            this.groupBox1.Location = new System.Drawing.Point(3, 284);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(620, 317);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Asservissement et localisation";
            // 
            // cbModealgo
            // 
            this.cbModealgo.FormattingEnabled = true;
            this.cbModealgo.Items.AddRange(new object[] {
            "Linéaire",
            "Circulaire"});
            this.cbModealgo.Location = new System.Drawing.Point(355, 289);
            this.cbModealgo.Name = "cbModealgo";
            this.cbModealgo.Size = new System.Drawing.Size(100, 21);
            this.cbModealgo.TabIndex = 88;
            this.cbModealgo.Text = "Linéaire";
            // 
            // lblLocal
            // 
            this.lblLocal.AutoSize = true;
            this.lblLocal.Location = new System.Drawing.Point(519, 266);
            this.lblLocal.Name = "lblLocal";
            this.lblLocal.Size = new System.Drawing.Size(42, 39);
            this.lblLocal.TabIndex = 87;
            this.lblLocal.Text = "Unread\r\n\r\nUnread";
            // 
            // lblAsserv
            // 
            this.lblAsserv.AutoSize = true;
            this.lblAsserv.Location = new System.Drawing.Point(519, 39);
            this.lblAsserv.Name = "lblAsserv";
            this.lblAsserv.Size = new System.Drawing.Size(42, 195);
            this.lblAsserv.TabIndex = 84;
            this.lblAsserv.Text = "Unread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nUnread\r\n\r\nUnread";
            // 
            // txtLocaTime
            // 
            this.txtLocaTime.Location = new System.Drawing.Point(355, 263);
            this.txtLocaTime.Name = "txtLocaTime";
            this.txtLocaTime.Size = new System.Drawing.Size(100, 20);
            this.txtLocaTime.TabIndex = 85;
            this.txtLocaTime.Text = "10";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(6, 266);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(188, 39);
            this.label23.TabIndex = 84;
            this.label23.Text = "Temps entre chaque localisation [ms] :\r\n\r\nMode d\'algorithmie :";
            // 
            // txtCorrRg
            // 
            this.txtCorrRg.Location = new System.Drawing.Point(355, 218);
            this.txtCorrRg.Name = "txtCorrRg";
            this.txtCorrRg.Size = new System.Drawing.Size(100, 20);
            this.txtCorrRg.TabIndex = 64;
            this.txtCorrRg.Text = "1000";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label22.Location = new System.Drawing.Point(5, 243);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(105, 20);
            this.label22.TabIndex = 83;
            this.label22.Text = "Localisation";
            // 
            // txtCorrRd
            // 
            this.txtCorrRd.Location = new System.Drawing.Point(355, 192);
            this.txtCorrRd.Name = "txtCorrRd";
            this.txtCorrRd.Size = new System.Drawing.Size(100, 20);
            this.txtCorrRd.TabIndex = 63;
            this.txtCorrRd.Text = "1000";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Dock = System.Windows.Forms.DockStyle.Top;
            this.label21.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label21.Location = new System.Drawing.Point(3, 16);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(135, 20);
            this.label21.TabIndex = 65;
            this.label21.Text = "Asservissement";
            // 
            // txtVitMax
            // 
            this.txtVitMax.Enabled = false;
            this.txtVitMax.Location = new System.Drawing.Point(355, 140);
            this.txtVitMax.Name = "txtVitMax";
            this.txtVitMax.Size = new System.Drawing.Size(100, 20);
            this.txtVitMax.TabIndex = 61;
            this.txtVitMax.Text = "1000";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(6, 39);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(314, 195);
            this.label19.TabIndex = 48;
            this.label19.Text = resources.GetString("label19.Text");
            // 
            // txtAccMax
            // 
            this.txtAccMax.Enabled = false;
            this.txtAccMax.Location = new System.Drawing.Point(355, 166);
            this.txtAccMax.Name = "txtAccMax";
            this.txtAccMax.Size = new System.Drawing.Size(100, 20);
            this.txtAccMax.TabIndex = 62;
            this.txtAccMax.Text = "1000";
            // 
            // txtAsservTime
            // 
            this.txtAsservTime.Location = new System.Drawing.Point(355, 36);
            this.txtAsservTime.Name = "txtAsservTime";
            this.txtAsservTime.Size = new System.Drawing.Size(100, 20);
            this.txtAsservTime.TabIndex = 57;
            this.txtAsservTime.Text = "1";
            // 
            // txtMotMin
            // 
            this.txtMotMin.Location = new System.Drawing.Point(355, 114);
            this.txtMotMin.Name = "txtMotMin";
            this.txtMotMin.Size = new System.Drawing.Size(100, 20);
            this.txtMotMin.TabIndex = 60;
            this.txtMotMin.Text = "500";
            // 
            // txtCorrCentri
            // 
            this.txtCorrCentri.Location = new System.Drawing.Point(355, 62);
            this.txtCorrCentri.Name = "txtCorrCentri";
            this.txtCorrCentri.Size = new System.Drawing.Size(100, 20);
            this.txtCorrCentri.TabIndex = 58;
            this.txtCorrCentri.Text = "0";
            // 
            // txtMotMax
            // 
            this.txtMotMax.Location = new System.Drawing.Point(355, 88);
            this.txtMotMax.Name = "txtMotMax";
            this.txtMotMax.Size = new System.Drawing.Size(100, 20);
            this.txtMotMax.TabIndex = 59;
            this.txtMotMax.Text = "1000";
            // 
            // SettingsDriverMot
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Silver;
            this.ClientSize = new System.Drawing.Size(934, 702);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.gbRobSettings);
            this.Controls.Add(this.mnu_Main);
            this.Controls.Add(this.grpPID);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "SettingsDriverMot";
            this.Text = "Settings (Driver Moteur)";
            this.grpPID.ResumeLayout(false);
            this.grpPID.PerformLayout();
            this.pnRegVit.ResumeLayout(false);
            this.pnRegVit.PerformLayout();
            this.mnu_Main.ResumeLayout(false);
            this.mnu_Main.PerformLayout();
            this.gbRobSettings.ResumeLayout(false);
            this.gbRobSettings.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grpPID;
        private System.Windows.Forms.TextBox txtIntegLimitDist;
        private System.Windows.Forms.TextBox txtKiDist;
        private System.Windows.Forms.TextBox txtKpDist;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lblPIDDist;
        private System.Windows.Forms.TextBox txtKdDist;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Panel pnRegVit;
        private System.Windows.Forms.TextBox txtKdRoueD;
        private System.Windows.Forms.TextBox txtIntegLimitRoueD;
        private System.Windows.Forms.TextBox txtKiRoueD;
        private System.Windows.Forms.TextBox txtKpRoueD;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label lblPIDRoueD;
        private System.Windows.Forms.TextBox txtKdRoueG;
        private System.Windows.Forms.TextBox txtIntegLimitRoueG;
        private System.Windows.Forms.TextBox txtKiRoueG;
        private System.Windows.Forms.TextBox txtKpRoueG;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label lblPIDRoueG;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txtKdOrient;
        private System.Windows.Forms.TextBox txtIntegLimitOrient;
        private System.Windows.Forms.TextBox txtKiOrient;
        private System.Windows.Forms.TextBox txtKpOrient;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label lblPIDOrient;
        private System.Windows.Forms.CheckBox cbPWMRoboteQ;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_readAll;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_WriteAll;
        private System.Windows.Forms.MenuStrip mnu_Main;
        private System.Windows.Forms.GroupBox gbRobSettings;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.TextBox txtIICRepeat;
        private System.Windows.Forms.TextBox txtIICWatchdog;
        private System.Windows.Forms.TextBox txtIICAddr;
        private System.Windows.Forms.TextBox txtUARTWatchdog;
        private System.Windows.Forms.TextBox txtUARTRepeat;
        private System.Windows.Forms.TextBox txtUARTAddr;
        private System.Windows.Forms.TextBox txtEntraxe;
        private System.Windows.Forms.TextBox txtDiamEnco;
        private System.Windows.Forms.TextBox txtNbreImpulses;
        private System.Windows.Forms.TextBox txtLocaTime;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.TextBox txtCorrRg;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.TextBox txtCorrRd;
        private System.Windows.Forms.TextBox txtVitMax;
        private System.Windows.Forms.TextBox txtAccMax;
        private System.Windows.Forms.TextBox txtAsservTime;
        private System.Windows.Forms.TextBox txtMotMin;
        private System.Windows.Forms.TextBox txtCorrCentri;
        private System.Windows.Forms.TextBox txtMotMax;
        private System.Windows.Forms.Label lblCaracRobot;
        private System.Windows.Forms.Label lblLocal;
        private System.Windows.Forms.Label lblAsserv;
        private System.Windows.Forms.ComboBox cbModealgo;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
    }
}