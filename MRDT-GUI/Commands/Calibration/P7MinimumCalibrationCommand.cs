namespace MRDT_GUI.Commands
{
    using System;
    using System.Windows.Input;
    using MRDT_GUI.Models;

    class P7MinimumCalibrationCommand : ICommand
    {
        public P7MinimumCalibrationCommand(NetworkControllerModel network, StateModel state, ConfigurationModel config)
        {
            _networkModel = network;
            _configModel = config;
            _stateModel = state;
        }

        private NetworkControllerModel _networkModel;
        private ConfigurationModel _configModel;
        private StateModel _stateModel;

        #region ICommandMembers

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        public bool CanExecute(object parameter)
        {
            return _networkModel.CanListen;
        }

        public void Execute(object parameter)
        {
            _configModel.P7CalibrationMinimum = _stateModel.Potentiometer7;
        }

        #endregion
    }
}
