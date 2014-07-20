namespace MRDT_GUI.Commands
{
    using System;
    using System.Windows.Input;
    using ViewModels;

    class NetworkDisconnectCommand : ICommand
    {
        public NetworkDisconnectCommand(NetworkControllerViewModel viewModel)
        {
            _ViewModel = viewModel;
        }

        private NetworkControllerViewModel _ViewModel;

        #region ICommandMembers

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        public bool CanExecute(object parameter)
        {
            return _ViewModel.NetworkControllerModel.CanDisconnect;
        }

        public void Execute(object parameter)
        {
            _ViewModel.Disconnect();
        }

        #endregion
    }
}
