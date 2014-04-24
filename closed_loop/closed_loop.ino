float measuredSpeed = 0;
const int SPEED_SAMPLE_RATE = 40;
const int TIMER0_DIVIDER = 40;
int timer0ExecuteCounter = 0;
float setSpeed = 8.4;
int pwm = 128;
int firstDirection = 0, secondDirection = 0;
int direct = 0;

int integralTerm = 0;
const int integralTermDT = 1;
int proportionalTerm = 0;

const float KP = 50;
const float KI = 100;


void setup()
{
  Serial.begin(115200);
  
  
  PRR = 0x0;//disable low power modes to enable extra counters
  
  //setup encoder counter
  DDRD |= 0x42;
  //DDRD |= 0xff;
  TCCR1A=0;        // reset timer / the current count is stored here
  //bitSet(TCCR1B ,CS12);  // Counter Clock source is external pin
  //bitSet(TCCR1B ,CS11);  // Clock on rising edge
  

  //timer 0 stuff
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  //TCCR0B |= (0 << CS01) | (1 << CS00);
  //1024 prescaler
  TCCR0A = 0x05;
  TCCR1B |= 0x06;//same as above two lines
  TIMSK0 |= (1 << OCIE0A);//enable timer 0 overflow interrupt
  
  
  
  //setup timer2 stuff for PWM output
  //TCCR2A &= (1 << COM2A1);//non-inverting mode
  //TCCR2A &= (0 << WGM22) & (0 << WGM21) & (1 << WGM20); //PWM Phase Correction
  //TCCR2B = TCCR2B & 0b11111000 | 0x01; //Set prescaler to 1 and start PWM
  TCCR2A = 0b10000001;
  TCCR2B = 0b00000001;
  OCR2A = 128;
  DDRB = 0b00101000;// set PWM pin as output
  PORTB = 0x0;
  
  Serial.println("Starting...");
}

void loop()
{
  //Serial.println(TCNT1);
  //delay(500);
}

//Timer and Counter Interrupt
ISR (TIMER0_COMPA_vect)  // timer0 overflow interrupt
{
  timer0ExecuteCounter++;
  if(timer0ExecuteCounter%TIMER0_DIVIDER == 0)
  {
    //Serial.println(count);
    timer0ExecuteCounter = 0;
    TCCR1B = 0; //Stop counting while reading out counter
    measuredSpeed = TCNT1/208.0; //Copy value from counter register
    
    TCNT1 = 0; //reset counter
    firstDirection = PIND & (0b00100100);//read channels A and B
    sei();
    EIMSK = 0x01;//enable interrupt 0
    EICRA = 0x01;//rising edge activated
    //bitSet(TCCR1B ,CS12);  // Restart counter  
    //bitSet(TCCR1B ,CS11);  //
    TCCR1B |= 0x06;//same as above two lines
    
    measuredSpeed *= direct;
    
    Serial.println(measuredSpeed);
    
    //TODO implement direction measurement
    //We know speed, now we require the direction
    //EIMSK |= (1 << INT0);//Enable interrupt on Pin3
  	
    //Calculate PI correction based on error
    int correction = PIcorrection();
    pwm += correction;
    //Serial.println(pwm);
  	
    pwm=constrain(pwm,0,256);
    Serial.println(OCR2A);
    OCR2A = pwm; //set new PWM duty cycle
  }
}

ISR(INT0_vect)
{
  EIMSK &= (0<< INT0 ) ; //disable this interrupt
  cli();
   
    // Turn off INT0 adain untill the controller gets executed again 
    
   
    //B=digitalRead(5) ;
    //delay(10);
    secondDirection = PIND & (0b00100100);//read channel A and B
    
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
   //Serial.println(firstDirection);
   //Serial.println(secondDirection);
    /*switch (secondDirection)
    { 
         case 0 : 
               direct=1 ; 
               Serial.println("F");
               break; 
         case 4 : 
               direct = -1 ;
               Serial.println("B"); 
               break ; 
           
         default : 
                direct = 0 ; 
                Serial.println(secondDirection);
                break ;  
                
     }*/
}

int PIcorrection()
{
  float error = setSpeed - measuredSpeed;
  //Serial.println(error);
  //TODO: implement error deadband
  
  //calculate integral term
  integralTerm += error*integralTermDT;
  integralTerm = constrain(integralTerm, 0, 1024);
  
  return (error/KP) + (integralTerm/KI);//TODO: may be able to remove the KI multiplication
}
