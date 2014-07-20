namespace MRDT_GUI.Views
{
    using System.Windows.Controls;
    using MRDT_GUI.ViewModels;

    public partial class SerialController : UserControl
    {
        public SerialController()
        {
            InitializeComponent();
            this.DataContext = new SerialControllerViewModel();
        }

        private void SerialConnectButton_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            var vm = this.DataContext as SerialControllerViewModel;
            vm.OpenSerialPort();
        }

        private void SerialDisconnectButton_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            var vm = this.DataContext as SerialControllerViewModel;
            vm.CloseSerialPort();
        }
    }
}
