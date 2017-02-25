//Test sketch for the spectrometer routine
/**********************************************
 * List of instructions:
 *    turn on motor for 5s
 *    then turn on laser - on for 30s
 *    ^soon as laser on, read photo diodes
 *    after 30s, turn off laser
 *    turn off motor
 *    stop reading photo diodes
 *    delay 2-3s
 *    return motor to initial position (35 seconds of reverse)
 */

uint16_t photo1, photo2;
 
void setup() {
  Serial.begin(9600);
  //initialize all pins 
  pinMode(PD_0, INPUT);//photodiode1
  pinMode(PD_1, INPUT);//photodiode2
  pinMode(PQ_3, OUTPUT);//laser
  /************************************
  * Spectrometer motor Initiaslization
  /***********************************/
  pinMode(PM_6, OUTPUT);//sleep
  pinMode(PQ_1, OUTPUT);//phase
  pinMode(PP_3, OUTPUT);//enable
  pinMode(PF_0, OUTPUT);//LED
  pinMode(PK_7, OUTPUT);//enable voltage reg
  digitalWrite(PK_7, HIGH);//turn on voltage reg

  Serial.println("Initialization Complete!");
}

void loop() {

   //turn on motor, run for 5s before continuing
   //direction is a bool! change true/false for direction
   spectroMotorOn(true);
   
   //do nothing except leave motor on for 5s
   delay(5000);

   //turn on laser
   turnOnLaser();
   
   //laser is on, motor should still be going?
   //keep laser and motor on for 30s
   int timer = 0;

    //loop takes analog readings 
    //delays for 1/8 second
    //should repeat until roughly 30s have passed.
   while (timer <= 30000)
   {
    //read photo diodes
    photo1 = analogRead(PD_0);
    photo2 = analogRead(PD_1);
    //print data
    Serial.println("Data for photodiodes 1 & 2, respectively:");
    Serial.println(photo1);
    Serial.println(photo2);
    timer += 125;
    delay(125); 
   }

   //turn off laser
   turnOffLaser();

   //turn off motor
   spectroMotorOff();

   //delay couple seconds
   delay(2000);

   //return motor to start position
   //opposite direction than what was called earlier!
   spectroMotorOn(false);

   //wait 35s for motor to return
   delay(35000);

   //stop motor again
   spectroMotorOff();

   //wait 10 seconds before repeating the loop
   delay(10000);
  
   
   
  
}

void spectroMotorOn(bool dir)
{
  digitalWrite(PM_6, HIGH);//nsleep
  if (dir)
    digitalWrite(PQ_1, HIGH);//phase
  if (!dir)
    digitalWrite(PQ_1, LOW);//opposoite phase
  
  digitalWrite(PP_3, HIGH);//ennable the motor
}

void spectroMotorOff()
{
  digitalWrite(PP_3, LOW);//en
  digitalWrite(PM_6, LOW);//nsleep
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
