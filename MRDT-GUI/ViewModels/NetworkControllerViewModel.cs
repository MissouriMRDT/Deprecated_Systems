namespace MRDT_GUI.ViewModels
{
    using Commands;
    using Models;
    using System;
    using System.Diagnostics;
    using System.Net;
    using System.Net.Sockets;
    using System.Text;
    using System.Threading;
    using System.Threading.Tasks;
    using System.Windows.Input;

    class NetworkControllerViewModel 
    {
        public NetworkControllerViewModel()
        {
            stateModel = Views.MainWindow.State;
            networkControllerModel = Views.MainWindow.Network;
            NetworkListenCommand = new NetworkListenCommand(this);
            NetworkDisconnectCommand = new NetworkDisconnectCommand(this);
            NetworkSendCommand = new NetworkSendCommand(this);
            networkControllerModel.CanListen = true;
            networkControllerModel.CanDisconnect = false;
            networkControllerModel.CanSend = false;
        }

        #region Models

        private readonly NetworkControllerModel networkControllerModel;
        public NetworkControllerModel NetworkControllerModel
        {
            get
            {
                return networkControllerModel;
            }
        }
        private readonly StateModel stateModel;
        public StateModel StateModel
        {
            get
            {
                return stateModel;
            }
        }

        #endregion

        #region Commands

        public ICommand NetworkListenCommand
        {
            get;
            private set;
        }
        public ICommand NetworkDisconnectCommand
        {
            get;
            private set;
        }
        public ICommand NetworkSendCommand
        {
            get;
            private set;
        }

        #endregion

        public void Listen()
        {
            NetworkControllerModel.ConsoleText = "";
            NetworkControllerModel.CanListen = false;
            UpdateConsole("Listening...");
            networkControllerModel.Cts = new CancellationTokenSource();
            networkControllerModel.Listener = new TcpListener(IPAddress.Any, 55555);
            var listenerTask = new Task(InitializeListener);
            listenerTask.Start();
            var timerTask = new Task(RunTimer);
            timerTask.Start();
        }

        private void InitializeListener()
        {
            networkControllerModel.StartTime = new DateTime();
            try
            {
                networkControllerModel.Listener.Start();
                var task = AcceptClientsAsync(networkControllerModel.Listener, networkControllerModel.Cts.Token);
            }
            catch (Exception) { }
        }

        private void RunTimer()
        {
            networkControllerModel.StartTime = DateTime.Now.ToUniversalTime();
            while (true)
            {
                if (networkControllerModel.Cts.IsCancellationRequested)
                {
                    break;
                }

                networkControllerModel.RunTime = GetCurrentConnectionTime();
            }
        }

        async Task AcceptClientsAsync(TcpListener listener, CancellationToken ct)
        {
            while (!ct.IsCancellationRequested)
            {
                networkControllerModel.Client = await listener.AcceptTcpClientAsync();
                stateModel.RoverConnectionStatus = true;
                UpdateConsole("Connected!");
                NetworkControllerModel.CanSend = true;
                NetworkControllerModel.CanDisconnect = true;
                ReceiveIncomingData(networkControllerModel.Client, ct);
            }
            Disconnect();
        }

        void ReceiveIncomingData(TcpClient client, CancellationToken ct)
        {
            var stream = client.GetStream();
            var buf = new byte[1024];
            var text = String.Empty;
            while (!ct.IsCancellationRequested && client.Connected)
            {
                var amountRead = stream.Read(buf, 0, buf.Length);
                if (amountRead == 0)
                    break;
                Array.Resize(ref buf, amountRead);
                try
                {
                    text += Encoding.ASCII.GetString(buf).Trim(new [] { '\0' });
                    var messages = text.Split(new [] { '\n' });
                    text = text.EndsWith("\n") ? "" : messages[messages.Length - 1];
                    if (text != "")
                        Array.Resize(ref messages, messages.Length - 1);
                    foreach (var message in messages)
                    {
                        //UpdateConsole(text); // Uncomment this line to see ALL network data that comes across (you probably don't want this)
                        var parser = new RoverMessageParser(stateModel, networkControllerModel);
                        parser.Parse(message);
                    }
                }
                catch (Exception e)
                {
                    Debug.Print(e.ToString());
                }
            }
            UpdateConsole("Client Disconnected");
            stateModel.RoverConnectionStatus = false;
            NetworkControllerModel.CanListen = true;
            NetworkControllerModel.CanDisconnect = false;
            NetworkControllerModel.CanSend = false;
            networkControllerModel.Cts.Cancel();
        }

        public void Disconnect()
        {
            networkControllerModel.Cts.Cancel();
            networkControllerModel.Listener.Stop();
            NetworkControllerModel.CanListen = true;
            NetworkControllerModel.CanSend = false;
        }

        public async void Send()
        {
            if (!networkControllerModel.CanSend) return;

            UpdateConsole("Sending: " + NetworkControllerModel.SendText);
            var encoder = new ASCIIEncoding();
            var bytes = encoder.GetBytes(NetworkControllerModel.SendText);
            var stream = networkControllerModel.Client.GetStream();
            await stream.WriteAsync(bytes, 0, bytes.Length);
        }

        private void UpdateConsole(string text)
        {
            networkControllerModel.ConsoleText = DateTime.Now.ToLongTimeString() + ": " + text + "\r\n" + networkControllerModel.ConsoleText;
        }

        private string GetCurrentConnectionTime()
        {
            return (59 - (networkControllerModel.StartTime - DateTime.Now).Minutes) + "m" + (59 - (networkControllerModel.StartTime - DateTime.Now).Seconds) + "s";
        }
    }
}
