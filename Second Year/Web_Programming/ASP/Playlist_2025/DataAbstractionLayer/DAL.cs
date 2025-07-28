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
        private string myConnectionString = "server=localhost;uid=root;pwd=;database=retake_db";

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

        public List<Song> GetSongs()
        {
            List<Song> songs = new List<Song>();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM song;";
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    Song song = new Song
                    {
                        Id = reader.GetInt32("id"),
                        Title = reader.GetString("title"),
                        Duration = reader.GetInt32("duration"),
                    };
                    songs.Add(song);
                }

                reader.Close();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return songs;
        }

        public string GetSong(int id)
        {
            string name = "";
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT title FROM song WHERE id=@id;";
                cmd.CommandText = query;
                cmd.Parameters.AddWithValue("@id", id);

                MySqlDataReader reader = cmd.ExecuteReader();
                if (reader.Read())
                {
                    name = reader.GetString("title");
                }

                reader.Close();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return name;
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

        public string SubmitPlaylist(string username, List<int> songs)
        {
            int u_id = 0;
            int duration = 0;
            List<string> genre = new List<string>();
            string warn="";
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

                string select_duration = "SELECT duration, title FROM song WHERE id=@id;";
                foreach (int id in songs)
                {
                    cmd.CommandText = select_duration;
                    cmd.Parameters.Clear();
                    cmd.Parameters.AddWithValue("@id", id);

                    reader = cmd.ExecuteReader();
                    if (reader.Read())
                    {
                        duration += reader.GetInt32("duration");
                        string title = reader.GetString("title");
                        var arr = title.Split("-");
                        genre.Add(arr[1]);
                        if (warn == "")
                        {
                            warn = "Playlist songs: " + title;
                        }
                        else
                        {
                            warn += ", " + title;
                        }
                    }
                    reader.Close();
                }

                warn += ". Total duration is: " + duration + ". ";
                bool flag = false;
                int i = 0;
                while (i < genre.Count()-2)
                {
                    if (genre[i].Equals(genre[i + 1]) && genre[i].Equals(genre[i + 2]))
                    {
                        flag = true;
                    }
                    i++;
                }
                
                string insert_playlist = "INSERT INTO playlist(u_id, duration) VALUES (@u_id, @duration);SELECT LAST_INSERT_ID();";
                cmd.CommandText = insert_playlist;
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@u_id", u_id);
                cmd.Parameters.AddWithValue("@duration", duration);
                var insertedId = Convert.ToInt32(cmd.ExecuteScalar());
                int p_id = insertedId;

                string insert_playlist_item = "INSERT INTO playlist_item(s_id, p_id) VALUES (@s_id, @p_id);";
                foreach(int id in songs)
                {
                    cmd.Parameters.Clear();
                    cmd.CommandText = insert_playlist_item;
                    cmd.Parameters.AddWithValue("@s_id", id);
                    cmd.Parameters.AddWithValue("@p_id", p_id);
                    cmd.ExecuteNonQuery();
                }
                if (!flag)
                {
                    warn += "Dynamic Mix! This playlist has a great variety in genre flow!";
                }
                return warn;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex.Message);
                return "Failed to add the playlist";
            }
        }

        public string VerifyPlaylist(int song, string username)
        {
            int u_id = 0;
            List<int> playlists = new List<int>();
            string genre = "";
            string warn = "";
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

                string select_song_title = "SELECT title FROM song WHERE id=@id;";
                cmd.CommandText = select_song_title;
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@id", song);

                reader = cmd.ExecuteReader();
                if (reader.Read())
                {
                    genre = (reader.GetString("title")).Split("-")[1];
                }
                reader.Close();

                string select_playlists = "SELECT id FROM playlist WHERE u_id=@u_id ORDER BY id DESC LIMIT 3;";
                cmd.CommandText = select_playlists;
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("@u_id", u_id);

                reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    playlists.Add(reader.GetInt32("id"));
                }
                reader.Close();

                string select_songs = "SELECT s_id FROM playlist_item WHERE p_id=@p_id;";
                int count_genre = 0;

                MySqlConnection conn1 = new MySqlConnection();
                conn1.ConnectionString = myConnectionString;
                MySqlCommand cmd1 = new MySqlCommand();
                foreach(int p in playlists)
                {
                    int count_playlist = 0;
                    cmd.CommandText = select_songs;
                    cmd.Parameters.Clear();
                    cmd.Parameters.AddWithValue("@p_id", p);

                    reader = cmd.ExecuteReader();
                    while (reader.Read())
                    {
                        conn1.Open();
                        cmd1.Connection = conn1;
                        int s_id = reader.GetInt32("s_id");
                        MySqlDataReader reader1;
                        cmd1.CommandText = select_song_title;
                        cmd1.Parameters.Clear();
                        cmd1.Parameters.AddWithValue("@id", s_id);
                        reader1 = cmd1.ExecuteReader();
                        if (reader1.Read())
                        {
                            string gen = (reader1.GetString("title")).Split("-")[1];
                            if(genre == gen)
                            {
                                count_playlist = 1;
                            }
                        }
                        reader1.Close();
                        conn1.Close();
                    }
                    reader.Close();
                    count_genre += count_playlist;
                }
                conn.Close();
                if (count_genre == 3)
                {
                    return genre;
                }
                return "";
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex.Message);
                return "";
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
