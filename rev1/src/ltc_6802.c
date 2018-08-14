/***********************************************************************************************************
Configuration (CFG) Register Group

REGISTER  |  RD/WR    BIT 7     BIT 6     BIT 5     BIT 4     BIT 3     BIT 2     BIT 1     BIT 0
--------------------------------------------------------------------------------------------------
CFGR0     |  RD/WR    WDT       GPIO2     GPIO1     LVLPL     CELL10    CDC[2]    CDC[1]    CDC[0]
CFGR1     |  RD/WR    DCC8      DCC7      DCC6      DCC5      DCC4      DCC3      DCC2      DCC1
CFGR2     |  RD/WR    MC4I      MC3I      MC2I      MC1I      DCC12     DCC11     DCC10     DCC9
CFGR3     |  RD/WR    MC12I     MC11I     MC10I     MC9I      MC8I      MC7I      MC6I      MC5I
CFGR4     |  RD/WR    VUV[7]    VUV[6]    VUV[5]    VUV[4]    VUV[3]    VUV[2]    VUV[1]    VUV[0]
CFGR5     |  RD/WR    VOV[7]    VOV[6]    VOV[5]    VOV[4]    VOV[3]    VOV[2]    VOV[1]    VOV[0


Explanation for symbols:
WDT       RD   : Logic level of WDT
GPIOn 1/2 RD/WR: RD= Logic level at GPIO | WR= 0= Pin pull down on, 1= pin pull down off
LVLPL     RD/WR: Level polling mode | 0= toggle polling (default)  1= level polling
CELL10    RD/WR: 0= 12 cell mode (default), 1= 10 cell mode
CDCn 0-2  RD/WR: Comparator Duty Cycle, see table at end of explanation.
DCCn 0-12 RD/WR: Discharge cell n | 0= turn off shorting switch (default), 1= turn on shorting switch
MCnI 0-12 RD/WR: Mask Cell n interrupt | 0= enable interrupts for cell (default), 1=turn off interrupts and clear flags
VUVn 0-7  RD/WR: Under voltage Comparison Voltage | comparison voltage = VUV * 16 * 1.5mv (default VUV= 0, MMB low implies a factory programmed voltage)
VOVn 0-7  RD/WR: Over voltage Comparison Voltage | comparison voltage = VUV * 16 * 1.5mv (default VUV= 0, MMB low implies a factory programmed voltage)


CDC Table of values:

CDC          |  UV/OV COMPARATOR PERIOD              Vref POWERED DOWN BETWEEN MEASUREMENTS    CELL VOLTAGE MEASUREMENT TIME
----------------------------------------------------------------------------------------------------------------------------
0 (default)  |  N/A (Comparator Off) Standby Mode    Yes                                       N/A
1            |  N/A (Comparator Off)                 No                                        13ms
2            |  13ms                                 No                                        13ms
3            |  130ms                                No                                        13ms
4            |  500ms                                No                                        13ms
5*           |  130ms                                Yes                                       21ms
6            |  500ms                                Yes                                       21ms
7            |  2000ms                               Yes                                       21ms

*when MMB is low, CDC is set to 5
***********************************************************************************************************/


/***********************************************************************************************************
Cell Voltage (CV) Register Group
*Registers CVR15, CVR16, and CVR17 can only be read if the CELL10 bit in register CFGR0 is low.

REGISTER  |  RD/WR    BIT 7       BIT 6       BIT 5      BIT 4      BIT 3       BIT 2       BIT 1      BIT 0
--------------------------------------------------------------------------------------------------------------
CVR00     |  RD       C1V[7]      C1V[6]      C1V[5]     C1V[4]     C1V[3]      C1V[2]      C1V[1]     C1V[0]
CVR01     |  RD       C2V[3]      C2V[2]      C2V[1]     C2V[0]     C1V[11]     C1V[10]     C1V[9]     C1V[8]
CVR02     |  RD       C2V[11]     C2V[10]     C2V[9]     C2V[8]     C2V[7]      C2V[6]      C2V[5]     C2V[4]
CVR03     |  RD       C3V[7]      C3V[6]      C3V[5]     C3V[4]     C3V[3]      C3V[2]      C3V[1]     C3V[0]
CVR04     |  RD       C4V[3]      C4V[2]      C4V[1]     C4V[0]     C3V[11]     C3V[10]     C3V[9]     C3V[8]
CVR05     |  RD       C4V[11]     C4V[10]     C4V[9]     C4V[8]     C4V[7]      C4V[6]      C4V[5]     C4V[4]
CVR06     |  RD       C5V[7]      C5V[6]      C5V[5]     C5V[4]     C5V[3]      C5V[2]      C5V[1]     C5V[0]
CVR07     |  RD       C6V[3]      C6V[2]      C6V[1]     C6V[0]     C5V[11]     C5V[10]     C5V[9]     C5V[8]
CVR08     |  RD       C6V[11]     C6V[10]     C6V[9]     C6V[8]     C6V[7]      C6V[6]      C6V[5]     C6V[4]
CVR09     |  RD       C7V[7]      C7V[6]      C7V[5]     C7V[4]     C7V[3]      C7V[2]      C7V[1]     C7V[0]
CVR10     |  RD       C8V[3]      C8V[2]      C8V[1]     C8V[0]     C7V[11]     C7V[10]     C7V[9]     C7V[8]
CVR11     |  RD       C8V[11]     C8V[10]     C8V[9]     C8V[8]     C8V[7]      C8V[6]      C8V[5]     C8V[4]
CVR12     |  RD       C9V[7]      C9V[6]      C9V[5]     C9V[4]     C9V[3]      C9V[2]      C9V[1]     C9V[0]
CVR13     |  RD       C10V[3]     C10V[2]     C10V[1]    C10V[0]    C9V[11]     C9V[10]     C9V[9]     C9V[8]
CVR14     |  RD       C10V[11]    C10V[10]    C10V[9]    C10V[8]    C10V[7]     C10V[6]     C10V[5]    C10V[4]
CVR15*    |  RD       C11V[7]     C11V[6]     C11V[5]    C11V[4]    C11V[3]     C11V[2]     C11V[1]    C11V[0]
CVR16*    |  RD       C12V[3]     C12V[2]     C12V[1]    C12V[0]    C11V[11]    C11V[10]    C11V[9]    C11V[8]
CVR17*    |  RD       C12V[11]    C12V[10]    C12V[9]    C12V[8]    C12V[7]     C12V[6]     C12V[5]    C12V[4]

Explanation for symbols:
CnV[x]   n(1,12) x(0,11): Cell Voltage = CnV * 1.5mv, reads 0xFFF while reading in progress
***********************************************************************************************************/


/***********************************************************************************************************
Flag (FLG) Register Group
*Bits C11UV, C12UV, C11OV, and C12OV are always low if the CELL10 bit in register CFGR0 is high.

REGISTER  |  RD/WR    BIT 7     BIT 6     BIT 5     BIT 4     BIT 3    BIT 2    BIT 1    BIT 0
FLGR0     |  RD       C4OV      C4UV      C3OV      C3UV      C2OV     C2UV     C1OV     C1UV
FLGR1     |  RD       C8OV      C8UV      C7OV      C7UV      C6OV     C6UV     C5OV     C5UV
FLGR2     |  RD       C12OV*    C12UV*    C11OV*    C11UV*    C10OV    C10UV    C9OV     C9UV

Explanation for symbols:
CnOV 1-12: Cell over voltage flag, 0= not flagged, 1 = flagged
CnUV 1-12: Cell under voltage flag, 0= not flagged, 1 = flagged
***********************************************************************************************************/


/***********************************************************************************************************
Temperature (TMP) Register Group

REGISTER  |  RD/WR    BIT 7        BIT 6        BIT 5       BIT 4       BIT 3        BIT 2        BIT 1       BIT 0
----------------------------------------------------------------------------------------------------------------------
TMPR0     |  RD       ETMP1[7]     ETMP1[6]     ETMP1[5]    ETMP1[4]    ETMP1[3]     ETMP1[2]     ETMP1[1]    ETMP1[0]
TMPR1     |  RD       ETMP2[3]     ETMP2[2]     ETMP2[1]    ETMP2[0]    ETMP1[11]    ETMP1[10]    ETMP1[9]    ETMP1[8]
TMPR2     |  RD       ETMP2[11]    ETMP2[10]    ETMP2[9]    ETMP2[8]    ETMP2[7]     ETMP2[6]     ETMP2[5]    ETMP2[4]
TMPR3     |  RD       ITMP[7]      ITMP[6]      ITMP[5]     ITMP[4]     ITMP[3]      ITMP[2]      ITMP[1]     ITMP[0]
TMPR4     |  RD       REV[2]       REV[1]       REV[0]      THSD        ITMP[11]     ITMP[10]     ITMP[9]     ITMP[8]
***********************************************************************************************************/


/***********************************************************************************************************
Packet Error Code (PEC)

REGISTER  |  RD/WR    BIT 7     BIT 6     BIT 5     BIT 4     BIT 3     BIT 2     BIT 1     BIT 0
--------------------------------------------------------------------------------------------------
PEC       |  RD       PEC[7]    PEC[6]    PEC[5]    PEC[4]    PEC[3]    PEC[2]    PEC[1]    PEC[0]
***********************************************************************************************************/


/***************************************************************************
*                                   INLCUDES                               *
***************************************************************************/

#include <stdint.h>
#include <stddef.h>

#include <cs.h>
#include <gpio.h>
#include <interrupt.h>
#include <spi.h>

#include <error_states.h>

#include "ltc_6802.h"

/***************************************************************************
*                             LITERAL CONSTANTS                            *
***************************************************************************/

#define BITS_IN_BYTE                8
#define CONFIG_REG_SIZE             6
#define CELL_VOLTAGE_REG_SIZE       16
#define MAX_RX_BYTES                18
#define MV_TO_V                     1000
#define ONE_MHZ                     1000000
#define PEC_INTIAL                  0x41
#define THIRTY_TWO_AND_CHANGE_KHZ   32768
#define VOLT_COMPARE_DEMONINATOR    ( 16 * 1.5 )

/***************************************************************************
*                                   MACROS                                 *
***************************************************************************/

/***************************************************************************
*                                    TYPES                                 *
***************************************************************************/

/***************************************************************************
*                              MEMORY CONSTANTS                            *
***************************************************************************/

enum e_command_codes
{
	CMD_WRCFG           = 0X01,     /* write configuration group    */
	CMD_RDCFG           = 0X02,     /* read configuration group     */
	CMD_RDCV            = 0X04,     /* read all cell voltages       */
	CMD_RDFLG           = 0X0C,     /* read flag register group     */
	CMD_RDTMP           = 0X0E,     /* read temperature group       */
	CMD_STCVAD          = 0X10,     /* start all cell A/D conversion*/
	CMD_STOWAD          = 0X20,     /* start open wire conversion   */
	CMD_STTMPAD         = 0X30,     /* start temperature conversion */
	CMD_PLADC           = 0X40,     /* poll A/D converter status    */
	CMD_PLINT           = 0X50,     /* poll interrupt status        */
	//CMD_STCVDC          = 0X60,      /* start cell A/D with discharge*/
	//CMD_STOWDC          = 0X70,     /* start open wire w/ discharge */
};

static const eUSCI_SPI_MasterConfig
                        LTC_SPI_CFG =
{
	EUSCI_B_SPI_CLOCKSOURCE_ACLK,                               /* clock source             */
	THIRTY_TWO_AND_CHANGE_KHZ,                                  /* clock source frequency   */
	ONE_MHZ,                                                    /* desired spi clock        */
	EUSCI_B_SPI_MSB_FIRST,                                      /* msb first                */
	EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,    /* clock phase              */
	EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH,                  /* clock low polarity       */
	EUSCI_B_SPI_4PIN_UCxSTE_ACTIVE_LOW                          /* spi mode                 */
};

/***************************************************************************
*                                   CLASSES                                *
***************************************************************************/

/***************************************************************************
*                                  VARIABLES                               *
***************************************************************************/

static uint8_t          bytes_rx[ MAX_RX_BYTES ];
                                    /* number of bytes received     */
static uint8_t          config_reg[ CONFIG_REG_SIZE ];
                                    /* configuration register       */
c_ltc_6802              ltc_6802 =
{
	{ PIN_3, MSP_PORT_6,  PIN_MODE_OUTPUT_GPIO },   /* clock        */
	{ PIN_2, MSP_PORT_6,  PIN_MODE_OUTPUT_GPIO },   /* enable       */
	{ PIN_8, MSP_PORT_NC, PIN_MODE_DONT_CARE },     /* gpio 1       */
	{ PIN_8, MSP_PORT_NC, PIN_MODE_DONT_CARE },     /* gpio 2       */
	LTC_STANDBY,                                    /* mode         */
	{ PIN_5, MSP_PORT_6,  PIN_MODE_INPUT_GPIO },    /* MISO         */
	{ PIN_4, MSP_PORT_6,  PIN_MODE_OUTPUT_GPIO },   /* MOSI         */
	{ PIN_8, MSP_PORT_NC, PIN_MODE_DONT_CARE }      /* watchdog     */
};                                  /* main LTC to read data from   */
static uint8_t          pec;        /* packet error correction bit  */
static uint8_t          num_byte_rx;/* number of bytes received     */
static uint32_t         spi_base;   /* selected spi module          */

/***************************************************************************
*                                 PROCEDURES                               *
***************************************************************************/

static uint8_t calculate_pec_array
	(
		const uint8_t * new_bytes,  /* new outgoing bytes           */
		const uint8_t   num_bytes   /* number of bytes to send      */
	);

static uint8_t calculate_pec_byte
	(
		const uint8_t   new_bytes   /* new outgoing byte            */
	);

inline static void start_spi
	(
		void
	);

inline static void wait_for_tx_ready
	(
		void
	);


/*******************************************************************
*
*	PROCEDURE NAME:
*		calculate_pec_array
*
*	DESCRIPTION:
*		Calculates a pec based off of an array of data
*
*******************************************************************/

static uint8_t calculate_pec_array
	(
		const uint8_t * new_byte,   /* new outgoing bytes           */
		const uint8_t   num_bytes   /* number of bytes to send      */
	)
{
	/*------------------------------------------------------
						Local Variables
	------------------------------------------------------*/
	static uint8_t      i;          /* loop iterator                */
	static uint8_t      j;          /* loop iterator                */
	static uint8_t      in0;        /* temporary variable           */
	static uint8_t      in1;        /* temporary variable           */
	static uint8_t      in2;        /* temporary variable           */

	for( i = 0; i < num_bytes; ++i )
	{
		for( j = 0; j < BITS_IN_BYTE; ++j )
		{
			in0 = ( ( new_byte[ i ] >> ( 7 - j ) ) & 0x01 ) ^ ( ( pec >> 7 ) & 0x01 );
			in1 = in0 ^ ( (pec >> 0 ) & 0x01 );
			in2 = in0 ^ ( (pec >> 1 ) & 0x01 );
			pec = in0 | ( in1 << 1 ) | ( in2 << 2 ) | ( ( pec << 1 ) & ~0x07 );
		}
	}

	return pec;

}	/* calculate_pec_array() */



/*******************************************************************
*
*	PROCEDURE NAME:
*		calculate_pec_byte
*
*	DESCRIPTION:
*		Calculates a pec based off of a single byte of data
*
*******************************************************************/

static uint8_t calculate_pec_byte
	(
		const uint8_t   new_byte    /* new outgoing byte            */
	)
{
	/*------------------------------------------------------
						Local Variables
	------------------------------------------------------*/
	static uint8_t      in0;        /* temporary variable           */
	static uint8_t      in1;        /* temporary variable           */
	static uint8_t      in2;        /* temporary variable           */
	static uint8_t      j;          /* loop iterator                */

	for( j = 0; j < BITS_IN_BYTE; ++j )
	{
		in0 = ( ( new_byte >> ( 7 - j ) ) & 0x01 ) ^ ( ( pec >> 7 ) & 0x01 );
		in1 = in0 ^ ( (pec >> 0 ) & 0x01 );
		in2 = in0 ^ ( (pec >> 1 ) & 0x01 );
		pec = in0 | ( in1 << 1 ) | ( in2 << 2 ) | ( ( pec << 1 ) & ~0x07 );
	}

	return pec;

}	/* calculate_pec_byte() */


/*******************************************************************
*
*	PROCEDURE NAME:
*		eusci_b0_isr
*
*	DESCRIPTION:
*		eUSCI b1 interrupt service routine.
*
*******************************************************************/

void eusci_b1_isr
	(
		void
	)
{
	/*------------------------------------------------------
						Local Variables
	------------------------------------------------------*/
	static uint32_t     status;     /* interrupt status             */

	status = SPI_getEnabledInterruptStatus( EUSCI_B1_BASE );

	if( status & EUSCI_B_SPI_RECEIVE_INTERRUPT )
	{
		bytes_rx[ num_byte_rx ] = SPI_receiveData( EUSCI_B1_BASE );
		num_byte_rx++;
	}

	SPI_clearInterruptFlag( EUSCI_B1_BASE, status );

}	/* eusci_b1_isr() */


/*******************************************************************
*
*	PROCEDURE NAME:
*		ltc_init_normal_op
*
*	DESCRIPTION:
*		Initializes the LTC to constantly monitor cell
*
*******************************************************************/

e_error_states ltc_init_normal_op
	(
		void
	)
{
	/*------------------------------------------------------
						Local Variables
	------------------------------------------------------*/
	static uint8_t      i;      /* loop iterator                */

	/*-----------------------------------
	WDT: X
	GPIO1/2: 0
	LVLPL: 0 ( toggle polling )
	CELL10: 1
	CDC: 7 (0xFF)
	DCC: 0 ( normal mode, not balancing )
	MCnI: 0b111100000000 (enable for active cells, disable others)
	VUV: Desired voltage: 3.3V: 3.3 * 1000 = x * 16 * 1.5 -> (3.3 * 1000) / ( 16 * 1.5) = x -> 3300 / 24 = x
	VOV: Desired voltage: 4.2V: 4.2 * 1000 = x * 16 * 1.5 -> (4.2 * 1000) / ( 16 * 1.5) = x -> 4200 / 24 = x
	-----------------------------------*/
	config_reg[ 0 ] = 0x0F;         /* 0b00001111 */
	config_reg[ 1 ] = 0x00;         /* 0b00000000 */
	config_reg[ 2 ] = 0x00;         /* 0b00000000 */
	config_reg[ 3 ] = 0xF0;         /* 0b11110000 */
	config_reg[ 4 ] = ( uint8_t )( CELL_MINIMAL_VOLTAGE * MV_TO_V / VOLT_COMPARE_DEMONINATOR );
	config_reg[ 5 ] = ( uint8_t )( CELL_MAX_VOLTAGE * MV_TO_V / VOLT_COMPARE_DEMONINATOR );

	/*-----------------------------------
	Starting and enabling LXFT (32kHz)
	-----------------------------------*/
    GPIO_setAsPeripheralModuleFunctionOutputPin( GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION );
    CS_setExternalClockSourceFrequency( THIRTY_TWO_AND_CHANGE_KHZ, 0);
    CS_initClockSignal( CS_ACLK, CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    CS_startLFXT( CS_LFXT_DRIVE0 );

	/*-----------------------------------
	Configuring the SPI module
	-----------------------------------*/
	SPI_selectFourPinFunctionality( spi_base, EUSCI_SPI_ENABLE_SIGNAL_FOR_4WIRE_SLAVE );
	SPI_initMaster( spi_base, &LTC_SPI_CFG );
    SPI_enableInterrupt( spi_base, EUSCI_B_SPI_RECEIVE_INTERRUPT );
    Interrupt_enableInterrupt(INT_EUSCIB1);
    Interrupt_enableSleepOnIsrExit();
    start_spi();

	/*-----------------------------------
	Transmit the set command byte
	-----------------------------------*/
	wait_for_tx_ready();
	SPI_transmitData( spi_base, CMD_WRCFG );
	wait_for_tx_ready();
	SPI_transmitData( spi_base, calculate_pec_byte( CMD_WRCFG ) );

	/*-----------------------------------
	Transmit the desired data values
	-----------------------------------*/
	for( i = 0; i < CONFIG_REG_SIZE; ++i )
	{
		wait_for_tx_ready();
		SPI_transmitData( spi_base, config_reg[ i ] );
	}
	calculate_pec_array( config_reg, CONFIG_REG_SIZE );
	wait_for_tx_ready();
	SPI_transmitData( spi_base, pec );

	while( SPI_isBusy( spi_base ) == EUSCI_SPI_BUSY )
	{
		/* do nothing */
	}
	SPI_disableModule( spi_base );
	//TODO wait for half a second
	return( ERROR_NO_ERROR );

}	/* ltc_init_normal_op() */


/*******************************************************************
*
*	PROCEDURE NAME:
*		ltc_powerup
*
*	DESCRIPTION:
*		Requests a voltage read and stores it into the supplied bms
*		cell information
*
*******************************************************************/

e_error_states ltc_powerup
	(
		void
	)
{
	/*-----------------------------------
	Setting the correct EUSCI module
	-----------------------------------*/
	switch( ltc_6802.m_clk_pin.m_port )
	{
		case MSP_PORT_6:
			spi_base = EUSCI_B1_BASE;
			break;

		default:
			return ERROR_DEFAULT_CASE;
	};

	msp_432_update_pin_mode( &( ltc_6802.m_clk_pin ) );
	msp_432_update_pin_mode( &( ltc_6802.m_enable_pin ) );
	msp_432_update_pin_mode( &( ltc_6802.m_miso_pin ) );
	msp_432_update_pin_mode( &( ltc_6802.m_mosi_pin ) );

	return( ERROR_NO_ERROR );

}	/* ltc_powerup() */


/*******************************************************************
*
*	PROCEDURE NAME:
*		ltc_request_voltage_read
*
*	DESCRIPTION:
*		Requests a voltage read and stores it into the supplied bms
*		cell information
*
*******************************************************************/

e_error_states ltc_request_voltage_read
	(
		c_bms_cell    * bms_cells,  /* bms cells to read data into  */
		const uint8_t   num_cells   /* num cells to read data for   */
	)
{
	/*------------------------------------------------------
						Local Variables
	------------------------------------------------------*/
	static uint8_t      i;          /* loop iterator                */
	static uint16_t     temp_var;   /* temporary variable           */

	/*-----------------------------------
	Send the start polling command to
	read all of the cell voltages
	-----------------------------------*/
	start_spi();
	wait_for_tx_ready();
	SPI_transmitData( spi_base, CMD_STCVAD );
	calculate_pec_byte( CMD_STCVAD );
	wait_for_tx_ready();
	SPI_transmitData( spi_base, pec );
	//TODO wait for transmit MISO to be pulled high
	SPI_disableModule( spi_base );

    SPI_enableInterrupt( spi_base, EUSCI_B_SPI_RECEIVE_INTERRUPT );
    Interrupt_enableInterrupt( INT_EUSCIB1 );

	/*-----------------------------------
	Get all of register values from the
	LTC
	-----------------------------------*/
	start_spi();
	wait_for_tx_ready();
	SPI_transmitData( spi_base, CMD_RDCV );
	calculate_pec_byte( CMD_RDCV );
	wait_for_tx_ready();
	SPI_transmitData( spi_base, pec );
	while( num_byte_rx < num_cells )
	{
		/* do nothing */
	}

	/*-----------------------------------
	Decode all of the register values
	from the LTC
	-----------------------------------*/
	for( i = 0; i < num_cells; ++i )
	{
		if( ( i % 2 ) == 0 )
		{
			temp_var = bytes_rx[ i ] | ( ( uint16_t )( bytes_rx[ i + 1 ] & 0x0F ) << 8 );
		}
		else
		{
			temp_var = ( bytes_rx[ i ] >> 4 ) | ( ( uint16_t )( bytes_rx[ i + 1 ] ) << 4 );
		}
		bms_cells[ i ].m_current_voltage = temp_var;
	}

	return( ERROR_NO_ERROR );

}	/* ltc_request_voltage_read() */


/*******************************************************************
*
*	PROCEDURE NAME:
*		start_spi
*
*	DESCRIPTION:
*		Initializes the LTC to constantly monitor cell
*
*******************************************************************/

inline static void start_spi
	(
		void
	)
{
	pec = PEC_INTIAL;
	num_byte_rx = 0;
	SPI_enableModule( spi_base );

}	/* start_spi() */


/*******************************************************************
*
*	PROCEDURE NAME:
*		start_spi
*
*	DESCRIPTION:
*		Initializes the LTC to constantly monitor cell
*
*******************************************************************/

inline static void wait_for_tx_ready
	(
		void
	)
{
	while( !SPI_getInterruptStatus( spi_base, EUSCI_SPI_TRANSMIT_INTERRUPT ) )
	{
		/* do nothing */
	}

	return;

}	/* wait_for_tx_ready() */
