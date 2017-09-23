  //declare integers for analog input, will be between 0 and 1023
  uint16_t analog1, analog2;

  int laserPin = 46;
  

void setup() {
  // put your setup code here, to run once:
  pinMode(laserPin, OUTPUT);//laser
  pinMode(PF_0, OUTPUT);//LED
  pinMode(PD_2, INPUT);//photo 1
  pinMode(PD_3, INPUT);//photo 2
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly: 

  
//  //read analog data
//  analog1 = analogRead(PD_2);
//  //some command here to send this value to base station
//  analog2 = analogRead(PD_3);
//
//  Serial.print("analog1 = ");
//  Serial.print(analog1);
//  Serial.print("\n");
//
//  Serial.print("analog2 = ");
//  Serial.print(analog2);
//  Serial.print("\n");  
  

  //turn on laser function
    
  turnOnLaser();
  

  delay(20000);

  //turn off laser function
  turnOffLaser();

  delay (5000);

  Serial.println("loop...");
  
  
}

void turnOnLaser()
{
  //turn on laser by setting pin to High
  digitalWrite(laserPin, HIGH);//laser
  digitalWrite(PF_0, HIGH);//LED
}

void turnOffLaser()
{
  //turn off laser by setting pin to low
  digitalWrite(laserPin, LOW);//laser
  digitalWrite(PF_0, LOW);//led
}
