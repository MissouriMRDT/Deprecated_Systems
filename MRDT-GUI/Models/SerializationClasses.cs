namespace MRDT_GUI.Models
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Threading.Tasks;

    #region Sensor Data JSON Classes

    internal class TemperatureObj
    {
        public string type;
        public int source_id;
        public float temp;
    }

    internal class GpsObj
    {
        public string type;
        public string nmea;
    }

    internal class GyroAccelObj
    {
        public string type;
        public int pitch;
        public int yaw;
        public int roll;
        public int x;
        public int y;
        public int z;
    }

    internal class LogDataObj
    {
        public string type;
        public string value;
        public string level;
    }

    #endregion

    #region Rover Message Classes

    internal class DriveSlewCommand
    {
        public string type = "drive_motor";
        public string action = "slew_axis";
        public int id;
        public int speed;
    }
    internal class DriveDirectionCommand
    {
        public string type = "drive_motor";
        public string action = "slew_axis";
        public int id;
        public int direction; // 0 or 1
    }
    internal class DriveMoveAbsoluteCommand
    {
        public string type = "drive_motor";
        public string action = "move_absolute";
    }
    internal class DriveMoveRelativeCommand
    {
        public string type = "drive_motor";
        public string action = "move_relative";
    }
    internal class BoxDropCommand
    {
        public string type = "box_drop";
        public int open;
        public int id;
    }
    internal class ArmCommand
    {
        public string type = "arm";
        public string value;
    }
    internal class CameraServoPanCommand
    {
        public string type = "camera";
        public int id;
        public int pan;
    }
    internal class CameraServoTiltCommand
    {
        public string type = "camera";
        public int id;
        public int tilt;
    }
    internal class ResetMicroControllerCommand
    {
        public string type = "reset"; // = reset
    } // Add button for this.
    internal class SwitchRelayCommand
    {
        public string type = "relay";
        public int value;
    }
    internal class PassCallSignCommand
    {
        public string type = "callsign";
        public string callsign = "KD0VOB";
    }
    internal class SolarPanelCleanerSwitchCommand
    {
        public string type = "panel_cleaner";
        public int on; // 0 or 1
    }
    internal class SolarPanelCleanerKnobCommand
    {
        public string type = "panel_cleaner";
        public int speed;
    }
    internal class ArmGripperCommand
    {
        public string type = "gripper";
        public int pressure;
    }
    internal class LEDBrightnessCommand
    {
        public string type = "LED";
        public int brightness;
    }

    #endregion
}
