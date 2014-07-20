namespace MRDT_GUI.Commands
{
    using System;
    using System.Windows.Input;
    using ViewModels;

    class NetworkListenCommand : ICommand
    {
        public NetworkListenCommand(NetworkControllerViewModel viewModel)
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
            return _ViewModel.NetworkControllerModel.CanListen;
        }

        public void Execute(object parameter)
        {
            _ViewModel.Listen();
        }

        #endregion
    }
}
