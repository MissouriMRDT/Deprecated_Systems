namespace MRDT_GUI.Commands
{
    using Models;
    using Newtonsoft.Json;
    using Newtonsoft.Json.Linq;
    using System;

    internal class RoverMessageParser
    {
        private StateModel _State { get; set; }
        private NetworkControllerModel _Network { get; set; }

        public RoverMessageParser(StateModel stateModel, NetworkControllerModel networkModel)
        {
            _State = stateModel;
            _Network = networkModel;
        }

        public void Parse(string text)
        {
            if (text.Trim().Length == 0)
                return;
            var parsedText = JObject.Parse(text);
            switch (parsedText["type"].ToString())
            {
                case "temp":
                    var deserializedTemperature = JsonConvert.DeserializeObject<TemperatureObj>(text);
                    switch (deserializedTemperature.source_id)
                    {
                        case 1:
                            _State.Sensor1Temp = deserializedTemperature.temp;
                            break;
                        case 2:
                            _State.Sensor2Temp = deserializedTemperature.temp;
                            break;
                        case 3:
                            _State.Sensor3Temp = deserializedTemperature.temp;
                            break;
                        case 4:
                            _State.Sensor4Temp = deserializedTemperature.temp;
                            break;
                        case 5:
                            _State.Sensor5Temp = deserializedTemperature.temp;
                            break;
                        case 6:
                            _State.Sensor6Temp = deserializedTemperature.temp;
                            break;
                        case 7:
                            _State.Sensor7Temp = deserializedTemperature.temp;
                            break;
                        case 8:
                            _State.Sensor8Temp = deserializedTemperature.temp;
                            break;
                        case 9:
                            _State.Sensor9Temp = deserializedTemperature.temp;
                            break;
                        case 10:
                            _State.Sensor10Temp = deserializedTemperature.temp;
                            break;
                        case 11:
                            _State.Sensor11Temp = deserializedTemperature.temp;
                            break;
                        default:
                            break;
                    }
                    break;
                case "log":
                    var deserializedLog = JsonConvert.DeserializeObject<LogDataObj>(text);
                    UpdateConsole("Level: " + deserializedLog.level + ", Value: " + deserializedLog.value);
                    break;
                default:

                    break;
            }
        }

        private void UpdateConsole(string text)
        {
            _Network.ConsoleText = DateTime.Now.ToLongTimeString() + ": " + text + "\r\n" + _Network.ConsoleText;
        }
    }
}
