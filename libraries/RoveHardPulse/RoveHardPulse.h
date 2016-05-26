/*

// Texas Instruments drivers
#include <inttypes.h>

// Wiring framework drivers
#include "Energia.h"

// Energai LM4F TivaC Specifics:

extern "C" void RovePulseOutRc_handleInterrupt(void);

//RovePulseInCapCmpr_handleInterrupt

#define PULSE_TIMER		 TIMER2_BASE
#define PULSE_TIME_CFG		 TIMER_CFG_PERIODIC
#define PULSE_TIMER_TRIGGER	 TIMER_TIMA_TIMEOUT
#define PULSE_TIMER_INTERRUPT    INT_TIMER2A
#define PULSE_TIMER_A		 TIMER_A
#define PULSE_TIMER_PERIPH	 SYSCTL_PERIPH_TIMER2

///////////////////////////////////
// Zenith Drive Motors API
class RoveRoboteqRcMLB1660
{
private:

    uint16_t RovePulse RoveRcPwm; 

public:
    RoveRoboteqRcMLB1660();
    
    void     pulseOut(uint16_t rc_micros);
    uint16_t attach(  uint16_t pin);
};//end class

///////////////////////////////////
// Zenith Arm Encoders API
class RoveUsDigitalPulseMA3
{
private:

    uint16_t RovePulse RoveCapCmprPwm; 

public:
    RoveUsDigitalPulseMA3();
    
    void     pulseIn(uint16_t capture_micros);
    uint16_t attach( uint16_t pin);
};//end class

///////////////////////////////////
// Zenith Mast Cam API
//class RoveSurvielZoneRcPtz

///////////////////////////////////
// Zenith Tool Deploy API
//class RovePositionalServo

///////////////////////////////////
// Zenith Tool Deploy API
//class RoveContinousServo

///////////////////////////////////////////////////////

typedef struct
{
    uint16_t pin_number;
    uint16_t pulse_width;
} RovePulse;

static   RovePulse Pulses[TIMER_PULSES_ATTACHED_MAX];

volatile uint16_t     pulse_current_vector_Vx;
volatile uint16_t     pulse_idle_TICKS_MICROS_Vx;

//int32?
volatile uint32_t     system_TICKS_MICROS_Vx;

#endif // SERVO_H


void attachPulse(uint16_t pin)
{
	Pulses[pulse_vector_current_Vx].pin_number  = pin;
	Pulses[pulse_vector_current_Vx].pulse_width = PULSE_DEACTIVE;
	pulse_vector_current_Vx++;
}//end constructor

//set a pulse width
void setPulseWidth(uint16_t pulse_micros)
{
	//Todo constrain();
	Pulses[pulse_vector_current_Vx].pulse_width = pulse_micros;
	pulse_idle_TICKS_MICROS_Vx();
}//end fnctn



// Calculate the new period remainder
static void recalcPulseIdle_TICKS_MICROS_V(void)
{
	uint16_t pulses_high_MICROS = 0;

//TODO? int i = 0;
	for (int i = 0; i < TIMER_PULSES_ATTACHED_MAX; i++)
	{
		pulses_high_MICROS += Pulses[i].pulse_width_MICROS;
	}//end for

	pulse_idle_TICKS_MICROS_Vx = PULSE_PERIOD_MICROS - pulses_high_MICROS;
}//end fnctn

//start a timer to handle each attached pulse
static void RovePulseTimer_begin(void) 
{
	// Work around for clock not up yet
	#ifdef TARGET_IS_BLIZZARD_RB1
	  ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	#endif

	// Initialize global variables
        pulse_vector_current_Vx    = 0;
	pulse_idle_TICKS_MICROS_Vx = 0;

	system_TICKS_MICROS_Vx     = 0;

	Pulses[0].pin_number   = 0;
	Pulses[0].pulse_width  = PULSE_DEACTIVE;

	recalcPulseIdle_TICKS_MICROS_Vx();

//ENERGIA SPECIFIC?

	// Enable TIMER
	ROM_SysCtlPeripheralEnable(PULSE_TIMER_PERIPH);

	// Enable processor interrupts.
	ROM_IntMasterEnable();

        //Grab the interrupt handler
	TimerIntRegister(PULSE_TIMER, PULSE_TIMER_A, RovePulseOutRc_handleInterrupt);

	// Configure the TIMER
	ROM_TimerConfigure(PULSE_TIMER, PULSE_TIME_CFG);

	// Calculate the number of timer counts/microsecond
	ticksPerMicrosecond = F_CPU / 1000000;

	// Initially load the timer with 20ms interval time
	ROM_TimerLoadSet(PULSE_TIMER, PULSE_TIMER_A, ticksPerMicrosecond * REFRESH_INTERVAL);

	// Setup the interrupt for the TIMER1A timeout.
	ROM_IntEnable(PULSE_TIMER_INTERRUPT);
	ROM_TimerIntEnable(PULSE_TIMER, PULSE_TIMER_TRIGGER);

	// Enable the timer.
	ROM_TimerEnable(PULSE_TIMER, SERVO_TIMER_A);
}//end fnctn


// ISR for generating the pulse widths
void RovePulseOutRc_handleInterrupt(void)
{
	// Clear the timer interrupt.
	ROM_TimerIntClear(PULSE_TIMER, PULSE_TIMER_TRIGGER);

	// Get the pulse width value for the current servo from the array
	// and reload the timer with the new pulse width count value
	// if we have already serviced all servos (motor = MAX_SERVO_NO)
	// then this value should be the 20ms period value
	if(pulse < PULSES_PER_TIMER)
	{
		ROM_TimerLoadSet(PULSE_TIMER, PULSE_TIMER_A, ticksPerMicrosecond * Pulses[pulse].pulse_width);
	}else{
		ROM_TimerLoadSet(PULSE_TIMER, PULSE_TIMER_A, ticksPerMicrosecond * remainderPulseWidth);
	}//end if

	// End the servo pulse set previously (if any)
	if(pulse > 0)  // If not the 1st Servo....
	{
		if (Pulses[pulse - 1].enabled)
		{
			digitalWrite(Pulses[pulse - 1].pin_number, LOW);
		}//end if
	}//end if

	// Set the current servo pin HIGH
	if(pulse < PULSES_PER_TIMER)
	{
		if (Pulses[pulse - 1].enabled)
		{
			digitalWrite(Pulses[pulse].pin_number, HIGH);
		}//end if

		// Advance to next servo for processing next time
		pulse++;  
	}else{
		// Start all over again
		pulse = 0; 
	}//end if
}//end ISR



///////////////////////////////////////

  // Energia.h      :extern const uint32_t port_to_base[];
  //                :#define portBASERegister(P)       ((volatile uint32_t *) port_to_base[P])
  //                :const uint32_t port_to_base[] = {NOT_A_PORT,(uint32_t) GPIO_PORTA_BASE, // 1(uint32_t) GPIO_PORTB_BASE, // 2
  // pins_energia.h :const uint32_t timer_to_pin_config[] = {GPIO_PD0_T0CCP0, //  0GPIO_PA0_T0CCP0, //  1  
  // timer to pin
  
  // ISR for generating the pulse widths
//void RovePulseOutRc_handleInterrupt(void)

  GPIOPinConfigure(GPIO_PB6_T0CCP0);
  GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_6);
  
  // wiring_analog.c     :void enableTimerPeriph(uint32_t offset) {ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0 + offset);}
  // enable timer
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  
  // wiring_analog.c      uint32_t getTimerBase(uint32_t offset) {return (TIMER0_BASE + (offset << 12));}
  // split the A and B sides of the timer, configure A side for time capture event
  TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME);
  
  // both edges
  TimerControlEvent(TIMER0_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);

  // CUSTOM PIN to HANDLER switch for function by pin table?
  
  // pins_energia.h   :const uint8_t timer_to_ab[] = { TIMA, // 0 TIMA, // 1
  // register our interrupt 
  TimerIntRegister(TIMER0_BASE, TIMER_A, my_pulse_pin_function);
  
  // interrupt on timer for the capture event
  TimerIntEnable(TIMER0_BASE, TIMER_CAPA_EVENT);
  
  // wiring_analog.c   :uint8_t getTimerInterrupt(uint8_t timer) {
  // enable
  IntEnable(INT_TIMER0A);
  
  // enable
  IntMasterEnable();
  
  // and turn it on
  TimerEnable(TIMER0_BASE, TIMER_A);

///////////////////////////////////////


//SysTick counter is 24 bits and rolls over at 1, for a range of 1 to 16,777,216 (2^24), inclusive
const uint32_t SYS_TICKS_MAX = 16777216;

volatile uint32_t pulse_capture_systicks = 0;

void timer_0_interrupt(void) 
{
  // save the timer config so we know which edge this is
  uint32_t edge = HWREG(TIMER0_BASE + TIMER_O_CTL);

  // clear our interrupt mask  
  TimerIntClear(TIMER0_BASE, TIMER_CAPA_EVENT);
  
  //check for falling edge
  if (edge & TIMER_EVENT_NEG_EDGE) 
  {   
    // save our ticks
    //pulse_capture_systicks = SYS_TICKS_MAX - SysTickValueGet();
    pulse_capture_systicks = TIMER_TICKS_16B_MAX - TimerValueGet();
       
    // set event control for the positive edge
    TimerControlEvent(TIMER0_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);
  } else {
 
    // this is a rising edge, so reset our system tick counter to 0;
    //SysTickPeriodSet(SYS_TICKS_MAX);
    //ROM_TimerLoadSet(SERVO_TIMER, SERVO_TIMER_A, ticksPerMicrosecond * servos[currentServo].pulse_width);  
    //HWREG(NVIC_ST_CURRENT) = 0;
    
    TimerLoadSet(SERVO_TIMER, SERVO_TIMER_A, TIMER_TICKS_16B_MAX);

    // set event control for the negative edge
    TimerControlEvent(TIMER0_BASE, TIMER_A, TIMER_EVENT_NEG_EDGE);
  }//end if
}//end interrupt

*/
