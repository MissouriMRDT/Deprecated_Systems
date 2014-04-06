#ifndef GAS_SENSE_H
#define GAS_SENSE_H

const int WARM_UP_DELAY = 25; //Warm up delay for gas sensors in milliseconds
const int ACCURACY = 20; //Number of reads to average data from
const int READ_SPACE = 1; //ms between reads of the sensor

//Desc: Reads gas sensor data from specified sensor and returns the gas concentration reading
//      on a scale of 0 to 1024
//Pre:  Gas sensors have been turned on with initGasSensors
//Post: Sensors are turned on, gas concentration data is returned, and sensors are turned off
int readGas(const int sensor)
{
  int result;
    
  //Gets average reading 
  for(int i=0; i<ACCURACY; i++)
  {
    result += analogRead(sensor);
    delay(READ_SPACE);
  }
  result /= ACCURACY;
  return result;
}

void init_gas_sensors()
{
  ToggleHeatingElement(true);
  delay(WARM_UP_DELAY);
}

void ToggleHeatingElement(bool state)
{
  if(state==true)
  {
    digitalWrite(HEAT_CTRL,HIGH);
  }
  else
  {
    digitalWrite(HEAT_CTRL,LOW);
  }
}

void updateGasData(SgasData &gasData)
{
  int hydrogen, methane, ammonia;
  

#endif  
