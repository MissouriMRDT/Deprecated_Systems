

void setup() {
  // put your setup code here, to run once:

pinMode(PM_6, OUTPUT);//sleep
pinMode(PQ_1, OUTPUT);//phase
pinMode(PP_3, OUTPUT);//enable
pinMode(PF_0, OUTPUT);//LED
pinMode(PK_7, OUTPUT);//enable voltage reg
digitalWrite(PK_7, HIGH);

Serial.begin(9600);
  

}
  
void loop() {
  // put your main code here, to run repeatedly: 
  Serial.println("Testing...");
  digitalWrite(PM_6, HIGH);//nsleep
  digitalWrite(PQ_1, LOW);//phase
  digitalWrite(PP_3, HIGH);//en
  digitalWrite(PF_0, HIGH);
  delay(15000);
  
  digitalWrite(PP_3, LOW);//en
  delay(100);
  digitalWrite(PM_6, LOW);//nsleep
  digitalWrite(PF_0, LOW);
  delay(15000);

  
}
