namespace MRDT_GUI.Views.Settings
{
    using System.Windows.Controls;
    using MRDT_GUI.ViewModels;

    public partial class ConfigurationSettings : UserControl
    {
        public ConfigurationSettings()
        {
            InitializeComponent();
            DataContext = new ConfigurationViewModel();
        }
    }
}
