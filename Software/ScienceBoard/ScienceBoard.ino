//----------------------
// Pin assignments
//----------------------

const int LASER_CTR = 6;

const int PH_SENS_RX = 2;
const int PH_SENS_TX = 3;

const int CCD_RX = 4;
const int CCD_TX = 5;

const int MOIS_SENSOR = 0; //Analog

void setup() {
  // put your setup code here, to run once:
  pinMode(LASER_CTR, OUTPUT);  
  Serial.begin(115200);
  
    digitalWrite(LASER_CTR, LOW);
  Serial.println("Laser off");
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(LASER_CTR, HIGH);
  Serial.println("Laser on");
  delay(5000);
  
}
