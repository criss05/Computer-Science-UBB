namespace Lab1
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
            this.CheckConnection = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // CheckConnection
            // 
            this.CheckConnection.BackColor = System.Drawing.SystemColors.Info;
            this.CheckConnection.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.CheckConnection.Location = new System.Drawing.Point(315, 133);
            this.CheckConnection.Name = "CheckConnection";
            this.CheckConnection.Size = new System.Drawing.Size(195, 85);
            this.CheckConnection.TabIndex = 0;
            this.CheckConnection.Text = "Check Connection";
            this.CheckConnection.UseVisualStyleBackColor = false;
            this.CheckConnection.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.CheckConnection);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button CheckConnection;
    }
}

