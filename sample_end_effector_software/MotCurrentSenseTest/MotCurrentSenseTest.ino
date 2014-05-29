const int INA = 7;
const int INB = 8;
const int MOT_PWM = 9;
const int CURR_SENS = 3;
const int STABILIZATION_TIME = 500; //time to allow drill to reach constant operation
const int SPEED_STEP = 15;
const int RELAY = 12;

//Descript: Reads average current over acc milliseconds
//Pre: Motor should be driving at desired speed to take measurements at
//Post: Other operations halt until acc milliseconds after this operation is run. Average
//      reading from the pin is reported within the range from 0 to 255
int currentRead(int pin, int acc = 0);

void raw_set_speed(byte speed);

int current;

void setup()
{
  delay(10000);
  Serial.begin(9600);
  pinMode(INA, OUTPUT);
  pinMode(INB,OUTPUT);
  pinMode(MOT_PWM, OUTPUT);
  pinMode(RELAY, OUTPUT);
  
  /*----Relay Test----*/
  digitalWrite(RELAY, LOW);
  delay(500);
  digitalWrite(RELAY, HIGH);
  delay(500);
  
  /*----Test in Forward Direction----*/
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);
  for(int i=255; i>0; i= i - SPEED_STEP)
  {
    String row = "";
    analogWrite(MOT_PWM, i);
    delay(STABILIZATION_TIME);
    current = currentRead(CURR_SENS,40);
    row += i;
    row += " , ";
    row += current;
    Serial.println(row);
  }
  digitalWrite(MOT_PWM, LOW);
  delay(2000);
  
  /*----Test in Reverse Direction----*/
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);
  for(int i=255; i>0; i = i - SPEED_STEP)
  {
    String row = "";
    analogWrite(MOT_PWM, i);
    delay(STABILIZATION_TIME);
    current = currentRead(CURR_SENS,40);
    row += i;
    row += " , ";
    row += current;
    Serial.println(row);
  }
  digitalWrite(MOT_PWM, LOW);
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);
}

void loop()
{
  
}

int currentRead(int pin, int acc)
{
  int current = 0;
  for(int i = 0; i<acc; i++)
  {
    current += analogRead(pin);
    delay(1);
  }
  current /= acc;
 
  return current;
}
