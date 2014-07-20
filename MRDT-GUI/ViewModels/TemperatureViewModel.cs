namespace MRDT_GUI.ViewModels
{
    using Models;

    public class TemperatureViewModel
    {
        public TemperatureViewModel()
        {
            stateModel = Views.MainWindow.State;
            stateModel.Sensor1Temp = 0;
        }

        private readonly StateModel stateModel;
        public StateModel StateModel
        {
            get { return stateModel; }
        }
    }
}
