namespace MRDT_GUI.Models
{
    using System;
    using System.ComponentModel;
    using System.Net;
    using System.Net.Sockets;
    using System.Threading;
    using System.Windows;

    public class NetworkControllerModel : INotifyPropertyChanged
    {
        public NetworkControllerModel()
        {
            startTime = new DateTime();
            StateModel = MRDT_GUI.Views.MainWindow.State;
        }

        private StateModel StateModel;
        public CancellationTokenSource Cts { get; set; }
        public TcpListener Listener = new TcpListener(IPAddress.Parse("127.0.0.1"), 55555);
        public TcpClient Client = new TcpClient();

        private string consoleText { get; set; }
        public string ConsoleText
        {
            get
            {
                return consoleText;
            }
            set
            {
                consoleText = value;
                OnPropertyChanged("consoleText");
            }
        }

        private string sendText { get; set; }
        public string SendText
        {
            get
            {
                return sendText;
            }
            set
            {
                sendText = value;
                OnPropertyChanged("sendText");
            }
        }

        private DateTime startTime { get; set; }
        public DateTime StartTime
        {
            get
            {
                return startTime;
            }
            set
            {
                startTime = value;
                OnPropertyChanged("startTime");
            }
        }

        private string runTime { get; set; }
        public string RunTime
        {
            get
            {
                return runTime;
            }
            set
            {
                runTime = value;
                OnPropertyChanged("runTime");
            }
        }

        private bool canListen { get; set; }
        public bool CanListen 
        {
            get
            {
                return canListen;
            }
            set
            {
                canListen = value;
                OnPropertyChanged("isListening");
            }
        }

        private bool canDisconnect { get; set; }
        public bool CanDisconnect
        {
            get
            {
                return canDisconnect;
            }
            set
            {
                canDisconnect = value;
                OnPropertyChanged("canDisconnect");
                OnPropertyChanged("progressBarVisible");
            }
        }

        private bool canSend { get; set; }
        public bool CanSend
        {
            get
            {
                return canSend;
            }
            set
            {
                canSend = value;
                OnPropertyChanged("canSend");
            }
        }

        private Visibility progressBarVisible { get; set; }
        public Visibility ProgressBarVisible
        {
            get
            {
                if (canDisconnect)
                    return Visibility.Visible;
                else
                    return Visibility.Hidden;
            }
        }

        #region SerialProperties

        private bool canOpen { get; set; }
        public bool CanOpen
        {
            get
            {
                return canOpen;
            }
            set
            {
                canOpen = value;
                OnPropertyChanged("canOpen");
            }
        }

        private bool canClose { get; set; }
        public bool CanClose
        {
            get
            {
                return canClose;
            }
            set
            {
                canClose = value;
                OnPropertyChanged("canClose");
            }
        }

        #endregion

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion

    }
}
