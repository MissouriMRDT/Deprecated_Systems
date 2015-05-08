const int DELAY = 20;
//char cmd;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if(Serial.available)
    Serial.read();
}
