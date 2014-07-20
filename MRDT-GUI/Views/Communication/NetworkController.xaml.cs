namespace MRDT_GUI.Views
{
    using System.Windows.Controls;
    using MRDT_GUI.ViewModels;

    public partial class NetworkController : UserControl
    {
        public NetworkController()
        {
            InitializeComponent();
            DataContext = new NetworkControllerViewModel();
        }
    }
}
