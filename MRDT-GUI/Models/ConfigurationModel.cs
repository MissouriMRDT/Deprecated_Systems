namespace MRDT_GUI.Models
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.Linq;
    using System.Text;
    using System.Threading.Tasks;

    public class ConfigurationModel : INotifyPropertyChanged
    {
        public ConfigurationModel()
        {
            rawMinimum = 0;
            rawMaximum = 1024;
            rawMinimum = 0;
            rawMaximum = 1024;
            resolution = 1024;
            deadZoneMinimumMagnitude = 100;
            deadZoneMaximumMagnitude = 100;
            leftCalibrationMinimum = 0;
            leftCalibrationMaximum = 1023;
            rightCalibrationMinimum = 0;
            rightCalibrationMaximum = 1023;

            p1CalibrationMaximum = 1024;
            p1CalibrationMinimum = 0;
            p2CalibrationMaximum = 1024;
            p2CalibrationMinimum = 0;
            p3CalibrationMaximum = 1024;
            p3CalibrationMinimum = 0;
            p4CalibrationMaximum = 1024;
            p4CalibrationMinimum = 0;
            p5CalibrationMaximum = 1024;
            p5CalibrationMinimum = 0;
            p6CalibrationMaximum = 1024;
            p6CalibrationMinimum = 0;
            p7CalibrationMaximum = 1024;
            p7CalibrationMinimum = 0;
        }

        private int rawMinimum { get; set; }
        public int RawMinimum
        {
            get
            {
                return rawMinimum;
            }
            set
            {
                rawMinimum = value;
                OnPropertyChanged("rawMinimum");
            }
        }

        private int rawMaximum { get; set; }
        public int RawMaximum
        {
            get
            {
                return rawMaximum;
            }
            set
            {
                rawMaximum = value;
                OnPropertyChanged("rawMaximum");
            }
        }

        private int resolution { get; set; }
        public int Resolution
        {
            get
            {
                return resolution;
            }
            set
            {
                resolution = value;
                OnPropertyChanged("resolution");
            }
        }

        public int MiddleValue
        {
            get
            {
                return resolution / 2;
            }
        }

        #region Slider Fields/Properties

        // Bottom value of slider deadzones
        private int deadZoneMinimumMagnitude { get; set; }
        public int DeadZoneMinimum
        {
            get
            {
                return MiddleValue - deadZoneMinimumMagnitude;
            }
            set
            {
                deadZoneMinimumMagnitude = value;
                OnPropertyChanged("deadZoneMinimumMagnitude");
            }
        }

        // Top value of slider deadzones
        private int deadZoneMaximumMagnitude { get; set; }
        public int DeadZoneMaximum
        {
            get
            {
                return MiddleValue + deadZoneMaximumMagnitude;
            }
            set
            {
                deadZoneMaximumMagnitude = value;
                OnPropertyChanged("deadZoneMaximumMagnitude");
            }
        }

        private int leftCalibrationMinimum { get; set; }
        public int LeftCalibrationMinimum
        {
            get
            {
                return leftCalibrationMinimum;
            }
            set
            {
                leftCalibrationMinimum = value;
                OnPropertyChanged("leftCalibrationMinimum");
            }
        }

        private int rightCalibrationMinimum { get; set; }
        public int RightCalibrationMinimum
        {
            get
            {
                return rightCalibrationMinimum;
            }
            set
            {
                rightCalibrationMinimum = value;
                OnPropertyChanged("rightCalibrationMinimum");
            }
        }

        private int leftCalibrationMaximum { get; set; }
        public int LeftCalibrationMaximum
        {
            get
            {
                return leftCalibrationMaximum;
            }
            set
            {
                leftCalibrationMaximum = value;
                OnPropertyChanged("leftCalibrationMaximum");
            }
        }

        private int rightCalibrationMaximum { get; set; }
        public int RightCalibrationMaximum
        {
            get
            {
                return rightCalibrationMaximum;
            }
            set
            {
                rightCalibrationMaximum = value;
                OnPropertyChanged("rightCalibrationMaximum");
            }
        }

        #endregion

        #region Potentiometers

        #region P1

        private int p1CalibrationMinimum { get; set; }
        public int P1CalibrationMinimum
        {
            get
            {
                return p1CalibrationMinimum;
            }
            set
            {
                p1CalibrationMinimum = value;
                OnPropertyChanged("p1CalibrationMinimum");
            }
        }

        private int p1CalibrationMaximum { get; set; }
        public int P1CalibrationMaximum
        {
            get
            {
                return p1CalibrationMaximum;
            }
            set
            {
                leftCalibrationMaximum = value;
                OnPropertyChanged("p1CalibrationMaximum");
            }
        }

        #endregion

        #region P2

        private int p2CalibrationMinimum { get; set; }
        public int P2CalibrationMinimum
        {
            get
            {
                return p2CalibrationMinimum;
            }
            set
            {
                p2CalibrationMinimum = value;
                OnPropertyChanged("p2CalibrationMinimum");
            }
        }

        private int p2CalibrationMaximum { get; set; }
        public int P2CalibrationMaximum
        {
            get
            {
                return p2CalibrationMaximum;
            }
            set
            {
                p2CalibrationMaximum = value;
                OnPropertyChanged("p2CalibrationMaximum");
            }
        }

        #endregion

        #region P3

        private int p3CalibrationMinimum { get; set; }
        public int P3CalibrationMinimum
        {
            get
            {
                return p3CalibrationMinimum;
            }
            set
            {
                p3CalibrationMinimum = value;
                OnPropertyChanged("p3CalibrationMinimum");
            }
        }

        private int p3CalibrationMaximum { get; set; }
        public int P3CalibrationMaximum
        {
            get
            {
                return p3CalibrationMaximum;
            }
            set
            {
                p3CalibrationMaximum = value;
                OnPropertyChanged("p3CalibrationMaximum");
            }
        }

        #endregion

        #region P4

        private int p4CalibrationMinimum { get; set; }
        public int P4CalibrationMinimum
        {
            get
            {
                return p4CalibrationMinimum;
            }
            set
            {
                p4CalibrationMinimum = value;
                OnPropertyChanged("p4CalibrationMinimum");
            }
        }

        private int p4CalibrationMaximum { get; set; }
        public int P4CalibrationMaximum
        {
            get
            {
                return p4CalibrationMaximum;
            }
            set
            {
                p4CalibrationMaximum = value;
                OnPropertyChanged("p4CalibrationMaximum");
            }
        }

        #endregion

        #region P5

        private int p5CalibrationMinimum { get; set; }
        public int P5CalibrationMinimum
        {
            get
            {
                return p5CalibrationMinimum;
            }
            set
            {
                p5CalibrationMinimum = value;
                OnPropertyChanged("p5CalibrationMinimum");
            }
        }

        private int p5CalibrationMaximum { get; set; }
        public int P5CalibrationMaximum
        {
            get
            {
                return p5CalibrationMaximum;
            }
            set
            {
                p5CalibrationMaximum = value;
                OnPropertyChanged("p5CalibrationMaximum");
            }
        }

        #endregion

        #region P6

        private int p6CalibrationMinimum { get; set; }
        public int P6CalibrationMinimum
        {
            get
            {
                return p6CalibrationMinimum;
            }
            set
            {
                p6CalibrationMinimum = value;
                OnPropertyChanged("p6CalibrationMinimum");
            }
        }

        private int p6CalibrationMaximum { get; set; }
        public int P6CalibrationMaximum
        {
            get
            {
                return p6CalibrationMaximum;
            }
            set
            {
                p6CalibrationMaximum = value;
                OnPropertyChanged("p6CalibrationMaximum");
            }
        }

        #endregion

        #region P7

        private int p7CalibrationMinimum { get; set; }
        public int P7CalibrationMinimum
        {
            get
            {
                return p7CalibrationMinimum;
            }
            set
            {
                p7CalibrationMinimum = value;
                OnPropertyChanged("p7CalibrationMinimum");
            }
        }

        private int p7CalibrationMaximum { get; set; }
        public int P7CalibrationMaximum
        {
            get
            {
                return p7CalibrationMaximum;
            }
            set
            {
                p7CalibrationMaximum = value;
                OnPropertyChanged("p7CalibrationMaximum");
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
                    default:

                        break;
                }

                return Error;
            }
        }

        #endregion
    }
}
