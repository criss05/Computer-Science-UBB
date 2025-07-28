using Lab10.Models;
using Microsoft.VisualBasic;
using MySql.Data.MySqlClient;
using System.Globalization;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace Lab10.DataAbstractionLayer
{
    public class DAL
    {
        private MySqlConnection conn;
        private string myConnectionString = "server=localhost;uid=root;pwd=;database=channels_db";

        public List<Channels> GetChannels(string name)
        {
            List<Channels> channels = new List<Channels>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM channels c INNER JOIN persons p ON c.p_id=p.id WHERE p.name=@name;";
                cmd.Parameters.AddWithValue("@name", name);
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while(reader.Read())
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
            catch(MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return channels;
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

        public void AddSubscription(string user, string channel)
        {
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string subscribers="";
                int id = -1;

                string query = "SELECT id, subscribers FROM channels WHERE name=@name AND subscribers LIKE @sub";
                cmd.Parameters.AddWithValue("@name", channel);
                cmd.Parameters.AddWithValue("@sub", "%" + user + "%");
                cmd.CommandText = query;
                MySqlDataReader reader = cmd.ExecuteReader();

                if (reader.Read())
                {
                    id = reader.GetInt32("id");
                    subscribers = reader.GetString("subscribers");
                }
                reader.Close();
                if (id>-1)
                {
                    List<string> subs = subscribers.Split(",").ToList();
                    string new_subscribers = "";
                    foreach (string sub in subs)
                    {
                        if (sub.Contains(user))
                        {
                            List<string> l = sub.Split(":").ToList();
                            l[1] = DateTime.Now.ToString("yyyy-MM-dd");
                            string updated = l[0] + ":" + l[1];
                            new_subscribers += "," + updated;
                        }
                        else
                        {
                            new_subscribers += "," + sub;
                        }
                    }
                    cmd.Parameters.Clear();
                    query = "UPDATE channels SET subscribers = @sub WHERE name = @channel";
                    cmd.Parameters.AddWithValue("@sub", new_subscribers);
                    cmd.Parameters.AddWithValue("@channel", channel);
                    cmd.CommandText = query;
                    cmd.ExecuteNonQuery();
                }
                else
                {
                    cmd.Parameters.Clear();
                    query = "UPDATE channels SET subscribers = CONCAT(subscribers,',', @name,':' @date) WHERE name=@channel";
                    cmd.Parameters.AddWithValue("@name", user);
                    cmd.Parameters.AddWithValue("@date", DateTime.Now.ToString("yyyy-MM-dd"));
                    cmd.Parameters.AddWithValue("@channel", channel);
                    cmd.CommandText = query;
                    cmd.ExecuteNonQuery();
                    conn.Close();
                }
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
        }

        //public Flight GetFlight(int id)
        //{
        //    Flight flight = new Flight();
        //    try
        //    {
        //        conn = new MySqlConnection();
        //        conn.ConnectionString = myConnectionString;
        //        conn.Open();

        //        MySqlCommand cmd = new MySqlCommand();
        //        cmd.Connection = conn;

        //        string query = "SELECT * FROM flights WHERE f_id=@id;";
        //        cmd.Parameters.AddWithValue("@id", id);
        //        cmd.CommandText = query;

        //        MySqlDataReader reader = cmd.ExecuteReader();
        //        while (reader.Read())
        //        {
        //            flight = new Flight
        //            {
        //                Id = reader.GetInt32("f_id"),
        //                Date = DateOnly.FromDateTime(reader.GetDateTime("f_date")),
        //                City = reader.GetString("f_destination_city"),
        //                Seats = reader.GetInt32("f_available_seats")
        //            };
        //        }

        //        reader.Close();
        //        conn.Close();
        //    }
        //    catch (MySqlException ex)
        //    {
        //        Console.WriteLine("Error: " + ex.Message);
        //    }
        //    return flight;
        //}

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

        //public Reservation AddReservation(Reservation reservation)
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

        //public void UpdateFlight(Flight flight)
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
