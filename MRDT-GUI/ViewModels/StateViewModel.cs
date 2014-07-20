namespace MRDT_GUI.ViewModels
{
    using Commands;
    using Models;
    using System.Windows.Input;

    public class StateViewModel
    {
        public StateViewModel()
        {
            networkModel = Views.MainWindow.Network;
            stateModel = Views.MainWindow.State;
            configModel = Views.MainWindow.Settings;
            
            LeftMaximumCalibrationCommand = new LeftMaximumCalibrationCommand(networkModel, stateModel, configModel);
            LeftMinimumCalibrationCommand = new LeftMinimumCalibrationCommand(networkModel, stateModel, configModel);
            RightMaximumCalibrationCommand = new RightMaximumCalibrationCommand(networkModel, stateModel, configModel);
            RightMinimumCalibrationCommand = new RightMinimumCalibrationCommand(networkModel, stateModel, configModel);

            P1MaximumCalibrationCommand = new P1MaximumCalibrationCommand(networkModel, stateModel, configModel);
            P1MinimumCalibrationCommand = new P1MinimumCalibrationCommand(networkModel, stateModel, configModel);
            P2MaximumCalibrationCommand = new P2MaximumCalibrationCommand(networkModel, stateModel, configModel);
            P2MinimumCalibrationCommand = new P2MinimumCalibrationCommand(networkModel, stateModel, configModel);
            P3MaximumCalibrationCommand = new P3MaximumCalibrationCommand(networkModel, stateModel, configModel);
            P3MinimumCalibrationCommand = new P3MinimumCalibrationCommand(networkModel, stateModel, configModel);
            P4MaximumCalibrationCommand = new P4MaximumCalibrationCommand(networkModel, stateModel, configModel);
            P4MinimumCalibrationCommand = new P4MinimumCalibrationCommand(networkModel, stateModel, configModel);
            P5MaximumCalibrationCommand = new P5MaximumCalibrationCommand(networkModel, stateModel, configModel);
            P5MinimumCalibrationCommand = new P5MinimumCalibrationCommand(networkModel, stateModel, configModel);
            P6MaximumCalibrationCommand = new P6MaximumCalibrationCommand(networkModel, stateModel, configModel);
            P6MinimumCalibrationCommand = new P6MinimumCalibrationCommand(networkModel, stateModel, configModel);
            P7MaximumCalibrationCommand = new P7MaximumCalibrationCommand(networkModel, stateModel, configModel);
            P7MinimumCalibrationCommand = new P7MinimumCalibrationCommand(networkModel, stateModel, configModel);

            stateModel.RoverConnectionStatus = false;
            stateModel.ControllerConnectionStatus = false;
        }

        #region Models

        private readonly ConfigurationModel configModel;
        public ConfigurationModel ConfigModel
        {
            get { return configModel; }
        }

        private readonly StateModel stateModel;
        public StateModel StateModel
        {
            get { return stateModel; }
        }

        private readonly NetworkControllerModel networkModel;
        public NetworkControllerModel NetworkModel
        {
            get { return networkModel; }
        }

        #endregion

        #region Commands

        public ICommand LeftMaximumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand LeftMinimumCalibrationCommand
        {
            get;
            private set;
        }

        public ICommand RightMaximumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand RightMinimumCalibrationCommand
        {
            get;
            private set;
        }

        public ICommand P1MaximumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand P1MinimumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand P2MaximumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand P2MinimumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand P3MaximumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand P3MinimumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand P4MaximumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand P4MinimumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand P5MaximumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand P5MinimumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand P6MaximumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand P6MinimumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand P7MaximumCalibrationCommand
        {
            get;
            private set;
        }
        public ICommand P7MinimumCalibrationCommand
        {
            get;
            private set;
        }

        #endregion
    }
}
