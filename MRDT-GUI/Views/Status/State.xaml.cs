namespace MRDT_GUI.Views
{
    using System.Windows.Controls;
    using MRDT_GUI.ViewModels;

    public partial class State : UserControl
    {
        public State()
        {
            InitializeComponent();
            DataContext = new StateViewModel();
        }
    }
}
