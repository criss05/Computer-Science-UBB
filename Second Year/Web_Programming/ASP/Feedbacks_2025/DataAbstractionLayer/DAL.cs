using Lab10.Models;
using Microsoft.VisualBasic;
using MySql.Data.MySqlClient;
using System.Globalization;
using System.Threading.Channels;
using System.Xml.Linq;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace Lab10.DataAbstractionLayer
{
    public class DAL
    {
        private MySqlConnection conn;
        private string myConnectionString = "server=localhost;uid=root;pwd=;database=feedback_db";

        public Customer GetCustomer(string name, string email)
        {
            Customer customer = new Customer();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM customer WHERE name=@name AND email=@email;";
                cmd.Parameters.AddWithValue("@name", name);
                cmd.Parameters.AddWithValue("@email", email);
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    customer = new Customer
                    {
                        Id = reader.GetInt32("id"),
                        Name = reader.GetString("name"),
                        Email = reader.GetString("email"),
                    };
                }

                reader.Close();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return customer;
        }

        public List<Feedback> GetFeedbacks()
        {
            List<Feedback> feedbacks = new List<Feedback>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM feedback;";
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while(reader.Read())
                {
                    Feedback feedback = new Feedback
                    {
                        Id = reader.GetInt32("id"),
                        CustomerId = reader.GetInt32("customer_id"),
                        Message = reader.GetString("message"),
                        Timestamp = reader.GetDateTime("timestamp"),
                    };
                    feedbacks.Add(feedback);
                }

                reader.Close();
                conn.Close();
            }
            catch(MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return feedbacks;
        }

        public bool AddFeedback(string message, int customerId)
        {
            int insertedId = 0;
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "INSERT INTO feedback(customer_id, message) VALUES (@customer, @message);SELECT LAST_INSERT_ID();";
                cmd.Parameters.AddWithValue("@customer", customerId);
                cmd.Parameters.AddWithValue("@message", message);
                cmd.CommandText = query;
                insertedId = Convert.ToInt32(cmd.ExecuteScalar());
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return insertedId != 0;
        }


        public List<string> VerifyFeedback(string message)
        {
            List<string> words = new List<string>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT pattern FROM blocked_words WHERE @message LIKE CONCAT('%', pattern, '%');";
                cmd.Parameters.AddWithValue("@message", message );
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    string word = reader.GetString("pattern");
                    words.Add(word);
                }

                reader.Close();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return words;
        }
    }
}
