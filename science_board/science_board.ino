

void setup() {
  // put your setup code here, to run once:

pinMode(PM_6, OUTPUT);//sleep
pinMode(PQ_1, OUTPUT);//phase
pinMode(PP_3, OUTPUT);//enable
Serial.begin(9600);
  

}
  
void loop() {
  // put your main code here, to run repeatedly: 
  Serial.println("Testing...");
  digitalWrite(PM_6, HIGH);
  digitalWrite(PQ_1, LOW);
  digitalWrite(PP_3, HIGH);
  delay(15000);
  digitalWrite(PP_3, LOW);
  delay(100);
  digitalWrite(PM_6, LOW);
  delay(3000);

  
}
