#define ZeroPercentVoltage 0.8;

float val = 0;
float RH = 0;
float my_room_temperature = 20; //in degrees C !
float max_voltage = 3.27;

void setup()
{
 Serial.begin(9600);
}

void loop()
{
 val = analogRead(0);
 delay(500);
 Serial.println(val);
 my_room_temperature = 20; // If you have temperature reading, put it here (centigrade!)
 max_voltage = (3.27-(0.006706*my_room_temperature)) ; // The max voltage value drops down 0.006705882 for each degree C over 0C. The voltage at 0C is 3.27 (corrected for zero precent voltage)
 RH = ((((val/1023)*5)-ZeroPercentVoltage)/max_voltage)*100;
 Serial.println(RH);
 delay(500);            
} 
