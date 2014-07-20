namespace MRDT_GUI.Views
{
    using System.Windows.Media;
    using FirstFloor.ModernUI.Windows.Controls;
    using FirstFloor.ModernUI.Presentation;
    using MRDT_GUI.Models;

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : ModernWindow
    {
        internal static StateModel State;
        internal static NetworkControllerModel Network;
        internal static ConfigurationModel Settings;

        public MainWindow()
        {
            AppearanceManager.Current.AccentColor = Color.FromRgb(0xe5, 0x14, 0x00);  
            Settings = new ConfigurationModel();
            State = new StateModel();
            Network = new NetworkControllerModel();
            InitializeComponent();
            
        }
    }
}
