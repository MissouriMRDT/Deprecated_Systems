namespace MRDT_GUI.ViewModels
{
    using Commands;
    using Models;
    using System;
    using System.ComponentModel;
    using System.IO.Ports;
    using System.Runtime.CompilerServices;
    using System.Windows.Input;

    class SerialControllerViewModel : INotifyPropertyChanged
    {
        private static readonly SerialPort MySerialPort = new SerialPort("COM6");
        private readonly ControlPanelParser parser;

        public SerialControllerViewModel()
        {
            stateModel = Views.MainWindow.State;
            networkControllerModel = Views.MainWindow.Network;
            configModel = Views.MainWindow.Settings;
            SerialCloseCommand = new SerialCloseCommand(this, networkControllerModel);
            SerialOpenCommand = new SerialOpenCommand(this, networkControllerModel);
            MySerialPort.DataReceived += DataReceivedHandler;
            parser = new ControlPanelParser(networkControllerModel, stateModel, configModel);
            networkControllerModel.CanClose = false;
            networkControllerModel.CanOpen = true;
        }
        
        private string textFromSerialPort;
        public string TextFromSerialPort
        {
            get { return textFromSerialPort; }
            set
            {
                if (value == textFromSerialPort)
                    return;
                textFromSerialPort += value;
                OnPropertyChanged();
            }
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
        private readonly ConfigurationModel configModel;
        public ConfigurationModel ConfigModel
        {
            get
            {
                return configModel;
            }
        }

        #endregion

        #region Commands

        public ICommand SerialOpenCommand
        {
            get;
            private set;
        }
        public ICommand SerialCloseCommand
        {
            get;
            private set;
        }

        #endregion

        private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                var sp = (SerialPort)sender;

                var indata = sp.ReadLine();

                parser.Parse(indata);
            }
            catch (Exception) { }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) 
                handler(this, new PropertyChangedEventArgs(propertyName));
        }

        public void OpenSerialPort()
        {
            try
            {
                MySerialPort.Open();
                networkControllerModel.CanClose = true;
                networkControllerModel.CanOpen = false;
                stateModel.ControllerConnectionStatus = true;
            }
            catch (Exception) { }
        }

        public void CloseSerialPort()
        {
            try
            {
                MySerialPort.Close();
                networkControllerModel.CanClose = false;
                networkControllerModel.CanOpen = true;
                stateModel.ControllerConnectionStatus = false;
            }
            catch (Exception) { }
        }

        public async void Send(string text)
        {
            if (!networkControllerModel.CanSend) return;
            networkControllerModel.ConsoleText += DateTime.Now.ToShortTimeString() + ": " + "Sent: " + text + "\r\n";
            var encoder = new System.Text.ASCIIEncoding();
            var bytes = encoder.GetBytes(text);
            var stream = networkControllerModel.Client.GetStream();
            await stream.WriteAsync(bytes, 0, bytes.Length);
        }
    }
}
