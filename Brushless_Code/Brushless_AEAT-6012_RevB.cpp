#inc#include <avr/pgmspace.h>

volatile int LongPWM = 0; //The effective duty cycle
volatile unsigned int Motor_pos=0;//current motor position
volatile unsigned int last_pos=0;//position of the motor at last sampling
unsigned int Motor_ang=0;//Motor angle
unsigned int PhaseA_pos=0;//Angle of the different phases
unsigned int PhaseB_pos=0;
unsigned int PhaseC_pos=0;
volatile int Phase_Shift=0;//Allows the phase to be shifted
volatile int c_speed = 0;//Speed based on interrupt speed
//PID variables
int error = 0;
int integral = 0;
int d_speed = 0;
int ki = 0;
int kp= 0;
//Bytes for the switch PWMs
byte PhaseA_angle=0;
byte PhaseB_angle=0;
byte PhaseC_angle=0;
byte PWM_A=0;
byte PWM_B=0;
byte PWM_C=0;
byte PWM_D =0;
//Look-up table for the PWM signals to generate a sine wave
//based on the motor position
const byte angle[] PROGMEM={//Sorry that this part is so long
255,255,255,255,254,254,254,253,253,252,251,250,250,249,248,246,245,244,243,241,240,238,
237,235,234,232,230,228,226,224,222,220,218,215,213,211,208,206,203,201,198,196,193,190,
188,185,182,179,176,173,170,167,165,162,158,155,152,149,146,143,140,137,134,131,128,124,
121,118,115,112,109,106,103,100,97,93,90,88,85,82,79,76,73,70,67,65,62,59,57,54,52,49,47,
44,42,40,37,35,33,31,29,27,25,23,21,20,18,17,15,14,12,11,10,9,7,6,5,5,4,3,2,2,1,1,1,0,0,
0,0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,17,18,20,21,23,25,27,29,31,33,35,37,40,
42,44,47,49,52,54,57,59,62,65,67,70,73,76,79,82,85,88,90,93,97,100,103,106,109,112,115,
118,121,124,128,131,134,137,140,143,146,149,152,155,158,162,165,167,170,173,176,179,182,
185,188,190,193,196,198,201,203,206,208,211,213,215,218,220,222,22,226,228,230,232,234,
235,237,238,240,241,243,244,245,246,248,249,250,250,251,252,253,253,254,254,254,255,255,
255,255,255,255,255,254,254,254,253,253,252,251,250,250,249,248,246,245,244,243,241,240,
238,237,235,234,232,230,228,226,224,222,220,218,215,213,211,208,206,203,201,198,196,193,
190,188,185,182,179,176,173,170,167,165,162,15,155,152,149,146,143,140,137,134,131,128,
124,121,118,115,112,109,106,103,100,97,93,90,88,85,82,79,76,73,70,67,65,62,59,57,54,52,
49,47,44,42,40,37,35,33,31,29,27,25,23,21,20,18,17,15,14,12,11,10,9,7,6,5,5,4,3,2,2,1,1,
1,0,0,0,0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,17,18,20,21,23,25,27,29,31,33,35,
37,40,42,44,47,49,52,54,57,59,62,65,67,70,73,76,79,82,85,88,90,93,97,100,103,106,109,112,
115,118,121,124,128,131,134,137,140,143,146,149,152,155,158,162,165,167,170,173,176,179,
182,185,188,190,193,196,198,201,203,206,208,211,213,215,218,220,222,24,226,228,230,232,
234,235,237,238,240,241,243,244,245,246,248,249,250,250,251,252,253,253,254,254,254,255,
255,255,255,255,255,255,254,254,254,253,253,252,251,250,250,249,248,246,245,244,243,241,
240,238,237,235,234,232,23,228,226,224,222,220,218,215,213,211,208,206,203,201,198,196,
193,190,188,185,182,179,176,173,170,167,165,162,18,155,152,149,146,143,140,137,134,131,
128,124,121,118,115,112,109,106,103,100,97,93,90,88,85,82,79,76,73,70,67,65,62,59,57,54,
52,49,47,44,42,40,37,35,33,31,29,27,25,23,21,20,18,17,15,14,12,11,10,9,7,6,5,5,4,3,2,2,
1,1,1,0,0,0,0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,17,18,20,21,23,25,27,29,31,33,
35,37,40,42,44,47,49,52,54,5,59,62,65,67,70,73,76,79,82,85,88,90,93,97,100,103,106,109,112,
115,118,121,124,128,131,134,137,140,143,146,149,152,155,158,162,165,167,170,173,176,179,
182,185,188,190,193,196,198,201,203,206,208,211,213,215,218,220,222,24,226,228,230,232,
234,235,237,238,240,241,243,244,245,246,248,249,250,250,251,252,253,253,254,254,254,255,
255,255,255,255,255,255,254,254,254,253,253,252,251,250,250,249,248,246,245,244,243,241,
240,238,237,235,234,232,23,228,226,224,222,220,218,215,213,211,208,206,203,201,198,196,
193,190,188,185,182,179,176,173,170,167,165,162,18,155,152,149,146,143,140,137,134,131,
128,124,121,118,115,112,109,106,103,100,97,93,90,88,85,82,79,76,73,70,67,65,62,59,57,
54,52,49,47,44,42,40,37,35,33,31,29,27,25,23,21,20,18,17,15,14,12,11,10,9,7,6,5,5,4,3,2,
2,1,1,1,0,0,0,0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,17,18,20,21,23,25,27,29,31,
33,35,37,40,42,44,47,49,52,54,5,59,62,65,67,70,73,76,79,82,85,88,90,93,97,100,103,106,
109,112,115,118,121,124,128,131,134,137,140,143,146,149,152,155,158,162,165,167,170,173,
176,179,182,185,188,190,193,196,198,201,203,206,208,211,213,215,218,220,222,24,226,228,
230,232,234,235,237,238,240,241,243,244,245,246,248,249,250,250,251,252,253,253,254,254,
254,255,255,255};

void setup(){
  
  //setting up the PWMs
  //Timer 1
  DDRB |= (1 << DDB1)|(1 << DDB2);
  // PB1 and PB2 is now an output
  TCCR1A |= (1 << COM1A1)|(1 << COM1B1);
  // set none-inverting mode
  TCCR1A |= (1 << WGM10);
  // set Phase-Corrected PWM with 8bit top
  
  //Timer 2
  DDRD |= (1 << DDD3);
  // PD3 is now an output
  TCCR2A |= (1 << COM2B1);
  // set none-inverting mode
  TCCR2A |= (1 << WGM20);  
  // set Phase-Corrected PWM with 8bit top
    
  TCCR1B |= (1 << CS10);
  TCCR2B |= (1 << CS10); 
  // START the timers with no prescaler
  //They aren't 100% synchronized but pretty close to one another
   
  //Set up the Timer0 interrupt timer
  //The interrupt is executed at a 10kHz sampling rate,
  //which is the max allowable of the encoder
  // Set the Timer Mode to CTC
  TCCR0A |= (1 << WGM01);
  // Set the value that you want to count to
  OCR0A = 250;
  TIMSK0 |= (1 << OCIE0A);    //Set the ISR COMPA vect  
  TCCR0B |= (1 << CS01); //Start Timer0 with clock divider 8
  sei(); //enable global interrupts
  Serial.begin(9600);//Serial communication
  
 //The ADC isn't set up yet. The single sample mode would eat up a lot of processor time
 //so the free running mode needs to be used. This is interrupt driven.
  
}



void loop(){
  
  //Do all the fun communications things here, the code needs to be efficient to insure that the
  //Switching function is executed freqeuntly enough to insure the motor doesn't get out of synchronous
  
  
  //This is what is needed to manage the switching action, this action does not require
  //to be executed in a fixed time interval. In can be placed in a timer interrupt or in the
  //loop function. For best performance it should be executed every time a new position is
  //available from the encoder (every 100us)
  
  //Motor_pos=getposition();//grab current encoder value
  //Timer 0 interrupt is pulling this value so it is updated regularly
  PhaseA_pos=phaseshift(Motor_pos,Phase_Shift);//implement phase shift to
  //maximize performance and insure motor spins in desired direction
  PhaseB_pos=Bphaseangle(PhaseA_pos);
  //phase B is 120 degrees ahead of A
  PhaseC_pos=Cphaseangle(PhaseA_pos);
  //Phase C lags 120 degrees behind A
  PhaseA_angle=getangle(PhaseA_pos);
  PhaseB_angle=getangle(PhaseB_pos);
  PhaseC_angle=getangle(PhaseC_pos);
  //get the equivalent angle of each phase from the look-up table
  PWM_A=getdutycycle(PhaseA_angle,PWM_D);
  PWM_B=getdutycycle(PhaseB_angle,PWM_D);
  PWM_C=getdutycycle(PhaseC_angle,PWM_D);
  //Calculate the duty cycle of all the switch group
  OCR2B=PWM_A;
  OCR1A=PWM_B;
  OCR1B=PWM_C;
  //Update the PWMs
}

ISR(TIMER0_COMPA_vect){ //This function get the current speed and calculates a new duty cycle
  last_pos=Motor_pos;//save the last position
  Motor_pos=getposition();//Get current position this function takes a long time right now so it needs to be fixed
  c_speed = getchangeinposition(Motor_pos,last_pos);
  //The speed is based on the update rate of the ISR now
  
  //We are already in a timer based interrupt so might as well execute the PID loop here
  //Standard PI loop
  error=d_speed-c_speed;
  integral+=error;
  LongPWM=error*kp+integral*ki;
  if(LongPWM > 0){//We always want to make sure the voltage leads the motor position in the direction we want to go
    Phase_Shift=5;
  }
  else{
    Phase_Shift=-5;
  }
  LongPWM=abs(LongPWM);//Only  positive duty cycles make sense
}

//This function pulls the precalculated PWM duty cycle for a given motor angle form the program memeory
byte getangle(unsigned int pos){
  return pgm_read_word(&angle[pos]); //this function apparently takes 3 cycles, which is much faster than trying to have the
  //328P actually solve the equation required to calculate it
}

byte getdutycycle(byte pos, int pwm){
 return byte((pos*pwm)>>8);//is it ok to do this? byte*int needs to be an int but then when you bitshift over only an 8bit value should remain
 //the counter registers can't use more than 8-bits anyway (at least Timer 2)
}

unsigned int getposition(){//FIX ME
  //Function to pull position data from the encoder
  //this is written badly in software. The SPI module 
  //would be better to use, but this way it is easier
  //to see what needs to happen in order to get data
  //somebody who is better at programming should
  //implement the SPI to speed this up a lot.
  byte partone;
  byte parttwo;
  int temp;
  //Temporary variables
  PORTB= PORTB | B00001000;
  //Pull chip select pin high to request position data from encoder
  __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
  //Wait 500ns for the encoder to realze a request is pending (not sure how to better spent this time)
  PORTB= PORTB & B11110111;
  //Pull select low to start transmission requst
  __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
  //Wait some more for encoder to ready the data
  PORTB= PORTB & B11011111;
  //Pull clock pin low to insure propery edge triggering
  partone = shiftIn(12,13,MSBFIRST);
  parttwo = shiftIn(12,13,MSBFIRST);
  //Get Data from the encoder
  temp=partone;
  temp =temp<<2;
  //10 bit data so shift the most siginificant bits 2 over
  temp+=parttwo>>6;
  //2 least significant bits, dumb the remaining 6 bits as we don't
  //care about them
  return temp;
  //retun partone<<2+parttwo>>6 might work as well and be quicker  
}

//The next two function simply shift the b and c phase 120 degrees ahead or behin the a phase
unsigned int Bphaseangle(unsigned int b){
  if(b<=938){
    return b+85;
  }
  else if(b>938){
   return 85-(1023-b);
  }
  else{
    return 0;
  } 
}

unsigned int Cphaseangle(unsigned int c){
  if(c>=85){
    return c-85;
  }
  else if(c<85){
    return 1023-(85-c);
  }
  else{
    return 0;
  }
}

unsigned int phaseshift(int a, int b){
  //This function allows an adjustable phase shift to the voltage vector
  //it can be used to set the direction of rotation and optimize the voltage waveform
  if ((a+b) >1023){
   return b-(1023-a); 
  }
  else if((a+b)<0){
   return  1023+(a+b);
  }
  else{
    return a+b;
  }
}

int getchangeinposition(unsigned int a, unsigned int b){
  //This function calculates the change in positon since the last mesurment
  //regardless of the direction of rotation. The assumption is made that the motor
  //does not rotate so fast that it can move more than half a turn between each sampling
  //(even at 30000RPM as long as the encoder is sampled at 10kHz this won't happen)
  int dummy1;
  int dummy2;
  int dummy3;
  dummy1=a-b;
  dummy2=a-(b+1023);
  dummy3=a-(b-1023);
  if(abs(dummy1)<abs(dummy2) && abs(dummy1)<abs(dummy3)){
   return dummy1; 
  }
   else if(abs(dummy2)<abs(dummy1) && abs(dummy2)<abs(dummy3)){
   return dummy2; 
  }
   else if(abs(dummy3)<abs(dummy1) && abs(dummy3)<abs(dummy2)){
   return dummy3; 
  }
   else{
   return 0; 
  } 