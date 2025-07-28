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
        private string myConnectionString = "server=localhost;uid=root;pwd=;database=hotel_db";

        public User GetUser(string username, int password)
        {
            User user = new User();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM users WHERE username=@username AND password=@password;";
                cmd.Parameters.AddWithValue("@username", username);
                cmd.Parameters.AddWithValue("@password", password);
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    user = new User
                    {
                        Id = reader.GetInt32("id"),
                        Username = reader.GetString("username"),
                        Password = reader.GetInt32("password"),
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

        public List<HotelRoom> GetFreeRooms(DateOnly checkIn, DateOnly checkOut)
        {
            List<HotelRoom> hotel_rooms = new List<HotelRoom>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM hotel_room WHERE id NOT IN (SELECT r_id FROM reservation WHERE NOT (check_out <= @checkIn OR check_in >= @checkOut));";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@checkIn", checkIn.ToDateTime(TimeOnly.MinValue));
                cmd.Parameters.AddWithValue("@checkOut", checkOut.ToDateTime(TimeOnly.MinValue));

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    HotelRoom room = new HotelRoom
                    {
                        Id = reader.GetInt32("id"),
                        RoomNumber = reader.GetString("room_number"),
                        Capacity = reader.GetInt32("capacity"),
                        Price = reader.GetInt32("price"),
                    };
                    hotel_rooms.Add(room);
                }

                reader.Close();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return hotel_rooms;
        }
        
        public List<Reservation> GetUserReservations(int id)
        {
            List<Reservation> reservations = new List<Reservation>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM reservation WHERE u_id=@id;";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@id", id);

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    Reservation reservation = new Reservation
                    {
                        Id = reader.GetInt32("id"),
                        UserId = reader.GetInt32("u_id"),
                        RoomId = reader.GetInt32("r_id"),
                        CheckIn = DateOnly.FromDateTime(reader.GetDateTime("check_in")),
                        CheckOut = DateOnly.FromDateTime(reader.GetDateTime("check_out")),
                        Guests = reader.GetInt32("guests"),
                        Price = reader.GetInt32("price"),
                    };
                    reservations.Add(reservation);
                }

                reader.Close();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return reservations;
        }

        public bool ReserveRoom(int u_id, int r_id, DateOnly check_in, DateOnly check_out)
        {
            int total_price=0;
            int base_price = 0;
            int reserved_rooms = 0;
            int total_rooms = 0;
            int res = 0;
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string total_price_query = "SELECT price FROM hotel_room WHERE id=@r_id";
                cmd.CommandText = total_price_query;
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@r_id", r_id);
                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    base_price = reader.GetInt32("price");
                }
                reader.Close();

                string count_reserved_room_query = "SELECT COUNT(*) AS rooms FROM hotel_room WHERE id IN (SELECT r_id FROM reservation WHERE NOT (check_out <= @checkIn OR check_in >= @checkOut));";
                cmd.CommandText = count_reserved_room_query;
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@checkIn", check_in.ToDateTime(TimeOnly.MinValue));
                cmd.Parameters.AddWithValue("@checkOut", check_out.ToDateTime(TimeOnly.MinValue));

                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    reserved_rooms = reader.GetInt32("rooms");
                }
                reader.Close();

                string count_room_query = "SELECT COUNT(*) AS rooms FROM hotel_room;";
                cmd.Parameters.Clear();
                cmd.CommandText = count_room_query;
                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    total_rooms = reader.GetInt32("rooms");
                }

                if (reserved_rooms <= 0.5f * total_rooms)
                {
                    total_price = base_price;
                }
                else if(reserved_rooms > 0.5f * total_rooms && reserved_rooms <= 0.8f * total_rooms)
                {
                    total_price = (int)(base_price + 0.2f * base_price);
                }
                else
                {
                    total_price = (int)(base_price + 0.5f * base_price);
                }

                reader.Close();

                string reservations_query = "SELECT COUNT(*) AS res FROM reservation WHERE id IN (SELECT id FROM reservation WHERE NOT (check_out <= @checkIn OR check_in >= @checkOut)) AND u_id=@u_id;";
                cmd.CommandText = reservations_query;
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@checkIn", check_in.ToDateTime(TimeOnly.MinValue));
                cmd.Parameters.AddWithValue("@checkOut", check_out.ToDateTime(TimeOnly.MinValue));
                cmd.Parameters.AddWithValue("@u_id", u_id);

                reader = cmd.ExecuteReader();
                if (reader.Read())
                {
                    res = reader.GetInt32("res");
                }
                reader.Close();

                if (res == 0)
                {
                    string query = "INSERT INTO reservation(u_id, r_id, check_in, check_out, price) VALUES (@u_id, @r_id, @check_in, @check_out, @price);";
                    cmd.Parameters.Clear();
                    cmd.Parameters.AddWithValue("@u_id", u_id);
                    cmd.Parameters.AddWithValue("@r_id", r_id);
                    cmd.Parameters.AddWithValue("@check_in", check_in.ToDateTime(TimeOnly.MinValue));
                    cmd.Parameters.AddWithValue("@check_out", check_out.ToDateTime(TimeOnly.MinValue));
                    cmd.Parameters.AddWithValue("@price", total_price);
                    cmd.CommandText = query;
                    cmd.ExecuteNonQuery();
                    conn.Close();
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

        public int GetGuests(DateOnly day)
        {
            int nr_guests = 0;
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT SUM(guests) AS guests FROM reservation WHERE check_in<=@day AND check_out>=@day;";
                cmd.Parameters.AddWithValue("@day", day.ToDateTime(TimeOnly.MinValue));
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    nr_guests = reader.GetInt32("guests");
                }
               

                reader.Close();
                conn.Close();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return nr_guests;
        }

        //public List<string> VerifyFeedback(string message)
        //{
        //    List<string> words = new List<string>();
        //    try
        //    {
        //        conn = new MySqlConnection();
        //        conn.ConnectionString = myConnectionString;
        //        conn.Open();

        //        MySqlCommand cmd = new MySqlCommand();
        //        cmd.Connection = conn;

        //        string query = "SELECT pattern FROM blocked_words WHERE @message LIKE CONCAT('%', pattern, '%');";
        //        cmd.Parameters.AddWithValue("@message", message );
        //        cmd.CommandText = query;

        //        MySqlDataReader reader = cmd.ExecuteReader();
        //        while (reader.Read())
        //        {
        //            string word = reader.GetString("pattern");
        //            words.Add(word);
        //        }

        //        reader.Close();
        //        conn.Close();
        //    }
        //    catch (MySqlException ex)
        //    {
        //        Console.WriteLine("Error: " + ex.Message);
        //    }
        //    return words;
        //}
    }
}
