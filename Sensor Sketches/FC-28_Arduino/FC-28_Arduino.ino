//const int MODE = 2;   // Mode 1: Percentage mode
                      // Mode 2: Raw data mode (for Python)
//const String SENSOR = "FC-28";
void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
//  int percentage = -(analogRead(26)-4095) * 100 / 3870;
  int percentage = -(analogRead(26) - 4095) * 100 / 1850;
  if(percentage >= 100)
    Serial.println(100);
  else
    Serial.println(percentage);

  delay(100);
}






