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
        private string myConnectionString = "server=localhost;uid=root;pwd=;database=user_orders";

        //public User GetUser(string username, int password)
        //{
        //    User user = new User();
        //    try
        //    {
        //        conn = new MySqlConnection();
        //        conn.ConnectionString = myConnectionString;
        //        conn.Open();

        //        MySqlCommand cmd = new MySqlCommand();
        //        cmd.Connection = conn;

        //        string query = "SELECT * FROM users WHERE username=@username AND password=@password;";
        //        cmd.Parameters.AddWithValue("@username", username);
        //        cmd.Parameters.AddWithValue("@password", password);
        //        cmd.CommandText = query;

        //        MySqlDataReader reader = cmd.ExecuteReader();
        //        while (reader.Read())
        //        {
        //            user = new User
        //            {
        //                Id = reader.GetInt32("id"),
        //                Username = reader.GetString("username"),
        //                Password = reader.GetInt32("password"),
        //            };
        //        }

        //        reader.Close();
        //        conn.Close();
        //    }
        //    catch (MySqlException ex)
        //    {
        //        Console.WriteLine("Error: " + ex.Message);
        //    }
        //    return user;
        //}

        public List<Product> GetProducts()
        {
            List<Product> products = new List<Product>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM products;";
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    Product product = new Product
                    {
                        Id = reader.GetInt32("id"),
                        Name = reader.GetString("name"),
                        Price = reader.GetDecimal("price"),
                    };
                    products.Add(product);
                }

                reader.Close();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return products;
        }

        //    public List<Reservation> GetUserReservations(int id)
        //    {
        //        List<Reservation> reservations = new List<Reservation>();
        //        try
        //        {
        //            conn = new MySqlConnection();
        //            conn.ConnectionString = myConnectionString;
        //            conn.Open();

        //            MySqlCommand cmd = new MySqlCommand();
        //            cmd.Connection = conn;

        //            string query = "SELECT * FROM reservation WHERE u_id=@id;";
        //            cmd.CommandText = query;
        //            cmd.Parameters.AddWithValue("@id", id);

        //            MySqlDataReader reader = cmd.ExecuteReader();
        //            while (reader.Read())
        //            {
        //                Reservation reservation = new Reservation
        //                {
        //                    Id = reader.GetInt32("id"),
        //                    UserId = reader.GetInt32("u_id"),
        //                    RoomId = reader.GetInt32("r_id"),
        //                    CheckIn = DateOnly.FromDateTime(reader.GetDateTime("check_in")),
        //                    CheckOut = DateOnly.FromDateTime(reader.GetDateTime("check_out")),
        //                    Guests = reader.GetInt32("guests"),
        //                    Price = reader.GetInt32("price"),
        //                };
        //                reservations.Add(reservation);
        //            }

        //            reader.Close();
        //            conn.Close();
        //        }
        //        catch (MySqlException ex)
        //        {
        //            Console.WriteLine("Error: " + ex.Message);
        //        }
        //        return reservations;
        //    }

        public decimal SubmitOrder(string username, List<int> products)
        {
            int u_id = 0;
            decimal price = 0;
            Dictionary<string, int> categories = new Dictionary<string, int>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                MySqlDataReader reader;

                string select_user = "SELECT id FROM users WHERE username=@username;";
                cmd.CommandText = select_user;
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@username", username);

                reader = cmd.ExecuteReader();
                if (reader.Read())
                {
                    u_id = reader.GetInt32("id");
                }
                reader.Close();

                string select_price = "SELECT price, name FROM products WHERE id=@id;";
                foreach (int id in products)
                {
                    cmd.CommandText = select_price;
                    cmd.Parameters.Clear();
                    cmd.Parameters.AddWithValue("@id", id);

                    reader = cmd.ExecuteReader();
                    if (reader.Read())
                    {
                        price += reader.GetDecimal("price");
                        string name = reader.GetString("name");
                        var arr = name.Split("-");
                        if (categories.ContainsKey(arr[0]))
                        {
                            categories[arr[0]]+=1;
                        }
                        else
                        {
                            categories.Add(arr[0], 1);
                        }
                    }
                    reader.Close();
                }

                bool flag = false;
                foreach(var category in categories)
                {
                    if (category.Value >= 2)
                    {
                        flag = true;
                    }
                }

                decimal discount = 0;
                if(products.Count >= 3)
                {
                    discount += 10;
                }
                if (flag)
                {
                    discount += 5;
                }

                price -= discount / 100 * price;

                string insert_order = "INSERT INTO orders(u_id, price) VALUES (@u_id, @price);SELECT LAST_INSERT_ID();";
                cmd.CommandText = insert_order;
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@u_id", u_id);
                cmd.Parameters.AddWithValue("@price", price);
                var insertedId = Convert.ToInt32(cmd.ExecuteScalar());
                int o_id = insertedId;


                string insert_order_item = "INSERT INTO order_item(o_id, p_id) VALUES (@o_id, @p_id);";
                foreach(int id in products)
                {
                    cmd.Parameters.Clear();
                    cmd.CommandText = insert_order_item;
                    cmd.Parameters.AddWithValue("@o_id", o_id);
                    cmd.Parameters.AddWithValue("@p_id", id);
                    cmd.ExecuteNonQuery();
                }
                return price;

            }
            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex.Message);
                return price;
            }
        }

        public bool VerifyOrder(int product, string username)
        {
            int u_id = 0;
            List<int> orders = new List<int>();
            string category = "";
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                MySqlDataReader reader;

                string select_user = "SELECT id FROM users WHERE username=@username;";
                cmd.CommandText = select_user;
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@username", username);

                reader = cmd.ExecuteReader();
                if (reader.Read())
                {
                    u_id = reader.GetInt32("id");
                }
                reader.Close();

                string select_product_name = "SELECT name FROM products WHERE id=@id;";
                cmd.CommandText = select_product_name;
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@id", product);

                reader = cmd.ExecuteReader();
                if (reader.Read())
                {
                    category = (reader.GetString("name")).Split("-")[0];
                }
                reader.Close();

                string select_orders = "SELECT id FROM orders WHERE u_id=@u_id ORDER BY id DESC LIMIT 3;";
                cmd.CommandText = select_orders;
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@u_id", u_id);

                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    orders.Add(reader.GetInt32("id"));
                }
                reader.Close();

                string select_products = "SELECT p_id FROM order_item WHERE o_id=@o_id;";
                int count_category = 0;

                MySqlConnection conn1 = new MySqlConnection();
                conn1.ConnectionString = myConnectionString;
                MySqlCommand cmd1 = new MySqlCommand();
                foreach(int order in orders)
                {
                    int count_order = 0;
                    cmd.CommandText = select_products;
                    cmd.Parameters.Clear();
                    cmd.Parameters.AddWithValue("@o_id", order);

                    reader = cmd.ExecuteReader();
                    while (reader.Read())
                    {
                        conn1.Open();
                        cmd1.Connection = conn1;
                        int p_id = reader.GetInt32("p_id");
                        MySqlDataReader reader1;
                        cmd1.CommandText = select_product_name;
                        cmd1.Parameters.Clear();
                        cmd1.Parameters.AddWithValue("@id", p_id);
                        reader1 = cmd1.ExecuteReader();
                        if (reader1.Read())
                        {
                            string cat = (reader1.GetString("name")).Split("-")[0];
                            if(category == cat)
                            {
                                count_order = 1;
                            }
                        }
                        reader1.Close();
                        conn1.Close();
                    }
                    reader.Close();
                    count_category += count_order;
                }
                conn.Close();
                if (count_category == 3)
                {
                    return true;
                }
                return false;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex.Message);
                return false;
            }
        }

        //    //public List<string> VerifyFeedback(string message)
        //    //{
        //    //    List<string> words = new List<string>();
        //    //    try
        //    //    {
        //    //        conn = new MySqlConnection();
        //    //        conn.ConnectionString = myConnectionString;
        //    //        conn.Open();

        //    //        MySqlCommand cmd = new MySqlCommand();
        //    //        cmd.Connection = conn;

        //    //        string query = "SELECT pattern FROM blocked_words WHERE @message LIKE CONCAT('%', pattern, '%');";
        //    //        cmd.Parameters.AddWithValue("@message", message );
        //    //        cmd.CommandText = query;

        //    //        MySqlDataReader reader = cmd.ExecuteReader();
        //    //        while (reader.Read())
        //    //        {
        //    //            string word = reader.GetString("pattern");
        //    //            words.Add(word);
        //    //        }

        //    //        reader.Close();
        //    //        conn.Close();
        //    //    }
        //    //    catch (MySqlException ex)
        //    //    {
        //    //        Console.WriteLine("Error: " + ex.Message);
        //    //    }
        //    //    return words;
        //    //}
    }
}
