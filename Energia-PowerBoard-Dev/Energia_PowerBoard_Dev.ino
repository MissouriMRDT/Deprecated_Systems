/////////////////////Control
//PP_2
#define SIG_5V_Pin 11
//PN_3 
#define SIG_12V_Pin 12
//PK_7 
#define SIG_M1_Pin 71
//PQ_1 
#define SIG_M2_Pin 52
//PK_6 
#define SIG_M3_Pin 72
//PP_3
#define SIG_M4_Pin 53
//PH_1 
#define SIG_M5_Pin 73
//PH_0 
#define SIG_M6_Pin 74
//PA_7 
#define SIG_M7_Pin 57
//PP_5 
#define SIG_M8_Pin 58

///////////////////////Sense
//PE_3 
//#define VMEAS_VBATT_Pin PE3
//PD_7 
#define IMEAS_12V_Pin 27
//PE_2 
#define IMEAS_5V_Pin 25
//PK_3 
#define IMEAS_M1_Pin 68
//PK_2 
#define IMEAS_M2_Pin 67
//PK_1 
#define IMEAS_M3_Pin 66
//PD_4 
#define IMEAS_M4_Pin 45
//PK_0 
#define IMEAS_M5_Pin 65
//PB_5 
#define IMEAS_M6_Pin 64
//PB_4 
#define IMEAS_M7_Pin 63
//PD_2 
#define IMEAS_M8_Pin 42

#define DELAY_mS 100


int ADC_Value = 0;
float current = 0;


//The board has a 10-bit analog to digital converter on a 3.3 pin
//The current sensors output voltage 1.667 for 0 Amps and 2.667 for 40 Amps, at 4096 resolution giving 102.4 mAmp increments
const float ADC_MIN_EXPECTED = 4096 * 1.6667/3.3;
const float ADC_MAX_EXPECTED = 4096 * 2.6667/3.3;
const float HUMAN_MIN_EXPECTED = 0;
const float HUMAN_MAX_EXPECTED = 40;
float humanReadable_Current(float adc_val, float adc_min, float adc_max, float human_read_min, float human_read_max)
{
  return (adc_val - adc_min) * (human_read_max - human_read_min) / (adc_max - adc_min) + human_read_min;
}//end fnctn

//float voltage = 0;
//float voltScale = (1023.0 / 1023.0);
int ctrl = 0;

// the setup routine runs once when you press reset
void setup() 
{ 
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
 
  pinMode(SIG_5V_Pin, OUTPUT);
  pinMode(SIG_12V_Pin, OUTPUT);
  pinMode(SIG_M1_Pin, OUTPUT);
  pinMode(SIG_M2_Pin, OUTPUT);
  pinMode(SIG_M3_Pin, OUTPUT); 
  pinMode(SIG_M4_Pin, OUTPUT);
  pinMode(SIG_M5_Pin, OUTPUT);
  pinMode(SIG_M6_Pin, OUTPUT);
  pinMode(SIG_M7_Pin, OUTPUT);
  pinMode(SIG_M8_Pin, OUTPUT);
  
  digitalWrite(SIG_5V_Pin, HIGH);
  digitalWrite(SIG_12V_Pin, HIGH);
  digitalWrite(SIG_M1_Pin, HIGH);
  digitalWrite(SIG_M2_Pin, HIGH);
  digitalWrite(SIG_M3_Pin, HIGH);
  digitalWrite(SIG_M4_Pin, HIGH);
  digitalWrite(SIG_M5_Pin, HIGH);
  digitalWrite(SIG_M6_Pin, HIGH);
  digitalWrite(SIG_M7_Pin, HIGH);
  digitalWrite(SIG_M8_Pin, HIGH);

}//end setup

// the loop routine runs over and over again forever:
void loop() 
{
  digitalWrite(SIG_5V_Pin, HIGH);
  digitalWrite(SIG_12V_Pin, HIGH);
  
  if(Serial.available() >0 )
  {
    ctrl = Serial.parseInt();
  }//end if
  
  switch (ctrl) 
  {
    case 0:
      digitalWrite(SIG_5V_Pin, LOW);
      digitalWrite(SIG_12V_Pin, LOW);
      break;
    case 1:
      digitalWrite(SIG_5V_Pin, LOW);
      digitalWrite(SIG_12V_Pin, HIGH);
      break;
    case 2:
      digitalWrite(SIG_5V_Pin, HIGH);
      digitalWrite(SIG_12V_Pin, LOW);
      break;
    case 3:
      digitalWrite(SIG_5V_Pin, HIGH);
      digitalWrite(SIG_12V_Pin, HIGH);
      break;
    default:
      digitalWrite(SIG_5V_Pin, LOW);
      digitalWrite(SIG_12V_Pin, LOW);
      break;  
  }//end switch
      
  /*ADC_Value = analogRead(VMEAS_VBATT_Pin);   
  voltage = ??;
  Serial.print("VMEAS_VBATT_Pin: ");
  delay(DELAY_mS);*/
 
  Serial.print("IMEAS_12V_Pin: ");
  ADC_Value = analogRead(IMEAS_12V_Pin);
  Serial.print(" ADC_Value: "); 
  Serial.print(ADC_Value);
  current = humanReadable_Current(ADC_Value, ADC_MIN_EXPECTED, ADC_MAX_EXPECTED, HUMAN_MIN_EXPECTED, HUMAN_MAX_EXPECTED);
  Serial.print(" humanReadable_Current: "); 
  Serial.println(current, DEC);
  delay(DELAY_mS);

  Serial.print("IMEAS_5V_Pin: ");
  ADC_Value = analogRead(IMEAS_5V_Pin);
  Serial.print(" ADC_Value: "); 
  Serial.print(ADC_Value);  
  current = humanReadable_Current(ADC_Value, ADC_MIN_EXPECTED, ADC_MAX_EXPECTED, HUMAN_MIN_EXPECTED, HUMAN_MAX_EXPECTED);
  Serial.print(" humanReadable_Current: "); 
  Serial.println(current, DEC);
  delay(DELAY_mS);
  
  Serial.print("IMEAS_M1_Pin: ");
  ADC_Value = analogRead(IMEAS_M1_Pin);
  Serial.print(" ADC_Value: "); 
  Serial.print(ADC_Value);  
  current = humanReadable_Current(ADC_Value, ADC_MIN_EXPECTED, ADC_MAX_EXPECTED, HUMAN_MIN_EXPECTED, HUMAN_MAX_EXPECTED);
  Serial.print(" humanReadable_Current: "); 
  Serial.println(current, DEC);
  delay(DELAY_mS);
  
  Serial.print("IMEAS_M2_Pin: ");
  ADC_Value = analogRead(IMEAS_M2_Pin);  
  Serial.print(" ADC_Value: ");  
  Serial.print(ADC_Value);
  current = humanReadable_Current(ADC_Value, ADC_MIN_EXPECTED, ADC_MAX_EXPECTED, HUMAN_MIN_EXPECTED, HUMAN_MAX_EXPECTED);
  Serial.print(" humanReadable_Current: "); 
  Serial.println(current, DEC);
  delay(DELAY_mS);
  
  Serial.print("IMEAS_M3_Pin: ");
  ADC_Value = analogRead(IMEAS_M3_Pin);  
  Serial.print(" ADC_Value: ");
  Serial.print(ADC_Value);  
  current = humanReadable_Current(ADC_Value, ADC_MIN_EXPECTED, ADC_MAX_EXPECTED, HUMAN_MIN_EXPECTED, HUMAN_MAX_EXPECTED);
  Serial.print(" humanReadable_Current: "); 
  Serial.println(current, DEC);
  delay(DELAY_mS);
  
  Serial.print("IMEAS_M4_Pin: ");
  ADC_Value = analogRead(IMEAS_M4_Pin);
  Serial.print(" ADC_Value: ");  
  Serial.print(ADC_Value); 
  current = humanReadable_Current(ADC_Value, ADC_MIN_EXPECTED, ADC_MAX_EXPECTED, HUMAN_MIN_EXPECTED, HUMAN_MAX_EXPECTED);
  Serial.print(" humanReadable_Current: "); 
  Serial.println(current, DEC);
  delay(DELAY_mS);
  
  Serial.print("IMEAS_M5_Pin: ");
  ADC_Value = analogRead(IMEAS_M5_Pin); 
  Serial.print(" ADC_Value: ");  
  Serial.print(ADC_Value); 
  current = humanReadable_Current(ADC_Value, ADC_MIN_EXPECTED, ADC_MAX_EXPECTED, HUMAN_MIN_EXPECTED, HUMAN_MAX_EXPECTED);
  Serial.print(" humanReadable_Current: "); 
  Serial.println(current, DEC);
  delay(DELAY_mS);
  
  Serial.print("IMEAS_M6_Pin: ");
  ADC_Value = analogRead(IMEAS_M6_Pin);
  Serial.print(" ADC_Value: ");
  Serial.print(ADC_Value);   
  current = humanReadable_Current(ADC_Value, ADC_MIN_EXPECTED, ADC_MAX_EXPECTED, HUMAN_MIN_EXPECTED, HUMAN_MAX_EXPECTED);
  Serial.print(" humanReadable_Current: "); 
  Serial.println(current, DEC);
  delay(DELAY_mS);
  
  Serial.print("IMEAS_M7_Pin: ");
  ADC_Value = analogRead(IMEAS_M7_Pin);
  Serial.print(" ADC_Value: ");   
  Serial.print(ADC_Value); 
  current = humanReadable_Current(ADC_Value, ADC_MIN_EXPECTED, ADC_MAX_EXPECTED, HUMAN_MIN_EXPECTED, HUMAN_MAX_EXPECTED);
  Serial.print(" humanReadable_Current: "); 
  Serial.println(current, DEC);
  delay(DELAY_mS);
  
  Serial.print("IMEAS_M8_Pin: ");
  ADC_Value = analogRead(IMEAS_M8_Pin);  
  Serial.print(" ADC_Value: ");  
  Serial.print(ADC_Value); 
  current = humanReadable_Current(ADC_Value, ADC_MIN_EXPECTED, ADC_MAX_EXPECTED, HUMAN_MIN_EXPECTED, HUMAN_MAX_EXPECTED);
  Serial.print(" humanReadable_Current: "); 
  Serial.println(current, DEC);
  delay(DELAY_mS);

}//end loop
