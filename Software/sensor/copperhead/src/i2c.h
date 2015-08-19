/*
 * i2c.h
 *
 *  Created on: Jul 28, 2015
 *      Author: milesm
 */

#ifndef I2C_H_
#define I2C_H_

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

#define DEFAULT_I2C          I2C0

//fine DEBUG_ENABLE

#define I2C_IOX_BUS          DEFAULT_I2C

#define SPEED_100KHZ         100000
#define SPEED_400KHZ         400000
#define I2C_DEFAULT_SPEED    SPEED_400KHZ
#define I2C_FASTPLUS_BIT     0

#if (I2C_DEFAULT_SPEED > SPEED_400KHZ)
#undef  I2C_FASTPLUS_BIT
#define I2C_FASTPLUS_BIT IOCON_FASTI2C_EN
#endif

static int mode_poll;	// Poll/Interrupt mode flag
static I2C_ID_T i2cDev = DEFAULT_I2C;	// Currently active I2C device

#define DEFAULT_I2C_SLAVE_ADDR          0x00

// Xfer structure for slave operations
static I2C_XFER_T iox_xfer;

// Data area for slave operations
static uint8_t buffer[2][256];
static uint8_t iox_data[2];	// PORT0 input port, PORT1 output port
static volatile uint32_t tick_cnt;

/*********************************************************************
 * Prototypes
 ********************************************************************/
//void i2c_iox_update_regs(int ops);
//int i2c_write(I2C_XFER_T *, uint8_t, uint8_t, int);
//int i2c_read(I2C_XFER_T *, uint8_t, int);
//int i2c_cmdwrite(I2C_XFER_T *, uint8_t, uint8_t, uint8_t);
//int i2c_cmdread(I2C_XFER_T *, uint8_t, uint8_t, int);
//void i2c_init();
//void i2c_write_byte(uint8_t, uint8_t, uint8_t);
//uint8_t i2c_read_byte(uint8_t, uint8_t);
//void i2c_read_bytes(uint8_t, uint8_t, uint8_t *, uint8_t);

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

static void Init_I2C_PinMux(void) {
	Chip_SYSCTL_PeriphReset(RESET_I2C0);
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_4,
			IOCON_FUNC1 | I2C_FASTPLUS_BIT);
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_5,
			IOCON_FUNC1 | I2C_FASTPLUS_BIT);
}

// State machine handler for I2C0 and I2C1
static void i2c_state_handling(I2C_ID_T id) {
	if (Chip_I2C_IsMasterActive(id)) {
		Chip_I2C_MasterStateHandler(id);
	} else {
		Chip_I2C_SlaveStateHandler(id);
	}
}

// Set I2C mode to polling/interrupt
static void i2c_set_mode(I2C_ID_T id, int polling) {
	if (!polling) { // Set mode to interrupt
		mode_poll &= ~(1 << id);
		Chip_I2C_SetMasterEventHandler(id, Chip_I2C_EventHandler);
		NVIC_EnableIRQ(I2C0_IRQn);
	} else { // Set mode to polling
		mode_poll |= 1 << id;
		NVIC_DisableIRQ(I2C0_IRQn);
		Chip_I2C_SetMasterEventHandler(id, Chip_I2C_EventHandlerPolling);
	}
}

// Initialize the I2C bus
static void i2c_app_init(I2C_ID_T id, int speed) {
	Init_I2C_PinMux();

	// Initialize I2C
	Chip_I2C_Init(id);
	Chip_I2C_SetClockRate(id, speed);

	// Set default mode to interrupt
	i2c_set_mode(id, 0);
}

/*--------- IO Expansion slave device implementation ----------*/

// Update IN/OUT port states to real devices
//void i2c_iox_update_regs(int ops) {
//	if (ops & 1) {	// update out port
//		Board_LED_Set(0, iox_data[1] & 1);
//		Board_LED_Set(1, iox_data[1] & 2);
//		Board_LED_Set(2, iox_data[1] & 4);
//		Board_LED_Set(3, iox_data[1] & 8);
//	}
//
//#ifndef CHIP_LPC11CXX
//	if (ops & 2) {	// update in port
//		iox_data[0] = (uint8_t) Buttons_GetStatus();
//	}
//#endif
//}

// Slave event handler for simulated EEPROM
static void i2c_iox_events(I2C_ID_T id, I2C_EVENT_T event) {
	switch (event) {
	case I2C_EVENT_DONE:
		iox_xfer.rxBuff = &iox_data[1];
		iox_xfer.rxSz = sizeof(iox_data);
		iox_xfer.txBuff = (const uint8_t *) iox_data;
		iox_xfer.txSz = sizeof(iox_data) + 1;
		break;

	case I2C_EVENT_SLAVE_RX:
		iox_xfer.rxBuff = &iox_data[1];
		iox_xfer.rxSz = sizeof(iox_data);
//		i2c_iox_update_regs(1);
		break;

	case I2C_EVENT_SLAVE_TX:
		if (iox_xfer.txSz == 1) {
			iox_xfer.txBuff = (const uint8_t *) iox_data[0];
			iox_xfer.txSz = sizeof(iox_data) + 1;
		}
		break;
	default:
	    break;
	}
}

// Simulate an IO Expansion slave device
static void i2c_iox_init(I2C_ID_T id) {
#ifndef CHIP_LPC11CXX
	Board_Buttons_Init();
#endif
	iox_xfer.slaveAddr = (DEFAULT_I2C_SLAVE_ADDR << 1);
	i2c_iox_events(id, I2C_EVENT_DONE);
	Chip_I2C_SlaveSetup(id, I2C_SLAVE_1, &iox_xfer, i2c_iox_events, 0);
//	i2c_iox_update_regs(3);
	// Setup SysTick timer to get the button status updated at regular intervals
//	SysTick_Config(Chip_Clock_GetSystemClockRate() / 50);
}

int i2c_write(I2C_XFER_T *xfer, uint8_t slaveAddr, uint8_t data, int length) {
	int tmp;

	xfer->slaveAddr = (slaveAddr & 0xFF);
	xfer->rxBuff = 0;
	xfer->txBuff = 0;
	xfer->txSz = 0;
	xfer->rxSz = 0;

	buffer[0][0] = data;

	xfer->txSz = length;
	xfer->txBuff = buffer[0];

	if (xfer->txSz == 0) {
		return 0;
	}

	tmp = Chip_I2C_MasterSend(	i2cDev,
								xfer->slaveAddr,
								xfer->txBuff,
								xfer->txSz);
	return tmp;
}

/*int i2c_read(I2C_XFER_T *xfer, uint8_t slaveAddr, int length) {
	int tmp;

	xfer->slaveAddr = (slaveAddr & 0xFF);
	xfer->rxBuff = 0;
	xfer->txBuff = 0;
	xfer->txSz = 0;
	xfer->rxSz = 0;

	xfer->rxSz = length;
	xfer->rxBuff = buffer[1];

	tmp = Chip_I2C_MasterRead(	i2cDev,
								xfer->slaveAddr,
								xfer->rxBuff,
								xfer->rxSz);
	return tmp;
}*/

int i2c_cmdwrite(I2C_XFER_T *xfer, uint8_t slaveAddr, uint8_t regAddr, uint8_t data) {
	xfer->slaveAddr = (slaveAddr & 0xFF);
	xfer->rxBuff = 0;
	xfer->txBuff = 0;
	xfer->txSz = 0;
	xfer->rxSz = 0;

	buffer[0][0] = regAddr;
	buffer[0][1] = data;

	xfer->txSz = 2;
	xfer->txBuff = buffer[0];

	if (xfer->txSz == 0) {
		return 0;
	}

	I2C_XFER_T mxfer = { 0 };
	mxfer.slaveAddr = (slaveAddr & 0xFF);
	mxfer.txBuff = xfer->txBuff;
	mxfer.txSz = 2;
	mxfer.rxBuff = xfer->rxBuff;
	mxfer.rxSz = 0;
	while (Chip_I2C_MasterTransfer(i2cDev, &mxfer) == I2C_STATUS_ARBLOST) {
	}
	return 1;
}

int i2c_cmdread(I2C_XFER_T *xfer, uint8_t slaveAddr, uint8_t cmd, int rxlength) {
	int tmp;

	xfer->slaveAddr = (slaveAddr & 0xFF);
	xfer->rxBuff = 0;
	xfer->txBuff = 0;
	xfer->txSz = 0;
	xfer->rxSz = 0;

	xfer->rxSz = rxlength;
	xfer->rxBuff = buffer[1];

	tmp = Chip_I2C_MasterCmdRead(	i2cDev,
									xfer->slaveAddr,
									cmd,
									xfer->rxBuff,
									xfer->rxSz);
	return tmp;
}

/*-------------------- End of IO Expansion slave device ----------------------*/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

void i2c_init(){
    Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);
	i2c_app_init(DEFAULT_I2C, I2C_DEFAULT_SPEED);
	i2c_iox_init(I2C_IOX_BUS);
	return;
}

void i2c_write_byte(uint8_t slaveAddr, uint8_t regAddr, uint8_t byte){
	I2C_XFER_T xfer;
	i2c_cmdwrite(&xfer, slaveAddr, regAddr, byte);
	return;
}

uint8_t i2c_read_byte(uint8_t slaveAddr, uint8_t regAddr){
	I2C_XFER_T xfer;
	i2c_cmdread(&xfer, slaveAddr, regAddr, 1);
	return xfer.rxBuff[0];
}

void i2c_read_bytes(uint8_t slaveAddr, uint8_t regAddr, uint8_t *dest, uint8_t count){
	int i;
	I2C_XFER_T xfer;

	i2c_cmdread(&xfer, slaveAddr, regAddr, count);

	for (i = 0; i<count; i++)
		dest[i] = buffer[1][i];

	return;
}

/**
 * @brief	SysTick Interrupt Handler
 * @return	Nothing
 * @note	Systick interrupt handler updates the button status
 */
//void SysTick_Handler(void) {
//	i2c_iox_update_regs(2);
//	tick_cnt++;
//}

/**
 * @brief	I2C Interrupt Handler
 * @return	None
 */
void I2C_IRQHandler(void) {
	i2c_state_handling(I2C0);
}

#endif /* I2C_H_ */
