namespace MRDT_GUI.Commands
{
    using System;
    using System.Windows.Input;
    using MRDT_GUI.Models;

    class P5MaximumCalibrationCommand : ICommand
    {
        public P5MaximumCalibrationCommand(NetworkControllerModel network, StateModel state, ConfigurationModel config)
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
            _configModel.P5CalibrationMaximum = _stateModel.Potentiometer5;
        }

        #endregion
    }
}
