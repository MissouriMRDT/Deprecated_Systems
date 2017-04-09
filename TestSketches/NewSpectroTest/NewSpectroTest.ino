void setup() {
  // put your setup code here, to run once:
  pinMode(PM_5, OUTPUT);
  pinMode(PB_3, OUTPUT);
  pinMode(PF_0,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly: 
  motorForward();
  delay(5000);
  motorOff();
  delay(500);
  motorReverse();
  delay(5000);
  motorOff();
  delay(500);
}


void motorForward()
{
  digitalWrite(PM_5,HIGH);
  digitalWrite(PB_3,LOW);
  digitalWrite(PF_0, LOW);//LED
}

void motorReverse()
{
  digitalWrite(PF_0,LOW);
  digitalWrite(PF_0,HIGH);
  digitalWrite(PM_5,LOW);
  digitalWrite(PB_3,HIGH);
}

void motorOff()
{
  digitalWrite(PM_5,LOW);
  digitalWrite(PB_3,LOW);
}

