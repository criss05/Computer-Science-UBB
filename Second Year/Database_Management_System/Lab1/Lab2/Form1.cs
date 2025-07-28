using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab2
{
    public partial class Form1 : Form
    { 
        SqlConnection connection;
        SqlDataAdapter adapterParent;
        SqlDataAdapter adapterChild;
        DataSet dataset;
        BindingSource bindingSourceParent;
        BindingSource bindingSourceChild;

        SqlCommandBuilder commandBuilderChild;

        string connectionString = "The connection string";

        string queryParent;
        string queryChild;

        public Form1()
        {
            InitializeComponent();
            loadAll();
        }


        private void loadAll()
        {
            try
            {
                connection = new SqlConnection(connectionString);
                queryParent = "Select * from Grupe";
                queryChild = "Select * from Elevi";

                adapterParent = new SqlDataAdapter(queryParent, connection);
                adapterChild = new SqlDataAdapter(queryChild, connection);

                dataset = new DataSet();

                adapterParent.Fill(dataset, "Grupe");
                adapterChild.Fill(dataset, "Elevi");

                commandBuilderChild = new SqlCommandBuilder(adapterChild);

                dataset.Relations.Add("Grupe_Elevi", dataset.Tables["Grupe"].Columns["Id"], dataset.Tables["Elevi"].Columns["Grupa"]);

                bindingSourceParent = new BindingSource();
                bindingSourceParent.DataSource = dataset.Tables["Grupe"];

                bindingSourceChild = new BindingSource(bindingSourceParent, "Grupe_Elevi");

                ParentDataGrid.DataSource = bindingSourceParent;
                childDataGrid.DataSource = bindingSourceChild;

                commandBuilderChild.GetUpdateCommand();
            }
            catch (SqlException e)
            {
                MessageBox.Show("Database error: " + e.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (Exception e)
            {
                MessageBox.Show("Error: " + e.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }


        private void saveButton_Click(object sender, EventArgs e)
        {
            try
            {
                adapterChild.Update(dataset, "Elevi");
                loadAll();
            }
            catch (SqlException ex)
            {
                MessageBox.Show("Database error: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void groupDataGrid_CellContentClick(object sender, DataGridViewCellEventArgs e) { }
        private void studentDataGrid_CellContentClick(object sender, DataGridViewCellEventArgs e) { }
        private void Form1_Load(object sender, EventArgs e) { }
    }
}
