namespace MRDT_GUI.Models
{
    using System;
    using System.Windows;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.Windows.Media;
    using System.Diagnostics;

    public class StateModel : INotifyPropertyChanged, IDataErrorInfo
    {
        public StateModel()
        {
            controlPanelMap = new Dictionary<string, int>();
            _Config = MRDT_GUI.Views.MainWindow.Settings;
            sliderLeft = 512;
            sliderRight = 512;
        }

        internal ConfigurationModel _Config { get; set; }

        #region Connection Status Fields

        private bool roverConnectionStatus { get; set; }
        public bool RoverConnectionStatus
        {
            get 
            {
                return roverConnectionStatus;
            }
            set
            {
                roverConnectionStatus = value;
                OnPropertyChanged("roverConnectionStatus");
                OnPropertyChanged("roverConnectionColor");
            }
        }

        private SolidColorBrush roverConnectionColor { get; set; }
        public SolidColorBrush RoverConnectionColor
        {
            get
            {
                if (roverConnectionStatus)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private bool controllerConnectionStatus { get; set; }
        public bool ControllerConnectionStatus
        {
            get 
            {
                return controllerConnectionStatus;
            }
            set
            {
                controllerConnectionStatus = value;
                OnPropertyChanged("controllerConnectionStatus");
                OnPropertyChanged("controllerConnectionColor");
            }
        }

        private SolidColorBrush controllerConnectionColor { get; set; }
        public SolidColorBrush ControllerConnectionColor
        {
            get
            {
                if (controllerConnectionStatus)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        #endregion

        #region Rover Fields

        private float sensor1Temp { get; set; }
        public float Sensor1Temp
        {
            get
            {
                return sensor1Temp;
            }
            set
            {
                sensor1Temp = value;
                OnPropertyChanged("sensor1Temp");
            }
        }

        private float sensor2Temp { get; set; }
        public float Sensor2Temp
        {
            get
            {
                return sensor2Temp;
            }
            set
            {
                sensor2Temp = value;
                OnPropertyChanged("sensor2Temp");
            }
        }

        private float sensor3Temp { get; set; }
        public float Sensor3Temp
        {
            get
            {
                return sensor3Temp;
            }
            set
            {
                sensor3Temp = value;
                OnPropertyChanged("sensor3Temp");
            }
        }

        private float sensor4Temp { get; set; }
        public float Sensor4Temp
        {
            get
            {
                return sensor4Temp;
            }
            set
            {
                sensor4Temp = value;
                OnPropertyChanged("sensor4Temp");
            }
        }

        private float sensor5Temp { get; set; }
        public float Sensor5Temp
        {
            get
            {
                return sensor5Temp;
            }
            set
            {
                sensor5Temp = value;
                OnPropertyChanged("sensor5Temp");
            }
        }

        private float sensor6Temp { get; set; }
        public float Sensor6Temp
        {
            get
            {
                return sensor6Temp;
            }
            set
            {
                sensor6Temp = value;
                OnPropertyChanged("sensor6Temp");
            }
        }

        private float sensor7Temp { get; set; }
        public float Sensor7Temp
        {
            get
            {
                return sensor7Temp;
            }
            set
            {
                sensor7Temp = value;
                OnPropertyChanged("sensor7Temp");
            }
        }

        private float sensor8Temp { get; set; }
        public float Sensor8Temp
        {
            get
            {
                return sensor8Temp;
            }
            set
            {
                sensor8Temp = value;
                OnPropertyChanged("sensor8Temp");
            }
        }

        private float sensor9Temp { get; set; }
        public float Sensor9Temp
        {
            get
            {
                return sensor9Temp;
            }
            set
            {
                sensor9Temp = value;
                OnPropertyChanged("sensor9Temp");
            }
        }

        private float sensor10Temp { get; set; }
        public float Sensor10Temp
        {
            get
            {
                return sensor10Temp;
            }
            set
            {
                sensor10Temp = value;
                OnPropertyChanged("sensor10Temp");
            }
        }

        private float sensor11Temp { get; set; }
        public float Sensor11Temp
        {
            get
            {
                return sensor11Temp;
            }
            set
            {
                sensor11Temp = value;
                OnPropertyChanged("sensor11Temp");
            }
        }


        #endregion

        #region Control Panel Fields

        private Dictionary<string, int> controlPanelMap { get; set; }
        public Dictionary<string, int> ControlPanelMap 
        {
            get
            {
                return controlPanelMap;
            }
            set
            {
                controlPanelMap = value;
            }
        }

        #region Colors

        private SolidColorBrush killSwitchColor { get; set; }
        public SolidColorBrush KillSwitchColor
        {
            get
            {
                if (killSwitch == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush key1Color { get; set; }
        public SolidColorBrush Key1Color
        {
            get
            {
                if (key1 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush key2Color { get; set; }
        public SolidColorBrush Key2Color 
        {
            get
            {
                if (key2 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush boxDrop1Color { get; set; }
        public SolidColorBrush BoxDrop1Color
        {
            get
            {
                if (boxDrop1 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush boxDrop2Color { get; set; }
        public SolidColorBrush BoxDrop2Color
        {
            get
            {
                if (boxDrop2 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush boxDrop3Color { get; set; }
        public SolidColorBrush BoxDrop3Color
        {
            get
            {
                if (boxDrop3 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush boxDrop4Color { get; set; }
        public SolidColorBrush BoxDrop4Color
        {
            get
            {
                if (boxDrop4 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush boxDrop5Color { get; set; }
        public SolidColorBrush BoxDrop5Color
        {
            get
            {
                if (boxDrop5 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush panelCleanerColor { get; set; }
        public SolidColorBrush PanelCleanerColor
        {
            get
            {
                if (panelCleaner == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush cameraSelect1Color { get; set; }
        public SolidColorBrush CameraSelect1Color
        {
            get
            {
                if (cameraSelect1 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush cameraSelect2Color { get; set; }
        public SolidColorBrush CameraSelect2Color
        {
            get
            {
                if (cameraSelect2 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush cameraSelect3Color { get; set; }
        public SolidColorBrush CameraSelect3Color
        {
            get
            {
                if (cameraSelect3 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush cameraSelect4Color { get; set; }
        public SolidColorBrush CameraSelect4Color
        {
            get
            {
                if (cameraSelect4 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush potentiometer1Color { get; set; }
        public SolidColorBrush Potentiometer1Color
        {
            get
            {
                if (potentiometer1 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush potentiometer2Color { get; set; }
        public SolidColorBrush Potentiometer2Color
        {
            get
            {
                if (potentiometer2 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush potentiometer3Color { get; set; }
        public SolidColorBrush Potentiometer3Color
        {
            get
            {
                if (potentiometer3 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush potentiometer4Color { get; set; }
        public SolidColorBrush Potentiometer4Color
        {
            get
            {
                if (potentiometer4 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush potentiometer5Color { get; set; }
        public SolidColorBrush Potentiometer5Color
        {
            get
            {
                if (potentiometer5 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush potentiometer6Color { get; set; }
        public SolidColorBrush Potentiometer6Color
        {
            get
            {
                if (potentiometer6 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        private SolidColorBrush potentiometer7Color { get; set; }
        public SolidColorBrush Potentiometer7Color
        {
            get
            {
                if (potentiometer7 == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        public SolidColorBrush ArmXUpColor
        {
            get
            {
                if (armX == 1) 
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }
        public SolidColorBrush ArmXDownColor
        {
            get
            {
                if (armX == 2)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        public SolidColorBrush ArmYUpColor
        {
            get
            {
                if (armY == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }
        public SolidColorBrush ArmYDownColor
        {
            get
            {
                if (armY == 2)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        public SolidColorBrush ArmZUpColor
        {
            get
            {
                if (armZ == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }
        public SolidColorBrush ArmZDownColor
        {
            get
            {
                if (armZ == 2)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        public SolidColorBrush ArmPUpColor
        {
            get
            {
                if (armP == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }
        public SolidColorBrush ArmPDownColor
        {
            get
            {
                if (armP == 2)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }


        public SolidColorBrush ArmWUpColor
        {
            get
            {
                if (armW == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }
        public SolidColorBrush ArmWDownColor
        {
            get
            {
                if (armW == 2)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        public SolidColorBrush ArmRUpColor
        {
            get
            {
                if (armR == 1)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }
        public SolidColorBrush ArmRDownColor
        {
            get
            {
                if (armR == 2)
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkGreen);
                    return colorBrush;
                }
                else
                {
                    var colorBrush = new SolidColorBrush(Colors.DarkRed);
                    return colorBrush;
                }
            }
        }

        #endregion

        #region Other Values

        //K:<kill_switch>
        private int killSwitch { get; set; }
        public int KillSwitch
        {
            get
            {
                return killSwitch;
            }
            set
            {
                killSwitch = value;
                OnPropertyChanged("killSwitch");
                OnPropertyChanged("killSwitchColor");
            }
        }
        //K1:<key_1>
        private int key1 { get; set; }
        public int Key1
        {
            get
            {
                return key1;
            }
            set
            {
                key1 = value;
                OnPropertyChanged("key1");
                OnPropertyChanged("key1Color");
            }
        }
        //K2:<key_2>
        private int key2 { get; set; }
        public int Key2
        {
            get
            {
                return key2;
            }
            set
            {
                key2 = value;
                OnPropertyChanged("key2");
                OnPropertyChanged("key2Color");
            }
        }

        //P:<panel_cleaner_switch>
        private int panelCleaner { get; set; }
        public int PanelCleaner
        {
            get
            {
                return panelCleaner;
            }
            set
            {
                panelCleaner = value;
                OnPropertyChanged("panelCleaner");
                OnPropertyChanged("panelCleanerColor");
            }
        }

        #endregion

        #region Sliders

        //SL:<slider_left>
        private int sliderLeft { get; set; }
        public int SliderLeft
        {
            get
            {
                return sliderLeft;
            }
            set
            {
                sliderLeft = value;
                OnPropertyChanged("sliderLeft");
                OnPropertyChanged("sliderLeftColor");
                OnPropertyChanged("SliderLeftActual");
            }
        }
        //SR:<slider_right>
        private int sliderRight { get; set; }
        public int SliderRight
        {
            get
            {
                return sliderRight;
            }
            set
            {
                sliderRight = value;
                OnPropertyChanged("sliderRight");
                OnPropertyChanged("sliderRightColor");
                OnPropertyChanged("SliderRightActual");
            }
        }

        public int SliderLeftActual
        {
            get
            {
                if (sliderLeft > _Config.MiddleValue)
                {
                    return (int)(((float)sliderLeft + (float)_Config.LeftCalibrationMaximum) - (float)_Config.MiddleValue);
                }
                else if (sliderLeft < _Config.MiddleValue)
                {
                    return (int)(((float)sliderLeft - (float)_Config.LeftCalibrationMinimum) - (float)_Config.MiddleValue);
                }
                else
                {
                    return 0;
                }
            }
        }

        public int SliderRightActual
        {
            get
            {
                if (sliderRight > _Config.MiddleValue)
                {
                    return (int)(((float)sliderRight + (float)_Config.RightCalibrationMaximum) - (float)_Config.MiddleValue);
                }
                else if (sliderRight < _Config.MiddleValue)
                {
                    return (int)(((float)sliderRight - (float)_Config.RightCalibrationMinimum) - (float)_Config.MiddleValue);
                }
                else
                {
                    return 0;
                }
            }
        }

        #endregion

        #region Potentiometers

        //P1:<potentiometer_1>
        private int potentiometer1 { get; set; }
        public int Potentiometer1
        {
            get
            {
                return potentiometer1;
            }
            set
            {
                potentiometer1 = value;
                OnPropertyChanged("potentiometer1");
                OnPropertyChanged("Potentiometer1Actual");
            }
        }
        //P2:<potentiometer_2>
        private int potentiometer2 { get; set; }
        public int Potentiometer2
        {
            get
            {
                return potentiometer2;
            }
            set
            {
                potentiometer2 = value;
                OnPropertyChanged("potentiometer2");
                OnPropertyChanged("Potentiometer2Actual");
            }
        }
        //P3:<potentiometer_3>
        private int potentiometer3 { get; set; }
        public int Potentiometer3
        {
            get
            {
                return potentiometer3;
            }
            set
            {
                potentiometer3 = value;
                OnPropertyChanged("potentiometer3");
                OnPropertyChanged("Potentiometer3Actual");
            }
        }
        //P4:<potentiometer_4>
        private int potentiometer4 { get; set; }
        public int Potentiometer4
        {
            get
            {
                return potentiometer4;
            }
            set
            {
                potentiometer4 = value;
                OnPropertyChanged("potentiometer4");
                OnPropertyChanged("Potentiometer4Actual");
            }
        }
        //P5:<potentiometer_5>
        private int potentiometer5 { get; set; }
        public int Potentiometer5
        {
            get
            {
                return potentiometer5;
            }
            set
            {
                potentiometer5 = value;
                OnPropertyChanged("potentiometer5");
                OnPropertyChanged("Potentiometer5Actual");
            }
        }
        //P6:<potentiometer_6>
        private int potentiometer6 { get; set; }
        public int Potentiometer6
        {
            get
            {
                return potentiometer6;
            }
            set
            {
                potentiometer6 = value;
                OnPropertyChanged("potentiometer6");
                OnPropertyChanged("Potentiometer6Actual");
            }
        }
        //P6:<potentiometer_7>
        private int potentiometer7 { get; set; }
        public int Potentiometer7
        {
            get
            {
                return potentiometer7;
            }
            set
            {
                potentiometer7 = value;
                OnPropertyChanged("potentiometer7");
                OnPropertyChanged("Potentiometer7Actual");
            }
        }

        public int Potentiometer1Actual
        {
            get
            {
                if (potentiometer1 > _Config.MiddleValue)
                {
                    return (int)((float)potentiometer1 + (float)_Config.RawMaximum - (float)_Config.P1CalibrationMaximum);
                }
                else if (potentiometer1 < _Config.MiddleValue)
                {
                    return (int)((float)potentiometer1 + (float)_Config.RawMinimum - (float)_Config.P1CalibrationMinimum);
                }
                else
                {
                    return potentiometer1;
                }
            }
        }
        public int Potentiometer2Actual
        {
            get
            {
                if (potentiometer2 > _Config.MiddleValue)
                {
                    return (int)((float)potentiometer2 + (float)_Config.RawMaximum - (float)_Config.P2CalibrationMaximum);
                }
                else if (potentiometer2 < _Config.MiddleValue)
                {
                    return (int)((float)potentiometer2 + (float)_Config.RawMinimum - (float)_Config.P2CalibrationMinimum);
                }
                else
                {
                    return potentiometer2;
                }
            }
        }
        public int Potentiometer3Actual
        {
            get
            {
                if (potentiometer3 > _Config.MiddleValue)
                {
                    return (int)((float)potentiometer3 + (float)_Config.RawMaximum - (float)_Config.P3CalibrationMaximum);
                }
                else if (potentiometer3 < _Config.MiddleValue)
                {
                    return (int)((float)potentiometer3 + (float)_Config.RawMinimum - (float)_Config.P3CalibrationMinimum);
                }
                else
                {
                    return potentiometer3;
                }
            }
        }
        public int Potentiometer4Actual
        {
            get
            {
                if (potentiometer4 > _Config.MiddleValue)
                {
                    return (int)((float)potentiometer4 + (float)_Config.RawMaximum - (float)_Config.P4CalibrationMaximum);
                }
                else if (potentiometer4 < _Config.MiddleValue)
                {
                    return (int)((float)potentiometer4 + (float)_Config.RawMinimum - (float)_Config.P4CalibrationMinimum);
                }
                else
                {
                    return potentiometer4;
                }
            }
        }
        public int Potentiometer5Actual
        {
            get
            {
                if (potentiometer5 > _Config.MiddleValue)
                {
                    return (int)((float)potentiometer5 + (float)_Config.RawMaximum - (float)_Config.P5CalibrationMaximum);
                }
                else if (potentiometer5 < _Config.MiddleValue)
                {
                    return (int)((float)potentiometer5 + (float)_Config.RawMinimum - (float)_Config.P5CalibrationMinimum);
                }
                else
                {
                    return potentiometer5;
                }
            }
        }
        public int Potentiometer6Actual
        {
            get
            {
                if (potentiometer6 > _Config.MiddleValue)
                {
                    return (int)((float)potentiometer6 + (float)_Config.RawMaximum - (float)_Config.P6CalibrationMaximum);
                }
                else if (potentiometer6 < _Config.MiddleValue)
                {
                    return (int)((float)potentiometer6 + (float)_Config.RawMinimum - (float)_Config.P6CalibrationMinimum);
                }
                else
                {
                    return potentiometer6;
                }
            }
        }
        public int Potentiometer7Actual
        {
            get
            {
                if (potentiometer7 > _Config.MiddleValue)
                {
                    return (int)((float)potentiometer7 + (float)_Config.RawMaximum - (float)_Config.P7CalibrationMaximum);
                }
                else if (potentiometer7 < _Config.MiddleValue)
                {
                    return (int)((float)potentiometer7 + (float)_Config.RawMinimum - (float)_Config.P7CalibrationMinimum);
                }
                else
                {
                    return potentiometer7;
                }
            }
        }

        #endregion

        #region Arm

        private int armX { get; set; }
        public int ArmX
        {
            get
            {
                return armX;
            }
            set
            {
                armX = value;
                OnPropertyChanged("armX");
                OnPropertyChanged("armXColor");
            }
        }

        private int armY { get; set; }
        public int ArmY
        {
            get
            {
                return armY;
            }
            set
            {
                armY = value;
                OnPropertyChanged("armY");
                OnPropertyChanged("armYColor");
            }
        }

        private int armZ { get; set; }
        public int ArmZ
        {
            get
            {
                return armZ;
            }
            set
            {
                armZ = value;
                OnPropertyChanged("armZ");
                OnPropertyChanged("armZColor");
            }
        }

        private int armP { get; set; }
        public int ArmP
        {
            get
            {
                return armP;
            }
            set
            {
                armP = value;
                OnPropertyChanged("armP");
                OnPropertyChanged("armPColor");
            }
        }

        private int armW { get; set; }
        public int ArmW
        {
            get
            {
                return armW;
            }
            set
            {
                armW = value;
                OnPropertyChanged("armW");
                OnPropertyChanged("armWColor");
            }
        }

        private int armR { get; set; }
        public int ArmR
        {
            get
            {
                return armR;
            }
            set
            {
                armR = value;
                OnPropertyChanged("armR");
                OnPropertyChanged("armRColor");
            }
        }

        #endregion

        #region Box Drops

        //B1:<box_drop_1>
        private int boxDrop1 { get; set; }
        public int BoxDrop1
        {
            get
            {
                return boxDrop1;
            }
            set
            {
                boxDrop1 = value;
                OnPropertyChanged("boxDrop1");
                OnPropertyChanged("boxDrop1Color");
            }
        }
        //B2:<box_drop_2>
        private int boxDrop2 { get; set; }
        public int BoxDrop2
        {
            get
            {
                return boxDrop2;
            }
            set
            {
                boxDrop2 = value;
                OnPropertyChanged("boxDrop2");
                OnPropertyChanged("boxDrop2Color");
            }
        }
        //B3:1<box_drop_3>
        private int boxDrop3 { get; set; }
        public int BoxDrop3
        {
            get
            {
                return boxDrop3;
            }
            set
            {
                boxDrop3 = value;
                OnPropertyChanged("boxDrop3");
                OnPropertyChanged("boxDrop3Color");
            }
        }
        //B4:<box_drop_4>
        private int boxDrop4 { get; set; }
        public int BoxDrop4
        {
            get
            {
                return boxDrop4;
            }
            set
            {
                boxDrop4 = value;
                OnPropertyChanged("boxDrop4");
                OnPropertyChanged("boxDrop4Color");
            }
        }
        //B5:<box_drop_5>
        private int boxDrop5 { get; set; }
        public int BoxDrop5
        {
            get
            {
                return boxDrop5;
            }
            set
            {
                boxDrop5 = value;
                OnPropertyChanged("boxDrop5");
                OnPropertyChanged("boxDrop5Color");
            }
        }

        #endregion

        #region Camera

        //C1:<camera_select_1>
        private int cameraSelect1 { get; set; }
        public int CameraSelect1
        {
            get
            {
                return cameraSelect1;
            }
            set
            {
                cameraSelect1 = value;
                OnPropertyChanged("cameraSelect1");
                OnPropertyChanged("cameraSelect1Color");
            }
        }
        //C1:<camera_select_2>
        private int cameraSelect2 { get; set; }
        public int CameraSelect2
        {
            get
            {
                return cameraSelect2;
            }
            set
            {
                cameraSelect2 = value;
                OnPropertyChanged("cameraSelect2");
                OnPropertyChanged("cameraSelect2Color");
            }
        }
        //C1:<camera_select_3>
        private int cameraSelect3 { get; set; }
        public int CameraSelect3
        {
            get
            {
                return cameraSelect3;
            }
            set
            {
                cameraSelect3 = value;
                OnPropertyChanged("cameraSelect3");
                OnPropertyChanged("cameraSelect3Color");
            }
        }
        //C1:<camera_select_4>
        private int cameraSelect4 { get; set; }
        public int CameraSelect4
        {
            get
            {
                return cameraSelect4;
            }
            set
            {
                cameraSelect4 = value;
                OnPropertyChanged("cameraSelect4");
                OnPropertyChanged("cameraSelect4Color");
            }
        }

        #endregion

        #endregion

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(propertyName));
            }
        }
        
        #endregion

        #region IDataErrorInfo Members

        public string Error
        {
            get;
            private set;
        }

        public string this[string columnName]
        {
            get
            {
                switch (columnName)
                {
                    case "sensor1Temp":

                        break;
                    default:
                        if (sensor1Temp < 0 || sensor1Temp > 200)
                            Error = "Controller status is not properly set (0/1).";
                        else
                            Error = null;
                        break;
                }

                return Error;
            }
        }

        #endregion

    }
}
