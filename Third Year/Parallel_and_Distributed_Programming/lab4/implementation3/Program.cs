using System;
using System.Collections.Generic;
using System.IO;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

class Program
{
    static async Task Main()
    {
        var urls = new List<string>
        {
            "http://example.com/",
            "http://info.cern.ch/",
            "http://www.textfiles.com/100/captmidn.txt",
            "http://www.textfiles.com/stories/13chil.txt",
            "http://www.textfiles.com/stories/cabin.txt",
            "http://www.textfiles.com/stories/100west.txt",
            "http://www.textfiles.com/stories/14.lws",
            "http://www.textfiles.com/stories/16.lws",
            "http://www.textfiles.com/stories/17.lws",
            "http://www.textfiles.com/stories/18.lws",
            "http://www.textfiles.com/stories/19.lws",
            "http://www.textfiles.com/stories/20.lws",
            "http://www.textfiles.com/stories/3gables.txt",
            "http://www.textfiles.com/stories/3lpigs.txt",
            "http://www.textfiles.com/stories/aesop11.txt",
            "http://www.textfiles.com/stories/3sonnets.vrs",
            "http://www.textfiles.com/stories/3student.txt",
            "http://www.textfiles.com/stories/3wishes.txt",
            "http://www.textfiles.com/stories/4moons.txt",
            "http://www.textfiles.com/stories/5orange.txt",
            "http://www.textfiles.com/stories/6ablemen.txt",
            "http://www.textfiles.com/stories/6napolen.txt",
            "http://www.textfiles.com/stories/7oldsamr.txt",
            "http://www.textfiles.com/stories/7voysinb.txt",
            "http://www.textfiles.com/stories/ab40thv.txt",
            "http://www.textfiles.com/stories/abbey.txt",
            "http://www.textfiles.com/stories/abyss.txt",
            "http://www.textfiles.com/stories/adler.txt",
            "http://www.textfiles.com/stories/adv_alad.txt",
            "http://www.textfiles.com/stories/advsayed.txt",
            "http://www.textfiles.com/stories/advtthum.txt",
            "http://www.textfiles.com/stories/aesopa10.txt",
            "http://www.textfiles.com/stories/aircon.txt",
            "http://www.textfiles.com/stories/aisle.six",
            "http://www.textfiles.com/stories/aislesix.txt",
            "http://www.textfiles.com/stories/alad10.txt",
            "http://www.textfiles.com/stories/aluminum.hum",
            "http://www.textfiles.com/stories/archive",
            "http://www.textfiles.com/stories/aquith.txt",
            "http://www.textfiles.com/stories/batlslau.txt",
            "http://www.textfiles.com/stories/beggars.txt",
            "http://www.textfiles.com/stories/breaks1.asc",
            "http://www.textfiles.com/stories/breaks2.asc",
            "http://www.textfiles.com/stories/breaks3.asc",
            "http://www.textfiles.com/stories/bureau.txt",
            "http://www.textfiles.com/stories/cooldark.sto",
            "http://www.textfiles.com/stories/cooldark.txt",
            "http://www.textfiles.com/stories/cybersla.txt",
            "http://www.textfiles.com/stories/dakota.txt",
            "http://www.textfiles.com/stories/deal",
            "http://www.textfiles.com/stories/darkness.txt",
            "http://www.textfiles.com/stories/elite.app",
            "http://www.textfiles.com/stories/domain.poe",
            "http://www.textfiles.com/stories/enchdup.hum",
            "http://www.textfiles.com/stories/vgilante.txt"
        };

        var downloader = new AsyncHttpDownloader();
        Stopwatch sw = Stopwatch.StartNew();

        var tasks = new List<Task>();
        foreach (var url in urls)
        {
            tasks.Add(downloader.DownloadFileAsync(url));
        }

        await Task.WhenAll(tasks);

        sw.Stop();
        Console.WriteLine("All downloads finished for implementation3.");
        Console.WriteLine($"Total elapsed time: {sw.Elapsed.TotalSeconds:F2} seconds");
    }
}

public class AsyncHttpDownloader
{
    private const int BufferSize = 8192;
    private Random Random = new Random();

    public async Task DownloadFileAsync(string url)
    {
        var uri = new Uri(url);
        var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        var state = new AsyncState(socket, uri);

        try
        {
            await ConnectAsync(socket, uri.Host, 80);

            string request = $"GET {uri.PathAndQuery} HTTP/1.1\r\nHost: {uri.Host}\r\nConnection: close\r\n\r\n";
            byte[] bytes = Encoding.ASCII.GetBytes(request);
            await SendAsync(socket, bytes);

            await ReceiveAsync(state);

            SaveToFile(state);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error downloading {uri}: {ex.Message}");
        }
    }

    private Task ConnectAsync(Socket socket, string host, int port)
    {
        var tcs = new TaskCompletionSource<bool>();
        socket.BeginConnect(host, port, ar =>
        {
            try
            {
                socket.EndConnect(ar);
                tcs.SetResult(true);
            }
            catch (Exception ex)
            {
                tcs.SetException(ex);
            }
        }, null);
        return tcs.Task;
    }

    private Task SendAsync(Socket socket, byte[] data)
    {
        var tcs = new TaskCompletionSource<bool>();
        socket.BeginSend(data, 0, data.Length, 0, ar =>
        {
            try
            {
                socket.EndSend(ar);
                tcs.SetResult(true);
            }
            catch (Exception ex)
            {
                tcs.SetException(ex);
            }
        }, null);
        return tcs.Task;
    }

    private Task ReceiveAsync(AsyncState state)
    {
        var tcs = new TaskCompletionSource<bool>();

        void ReceiveCallback(IAsyncResult ar)
        {
            try
            {
                int bytesRead = state.Socket.EndReceive(ar);
                if (bytesRead > 0)
                {
                    state.Response.Write(state.Buffer, 0, bytesRead);

                    if (!state.HeadersParsed)
                    {
                        string textSoFar = Encoding.ASCII.GetString(state.Response.ToArray());
                        int headerEnd = textSoFar.IndexOf("\r\n\r\n");
                        if (headerEnd >= 0)
                        {
                            state.HeadersParsed = true;
                            string headers = textSoFar.Substring(0, headerEnd);
                            using (StringReader reader = new StringReader(headers))
                            {
                                string line;
                                while ((line = reader.ReadLine()) != null)
                                {
                                    if (line.StartsWith("Content-Length:", StringComparison.OrdinalIgnoreCase))
                                    {
                                        string value = line.Substring("Content-Length:".Length).Trim();
                                        if (int.TryParse(value, out int length))
                                        {
                                            state.ContentLength = length;
                                            break;
                                        }
                                    }
                                }
                            }

                            int bodyStartIndex = headerEnd + 4;
                            if (state.ContentLength >= 0)
                            {
                                state.BodyBuffer = new byte[state.ContentLength];
                                byte[] fullData = state.Response.ToArray();
                                int bodyBytesAvailable = fullData.Length - bodyStartIndex;
                                int toCopy = Math.Min(bodyBytesAvailable, state.ContentLength);
                                Array.Copy(fullData, bodyStartIndex, state.BodyBuffer, 0, toCopy);
                                state.BodyBytesReceived = toCopy;
                            }
                        }
                    }
                    else
                    {
                        if (state.ContentLength >= 0)
                        {
                            int remaining = state.ContentLength - state.BodyBytesReceived;
                            int toCopy = Math.Min(remaining, bytesRead);
                            Array.Copy(state.Buffer, 0, state.BodyBuffer, state.BodyBytesReceived, toCopy);
                            state.BodyBytesReceived += toCopy;
                        }
                    }

                    if (state.ContentLength < 0 || state.BodyBytesReceived < state.ContentLength)
                        state.Socket.BeginReceive(state.Buffer, 0, BufferSize, 0, ReceiveCallback, null);
                    else
                    {
                        state.Socket.Close();
                        tcs.SetResult(true);
                    }
                }
                else
                {
                    state.Socket.Close();
                    tcs.SetResult(true);
                }
            }
            catch (Exception ex)
            {
                tcs.SetException(ex);
            }
        }

        state.Socket.BeginReceive(state.Buffer, 0, BufferSize, 0, ReceiveCallback, null);
        return tcs.Task;
    }

    private void SaveToFile(AsyncState state)
    {
        byte[] bodyData;

        if (state.ContentLength >= 0)
            bodyData = state.BodyBuffer;
        else
        {
            var data = state.Response.ToArray();
            int headerEnd = Encoding.ASCII.GetString(data).IndexOf("\r\n\r\n");
            bodyData = headerEnd >= 0 ? data[(headerEnd + 4)..] : data;
        }

        string current = Environment.CurrentDirectory;
        string projectRoot = Directory.GetParent(current).Parent.Parent.FullName;
        string downloadFolder = Path.Combine(projectRoot, "downloaded_async");
        Directory.CreateDirectory(downloadFolder);

        string filePath = Path.Combine(
            downloadFolder,
            $"async_{state.Uri.Host}_{Path.GetFileName(state.Uri.LocalPath)}_{Random.Next(500)}.txt"
        );

        File.WriteAllBytes(filePath, bodyData);
        Console.WriteLine("Saved to: " + filePath);
    }
}

public class AsyncState
{
    public Socket Socket;
    public Uri Uri;
    public byte[] Buffer = new byte[8192];
    public MemoryStream Response = new MemoryStream();
    public bool HeadersParsed = false;
    public int ContentLength = -1;
    public int BodyBytesReceived = 0;
    public byte[] BodyBuffer;

    public AsyncState(Socket s, Uri uri)
    {
        Socket = s;
        Uri = uri;
    }
}
