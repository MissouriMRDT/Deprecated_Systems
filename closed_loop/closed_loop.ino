/*
 * Missouri S&T Mars Rover Design Team
 * Main Brushed DC Motor Controller Closed-Loop (PI) Speed Control Software
 * Tuned to 2014 Rover with 500CPR encoder, specific gearbox and wheel size
 * Software: Josh Jetter and Lukas Mueller
 * Hardware: Lukas Mueller
 * (C) 2014
 */

#define DEBUG_MODE
 
//Global variables
float measuredSpeed = 0; // speed measured by the encoder
const int TIMER0_DIVIDER = 40; // Timer0 will rollover multiple times before we actually use the ISR
int timer0ExecuteCounter = 0; // Keep track of how many times Timer0 has rolled over
float setSpeed = 5.4;//The user will specify this in km/hr
int pwm = 128; // written to the OCR2A to control PWM duty cycle. 128 = 0rpm
int firstDirection = 0, secondDirection = 0; // Used to determine encoder direction by tracking state of channel A and B
int direct = 0; // Global to add direction to speed scalar

int integralTerm = 0; // Used to keep track of integral term over time
const int integralTermDT = 1; // Used in discrete-time calculation of integral term
int proportionalTerm = 0; // Used to keep track of proportional error term

//PI constants
const float KP = 60;//50
const float KI = 150;//100


void setup()
{
  Serial.begin(115200); // Communicate at 115200 baud
  
  PRR = 0x0;//disable low power modes to enable extra counters
  
  //setup encoder counter
  DDRD |= 0x42; // set pins as inputs
  TCCR1A=0;        // reset timer / the current count is stored here
  

  //timer 0 stuff
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  //TCCR0B |= (0 << CS01) | (1 << CS00);
  //1024 prescaler
  TCCR0A = 0x05;
  TCCR1B |= 0x06;// Counter for encoder. Make source external pin, and increment on rising edge
  TIMSK0 |= (1 << OCIE0A);//enable timer 0 overflow interrupt
  
  
  
  //setup timer2 stuff for PWM output
  TCCR2A = 0b10000001; // Set non-inverting mode with PWM phase correction
  TCCR2B = 0b00000001; // Set prescaler to 1 and start PWM
  OCR2A = 128; // Start at 50% duty cycle
  DDRB = 0b00101000;// set PWM pin as output
  PORTB = 0x0;
  
  #ifdef DEBUG_MODE
    Serial.println("Starting...");
  #endif
}

void loop()
{
  // Serial communication will happen here
}

//Timer and Counter Interrupt (for making speed measurements)
ISR (TIMER0_COMPA_vect)  // timer0 overflow interrupt
{
  timer0ExecuteCounter++;
  if(timer0ExecuteCounter%TIMER0_DIVIDER == 0)
  {
    
    timer0ExecuteCounter = 0; // reset ISR counter
    TCCR1B = 0; //Stop counting while reading out counter
    measuredSpeed = TCNT1/208.0; //Copy value from counter register. Scalar 208.0 changes from CPR to Km/Hr for our rover
    
    TCNT1 = 0; //reset counter
    firstDirection = PIND & (0b00100100); // read channels A and B. This will be used in the other ISR to determine direction
    sei(); // enable external interrupts so we can make a direction measurement on next encoder waveform rising edge
    EIMSK = 0x01;//enable interrupt 0
    EICRA = 0x01;//rising edge activated
    TCCR1B |= 0x06;// Restart counter
    
    measuredSpeed *= direct; // add direction component to speed scalar
    
    #ifdef DEBUG_MODE
      Serial.println(measuredSpeed);
    #endif
  	
    // Calculate PI correction based on error
    int correction = PIcorrection();
    #ifdef DEBUG_MODE
      Serial.println(correction);
    #endif
    pwm += correction;
  	
    pwm=constrain(pwm,0,255); // constrain pwm duty cycle value to register constraints [0,255]
    #ifdef DEBUG_MODE
      Serial.println(OCR2A);
    #endif
    OCR2A = pwm; // set new PWM duty cycle
  }
}

// interrupt for determining direction
ISR(INT0_vect)
{
  EIMSK &= (0 << INT0) ; //disable this interrupt
  cli();
   
    // Turn off INT0 adain untill the controller gets executed again 
    
    secondDirection = PIND & (0b00100100); // read econder channel A and B
    
    
    if(firstDirection == 0)
    {
      // 00 direction
      if(secondDirection == 4)
      {
        direct = 1;
        return;
      }
      else if(secondDirection == 32)
      {
        direct = -1;
        return;
      }
    }
    else if(firstDirection == 4)
    {
      // 01 direction
      if(secondDirection == 36)
      {
        direct = 1;
        return;
      }
      else if(secondDirection == 0)
      {
        direct = -1;
        return;
      }
    }
    else if(firstDirection == 36)
    {
      // 11 direction
      if(secondDirection == 32)
      {
        direct = 1;
        return;
      }
      else if(secondDirection == 4)
      {
        direct = -1;
        return;
      }
    }
    else if(firstDirection == 32)
    {
      if(secondDirection == 0)
      {
        direct = 1;
        return;
      }
      else if(secondDirection == 36)
      {
        direct = -1;
        return;
      }
    }
}

int PIcorrection()
{
  float error = (setSpeed - measuredSpeed)*200;
  //Serial.println(error);
  //TODO: implement error deadband
  
  //calculate integral term
  integralTerm += error*integralTermDT;
  integralTerm = constrain(integralTerm, 0, 1024);
  
  return (error/KP) + (integralTerm/KI);//TODO: may be able to remove the KI multiplication by combining it with the integral term DT multiplication
}
