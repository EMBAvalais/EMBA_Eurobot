namespace Eurobot
{
    partial class RoboteQ
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(RoboteQ));
            this.mnu_Main = new System.Windows.Forms.MenuStrip();
            this.tlStrMnuItm_readAll = new System.Windows.Forms.ToolStripMenuItem();
            this.tlStrMnuItm_WriteAll = new System.Windows.Forms.ToolStripMenuItem();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.txtDEC1 = new System.Windows.Forms.TextBox();
            this.txtACC1 = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.txtKd2 = new System.Windows.Forms.TextBox();
            this.txtKi2 = new System.Windows.Forms.TextBox();
            this.txtKp2 = new System.Windows.Forms.TextBox();
            this.txtKd1 = new System.Windows.Forms.TextBox();
            this.txtKi1 = new System.Windows.Forms.TextBox();
            this.txtKp1 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.lblDCC1 = new System.Windows.Forms.Label();
            this.lblACC1 = new System.Windows.Forms.Label();
            this.labelkd2 = new System.Windows.Forms.Label();
            this.labelki2 = new System.Windows.Forms.Label();
            this.labelkp2 = new System.Windows.Forms.Label();
            this.labelkd1 = new System.Windows.Forms.Label();
            this.labelki1 = new System.Windows.Forms.Label();
            this.labelkp1 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.txtACC2 = new System.Windows.Forms.TextBox();
            this.txtDEC2 = new System.Windows.Forms.TextBox();
            this.lblACC2 = new System.Windows.Forms.Label();
            this.lblDCC2 = new System.Windows.Forms.Label();
            this.mnu_Main.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // mnu_Main
            // 
            this.mnu_Main.AutoSize = false;
            this.mnu_Main.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tlStrMnuItm_readAll,
            this.tlStrMnuItm_WriteAll});
            this.mnu_Main.Location = new System.Drawing.Point(0, 0);
            this.mnu_Main.Name = "mnu_Main";
            this.mnu_Main.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.mnu_Main.Size = new System.Drawing.Size(334, 26);
            this.mnu_Main.TabIndex = 1;
            this.mnu_Main.Text = "menuStrip1";
            // 
            // tlStrMnuItm_readAll
            // 
            this.tlStrMnuItm_readAll.Name = "tlStrMnuItm_readAll";
            this.tlStrMnuItm_readAll.Size = new System.Drawing.Size(84, 22);
            this.tlStrMnuItm_readAll.Text = "Read Config";
            this.tlStrMnuItm_readAll.Click += new System.EventHandler(this.tlStrMnuItm_readAll_Click);
            // 
            // tlStrMnuItm_WriteAll
            // 
            this.tlStrMnuItm_WriteAll.Name = "tlStrMnuItm_WriteAll";
            this.tlStrMnuItm_WriteAll.Size = new System.Drawing.Size(86, 22);
            this.tlStrMnuItm_WriteAll.Text = "Write Config";
            this.tlStrMnuItm_WriteAll.Click += new System.EventHandler(this.tlStrMnuItm_WriteAll_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Location = new System.Drawing.Point(12, 29);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.BackColor = System.Drawing.Color.CornflowerBlue;
            this.splitContainer1.Panel1.Controls.Add(this.txtDEC2);
            this.splitContainer1.Panel1.Controls.Add(this.txtACC2);
            this.splitContainer1.Panel1.Controls.Add(this.label10);
            this.splitContainer1.Panel1.Controls.Add(this.txtDEC1);
            this.splitContainer1.Panel1.Controls.Add(this.txtACC1);
            this.splitContainer1.Panel1.Controls.Add(this.label9);
            this.splitContainer1.Panel1.Controls.Add(this.label6);
            this.splitContainer1.Panel1.Controls.Add(this.label5);
            this.splitContainer1.Panel1.Controls.Add(this.label4);
            this.splitContainer1.Panel1.Controls.Add(this.txtKd2);
            this.splitContainer1.Panel1.Controls.Add(this.txtKi2);
            this.splitContainer1.Panel1.Controls.Add(this.txtKp2);
            this.splitContainer1.Panel1.Controls.Add(this.txtKd1);
            this.splitContainer1.Panel1.Controls.Add(this.txtKi1);
            this.splitContainer1.Panel1.Controls.Add(this.txtKp1);
            this.splitContainer1.Panel1.Controls.Add(this.label3);
            this.splitContainer1.Panel1.Controls.Add(this.label2);
            this.splitContainer1.Panel1.Controls.Add(this.label1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.splitContainer1.Panel2.Controls.Add(this.lblDCC2);
            this.splitContainer1.Panel2.Controls.Add(this.lblACC2);
            this.splitContainer1.Panel2.Controls.Add(this.lblDCC1);
            this.splitContainer1.Panel2.Controls.Add(this.lblACC1);
            this.splitContainer1.Panel2.Controls.Add(this.labelkd2);
            this.splitContainer1.Panel2.Controls.Add(this.labelki2);
            this.splitContainer1.Panel2.Controls.Add(this.labelkp2);
            this.splitContainer1.Panel2.Controls.Add(this.labelkd1);
            this.splitContainer1.Panel2.Controls.Add(this.labelki1);
            this.splitContainer1.Panel2.Controls.Add(this.labelkp1);
            this.splitContainer1.Panel2.Controls.Add(this.label8);
            this.splitContainer1.Panel2.Controls.Add(this.label7);
            this.splitContainer1.Size = new System.Drawing.Size(572, 350);
            this.splitContainer1.SplitterDistance = 189;
            this.splitContainer1.TabIndex = 2;
            // 
            // txtDEC1
            // 
            this.txtDEC1.Location = new System.Drawing.Point(76, 139);
            this.txtDEC1.Name = "txtDEC1";
            this.txtDEC1.Size = new System.Drawing.Size(100, 20);
            this.txtDEC1.TabIndex = 25;
            this.txtDEC1.Text = "0";
            // 
            // txtACC1
            // 
            this.txtACC1.Location = new System.Drawing.Point(76, 113);
            this.txtACC1.Name = "txtACC1";
            this.txtACC1.Size = new System.Drawing.Size(100, 20);
            this.txtACC1.TabIndex = 24;
            this.txtACC1.Text = "0";
            // 
            // label9
            // 
            this.label9.AutoEllipsis = true;
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(12, 273);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(48, 13);
            this.label9.TabIndex = 23;
            this.label9.Text = "Ac(*10) :";
            // 
            // label6
            // 
            this.label6.AutoEllipsis = true;
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 142);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(49, 13);
            this.label6.TabIndex = 22;
            this.label6.Text = "Dc(*10) :";
            // 
            // label5
            // 
            this.label5.AutoEllipsis = true;
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 116);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(48, 13);
            this.label5.TabIndex = 21;
            this.label5.Text = "Ac(*10) :";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 195);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(51, 65);
            this.label4.TabIndex = 10;
            this.label4.Text = "Kp (*10) :\r\n\r\nKi (*10) :\r\n\r\nKd (*10) :";
            // 
            // txtKd2
            // 
            this.txtKd2.Location = new System.Drawing.Point(76, 244);
            this.txtKd2.Name = "txtKd2";
            this.txtKd2.Size = new System.Drawing.Size(100, 20);
            this.txtKd2.TabIndex = 9;
            this.txtKd2.Text = "0";
            // 
            // txtKi2
            // 
            this.txtKi2.Location = new System.Drawing.Point(76, 218);
            this.txtKi2.Name = "txtKi2";
            this.txtKi2.Size = new System.Drawing.Size(100, 20);
            this.txtKi2.TabIndex = 8;
            this.txtKi2.Text = "0";
            // 
            // txtKp2
            // 
            this.txtKp2.Location = new System.Drawing.Point(76, 192);
            this.txtKp2.Name = "txtKp2";
            this.txtKp2.Size = new System.Drawing.Size(100, 20);
            this.txtKp2.TabIndex = 7;
            this.txtKp2.Text = "0";
            // 
            // txtKd1
            // 
            this.txtKd1.Location = new System.Drawing.Point(76, 85);
            this.txtKd1.Name = "txtKd1";
            this.txtKd1.Size = new System.Drawing.Size(100, 20);
            this.txtKd1.TabIndex = 6;
            this.txtKd1.Text = "0";
            // 
            // txtKi1
            // 
            this.txtKi1.Location = new System.Drawing.Point(76, 59);
            this.txtKi1.Name = "txtKi1";
            this.txtKi1.Size = new System.Drawing.Size(100, 20);
            this.txtKi1.TabIndex = 5;
            this.txtKi1.Text = "0";
            // 
            // txtKp1
            // 
            this.txtKp1.Location = new System.Drawing.Point(76, 33);
            this.txtKp1.Name = "txtKp1";
            this.txtKp1.Size = new System.Drawing.Size(100, 20);
            this.txtKp1.TabIndex = 4;
            this.txtKp1.Text = "0";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 36);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(51, 65);
            this.label3.TabIndex = 2;
            this.label3.Text = "Kp (*10) :\r\n\r\nKi (*10) :\r\n\r\nKd (*10) :";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(84, 160);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(80, 20);
            this.label2.TabIndex = 1;
            this.label2.Text = "Moteur 2";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(84, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(80, 20);
            this.label1.TabIndex = 0;
            this.label1.Text = "Moteur 1";
            // 
            // lblDCC1
            // 
            this.lblDCC1.AutoEllipsis = true;
            this.lblDCC1.AutoSize = true;
            this.lblDCC1.Location = new System.Drawing.Point(45, 134);
            this.lblDCC1.Name = "lblDCC1";
            this.lblDCC1.Size = new System.Drawing.Size(42, 26);
            this.lblDCC1.TabIndex = 22;
            this.lblDCC1.Text = "Unread\r\n\r\n";
            // 
            // lblACC1
            // 
            this.lblACC1.AutoEllipsis = true;
            this.lblACC1.AutoSize = true;
            this.lblACC1.Location = new System.Drawing.Point(45, 107);
            this.lblACC1.Name = "lblACC1";
            this.lblACC1.Size = new System.Drawing.Size(42, 26);
            this.lblACC1.TabIndex = 21;
            this.lblACC1.Text = "Unread\r\n\r\n";
            // 
            // labelkd2
            // 
            this.labelkd2.AutoEllipsis = true;
            this.labelkd2.AutoSize = true;
            this.labelkd2.Location = new System.Drawing.Point(45, 235);
            this.labelkd2.Name = "labelkd2";
            this.labelkd2.Size = new System.Drawing.Size(42, 26);
            this.labelkd2.TabIndex = 20;
            this.labelkd2.Text = "Unread\r\n\r\n";
            // 
            // labelki2
            // 
            this.labelki2.AutoEllipsis = true;
            this.labelki2.AutoSize = true;
            this.labelki2.Location = new System.Drawing.Point(45, 209);
            this.labelki2.Name = "labelki2";
            this.labelki2.Size = new System.Drawing.Size(42, 26);
            this.labelki2.TabIndex = 19;
            this.labelki2.Text = "Unread\r\n\r\n";
            // 
            // labelkp2
            // 
            this.labelkp2.AutoEllipsis = true;
            this.labelkp2.AutoSize = true;
            this.labelkp2.Location = new System.Drawing.Point(45, 186);
            this.labelkp2.Name = "labelkp2";
            this.labelkp2.Size = new System.Drawing.Size(42, 26);
            this.labelkp2.TabIndex = 18;
            this.labelkp2.Text = "Unread\r\n\r\n";
            // 
            // labelkd1
            // 
            this.labelkd1.AutoEllipsis = true;
            this.labelkd1.AutoSize = true;
            this.labelkd1.Location = new System.Drawing.Point(45, 85);
            this.labelkd1.Name = "labelkd1";
            this.labelkd1.Size = new System.Drawing.Size(42, 26);
            this.labelkd1.TabIndex = 17;
            this.labelkd1.Text = "Unread\r\n\r\n";
            // 
            // labelki1
            // 
            this.labelki1.AutoEllipsis = true;
            this.labelki1.AutoSize = true;
            this.labelki1.Location = new System.Drawing.Point(45, 59);
            this.labelki1.Name = "labelki1";
            this.labelki1.Size = new System.Drawing.Size(42, 26);
            this.labelki1.TabIndex = 16;
            this.labelki1.Text = "Unread\r\n\r\n";
            // 
            // labelkp1
            // 
            this.labelkp1.AutoEllipsis = true;
            this.labelkp1.AutoSize = true;
            this.labelkp1.Location = new System.Drawing.Point(45, 36);
            this.labelkp1.Name = "labelkp1";
            this.labelkp1.Size = new System.Drawing.Size(42, 26);
            this.labelkp1.TabIndex = 14;
            this.labelkp1.Text = "Unread\r\n\r\n";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(27, 10);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(80, 20);
            this.label8.TabIndex = 10;
            this.label8.Text = "Moteur 1";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(27, 160);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(80, 20);
            this.label7.TabIndex = 11;
            this.label7.Text = "Moteur 2";
            // 
            // label10
            // 
            this.label10.AutoEllipsis = true;
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(12, 299);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(49, 13);
            this.label10.TabIndex = 26;
            this.label10.Text = "Dc(*10) :";
            // 
            // txtACC2
            // 
            this.txtACC2.Location = new System.Drawing.Point(76, 270);
            this.txtACC2.Name = "txtACC2";
            this.txtACC2.Size = new System.Drawing.Size(100, 20);
            this.txtACC2.TabIndex = 27;
            this.txtACC2.Text = "0";
            // 
            // txtDEC2
            // 
            this.txtDEC2.Location = new System.Drawing.Point(76, 296);
            this.txtDEC2.Name = "txtDEC2";
            this.txtDEC2.Size = new System.Drawing.Size(100, 20);
            this.txtDEC2.TabIndex = 28;
            this.txtDEC2.Text = "0";
            // 
            // lblACC2
            // 
            this.lblACC2.AutoEllipsis = true;
            this.lblACC2.AutoSize = true;
            this.lblACC2.Location = new System.Drawing.Point(45, 260);
            this.lblACC2.Name = "lblACC2";
            this.lblACC2.Size = new System.Drawing.Size(42, 26);
            this.lblACC2.TabIndex = 23;
            this.lblACC2.Text = "Unread\r\n\r\n";
            // 
            // lblDCC2
            // 
            this.lblDCC2.AutoEllipsis = true;
            this.lblDCC2.AutoSize = true;
            this.lblDCC2.Location = new System.Drawing.Point(45, 286);
            this.lblDCC2.Name = "lblDCC2";
            this.lblDCC2.Size = new System.Drawing.Size(42, 26);
            this.lblDCC2.TabIndex = 24;
            this.lblDCC2.Text = "Unread\r\n\r\n";
            // 
            // RoboteQ
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
            this.ClientSize = new System.Drawing.Size(334, 361);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.mnu_Main);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(350, 400);
            this.MinimumSize = new System.Drawing.Size(350, 400);
            this.Name = "RoboteQ";
            this.Text = "RoboteQ";
            this.mnu_Main.ResumeLayout(false);
            this.mnu_Main.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.MenuStrip mnu_Main;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_readAll;
        private System.Windows.Forms.ToolStripMenuItem tlStrMnuItm_WriteAll;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.TextBox txtKd2;
        private System.Windows.Forms.TextBox txtKi2;
        private System.Windows.Forms.TextBox txtKp2;
        private System.Windows.Forms.TextBox txtKd1;
        private System.Windows.Forms.TextBox txtKi1;
        private System.Windows.Forms.TextBox txtKp1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label4;
        public System.Windows.Forms.Label labelkp1;
        public System.Windows.Forms.Label labelkd1;
        public System.Windows.Forms.Label labelki1;
        public System.Windows.Forms.Label labelkd2;
        public System.Windows.Forms.Label labelki2;
        public System.Windows.Forms.Label labelkp2;
        public System.Windows.Forms.Label label9;
        public System.Windows.Forms.Label label6;
        public System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtDEC1;
        private System.Windows.Forms.TextBox txtACC1;
        public System.Windows.Forms.Label lblDCC1;
        public System.Windows.Forms.Label lblACC1;
        private System.Windows.Forms.TextBox txtDEC2;
        private System.Windows.Forms.TextBox txtACC2;
        public System.Windows.Forms.Label label10;
        public System.Windows.Forms.Label lblDCC2;
        public System.Windows.Forms.Label lblACC2;

        public System.Windows.Forms.Control txtAC2 { get; set; }

        public System.Windows.Forms.Control txtAC1 { get; set; }
    }
}