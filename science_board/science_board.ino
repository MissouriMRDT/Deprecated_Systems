void setup() {
  // put your setup code here, to run once:
  
  timecnt=millis();
  digitalwrite(PM_6, HIGH);
  digitalwrite(PQ_1, LOW);
  while(timecnt<120000)
  {
    analogwrite(PP_3, 4);
    timecnt=millis();  
  }
  digitalwrite(PP_3, LOW);
  delay(100);
  digitalwrite(PM_6, LOW);

}
  
void loop() {
  // put your main code here, to run repeatedly: 
  
}
