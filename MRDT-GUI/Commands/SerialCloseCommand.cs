namespace MRDT_GUI.Commands
{
    using System;
    using System.Windows.Input;
    using Models;
    using ViewModels;

    class SerialCloseCommand : ICommand
    {
        public SerialCloseCommand(SerialControllerViewModel serialViewModel, NetworkControllerModel networkModel)
        {
            _SerialViewModel = serialViewModel;
            _NetworkModel = networkModel;
        }

        private SerialControllerViewModel _SerialViewModel;

        #region ICommandMembers

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        public bool CanExecute(object parameter)
        {
            return _NetworkModel.CanClose;
        }

        public void Execute(object parameter)
        {
            _SerialViewModel.CloseSerialPort();
        }

        #endregion

        private NetworkControllerModel _NetworkModel { get; set; }
    }
}
