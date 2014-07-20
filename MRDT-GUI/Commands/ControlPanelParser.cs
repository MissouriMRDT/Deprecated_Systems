namespace MRDT_GUI.Commands
{
    using Models;
    using Newtonsoft.Json;
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;

    internal class ControlPanelParser
    {
        private StateModel _State { get; set; }
        private NetworkControllerModel _Network { get; set; }
        private ConfigurationModel _Config { get; set; }
        private List<string> ControllerHeaders = new List<string>() { "K", "K1", "K2", "B1", "B2", "B3", "B4", "B5", "P", "C1", "C2", "C3", "C4", "P1", "P2", "P3", "P4", "P5", "P6", "P7", "SL", "SR", "AX", "AY", "AZ", "AP", "AW", "AR" };

        public ControlPanelParser(NetworkControllerModel network, StateModel state, ConfigurationModel config)
        {
            _Network = network;
            _State = state;
            _Config = config;
        }

        private void Send(string msg)
        {
            if (_Network.CanSend && _Network.Client.Connected)
            {
                msg += "\n";
                var encoder = new System.Text.ASCIIEncoding();
                var bytes = encoder.GetBytes(msg);
                var stream = _Network.Client.GetStream();
                stream.Write(bytes, 0, bytes.Length);
            }
        }

        public void Parse(string input)
        {
            if (input[0] == 'K' && input[1] == ':')
            {
                string[] values = input.Split(',');
                Dictionary<string, int> map = new Dictionary<string, int>();
                foreach (var com in values)
                {
                    if (com.Contains(":"))
                    {
                        try
                        {
                            string[] commandSplit = com.Split(':');
                            var key = commandSplit[0];
                            var value = Int32.Parse(commandSplit[1]);
                            if(!map.ContainsKey(key))
                                map.Add(key, value);
                        }
                        catch (Exception e)
                        {
                            Debug.Print("Fail parsing control panel input: " + input + ": " + e.Message);
                        }
                    }
                }

                if (_State.ControlPanelMap.Keys.Count > 0)
                {
                    foreach (var mapping in map)
                    {
                        if (ControllerHeaders.Contains(mapping.Key) && _State.ControlPanelMap[mapping.Key] == map[mapping.Key])
                        {
                            map.Remove(mapping.Key);
                        }
                    }
                }
                ProcessNewData(map);
            }
        }

        private void ProcessNewData(Dictionary<string, int> map)
        {
            foreach (var mapping in map)
            {
                var newValue = map[mapping.Key];
                switch (mapping.Key)
                {
                    case "SL":
                        if (_State.SliderLeft == newValue)
                            break;

                        if (newValue > _Config.DeadZoneMaximum && newValue < _Config.DeadZoneMinimum)
                        {
                            if (Math.Sign(_State.SliderLeft) != Math.Sign(newValue))
                            {
                                var com1 = new DriveDirectionCommand();
                                if (newValue > 0)
                                {
                                    com1.direction = 1;
                                }
                                else
                                {
                                    com1.direction = 0;
                                }
                                com1.id = 1;
                                string msg1 = JsonConvert.SerializeObject(com1);
                                Send(msg1);
                            }

                            var com2 = new DriveSlewCommand();
                            com2.speed = newValue;
                            com2.id = 1;
                            string msg2 = JsonConvert.SerializeObject(com2);
                            Send(msg2);
                        }
                        else
                        {
                            var com1 = new DriveSlewCommand();
                            com1.speed = 0;
                            com1.id = 1;
                            string msg1 = JsonConvert.SerializeObject(com1);
                            Send(msg1);
                        }

                        _State.SliderLeft = newValue;
                        break;
                    case "SR":
                        if (_State.SliderRight == newValue)
                            break;

                        if (newValue > _Config.DeadZoneMaximum && newValue < _Config.DeadZoneMinimum)
                        {
                            if (Math.Sign(_State.SliderRight) != Math.Sign(newValue))
                            {
                                var com3 = new DriveDirectionCommand();
                                if (newValue > 0)
                                {
                                    com3.direction = 1;
                                }
                                else
                                {
                                    com3.direction = 0;
                                }
                                com3.id = 3;
                                string msg3 = JsonConvert.SerializeObject(com3);
                                Send(msg3);
                            }

                            if (_State.SliderRight != newValue)
                            {
                                var com4 = new DriveSlewCommand();
                                com4.speed = newValue;
                                com4.id = 3;
                                string msg4 = JsonConvert.SerializeObject(com4);
                                Send(msg4);
                            }
                        }
                        else
                        {
                            var com1 = new DriveSlewCommand();
                            com1.speed = 0;
                            com1.id = 3;
                            string msg1 = JsonConvert.SerializeObject(com1);
                            Send(msg1);
                        }

                        _State.SliderRight = newValue;
                        break;
                    case "AX": //5
                        if (_State.ArmX == newValue)
                            break;
                        var armMessage = GetArmXMessage(newValue);
                        Send(armMessage);
                        _State.ArmX = newValue;
                        break;
                    case "AY"://6
                        if (_State.ArmY == newValue)
                            break;
                        Send(GetArmYMessage(newValue));
                        _State.ArmY = newValue;
                        break;
                    case "AZ"://7
                        if (_State.ArmZ == newValue)
                            break;
                        Send(GetArmZMessage(newValue));
                        _State.ArmZ = newValue;
                        break;
                    case "AP"://8
                        if (_State.ArmP == newValue)
                            break;
                        Send(GetArmPMessage(newValue));
                        _State.ArmP = newValue;
                        break;
                    case "AW"://9
                        if (_State.ArmW == newValue)
                            break;
                        Send(GetArmWMessage(newValue));
                        _State.ArmW = newValue;
                        break;
                    case "AR"://10
                        if (_State.ArmR == newValue)
                            break;
                        Send(GetArmRMessage(newValue));
                        _State.ArmR = newValue;
                        break;
                    case "P1"://11
                        if (_State.Potentiometer1 == newValue)
                            break;
                        var com11 = new CameraServoPanCommand();
                        com11.id = 1;
                        com11.pan = (int)((float)newValue * (float)180 / (float)1024);
                        string msg11 = JsonConvert.SerializeObject(com11);
                        Send(msg11);
                        _State.Potentiometer1 = newValue;
                        break;
                    case "P2":
                        if (_State.Potentiometer2 == newValue)
                            break;
                        var com12 = new CameraServoTiltCommand();
                        com12.id = 1;
                        com12.tilt = (int)((float)newValue * (float)90 / (float)1024);
                        string msg12 = JsonConvert.SerializeObject(com12);
                        Send(msg12);
                        _State.Potentiometer2 = newValue;
                        break;
                    case "P3":
                        if (_State.Potentiometer3 == newValue)
                            break;
                        var com13 = new CameraServoPanCommand();
                        com13.id = 2;
                        com13.pan = (int)((float)newValue * (float)180 / (float)1024);
                        string msg13 = JsonConvert.SerializeObject(com13);
                        Send(msg13);
                        _State.Potentiometer3 = newValue;
                        break;
                    case "P4":
                        if (_State.Potentiometer4 == newValue)
                            break;
                        var com14 = new CameraServoTiltCommand();
                        com14.id = 2;
                        com14.tilt = (int)((float)newValue * (float)90 / (float)1024);
                        string msg14 = JsonConvert.SerializeObject(com14);
                        Send(msg14);
                        _State.Potentiometer4 = newValue;
                        break;
                    case "P5":
                        if (_State.Potentiometer5 == newValue)
                            break;
                        // FIXME
                        /*var com15 = new SolarPanelCleanerKnobCommand();
                        com15.speed = newValue;
                        string msg15 = JsonConvert.SerializeObject(com15);
                        Send(msg15);
                        _State.Potentiometer5 = newValue;*/
                        break;
                    case "P6":
                        if (_State.Potentiometer6 == newValue)
                            break;
                        var com16 = new ArmGripperCommand();
                        com16.pressure = newValue;
                        string msg16 = JsonConvert.SerializeObject(com16);
                        Send(msg16);
                        _State.Potentiometer6 = newValue;
                        break;
                    case "P7":
                        if (_State.Potentiometer7 == newValue)
                            break;
                        var com17 = new LEDBrightnessCommand();
                        com17.brightness = newValue;
                        string msg17 = JsonConvert.SerializeObject(com17);
                        Send(msg17);
                        _State.Potentiometer7 = newValue;
                        break;
                    case "K":
                        if (_State.KillSwitch == newValue)
                            break;
                        var com18 = new SwitchRelayCommand();
                        com18.value = newValue;
                        string msg18 = JsonConvert.SerializeObject(com18);
                        Send(msg18);
                        _State.KillSwitch = newValue;
                        break;
                    case "K1":
                        // Not used.
                        _State.Key1 = newValue;
                        break;
                    case "K2":
                        // Not used.
                        _State.Key2 = newValue;
                        break;
                    case "B1":
                        if (_State.BoxDrop1 == newValue)
                            break;
                        var com19 = new BoxDropCommand();
                        com19.open = newValue;
                        com19.id = 1;
                        string msg19 = JsonConvert.SerializeObject(com19);
                        Send(msg19);
                        _State.BoxDrop1 = newValue;
                        break;
                    case "B2":
                        if (_State.BoxDrop2 == newValue)
                            break;
                        var com20 = new BoxDropCommand();
                        com20.open = newValue;
                        com20.id = 2;
                        string msg20 = JsonConvert.SerializeObject(com20);
                        Send(msg20);
                        _State.BoxDrop2 = newValue;
                        break;
                    case "B3":
                        if (_State.BoxDrop3 == newValue)
                            break;
                        var com21 = new BoxDropCommand();
                        com21.open = newValue;
                        com21.id = 3;
                        string msg21 = JsonConvert.SerializeObject(com21);
                        Send(msg21);
                        _State.BoxDrop3 = newValue;
                        break;
                    case "B4":
                        if (_State.BoxDrop4 == newValue)
                            break;
                        var com22 = new BoxDropCommand();
                        com22.open = newValue;
                        com22.id = 4;
                        string msg22 = JsonConvert.SerializeObject(com22);
                        Send(msg22);
                        _State.BoxDrop4 = newValue;
                        break;
                    case "B5":
                        if (_State.BoxDrop5 == newValue)
                            break;
                        var com23 = new BoxDropCommand();
                        com23.open = newValue;
                        com23.id = 5;
                        string msg23 = JsonConvert.SerializeObject(com23);
                        Send(msg23);
                        _State.BoxDrop5 = newValue;
                        break;
                    case "P":
                        if (_State.PanelCleaner == newValue)
                            break;
                        var com24 = new SolarPanelCleanerSwitchCommand();
                        com24.on = newValue;
                        string msg24 = JsonConvert.SerializeObject(com24);
                        Send(msg24);
                        _State.PanelCleaner = newValue;
                        break;
                    case "C1":
                        // Not used.
                        _State.CameraSelect1 = newValue;
                        break;
                    case "C2":
                        // Not used.
                        _State.CameraSelect2 = newValue;
                        break;
                    case "C3":
                        // Not used.
                        _State.CameraSelect3 = newValue;
                        break;
                    case "C4":
                        // Not used.
                        _State.CameraSelect4 = newValue;
                        break;
                    default:
                        break;
                }
            }
        }

        private string GetArmXMessage(int newValue)
        {
            var command = new ArmCommand();
            if (newValue == 0)
                command.value = "0000000"; // Stop
            else if (newValue == 1)
                command.value = "0010000"; // Positive-X
            else if (newValue == 2)
                command.value = "0010001"; // Negative-X
            string msg = JsonConvert.SerializeObject(command);
            return msg;
        }

        private string GetArmYMessage(int newValue)
        {
            var command = new ArmCommand();
            if (newValue == 0)
                command.value = "0000000"; // Stop
            else if (newValue == 1)
                command.value = "0010010"; // Positive-Y
            else if (newValue == 2)
                command.value = "0010011"; // Negative-Y
            string msg = JsonConvert.SerializeObject(command);
            return msg;
        }

        private string GetArmZMessage(int newValue)
        {
            var command = new ArmCommand();
            if (newValue == 0)
                command.value = "0000000"; // Stop
            else if (newValue == 1)
                command.value = "0010100"; // Positive-Z
            else if (newValue == 2)
                command.value = "0010101"; // Negative-Z
            string msg = JsonConvert.SerializeObject(command);
            return msg;
        }

        private string GetArmPMessage(int newValue)
        {
            var command = new ArmCommand();
            if (newValue == 0)
                command.value = "0000000"; // Stop
            else if (newValue == 1)
                command.value = "0100100"; // Positive-P
            else if (newValue == 2)
                command.value = "0100101"; // Negative-P
            string msg = JsonConvert.SerializeObject(command);
            return msg;
        }

        private string GetArmWMessage(int newValue)
        {
            var command = new ArmCommand();
            if (newValue == 0)
                command.value = "0000000"; // Stop
            else if (newValue == 1)
                command.value = "0100110"; // Positive-W
            else if (newValue == 2)
                command.value = "0100111"; // Negative-W
            string msg = JsonConvert.SerializeObject(command);
            return msg;
        }

        private string GetArmRMessage(int newValue)
        {
            var command = new ArmCommand();
            if (newValue == 0)
                command.value = "0000000"; // Stop
            else if (newValue == 1)
                command.value = "0100010"; // Positive-R
            else if (newValue == 2)
                command.value = "0100011"; // Negative-R
            string msg = JsonConvert.SerializeObject(command);
            return msg;
        }
    }
}
