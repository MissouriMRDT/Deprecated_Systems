namespace MRDT_GUI.Commands
{
    using System;
    using System.Windows.Input;
    using ViewModels;

    class NetworkSendCommand : ICommand
    {
        public NetworkSendCommand(NetworkControllerViewModel viewModel)
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
            return _ViewModel.NetworkControllerModel.CanSend;
        }

        public void Execute(object parameter)
        {
            _ViewModel.Send();
        }

        #endregion
    }
}