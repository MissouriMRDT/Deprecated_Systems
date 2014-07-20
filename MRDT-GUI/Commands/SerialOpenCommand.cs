namespace MRDT_GUI.Commands
{
    using Models;
    using System;
    using System.Windows.Input;
    using ViewModels;

    class SerialOpenCommand : ICommand
    {
        public SerialOpenCommand(SerialControllerViewModel serialViewModel, NetworkControllerModel networkModel)
        {
            _SerialViewModel = serialViewModel;
            _NetworkModel = networkModel;
        }

        private SerialControllerViewModel _SerialViewModel;
        private NetworkControllerModel _NetworkModel;

        #region ICommandMembers

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        public bool CanExecute(object parameter)
        {
            return _NetworkModel.CanOpen; 
        }

        public void Execute(object parameter)
        {
            _SerialViewModel.OpenSerialPort();
        }

        #endregion
    }
}
