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


namespace Eurobot
{
    public class UpgradedDataGrid
    {
        string _fileName = null;

        DataGridView _DataGV;

        public UpgradedDataGrid(DataGridView myDataGridView)
        {
            _DataGV = myDataGridView;
            _DataGV.AllowDrop = true;

            _DataGV.DragDrop += new System.Windows.Forms.DragEventHandler(this.dataGV_DragDrop);
            _DataGV.DragOver += new System.Windows.Forms.DragEventHandler(this.dataGV_DragOver);
            _DataGV.MouseDown += new System.Windows.Forms.MouseEventHandler(this.dataGV_MouseDown);
            _DataGV.MouseMove += new System.Windows.Forms.MouseEventHandler(this.dataGV_MouseMove);
            _DataGV.MouseClick += new System.Windows.Forms.MouseEventHandler(this.dataGV_MouseClick);
        }

        int currentMouseOverRow = 0;
        int currentMouseOverCol = 0;

        private void dataGV_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                currentMouseOverRow = _DataGV.HitTest(e.X, e.Y).RowIndex;
                currentMouseOverCol = _DataGV.HitTest(e.X, e.Y).ColumnIndex;

                if (currentMouseOverRow >= 0)
                {
                    ContextMenu m = new ContextMenu();
                    m.MenuItems.Add(new MenuItem("Aller à"));
                    m.MenuItems.Add(new MenuItem("Insérer au dessus"));
                    m.MenuItems.Add(new MenuItem("Insérer au dessous"));
                    m.MenuItems.Add(new MenuItem("Supprimer"));

                    m.MenuItems[0].Click += new EventHandler(this.ContextMenuGoTo);
                    m.MenuItems[1].Click += new EventHandler(this.ContextMenuInsertUp);
                    m.MenuItems[2].Click += new EventHandler(this.ContextMenuInsertDown);
                    m.MenuItems[3].Click += new EventHandler(this.ContextMenuDelete);
                    m.Show(_DataGV, new Point(e.X, e.Y));
                }
            }
        }

        void ContextMenuGoTo(object sender, EventArgs e)
        {
            string dataToSend = "0|12|" + _DataGV.Rows[currentMouseOverRow].Cells[1].Value + "|" + _DataGV.Rows[currentMouseOverRow].Cells[2].Value + "@";
            //Form1.SendDataRS(dataToSend);
        }

        void ContextMenuInsertUp(object sender, EventArgs e)
        {
            _DataGV.Rows.Insert(currentMouseOverRow, 1);
        }

        void ContextMenuDelete(object sender, EventArgs e)
        {
            if (currentMouseOverRow < _DataGV.Rows.Count - 1)
                _DataGV.Rows.RemoveAt(currentMouseOverRow);
        }

        void ContextMenuInsertDown(object sender, EventArgs e)
        {
            if (currentMouseOverRow + 1 < _DataGV.Rows.Count)
                _DataGV.Rows.Insert(currentMouseOverRow + 1, 1);
        }

        public void AddSaveHandler(ToolStripMenuItem save, ToolStripMenuItem quickSave, ToolStripMenuItem load)
        {
            save.Click += new System.EventHandler(this.SaveToFile);
            quickSave.Click += new System.EventHandler(this.QuickSave);
            load.Click += new System.EventHandler(this.LoadFromFile);
        }

        /// ---------------------------------------------------------------------------------------
        /// 
        /// Permet d'effectuer des sauvegardes et des chargements de fichiers
        /// 

        // Chargement de fichier
        public void LoadFromFile(object sender, EventArgs e)
        {
            OpenFileDialog myDialog = new OpenFileDialog();

            myDialog.Title = "Choisissez un fichier de sauvegarde";
            myDialog.Filter = "Fichiers de sauvegarde|*.save";

            if (myDialog.ShowDialog() == DialogResult.OK)
            {
                string[] lines = File.ReadAllLines(myDialog.FileName);

                _fileName = myDialog.FileName;

                while (_DataGV.Rows.Count > 1)
                {
                    _DataGV.Rows.RemoveAt(0);
                }

                List<string[]> values = new List<string[]>();

                for (int i = 0; i < lines.Length; i++)
                {
                    values.Add(lines[i].Split('|'));
                }

                if (values.Count <= 0)
                    return;
                _DataGV.Rows.Add(values.Count);

                for (int row = 0; row < values.Count; row++)
                {
                    for (int col = 0; col < values[row].Length; col++)
                    {
                        if (_DataGV.ColumnCount > col)
                            _DataGV.Rows[row].Cells[col].Value = values[row][col];
                    }
                }
            }
        }

        // Sauvegarde de fichier: Enregistrer sous
        public void SaveToFile(object sender, EventArgs e)
        {
            SaveFileDialog myDialog = new SaveFileDialog();

            myDialog.Title = "Choisissez un fichier de sauvegarde";
            myDialog.Filter = "Fichiers de sauvegarde|*.save";

            if (myDialog.ShowDialog() == DialogResult.OK)
            {
                _fileName = myDialog.FileName;

                Save();
            }
        }

        // Sauvegarde de fichier: Enregistrer
        public void QuickSave(object sender, EventArgs e)
        {
            if (_fileName == null)
            {
                SaveToFile(null, null);
                return;
            }

            Save();
        }

        // Génération du fichier de sauvegarde
        void Save()
        {
            string[] lines = new string[_DataGV.Rows.Count - 1];
            List<string[]> values = new List<string[]>();

            for (int i = 0; i < _DataGV.Rows.Count - 1; i++)
            {
                values.Add(new string[_DataGV.Columns.Count]);
                for (int j = 0; j < _DataGV.Columns.Count; j++)
                {
                    if (_DataGV.Rows[i].Cells[j].Value != null)
                        values[i][j] = _DataGV.Rows[i].Cells[j].Value.ToString();
                }
                lines[i] = String.Join("|", values[i]);
            }

            File.WriteAllLines(_fileName, lines);
        }

        /// ---------------------------------------------------------------------------------------
        /// 
        /// Permet d'effectuer un drag and drop des lignes
        /// 

        private Rectangle dragBoxFromMouseDown;
        private int rowIndexFromMouseDown;
        private int rowIndexOfItemUnderMouseToDrop;

        private void dataGV_MouseMove(object sender, MouseEventArgs e)
        {
            if ((e.Button & MouseButtons.Left) == MouseButtons.Left)
            {
                // If the mouse moves outside the rectangle, start the drag.
                if (dragBoxFromMouseDown != Rectangle.Empty &&
                    !dragBoxFromMouseDown.Contains(e.X, e.Y))
                {

                    // Proceed with the drag and drop, passing in the list item.                    
                    DragDropEffects dropEffect = _DataGV.DoDragDrop(
                    _DataGV.Rows[rowIndexFromMouseDown],
                    DragDropEffects.Move);
                }
            }
        }

        private void dataGV_DragDrop(object sender, DragEventArgs e)
        {
            // The mouse locations are relative to the screen, so they must be 
            // converted to client coordinates.
            Point clientPoint = _DataGV.PointToClient(new Point(e.X, e.Y));

            // Get the row index of the item the mouse is below. 
            rowIndexOfItemUnderMouseToDrop =
                _DataGV.HitTest(clientPoint.X, clientPoint.Y).RowIndex;

            // If the drag operation was a move then remove and insert the row.
            if (e.Effect == DragDropEffects.Move && rowIndexOfItemUnderMouseToDrop < _DataGV.Rows.Count - 1
                && rowIndexOfItemUnderMouseToDrop >= 0 && rowIndexFromMouseDown != _DataGV.Rows.Count - 1)
            {
                DataGridViewRow rowToMove = e.Data.GetData(
                    typeof(DataGridViewRow)) as DataGridViewRow;
                _DataGV.Rows.RemoveAt(rowIndexFromMouseDown);
                _DataGV.Rows.Insert(rowIndexOfItemUnderMouseToDrop, rowToMove);
            }
        }

        private void dataGV_DragOver(object sender, DragEventArgs e)
        {
            e.Effect = DragDropEffects.Move;
        }

        private void dataGV_MouseDown(object sender, MouseEventArgs e)
        {
            // Get the index of the item the mouse is below.
            rowIndexFromMouseDown = _DataGV.HitTest(e.X, e.Y).RowIndex;
            if (rowIndexFromMouseDown != -1)
            {
                // Remember the point where the mouse down occurred. 
                // The DragSize indicates the size that the mouse can move 
                // before a drag event should be started.                
                Size dragSize = SystemInformation.DragSize;

                // Create a rectangle using the DragSize, with the mouse position being
                // at the center of the rectangle.
                dragBoxFromMouseDown = new Rectangle(new Point(e.X - (dragSize.Width / 2),
                                                               e.Y - (dragSize.Height / 2)),
                                    dragSize);
            }
            else
                // Reset the rectangle if the mouse is not over an item in the ListBox.
                dragBoxFromMouseDown = Rectangle.Empty;
        }
    }
}
