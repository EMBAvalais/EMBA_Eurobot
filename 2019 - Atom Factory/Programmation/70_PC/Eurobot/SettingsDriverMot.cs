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
    public partial class SettingsDriverMot : Form
    {
        public SettingsDriverMot()
        {
            InitializeComponent();
        }

        private void cbPWMRoboteQ_CheckedChanged(object sender, EventArgs e)
        {
            pnRegVit.Enabled = cbPWMRoboteQ.Checked;
        }

        private void tlStrMnuItm_WriteAll_Click(object sender, EventArgs e)
        {
            Form1 Form1 = (Form1)this.Owner;
            try
            {
                string Error24 = "La valeur ne peut pas dépasser 24 bits - 16777215.\rCeci est dû au byte phantôme lors de la mémorisation en flash sur le dsPic.\rIl n'est pas géré sur les cartes.";
                // On passe toutes les valeurs dans des variables, histoire de tester si ce sont bien des valeurs.
                // Il faudrait tester et envoyer un message d'erreur au cas par cas.
                string ToSend = Form1.DriverAdr + " 4 ";
                UInt32 Val = Convert.ToUInt32(txtDiamEnco.Text);
                if (Val > 16777215) throw new Exception(Error24);
                UInt16 Val1 = Convert.ToUInt16(txtNbreImpulses.Text);
                Val = Convert.ToUInt32(txtEntraxe.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtUARTAddr.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val1 = Convert.ToUInt16(txtUARTWatchdog.Text);
                Val1 = Convert.ToUInt16(txtUARTRepeat.Text);
                Val1 = Convert.ToUInt16(txtIICAddr.Text);
                if (Val1 % 2 != 0) throw new Exception("L'adresse IIC n'est pas paire !");
                Val1 = Convert.ToUInt16(txtIICWatchdog.Text);
                Val1 = Convert.ToUInt16(txtIICRepeat.Text);
                Val1 = Convert.ToUInt16(txtAsservTime.Text);
                Val = Convert.ToUInt32(txtCorrCentri.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val1 = Convert.ToUInt16(txtMotMax.Text);
                if (cbPWMRoboteQ.Checked && Val1 > 2399) throw new Exception("La valeur maximale du moteur dépasse 2399 (PWMs) !");
                else if (!cbPWMRoboteQ.Checked && Val1 > 1000) throw new Exception("La valeur maximale du moteur dépasse 1000 (RoboteQ) !");
                Val1 = Convert.ToUInt16(txtMotMin.Text);
                if (Val1 > Convert.ToUInt16(txtMotMax.Text)) throw new Exception("La valeur minimale du moteur dépasse la valeur maximale définie !");
                Val = Convert.ToUInt32(txtVitMax.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtAccMax.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtCorrRd.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtCorrRg.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val1 = Convert.ToUInt16(txtLocaTime.Text);
                ToSend += txtDiamEnco.Text + " " + txtNbreImpulses.Text + " " + txtEntraxe.Text + " " + txtUARTAddr.Text + " " + txtUARTWatchdog.Text + " " + txtUARTRepeat.Text + " " + txtIICAddr.Text + " " + txtIICWatchdog.Text + " " + txtIICRepeat.Text + " " + txtAsservTime.Text + " " + txtCorrCentri.Text + " " + txtMotMax.Text + " " + txtMotMin.Text + " " + txtVitMax.Text + " " + txtAccMax.Text + " " + txtCorrRd.Text + " " + txtCorrRg.Text + " " + txtLocaTime.Text;
                if (cbModealgo.SelectedIndex == 0) ToSend += " 0 ";
                else if (cbModealgo.SelectedIndex == 1) ToSend += " 1 ";
                else throw new Exception("Arrête de jouer avec le mode d'algorithmie et choisi dans la liste déroulante !");
                Val = Convert.ToUInt32(txtKpDist.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtKiDist.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtIntegLimitDist.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtKdDist.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtKpOrient.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtKiOrient.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtIntegLimitOrient.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtKdOrient.Text);
                if (Val > 16777215) throw new Exception(Error24);
                ToSend+=txtKpDist.Text+" "+txtKiDist.Text+" "+txtIntegLimitDist.Text+" "+txtKdDist.Text+" "+txtKpOrient.Text+" "+txtKiOrient.Text+" "+txtIntegLimitOrient.Text+" "+txtKdOrient.Text;
                if (cbPWMRoboteQ.Checked) ToSend += " 0 ";
                else ToSend += " 1 ";
                Val = Convert.ToUInt32(txtKpRoueG.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtKiRoueG.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtIntegLimitRoueG.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtKdRoueG.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtKpRoueD.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtKiRoueD.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtIntegLimitRoueD.Text);
                if (Val > 16777215) throw new Exception(Error24);
                Val = Convert.ToUInt32(txtKdRoueD.Text);
                if (Val > 16777215) throw new Exception(Error24);
                ToSend+=txtKpRoueG.Text+" "+txtKiRoueG.Text+" "+txtIntegLimitRoueG.Text+" "+txtKdRoueG.Text+" "+txtKpRoueD.Text+" "+txtKiRoueD.Text+" "+txtIntegLimitRoueD.Text+" "+txtKdRoueD.Text;
                // Si tout est OK, on affiche un message de confirmation
                if ((MessageBox.Show("Configurer le driver moteur le fera redémarrer. Êtes-vous sûr de vouloir envoyer la configuration ?", "Envoi de la configuration",
                MessageBoxButtons.YesNo, MessageBoxIcon.Warning)) == DialogResult.Yes)
                {
                    // Envoi
                    try
                    {
                        Form1.SendDataRS(ToSend);
                    }
                    catch { }
                }
            }
            catch (Exception ui)
            {
                MessageBox.Show("Erreur dans l'une des cases (! toutes les erreurs ne sont pas encore gérées !). \rContrôlez que les valeurs soient bien entières, positives, et définies dans leurs champs de valeurs possibles. \r\r Erreur : \r" + ui.ToString(), "Erreur de valeur");
                MessageBox.Show("La configuration n'a pas été envoyée !", "Configuration non transmise");
            }
        }

    }
}
