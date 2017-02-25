  //declare integers for analog input, will be between 0 and 1023
  uint16_t analog1, analog2;

  int laserPin = PQ_3;
  

void setup() {
  // put your setup code here, to run once:
  pinMode(PQ_3, OUTPUT);//laser
  pinMode(PF_0, OUTPUT);//LED
  pinMode(PD_0, INPUT);
  pinMode(PD_1, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly: 

  
  //read analog data
  //analog1 = analogRead(PD_0);
  //some command here to send this value to base station
  //analog2 = analogRead(PD_1);

  /*Serial.print("analog1 = ");
  Serial.print(analog1);
  Serial.print("\n");*/

 // Serial.print("analog2 = ");
 // Serial.print(analog2);
  //Serial.print("\n");  
  

    //turn on laser function
    
  turnOnLaser();
  

  delay(2000);

  //turn off laser function
  turnOffLaser();

  delay (2000);

  Serial.println("loop...");
  
  
}

void turnOnLaser()
{
  //turn on laser by setting pin to High
  digitalWrite(PQ_3, HIGH);//laser
  digitalWrite(PF_0, HIGH);//LED
}

void turnOffLaser()
{
  //turn off laser by setting pin to low
  digitalWrite(PQ_3, LOW);//laser
  digitalWrite(PF_0, LOW);//led
}
