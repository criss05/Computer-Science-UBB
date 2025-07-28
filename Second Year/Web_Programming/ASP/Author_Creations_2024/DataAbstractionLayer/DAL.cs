using Lab10.Models;
using Microsoft.VisualBasic;
using MySql.Data.MySqlClient;
using Org.BouncyCastle.Crypto;
using System.Globalization;
using System.Threading.Channels;
using System.Xml.Linq;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace Lab10.DataAbstractionLayer
{
    public class DAL
    {
        private MySqlConnection conn;
        private string myConnectionString = "server=localhost;uid=root;pwd=;database=user_movies_documents";

        public Author GetAuthor(string name, string creation)
        {
            Author author = new Author();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM author WHERE name=@name AND (movies_list LIKE @creation OR documents_list LIKE @creation);";
                cmd.Parameters.AddWithValue("@name", name);
                cmd.Parameters.AddWithValue("@creation", "%" + creation + "%");
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    author = new Author
                    {
                        Id = reader.GetInt32("id"),
                        Name = reader.GetString("name"),
                        Movies = reader.GetString("movies_list"),
                        Documents = reader.GetString("documents_list"),
                    };
                }

                reader.Close();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return author;
        }

        //public List<Product> GetProducts()
        //{
        //    List<Product> products = new List<Product>();
        //    try
        //    {
        //        conn = new MySqlConnection();
        //        conn.ConnectionString = myConnectionString;
        //        conn.Open();

        //        MySqlCommand cmd = new MySqlCommand();
        //        cmd.Connection = conn;

        //        string query = "SELECT * FROM products;";
        //        cmd.CommandText = query;

        //        MySqlDataReader reader = cmd.ExecuteReader();
        //        while (reader.Read())
        //        {
        //            Product product = new Product
        //            {
        //                Id = reader.GetInt32("id"),
        //                Name = reader.GetString("name"),
        //                Price = reader.GetDecimal("price"),
        //            };
        //            products.Add(product);
        //        }

        //        reader.Close();
        //        conn.Close();
        //    }
        //    catch (MySqlException ex)
        //    {
        //        Console.WriteLine("Error: " + ex.Message);
        //    }
        //    return products;
        //}

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

        public void AddDocument(string name, string author, string contents)
        {
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                MySqlDataReader reader;

                string insert_document = "INSERT INTO documents(name, contents) VALUES (@name, @contents);";
                cmd.CommandText = insert_document;
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@name", name);
                cmd.Parameters.AddWithValue("@contents", contents);
                cmd.ExecuteNonQuery();

                string update_author = "UPDATE author SET documents_list = CONCAT(documents_list, @document) WHERE name=@author;";
                cmd.Parameters.Clear();
                cmd.CommandText = update_author;
                cmd.Parameters.AddWithValue("@document", ","+name);
                cmd.Parameters.AddWithValue("@author", author);
                cmd.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
        }

        //public bool VerifyOrder(int product, string username)
        //{
        //    int u_id = 0;
        //    List<int> orders = new List<int>();
        //    string category = "";
        //    try
        //    {
        //        conn = new MySqlConnection();
        //        conn.ConnectionString = myConnectionString;
        //        conn.Open();

        //        MySqlCommand cmd = new MySqlCommand();
        //        cmd.Connection = conn;
        //        MySqlDataReader reader;

        //        string select_user = "SELECT id FROM users WHERE username=@username;";
        //        cmd.CommandText = select_user;
        //        cmd.Parameters.Clear();
        //        cmd.Parameters.AddWithValue("@username", username);

        //        reader = cmd.ExecuteReader();
        //        if (reader.Read())
        //        {
        //            u_id = reader.GetInt32("id");
        //        }
        //        reader.Close();

        //        string select_product_name = "SELECT name FROM products WHERE id=@id;";
        //        cmd.CommandText = select_product_name;
        //        cmd.Parameters.Clear();
        //        cmd.Parameters.AddWithValue("@id", product);

        //        reader = cmd.ExecuteReader();
        //        if (reader.Read())
        //        {
        //            category = (reader.GetString("name")).Split("-")[0];
        //        }
        //        reader.Close();

        //        string select_orders = "SELECT id FROM orders WHERE u_id=@u_id ORDER BY id DESC LIMIT 3;";
        //        cmd.CommandText = select_orders;
        //        cmd.Parameters.Clear();
        //        cmd.Parameters.AddWithValue("@u_id", u_id);

        //        reader = cmd.ExecuteReader();
        //        while (reader.Read())
        //        {
        //            orders.Add(reader.GetInt32("id"));
        //        }
        //        reader.Close();

        //        string select_products = "SELECT p_id FROM order_item WHERE o_id=@o_id;";
        //        int count_category = 0;

        //        MySqlConnection conn1 = new MySqlConnection();
        //        conn1.ConnectionString = myConnectionString;
        //        MySqlCommand cmd1 = new MySqlCommand();
        //        foreach(int order in orders)
        //        {
        //            int count_order = 0;
        //            cmd.CommandText = select_products;
        //            cmd.Parameters.Clear();
        //            cmd.Parameters.AddWithValue("@o_id", order);

        //            reader = cmd.ExecuteReader();
        //            while (reader.Read())
        //            {
        //                conn1.Open();
        //                cmd1.Connection = conn1;
        //                int p_id = reader.GetInt32("p_id");
        //                MySqlDataReader reader1;
        //                cmd1.CommandText = select_product_name;
        //                cmd1.Parameters.Clear();
        //                cmd1.Parameters.AddWithValue("@id", p_id);
        //                reader1 = cmd1.ExecuteReader();
        //                if (reader1.Read())
        //                {
        //                    string cat = (reader1.GetString("name")).Split("-")[0];
        //                    if(category == cat)
        //                    {
        //                        count_order = 1;
        //                    }
        //                }
        //                reader1.Close();
        //                conn1.Close();
        //            }
        //            reader.Close();
        //            count_category += count_order;
        //        }
        //        conn.Close();
        //        if (count_category == 3)
        //        {
        //            return true;
        //        }
        //        return false;
        //    }
        //    catch (Exception ex)
        //    {
        //        Console.WriteLine("Error: " + ex.Message);
        //        return false;
        //    }
        //}

        public List<Movie> GetMovies(string name)
        {
            List<Movie> movies = new List<Movie>();
            List<string> movie_names = new List<string>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT movies_list FROM author WHERE name = @name;";
                cmd.Parameters.AddWithValue("@name", name);
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    string m_list = reader.GetString("movies_list");
                    var arr = m_list.Split(",");
                    foreach(string m in arr)
                    {
                        movie_names.Add(m);
                    }
                }
                reader.Close();


                string select_movie = "SELECT * FROM movies WHERE title = @name;";
                cmd.Parameters.Clear();
                foreach(string m_name in movie_names)
                {
                    cmd.Parameters.Clear();
                    cmd.Parameters.AddWithValue("@name", m_name);
                    cmd.CommandText = select_movie;

                    reader = cmd.ExecuteReader();
                    while (reader.Read())
                    {
                        Movie m = new Movie
                        {
                            Id = reader.GetInt32("id"),
                            Title = reader.GetString("title"),
                            Duration = reader.GetInt32("duration")
                        };
                        movies.Add(m);
                    }
                    reader.Close();
                }

                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return movies;
        }

        public List<Document> GetDocuments(string name)
        {
            List<Document> documents = new List<Document>();
            List<string> document_names = new List<string>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT documents_list FROM author WHERE name = @name;";
                cmd.Parameters.AddWithValue("@name", name);
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    string d_list = reader.GetString("documents_list");
                    var arr = d_list.Split(",");
                    foreach (string d in arr)
                    {
                        document_names.Add(d);
                    }
                }
                reader.Close();


                string select_document = "SELECT * FROM documents WHERE name = @name;";
                cmd.Parameters.Clear();
                foreach (string d_name in document_names)
                {
                    cmd.Parameters.Clear();
                    cmd.Parameters.AddWithValue("@name", d_name);
                    cmd.CommandText = select_document;

                    reader = cmd.ExecuteReader();
                    while (reader.Read())
                    {
                        Document d = new Document
                        {
                            Id = reader.GetInt32("id"),
                            Name = reader.GetString("name"),
                            Contents = reader.GetString("contents")
                        };
                        documents.Add(d);
                    }
                    reader.Close();
                }

                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return documents;
        }

        public void DeleteDocument(int id, string author)
        {
            string name = "";
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                MySqlDataReader reader;

                string select_document = "SELECT name FROM documents WHERE id = @id;";
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@id", id);
                cmd.CommandText = select_document;

                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    name = reader.GetString("name");
                }
                reader.Close();

                string delete_document = "DELETE FROM documents WHERE id=@id;";
                cmd.CommandText = delete_document;
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@id", id);
                cmd.ExecuteNonQuery();


                string update_author = "UPDATE author SET documents_list = REPLACE(documents_list, @name, '') WHERE name=@author;";
                cmd.Parameters.Clear();
                cmd.CommandText = update_author;
                cmd.Parameters.AddWithValue("@name", name);
                cmd.Parameters.AddWithValue("@author", author);
                cmd.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
        }

        public void DeleteMovie(int id, string author)
        {
            string name = "";
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                MySqlDataReader reader;

                string select_movie = "SELECT title FROM movies WHERE id = @id;";
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@id", id);
                cmd.CommandText = select_movie;

                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    name = reader.GetString("title");
                }
                reader.Close();

                string delete_movie = "DELETE FROM movies WHERE id=@id;";
                cmd.CommandText = delete_movie;
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@id", id);
                cmd.ExecuteNonQuery();


                string update_author = "UPDATE author SET movies_list = REPLACE(movies_list, @name, '') WHERE name=@author;";
                cmd.Parameters.Clear();
                cmd.CommandText = update_author;
                cmd.Parameters.AddWithValue("@name", name);
                cmd.Parameters.AddWithValue("@author", author);
                cmd.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
        }

        public string GetLargestNrAuthors()
        {
            string document = "";
            Dictionary<string, int> documents = new Dictionary<string, int>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT documents_list FROM author;";
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    string d_list = reader.GetString("documents_list");
                    var arr = d_list.Split(",");
                    foreach (string d in arr)
                    {
                        if (documents.ContainsKey(d))
                        {
                            documents[d] += 1;
                        }
                        else
                        {
                            documents.Add(d, 0);
                        }
                    }
                }
                reader.Close();

                int val = documents.Values.Max();

                document = documents.MaxBy(entry => entry.Value).Key;
                
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return document;
        }
    }
}
