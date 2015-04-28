#define CCD_CLOCK_LINE 4
#define CCD_SHUTTER 5
#define CCD_ICG 6
#define CCD_OS 0

const int CLOCKS_PER_CCD_CYCLE = 3;
const int SIGNAL_ELEMENTS = 3648;
const int PRE_DUMMY_ELEMENTS = 32;
const int POST_DUMMY_ELEMENTS = 14;


// -------  Clock bit-banging --------- //
void pulseClock()
{
  digitalWrite(CCD_CLOCK_LINE, HIGH);
  delayMicroseconds(4);
  digitalWrite(CCD_CLOCK_LINE, LOW);
  delayMicroseconds(4);
  return;  
}

void advanceElement()
{
  for(int i = 0; i < CLOCKS_PER_CCD_CYCLE; i++)
  {
    pulseClock();
  }
  return;
}

void CCD_StartStopSignal()
{
  pulseClock();
  digitalWrite(CCD_ICG, LOW);
  pulseClock();
  digitalWrite(CCD_SHUTTER, HIGH);
  for(int i = 0; i < 4; i++)
  {
    pulseClock();
  }
  digitalWrite(CCD_SHUTTER,LOW);
  for(int i = 0; i < 4; i++)
  {
    pulseClock();
  }
  digitalWrite(CCD_ICG, HIGH);
  return;    
}

// -------- Main Code -----------//
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(CCD_CLOCK_LINE, OUTPUT);
  pinMode(CCD_SHUTTER, OUTPUT);
  pinMode(CCD_ICG, OUTPUT);
}



void loop() {
  int starttime, stoptime;
  // put your main code here, to run repeatedly:
  Serial.println("Starting to read CCD");
  Serial.println("Element \tValue");
  Serial.println("-----------------------------------------");
  
  int value;
  int readingbuffer[50];
  
  CCD_StartStopSignal();
  for(int i = 0; i < PRE_DUMMY_ELEMENTS; i++)
  {
    advanceElement();
  }
  for(int i = 0; i < SIGNAL_ELEMENTS; i++)
  {
    value = analogRead(CCD_OS);
    if((i % 73) == 0) //Read one out of 73 elements, for a total of 50 / 3649
    {
      readingbuffer[i / 73] = value;
    }
    advanceElement();
  }
  for(int i = 0; i < POST_DUMMY_ELEMENTS; i++)
  {
    advanceElement();
  }
  CCD_StartStopSignal();
  
  for(int i = 0; i < 50; i ++)
  {
    Serial.print(i * 73, DEC);
    Serial.print("\t\t");
    Serial.println(readingbuffer[i]);
  }
  Serial.println("Done reading CCD array\n");
}
