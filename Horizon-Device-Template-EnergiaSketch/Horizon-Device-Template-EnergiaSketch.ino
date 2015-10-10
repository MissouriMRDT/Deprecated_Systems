void setup()
{
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  
}//endsetup

void loop()
{
  // put your main code here, to run repeatedly:
  
  // wait for a thousnad milliseconds second
  delay(1000);  

  //Printf a debug message
  Serial.println("Rove So Hard");
  
}//endloop
