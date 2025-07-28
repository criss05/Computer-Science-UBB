namespace Lab2
{
    partial class Form1
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
            this.saveButton = new System.Windows.Forms.Button();
            this.ParentDataGrid = new System.Windows.Forms.DataGridView();
            this.childDataGrid = new System.Windows.Forms.DataGridView();
            ((System.ComponentModel.ISupportInitialize)(this.ParentDataGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.childDataGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // saveButton
            // 
            this.saveButton.Location = new System.Drawing.Point(505, 420);
            this.saveButton.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(100, 28);
            this.saveButton.TabIndex = 2;
            this.saveButton.Text = "Save";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.saveButton_Click);
            // 
            // ParentDataGrid
            // 
            this.ParentDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ParentDataGrid.Location = new System.Drawing.Point(16, 15);
            this.ParentDataGrid.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.ParentDataGrid.Name = "ParentDataGrid";
            this.ParentDataGrid.RowHeadersWidth = 51;
            this.ParentDataGrid.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.ParentDataGrid.Size = new System.Drawing.Size(1073, 204);
            this.ParentDataGrid.TabIndex = 3;
            this.ParentDataGrid.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.groupDataGrid_CellContentClick);
            // 
            // childDataGrid
            // 
            this.childDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.childDataGrid.Location = new System.Drawing.Point(16, 241);
            this.childDataGrid.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.childDataGrid.Name = "childDataGrid";
            this.childDataGrid.RowHeadersWidth = 51;
            this.childDataGrid.Size = new System.Drawing.Size(1073, 171);
            this.childDataGrid.TabIndex = 4;
            this.childDataGrid.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.studentDataGrid_CellContentClick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1105, 450);
            this.Controls.Add(this.childDataGrid);
            this.Controls.Add(this.ParentDataGrid);
            this.Controls.Add(this.saveButton);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.ParentDataGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.childDataGrid)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.DataGridView ParentDataGrid;
        private System.Windows.Forms.DataGridView childDataGrid;
    }
}

