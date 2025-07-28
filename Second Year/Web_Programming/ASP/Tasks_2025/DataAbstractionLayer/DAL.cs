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
        private string myConnectionString = "server=localhost;uid=root;pwd=;database=exam_db";

        public User GetUser(string name)
        {
            User user = new User();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM users WHERE username=@name;";
                cmd.Parameters.AddWithValue("@name", name);
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    user = new User
                    {
                        Id = reader.GetInt32("id"),
                        Username = reader.GetString("username"),
                    };
                }

                reader.Close();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return user;
        }

        public List<Models.Task> GetToDoTasks()
        {
            List<Models.Task> tasks = new List<Models.Task>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM task WHERE status=\"todo\";";
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while(reader.Read())
                {
                    Models.Task task = new Models.Task
                    {
                        Id = reader.GetInt32("id"),
                        Title = reader.GetString("title"),
                        Status = reader.GetString("status"),
                        UserId = reader.GetInt32("assigned_to"),
                        Updated = reader.GetDateTime("last_updated"),
                    };
                    tasks.Add(task);
                }

                reader.Close();
                conn.Close();
            }
            catch(MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return tasks;
        }

        public List<Models.Task> GetInProgressTasks()
        {
            List<Models.Task> tasks = new List<Models.Task>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM task WHERE status=\"in_progress\";";
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    Models.Task task = new Models.Task
                    {
                        Id = reader.GetInt32("id"),
                        Title = reader.GetString("title"),
                        Status = reader.GetString("status"),
                        UserId = reader.GetInt32("assigned_to"),
                        Updated = reader.GetDateTime("last_updated"),
                    };
                    tasks.Add(task);
                }

                reader.Close();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return tasks;
        }

        public List<Models.Task> GetDoneTasks()
        {
            List<Models.Task> tasks = new List<Models.Task>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM task WHERE status=\"done\";";
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    Models.Task task = new Models.Task
                    {
                        Id = reader.GetInt32("id"),
                        Title = reader.GetString("title"),
                        Status = reader.GetString("status"),
                        UserId = reader.GetInt32("assigned_to"),
                        Updated = reader.GetDateTime("last_updated"),
                    };
                    tasks.Add(task);
                }

                reader.Close();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return tasks;
        }

        public List<Channels> GetSubscribedChannels(string name)
        {
            List<Channels> channels = new List<Channels>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM channels WHERE subscribers LIKE @sub;";
                cmd.Parameters.AddWithValue("@sub", "%" + name +"%");
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    Channels channel = new Channels
                    {
                        Id = reader.GetInt32("id"),
                        Name = reader.GetString("name"),
                        Description = reader.GetString("description"),
                        Subscribers = reader.GetString("subscribers")
                    };
                    channels.Add(channel);
                }

                reader.Close();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return channels;
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

        public void UpdateStatus(string status, int id)
        {
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "UPDATE task SET status=@status WHERE id=@id;";
                cmd.Parameters.AddWithValue("@status", status);
                cmd.Parameters.AddWithValue("@id", id);
                cmd.CommandText = query;
                cmd.ExecuteNonQuery();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
        }

        public void InsertLog(int task, int user, string new_status)
        {
            try
            {
                string old_status = "";
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT status FROM task WHERE id=@id;";
                cmd.Parameters.AddWithValue("@id", task);
                cmd.CommandText = query;
                MySqlDataReader reader = cmd.ExecuteReader();

                if (reader.Read())
                {
                    old_status = reader.GetString("status");
                }
                reader.Close();

                query = "INSERT INTO task_log(task_id, user_id, old_status, new_status) VALUES (@task, @user, @old, @new);";
                cmd.Parameters.AddWithValue("@task", task);
                cmd.Parameters.AddWithValue("@user", user);
                cmd.Parameters.AddWithValue("@old", old_status);
                cmd.Parameters.AddWithValue("@new", new_status);
                cmd.CommandText = query;
                cmd.ExecuteNonQuery();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
        }

        public string GetLastModifiedUser()
        {
            string username = "";
            int user_id=0;
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT user_id FROM task_log ORDER BY timestamp DESC Limit 1;";
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                if (reader.Read())
                {
                   user_id = reader.GetInt32("user_id");
                }

                reader.Close();
                if (user_id != 0)
                {
                    query = "SELECT username FROM users WHERE @id=id;";
                    cmd.Parameters.AddWithValue("@id", user_id);
                    cmd.CommandText = query;

                    MySqlDataReader reader1 = cmd.ExecuteReader();
                    if (reader1.Read())
                    {
                        username = reader1.GetString("username");
                    }
                }
               

                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return username;
        }

        //public List<Hotel> GetHotels(DateOnly date, string city)
        //{
        //    List<Hotel> hotels = new List<Hotel>();
        //    try
        //    {
        //        conn = new MySqlConnection();
        //        conn.ConnectionString = myConnectionString;
        //        conn.Open();

        //        MySqlCommand cmd = new MySqlCommand();
        //        cmd.Connection = conn;

        //        string query = "SELECT * FROM hotels WHERE h_date = @date AND h_city = @city AND h_available_rooms>0;";
        //        cmd.Parameters.AddWithValue("@date", date.ToDateTime(TimeOnly.MinValue));
        //        cmd.Parameters.AddWithValue("@city", city);
        //        cmd.CommandText = query;

        //        MySqlDataReader reader = cmd.ExecuteReader();
        //        while (reader.Read())
        //        {
        //            Hotel hotel = new Hotel
        //            {
        //                Id = reader.GetInt32("h_id"),
        //                Name = reader.GetString("h_name"),
        //                Date = DateOnly.FromDateTime(reader.GetDateTime("h_date")),
        //                City = reader.GetString("h_city"),
        //                Rooms = reader.GetInt32("h_available_rooms")
        //            };
        //            hotels.Add(hotel);
        //        }

        //        reader.Close();
        //        conn.Close();
        //    }
        //    catch (MySqlException ex)
        //    {
        //        Console.WriteLine("Error: " + ex.Message);
        //    }
        //    return hotels;
        //}

        //public Hotel GetHotel(int id)
        //{
        //    Hotel hotel = new Hotel();
        //    try
        //    {
        //        conn = new MySqlConnection();
        //        conn.ConnectionString = myConnectionString;
        //        conn.Open();

        //        MySqlCommand cmd = new MySqlCommand();
        //        cmd.Connection = conn;

        //        string query = "SELECT * FROM hotels WHERE h_id=@id;";
        //        cmd.Parameters.AddWithValue("@id", id);
        //        cmd.CommandText = query;

        //        MySqlDataReader reader = cmd.ExecuteReader();
        //        while (reader.Read())
        //        {
        //            hotel = new Hotel
        //            {
        //                Id = reader.GetInt32("h_id"),
        //                Name = reader.GetString("h_name"),
        //                Date = DateOnly.FromDateTime(reader.GetDateTime("h_date")),
        //                City = reader.GetString("h_city"),
        //                Rooms = reader.GetInt32("h_available_rooms")
        //            };
        //        }

        //        reader.Close();
        //        conn.Close();
        //    }
        //    catch (MySqlException ex)
        //    {
        //        Console.WriteLine("Error: " + ex.Message);
        //    }
        //    return hotel;
        //}

        //public Reservation GetReservation(int id)
        //{
        //    Reservation reservation = new Reservation();
        //    try
        //    {
        //        conn = new MySqlConnection();
        //        conn.ConnectionString = myConnectionString;
        //        conn.Open();

        //        MySqlCommand cmd = new MySqlCommand();
        //        cmd.Connection = conn;

        //        string query = "SELECT * FROM reservations WHERE r_id=@id;";
        //        cmd.Parameters.AddWithValue("@id", id);
        //        cmd.CommandText = query;

        //        MySqlDataReader reader = cmd.ExecuteReader();
        //        while (reader.Read())
        //        {
        //            reservation = new Reservation
        //            {
        //                Id = reader.GetInt32("r_id"),
        //                Person = reader.GetString("r_person"),
        //                Type = reader.GetString("r_type"),
        //                ResourceId = reader.GetInt32("id_reserved_resource")
        //            };
        //        }

        //        reader.Close();
        //        conn.Close();
        //    }
        //    catch (MySqlException ex)
        //    {
        //        Console.WriteLine("Error: " + ex.Message);
        //    }
        //    return reservation;
        //}

        //public Reservation InsertLog(Reservation reservation)
        //{
        //    try
        //    {
        //        conn = new MySqlConnection();
        //        conn.ConnectionString = myConnectionString;
        //        conn.Open();

        //        MySqlCommand cmd = new MySqlCommand();
        //        cmd.Connection = conn;

        //        string query = "INSERT INTO reservations(r_person, r_type, id_reserved_resource) VALUES (@person, @type, @resourceId);SELECT LAST_INSERT_ID();";
        //        cmd.Parameters.AddWithValue("@person", reservation.Person);
        //        cmd.Parameters.AddWithValue("@type", reservation.Type);
        //        cmd.Parameters.AddWithValue("@resourceId", reservation.ResourceId);
        //        cmd.CommandText = query;
        //        var insertedId = Convert.ToInt32(cmd.ExecuteScalar());
        //        reservation.Id = insertedId;
        //        conn.Close();
        //    }
        //    catch (MySqlException ex)
        //    {
        //        Console.WriteLine("Error: " + ex.Message);
        //    }
        //    return reservation;
        //}

        //public void DeleteReservation(int id)
        //{
        //    try
        //    {
        //        conn = new MySqlConnection();
        //        conn.ConnectionString = myConnectionString;
        //        conn.Open();

        //        MySqlCommand cmd = new MySqlCommand();
        //        cmd.Connection = conn;

        //        string query = "DELETE FROM reservations WHERE r_id=@id;";
        //        cmd.Parameters.AddWithValue("@id", id);
        //        cmd.CommandText = query;
        //        cmd.ExecuteNonQuery();
        //        conn.Close();
        //    }
        //    catch (MySqlException ex)
        //    {
        //        Console.WriteLine("Error: " + ex.Message);
        //    }
        //}

        //public void UpdateStatus(Flight flight)
        //{
        //    try
        //    {
        //        conn = new MySqlConnection();
        //        conn.ConnectionString = myConnectionString;
        //        conn.Open();

        //        MySqlCommand cmd = new MySqlCommand();
        //        cmd.Connection = conn;

        //        string query = "UPDATE flights SET f_destination_city=@city, f_available_seats=@seats WHERE f_id=@id;";
        //        cmd.Parameters.AddWithValue("@city", flight.City);
        //        cmd.Parameters.AddWithValue("@seats", flight.Seats);
        //        cmd.Parameters.AddWithValue("@id", flight.Id);
        //        cmd.CommandText = query;
        //        cmd.ExecuteNonQuery();
        //        conn.Close();
        //    }
        //    catch (MySqlException ex)
        //    {
        //        Console.WriteLine("Error: " + ex.Message);
        //    }
        //}

        //public void UpdateHotel(Hotel hotel)
        //{
        //    try
        //    {
        //        conn = new MySqlConnection();
        //        conn.ConnectionString = myConnectionString;
        //        conn.Open();

        //        MySqlCommand cmd = new MySqlCommand();
        //        cmd.Connection = conn;

        //        string query = "UPDATE hotels SET h_name=@name, h_city=@city, h_available_rooms=@rooms WHERE h_id=@id;";
        //        cmd.Parameters.AddWithValue("@name", hotel.Name);
        //        cmd.Parameters.AddWithValue("@city", hotel.City);
        //        cmd.Parameters.AddWithValue("@rooms", hotel.Rooms);
        //        cmd.Parameters.AddWithValue("@id", hotel.Id);
        //        cmd.CommandText = query;
        //        cmd.ExecuteNonQuery();
        //        conn.Close();
        //    }
        //    catch (MySqlException ex)
        //    {
        //        Console.WriteLine("Error: " + ex.Message);
        //    }
        //}
    }
}
