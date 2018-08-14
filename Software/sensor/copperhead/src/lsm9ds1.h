/*
 * lsm9ds1.h
 *
 *  Created on: Jul 24, 2015
 *      Author: milesm
 */

#ifndef LSM9DS1_H_
#define LSM9DS1_H_

////////////////////
// Other Includes //
////////////////////
#include <math.h>
#include <stdint.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "i2c.h"
#include "SYC_pub.h"

/////////////////
// Global Data //
/////////////////
#define PI 3.14159265
const float RAD2DEG = 57.29577951; // RAD2DEG = 180.0/PI

///////////////////
// Code Settings //
///////////////////
#define WHO_AM_I			0x3D68 // WHO_AM_I value of mag (0x3D) and accel/gyro (0x68), used to check successful communication
#define I2C_SLAVE_AG_ADDR	0x6A // I2C address of Accel/Gyro (LSB high)
#define I2C_SLAVE_M_ADDR	0x1C // I2C address of Mag (LSB high)
#define PRINT_CALCULATED // if defined, prints calculated data instead of direct ADC output

//////////////////////////////////
// LSM9DS1 Accel/Gyro Registers //
//////////////////////////////////
#define ACT_THS				0x04
#define ACT_DUR             0x05
#define INT_GEN_CFG_XL      0x06
#define INT_GEN_THS_X_XL    0x07
#define INT_GEN_THS_Y_XL    0x08
#define INT_GEN_THS_Z_XL    0x09
#define INT_GEN_DUR_XL      0x0A
#define REFERENCE_G         0x0B
#define INT1_CTRL           0x0C
#define INT2_CTRL           0x0D
#define WHO_AM_I_AG         0x0F
#define CTRL_REG1_G         0x10
#define CTRL_REG2_G         0x11
#define CTRL_REG3_G         0x12
#define ORIENT_CFG_G        0x13
#define INT_GEN_SRC_G       0x14
#define OUT_TEMP_L          0x15
#define OUT_TEMP_H          0x16
#define STATUS_REG_G        0x17
#define OUT_X_L_G           0x18
#define OUT_X_H_G           0x19
#define OUT_Y_L_G           0x1A
#define OUT_Y_H_G           0x1B
#define OUT_Z_L_G           0x1C
#define OUT_Z_H_G           0x1D
#define CTRL_REG4           0x1E
#define CTRL_REG5_XL        0x1F
#define CTRL_REG6_XL        0x20
#define CTRL_REG7_XL        0x21
#define CTRL_REG8           0x22
#define CTRL_REG9           0x23
#define CTRL_REG10          0x24
#define INT_GEN_SRC_XL      0x26
#define STATUS_REG_XL       0x27
#define OUT_X_L_XL          0x28
#define OUT_X_H_XL          0x29
#define OUT_Y_L_XL          0x2A
#define OUT_Y_H_XL          0x2B
#define OUT_Z_L_XL          0x2C
#define OUT_Z_H_XL          0x2D
#define FIFO_CTRL           0x2E
#define FIFO_SRC            0x2F
#define INT_GEN_CFG_G       0x30
#define INT_GEN_THS_XH_G    0x31
#define INT_GEN_THS_XL_G    0x32
#define INT_GEN_THS_YH_G    0x33
#define INT_GEN_THS_YL_G    0x34
#define INT_GEN_THS_ZH_G    0x35
#define INT_GEN_THS_ZL_G    0x36
#define INT_GEN_DUR_G       0x37

///////////////////////////
// LSM9DS1 Mag Registers //
///////////////////////////
#define OFFSET_X_REG_L_M    0x05
#define OFFSET_X_REG_H_M    0x06
#define OFFSET_Y_REG_L_M    0x07
#define OFFSET_Y_REG_H_M    0x08
#define OFFSET_Z_REG_L_M    0x09
#define OFFSET_Z_REG_H_M    0x0A
#define WHO_AM_I_M          0x0F
#define CTRL_REG1_M         0x20
#define CTRL_REG2_M         0x21
#define CTRL_REG3_M         0x22
#define CTRL_REG4_M         0x23
#define CTRL_REG5_M         0x24
#define STATUS_REG_M        0x27
#define OUT_X_L_M           0x28
#define OUT_X_H_M           0x29
#define OUT_Y_L_M           0x2A
#define OUT_Y_H_M           0x2B
#define OUT_Z_L_M           0x2C
#define OUT_Z_H_M           0x2D
#define INT_CFG_M           0x30
#define INT_SRC_M           0x31
#define INT_THS_L_M         0x32
#define INT_THS_H_M         0x33

/*********************** ENUMS ***********************/

// SENSOR_TYPE defines which sensor is being passed to a function
typedef enum {
	GYRO, ACCEL, MAG,
} SENSOR_TYPE;

// GYRO_SCALE_VAR defines the possible full-scale ranges of the gyroscope:
typedef enum {
	G_SCALE_245DPS,   // 00:  245 degrees per second
	G_SCALE_500DPS,   // 01:  500 dps
	G_SCALE_2000DPS,  // 11: 2000 dps
} GYRO_SCALE_VAR;

// ACCEL_SCALE_VAR defines all possible FSR's of the accelerometer:
typedef enum {
	A_SCALE_2G,   // 00:  2g
	A_SCALE_16G,  // 01: 16g
	A_SCALE_4G,   // 10:  4g
	A_SCALE_8G,   // 11:  8g
} ACCEL_SCALE_VAR;

// MAG_SCALE_VAR defines all possible FSR's of the magnetometer:
typedef enum {
	M_SCALE_4GS,   // 00:  4 Gs
	M_SCALE_8GS,   // 01:  8 Gs
	M_SCALE_12GS,  // 10: 12 Gs
	M_SCALE_16GS,  // 11: 16 Gs
} MAG_SCALE_VAR;

// GYRO_ODR_VAR defines all possible data rate/bandwidth combos of the gyro (and accel if not accel-only mode):
typedef enum {				 // ODR (Hz) --- Cutoff
	G_ODR_POWER_DOWN = 0x00, // power-down	 N/A
	G_ODR_149_BW_NA = 0x20,  // 14.9		 N/A
	G_ODR_595_BW_16 = 0x40,  // 59.5		 N/A
	G_ODR_119_BW_14 = 0x60,  // 119			 14
	G_ODR_119_BW_31 = 0x61,  // 119		 	 31
	G_ODR_238_BW_14 = 0x80,  // 238		 	 14
	G_ODR_238_BW_29 = 0x81,  // 238		 	 29
	G_ODR_238_BW_63 = 0x82,  // 238		 	 63
	G_ODR_238_BW_78 = 0x83,  // 238		 	 78
	G_ODR_476_BW_21 = 0xA0,  // 479		 	 21
	G_ODR_476_BW_28 = 0xA1,  // 479		 	 28
	G_ODR_476_BW_57 = 0xA2,  // 479		 	 57
	G_ODR_476_BW_100 = 0xA3, // 479		 	 100
	G_ODR_952_BW_33 = 0xC0,  // 952		 	 33
	G_ODR_952_BW_40 = 0xC1,  // 952		 	 40
	G_ODR_952_BW_58 = 0xC2,  // 952		 	 58
	G_ODR_952_BW_100 = 0xC3, // 952		 	 100
	G_ODR_NA_BW_NA = 0xE0,   // N/A		 	 N/A
} GYRO_ODR_VAR;

// ACCEL_ODR_VAR defines all possible output data rates of the accelerometer (accel-only mode, else odr defined by gyro_odr):
typedef enum {
	A_POWER_DOWN = 0x00, // Power-down mode (0x00)
	A_ODR_10 = 0x01,	 //  10 Hz (0x01)
	A_ODR_50 = 0x02,	 //  50 Hz (0x02)
	A_ODR_119 = 0x03,	 // 119 Hz (0x03)
	A_ODR_238 = 0x04,	 // 238 Hz (0x04)
	A_ODR_476 = 0x05,	 // 476 Hz (0x05)
	A_ODR_952 = 0x06,	 // 952 Hz (0x06)
	A_ODR_NA = 0x07,	 // N/A Hz (0x07)
} ACCEL_ODR_VAR;

// ACCEL_ABW_VAR defines all possible anti-aliasing filter rates of the accelerometer:
typedef enum {
	A_ABW_408 = 0x00, // 408 Hz (0x00)
	A_ABW_211 = 0x01, // 211 Hz (0x01)
	A_ABW_105 = 0x02, // 105 Hz (0x02)
	A_ABW_50 = 0x03,  //  50 Hz (0x03)
} ACCEL_ABW_VAR;

// MAG_ODR_VAR defines all possible output data rates of the magnetometer:
typedef enum {
	M_ODR_625 = 0x00, //  0.625 Hz (0x00)
	M_ODR_125 = 0x01, //  1.25  Hz (0x01)
	M_ODR_25 = 0x02,  //  2.5 Hz   (0x02)
	M_ODR_5 = 0x03,   //  5 Hz     (0x03)
	M_ODR_10 = 0x04,  // 10 Hz     (0x04)
	M_ODR_20 = 0x05,  // 20 Hz     (0x05)
	M_ODR_40 = 0x06,  // 40 Hz     (0x06)
	M_ODR_80 = 0x07,  // 80 Hz     (0x07)
} MAG_ODR_VAR;

// MAG_XY_OM_VAR defines the X and Y axes operative mode selection of the magnetometer:
typedef enum {
	M_XY_OM_L = 0x00,  // low-power mode (0x00)
	M_XY_OM_M = 0x01,  // medium-performance mode (0x01)
	M_XY_OM_H = 0x02,  // high-performance mode (0x02)
	M_XY_OM_UH = 0x03, // ultra-high performance mode (0x03)
} MAG_XY_OM_VAR;

// MAG_Z_OM_VAR defines the Z axis operative mode selection of the magnetometer:
typedef enum {
	M_Z_OM_L = 0x00,   // low-power mode (0x00)
	M_Z_OM_M = 0x01,   // medium-performance mode (0x01)
	M_Z_OM_H = 0x02,   // high-performance mode (0x02)
	M_Z_OM_UH = 0x03, // ultra-high performance mode (0x03)
} MAG_Z_OM_VAR;

// raw_data is a struct of raw x/y/z ADC values
typedef struct {
	/* We'll store the gyro, accel, and magnetometer readings in a series of
	 public class variables. Each sensor gets three variables -- one for each
	 axis. Call readGyro(), readAccel(), and readMag() first, before using
	 these variables!
	 These values are the RAW signed 16-bit readings from the sensors.*/
	int16_t x, y, z;
} rawdata;

// calc_data is a struct of x/y/z values that have been calculated to scale and adjusted relative to each other
typedef struct {
	float x, y, z;
} calcdata;

// lsm9ds1 is a struct representing the LSM9DS1 Gyro/Accel/Mag chip that contains all relevant information
typedef struct {

// Sensor I2C slave addresses
	uint8_t accelgyro_i2c_addr;
	uint8_t mag_i2c_addr;

// Sensor raw ADC values
	rawdata gyro_rdat;
	rawdata accel_rdat;
	rawdata mag_rdat;
	uint16_t temperature;

// Sensor calculated values
	calcdata gyro_cdat; // in degrees/sec
	calcdata accel_cdat; // in g's
	calcdata mag_cdat; // in Gauss

// Sensor derived pitch, roll, yaw
	calcdata pry;

// Sensor dc biases
	calcdata gyro_dc_bias;
	calcdata accel_dc_bias;
	calcdata mag_dc_bias;

// Sensor scaling biases
	calcdata gyro_scale_bias;
	calcdata accel_scale_bias;
	calcdata mag_scale_bias;

// Gyro deadzone value
	float gyro_deadzone;

// Sensor raw ADC scaling values
	GYRO_SCALE_VAR gyro_scale;
	ACCEL_SCALE_VAR accel_scale;
	MAG_SCALE_VAR mag_scale;

// Sensor resolutions
	float gyro_res;
	float accel_res;
	float mag_res;

// Sensor output data rate
	GYRO_ODR_VAR gyro_odr;
	ACCEL_ODR_VAR accel_odr;
	MAG_ODR_VAR mag_odr;

// Accelerometer bandwidth
	ACCEL_ABW_VAR accel_abw;

// Magnetometer operating performance modes
	MAG_XY_OM_VAR mag_xy_om;
	MAG_Z_OM_VAR mag_z_om;

} lsm9ds1;

/*********************** PROTOTYPES ***********************/

// Initialize chip object
uint16_t init_lsm9ds1(lsm9ds1 *, GYRO_SCALE_VAR, ACCEL_SCALE_VAR, MAG_SCALE_VAR,
		GYRO_ODR_VAR, ACCEL_ODR_VAR, MAG_ODR_VAR, MAG_XY_OM_VAR, MAG_Z_OM_VAR);

// Init sensors
void init_accelgyro(lsm9ds1 *);
void init_mag(lsm9ds1 *);

// Calibrate sensors
void cal_lsm9ds1(lsm9ds1 *);
// During cal_gyro, unit must not be moved.
void cal_gyro(lsm9ds1 *);
// During cal_mag_xy, unit must be rotated in one direction about the z axis (PCB parallel to Earth). Orientation during calibration must be that of the desired operation.
void cal_mag_xy(lsm9ds1 *);

// Set biases for sensor calculated data
void set_biases(lsm9ds1 *);

// Update Gyro/Accel/Mag values
void update_gam(lsm9ds1 *);

// Read sensor data regs, convert raw values to calculated values, scale using biases
void update_sensor(SENSOR_TYPE, lsm9ds1 *);

// Read sensor data regs and re-populate sensor raw data fields
void read_sensor(SENSOR_TYPE, lsm9ds1 *);

// Use raw sensor values and sensor resolutions to populate calculated sensor values
void conv_sensor(SENSOR_TYPE, lsm9ds1 *);

// Update calculated sensor values with biasing/deadzoning
void fix_sensor(SENSOR_TYPE, lsm9ds1 *);

// Update Pitch/Roll/Yaw values
void update_pry(lsm9ds1 *);
void update_pitch(lsm9ds1 *);
void update_roll(lsm9ds1 *);
void update_yaw(lsm9ds1 *);

// Calculate sensor resolutions
void calc_sensor_res(SENSOR_TYPE, lsm9ds1 *);

// Return calculated x/y/z values of sensor
float get_calc_x(SENSOR_TYPE, lsm9ds1 *);
float get_calc_y(SENSOR_TYPE, lsm9ds1 *);
float get_calc_z(SENSOR_TYPE, lsm9ds1 *);

// Return raw x/y/z values of sensor
int16_t get_raw_x(SENSOR_TYPE, lsm9ds1 *);
int16_t get_raw_y(SENSOR_TYPE, lsm9ds1 *);
int16_t get_raw_z(SENSOR_TYPE, lsm9ds1 *);

// Return x/y/z dc bias of sensor
float get_x_dc_bias(SENSOR_TYPE, lsm9ds1 *);
float get_y_dc_bias(SENSOR_TYPE, lsm9ds1 *);
float get_z_dc_bias(SENSOR_TYPE, lsm9ds1 *);

// Return x/y/z scale bias of sensor
float get_x_scale_bias(SENSOR_TYPE, lsm9ds1 *);
float get_y_scale_bias(SENSOR_TYPE, lsm9ds1 *);
float get_z_scale_bias(SENSOR_TYPE, lsm9ds1 *);

// Return resolution of sensor
float get_sensor_res(SENSOR_TYPE, lsm9ds1 *);

// Return pitch/roll/yaw values
float get_pitch(lsm9ds1 *);
float get_roll(lsm9ds1 *);
float get_yaw(lsm9ds1 *);

float get_heading(lsm9ds1 *);

// Set calculated x/y/z of sensor
void set_x(SENSOR_TYPE, lsm9ds1 *, float);
void set_y(SENSOR_TYPE, lsm9ds1 *, float);
void set_z(SENSOR_TYPE, lsm9ds1 *, float);

// Set pitch/roll/yaw values
void set_pitch(lsm9ds1 *, float);
void set_roll(lsm9ds1 *, float);
void set_yaw(lsm9ds1 *, float);

// Return I2C slave address of sensor
uint8_t get_sensor_addr(SENSOR_TYPE, lsm9ds1 *);

// Init I2C interface
void init_lsm9ds1_i2c();

// Write bytes to I2C
void write_byte(SENSOR_TYPE, lsm9ds1 *, uint8_t, uint8_t);
uint8_t read_byte(SENSOR_TYPE, lsm9ds1 *, uint8_t);
void read_bytes(SENSOR_TYPE, lsm9ds1 *, uint8_t, uint8_t *, uint8_t);

// Return sign of float
int sign(float);

/*********************** FUNCTIONS ***********************/

//////////////////////
// INIT FUNCTIONS   //
// - lsm9ds1_init   //
// - init_accelgyro //
// - init_mag       //
//////////////////////
uint16_t init_lsm9ds1(lsm9ds1 *me, GYRO_SCALE_VAR gScale,
		ACCEL_SCALE_VAR aScale, MAG_SCALE_VAR mScale, GYRO_ODR_VAR gOdr,
		ACCEL_ODR_VAR aOdr, MAG_ODR_VAR mOdr, MAG_XY_OM_VAR mXYOM,
		MAG_Z_OM_VAR mZOM) {

	me->accelgyro_i2c_addr = I2C_SLAVE_AG_ADDR;
	me->mag_i2c_addr = I2C_SLAVE_M_ADDR;

	// Scaling of raw ADC values
	me->gyro_scale = gScale;
	me->accel_scale = aScale;
	me->mag_scale = mScale;

	// Calc resolution of each sensor
	calc_sensor_res(GYRO, me);
	calc_sensor_res(ACCEL, me);
	calc_sensor_res(MAG, me);

	// Init I2C
	init_lsm9ds1_i2c();

	// Read WHO_AM_I reg of each sensor to verify communication
	uint8_t agTest = read_byte(GYRO, me, WHO_AM_I_AG);
	uint8_t mTest = read_byte(MAG, me, WHO_AM_I_M);

	// Init accelerometer/gyroscope
	init_accelgyro(me);
	me->gyro_odr = gOdr;
	me->gyro_scale = gScale;
	me->accel_odr = aOdr;
	me->accel_scale = aScale;
	//TODO: write these to hardware regs

	// Init magnetometer
	init_mag(me);
	me->mag_odr = mOdr;
	me->mag_scale = mScale;
	me->mag_xy_om = mXYOM;
	me->mag_z_om = mZOM;
	//TODO: write these to hardware regs

	// Init sensor calculated DC and Scale biases
	set_biases(me);
	me->gyro_deadzone = 1.0;

	// Calibrate sensors
//	cal_lsm9ds1(me);

	return (mTest << 8) | agTest;
}

void init_accelgyro(lsm9ds1 *me) {
	/* CTRL_REG1_G sets output data rate, full-scale selection, and bandwidth
	 Bits[7:0]: ODR_G2 ODR_G1 ODR_G0 FS_G1 FS_G0 0 BW_G1 BW_G0
	 ODR[2:0] - Output data rate selection
	 *See Table 46 in datasheet
	 FS[1:0] - Full-scale selection
	 00: 245 dps, 01: 500 dps, 10: N/A, 11: 2000 dps
	 BW[1:0] - Bandwidth selection (sets cutoff frequency)
	 *See Table 47 in datasheet. Depends on ODR. */
	write_byte(GYRO, me, CTRL_REG1_G, 0B01100000); // ODR=119Hz, Scale=245dps, BW=14Hz

	/* CTRL_REG2_G sets up INT/OUT config
	 Bits[7:0]: 0 0 0 0 INT_SEL1 INT_SEL0 OUT_SEL1 OUT_SEL0
	 INT_SEL[1:0]: INT selection config
	 OUT_SEL[1:0]: OUT selection config */
	write_byte(GYRO, me, CTRL_REG2_G, 0x00); // Default mode

	/* CTRL_REG3_G sets up low power mode and HPF
	 Bits[7:0]: LP_mode HP_EN 0 0 HPCF3_G HPCF2_G HPCF1_G HPCF0_G
	 LP_mode - low-power mode enable
	 0: LPM disabled, 1: LPM enabled.
	 HP_EN - high-pass filter enable
	 0: HPF disable, 1: HPF enabled.
	 HPCF[3:0] - HPF cutoff frequency selection
	 *See Table 52 in datasheet. */
	write_byte(GYRO, me, CTRL_REG3_G, 0B01000000); // LPM=disabled, HPF=enabled, HPFC=8Hz (ODR=119Hz)

	/* ORIENT_CFG_G sets up sensor sign and orientation
	 Bits[7:0]: 0 0 SignX_G SignY_G SignZ_G Orient_2 Orient_1 Orient_0
	 SignX_G - Pitch axis angular rate sign; 0: positive sign, 1: negative sign
	 SignY_G - Roll axis angular rate sign; 0: positive sign, 1: negative sign
	 SignZ_G - Yaw axis angular rate sign; 0: positive sign, 1: negative sign
	 Orient[2:0] - Directional user orientation selection */
	write_byte(GYRO, me, ORIENT_CFG_G, 0x00); // all axis signs positive

	/* CTRL_REG4 sets up gyro axis output enables and accel latched interrupts
	 Bits[7:0] - 0 0 Zen_G Yen_G Xen_G 0 LIR_XL1 4D_XL1
	 Zen_G - Yaw axis output enable; 0: output disabled, 1: output enabled
	 Yen_G - Roll axis output enable; 0: output disabled, 1: output enabled
	 Xen_G - Pitch axis output enable; 0: output disabled, 1: output enabled
	 LIR_XL1 - Latched interrupt; 0: interrupt request not latched, 1: interupt request latched
	 4D_XL1 - 4D opetion enabled on Interrupt
	 0: interrupt generator uses 6D for position recognition; 1: interrupt generator uses 4D for position recognition. */
	write_byte(GYRO, me, CTRL_REG4, 0B00111000); // all gyro axes enabled, interrupt not latched, interrupt generator uses 6D

	// Temporary !!! For testing !!! Remove !!! Or make useful !!!
	//configGyroInt(0x2A, 0, 0, 0, 0); // Trigger interrupt when above 0 DPS...

	/* CTRL_REG5_XL sets up decimation of accel data and accel axes output enables
	 Bits[7:0] - DEC_1 DEC_0 Zen_XL Yen_XL Xen_XL 0 0 0
	 DEC[1:0] - decimation of accel data on OUT REG and FIFO
	 Zen_XL - Accel Z-axis output enable; 0: output disabled, 1: output enabled
	 Yen_XL - Accel Y-axis output enable; 0: output disabled, 1: output enabled
	 Xen_XL - Accel X-axis output enable; 0: output disabled, 1: output enabled */
	write_byte(GYRO, me, CTRL_REG5_XL, 0B00111000); // no decimation, all Z axes enabled

	/* CTRL_REG6_XL sets up output data rate, power mode selection, accel full-scale selection, and BW selection
	 Bits[7:0] - ODR_XL2 ORD_XL1 ODR_XL0 FS1_XL FS0_XL BW_SCAL_ODR BW_XL1 BW_XL0
	 ODR_XL[2:0] - output data rate and power mode selection
	 *See Table 68 in datasheet
	 FS[1:0] - accel full-scale selection; 00: 2g, 01: 16g, 10: 4g, 11: 8g
	 BW_SCAL_ODR - BW selection; 0: BW determined by ODR selection (See Table 67), 1: BW selected by BW_XL[1:0]
	 BW_XL[1:0] - anti-aliasing filter BW selection; 00: 408Hz, 01: 211Hz, 10: 105Hz, 11: 50Hz */
	write_byte(GYRO, me, CTRL_REG6_XL, 0B01000000); // ODR=50Hz, FS=2g, BW=50Hz (ODR=119Hz)

	/* CTRL_REG7_XL sets up high res mode, digital filter, HPF enable
	 Bits[7:0] - HR DCF1 DCF0 0 0 FDS 0 HPIS1
	 HR - high resolution mode; 0: disabled, 1: enabled
	 DCF[1:0] - accel digital filter cutoff frequency selection
	 *See Table 71 in datasheet
	 FDS - filtered data selection
	 HPIS1 - HPF enabled for accel sensor interrupt funciton on Interrupt */
	write_byte(GYRO, me, CTRL_REG7_XL, 0x00); // default

	/* CTRL_REG8
	 Bits[7:0] - BOOT BDU H_LACTIVE PP_OD SIM IF_ADD_INC BLE SW_RESET
	 BOOT - Reboot memory content (0: normal, 1: reboot)
	 BDU - block data update for accel AND gyro
	 0: Continuous update
	 1: Output registers aren't updated until MSB and LSB have been read
	 H_LACTIVE - interrupt activation level
	 0: interrupt output pins active high
	 1: interrupt output pins active low
	 PP_OD - Push-pull/open-drain selection on INT1_A/G and INT2_A/G (0=push-pull, 1=open-drain)
	 SIM - SPI mode selection
	 0=4-wire, 1=3-wire
	 IF_ADD_INC - register address auto incremented during a multiple byte access with a serial interface
	 0: disabled, 1: enabled
	 BLE - Big/Little Endian data selection
	 0: data LSB @ lower address, 1: data MSB @ lower address
	 SW_RESET - software reset (cleared by hardware after next flash boot) */
	write_byte(GYRO, me, CTRL_REG8, 0B0000100); //normal boot content, continuous data update, interrupt active high,
	//push-pull int, 4-wire SPI, IF_ADD_INC enabled, data LSB @ lower address

	/* CTRL_REG9
	 Bits[7:0] - 0 SLEEP_G 0 FIFO_TEMP_EN DRDY_mask_bit I2C_DISABLE FIFO_EN STOP_ON_FTH
	 SLEEP_G - gyro sleep mode enable; 0: disabled, 1: enabled
	 FIFO_TEMP_EN - temp data storage in FIFO enable; 0: data not stored in FIFO, 1: data stored in FIFO
	 DRDY_mask_bit - data available enable bit; 0: DA timer disabled, 1: DA timer enabled
	 I2C_DISABLE - disable I2C interface; 0: both I2C and SPI enabled, 1: I2C disabled, SPI only
	 FIFO_EN - FIFO memory enable; 0: disabled, 1: enabled
	 STOP_ON_FTH - enable FIFO threshold level use; 0: FIFO depth not limited, 1: FIFO depth limited to threshold level */
	write_byte(GYRO, me, CTRL_REG9, 0x00); // gyro sleep mode disabled, temp data not stored in FIFO, DA timer disabled, I2C and SPI enabled

	/* CTRL_REG10 sets up self-tests
	 Bits[7:0] - 0 0 0 0 0 ST_G 0 ST_XL
	 ST_G - gyro sensor self-test enable; 0: disabled, 1: enabled
	 ST_XL - accel sensor self-test enable; 0: disabled, 1: enabled */
	write_byte(GYRO, me, CTRL_REG10, 0x00); // self-tests disabled
}

void init_mag(lsm9ds1 *me) {
	/* CTRL_REG1_M sets up temp compensation, X/Y axes operative mode, output data rate, self-test
	 Bits[7:0] - TEMP_COMP OM1 OM0 DO2 DO1 DO0 0 ST
	 TEMP_COMP - temperature compensation enable; 0: disabled, 1: enabled
	 OM[1:0] - X and Y axes operative mode selection
	 00: low-power
	 01: medium-performance
	 10: high-performance
	 11: ultra-high performance
	 DO[2:0] - output data rate selection
	 *See Table 111 in datasheet
	 ST - self test enable; 0: disabled, 1: enabled */
	write_byte(MAG, me, CTRL_REG1_M, 0B00110000); // no temp comp, medium performance, 10Hz ODR, no self test

	/* CTRL_REG2_M sets up full-scale selection, reboot, sw reset
	 Bits[7:0] - 0 FS1 FS0 0 REBOOT SOFT_RST 0 0
	 FS[1:0] - full-scale selection; 00: 4g, 01: 8g, 10: 12g, 11: 16g
	 REBOOT - reboot memory content; 0: normal mode, 1: reboot memory content
	 SOFT_RST - config regs and user reg reset function; 0: default value, 1: reset operation */
	write_byte(MAG, me, CTRL_REG2_M, 0B00000000);

	/* CTRL_REG3_M sets up I2C disable, low power mode, SPI mode select, operating mode
	 Bits[7:0] - I2C_DISABLE 0 LP 0 0 SIM MD1 MD0
	 I2C_DISABLE - disable I2C interface; 0: I2C enable, 1: I2C disable
	 LP - low-power mode config
	 If this bit is ‘1’, the DO[2:0] is set to 0.625 Hz and the system performs, for each
	 channel, the minimum number of averages. Once the bit is set to ‘0’, the magnetic
	 data rate is configured by the DO bits in the CTRL_REG1_M (20h) register.
	 SIM - SPI Serial Interface mode selection
	 0: SPI only write operations enabled
	 1: SPI read and write operations enabled
	 MD[1:0] - operating mode selection
	 00: Continuous-conversion mode
	 01: Single-conversion mode
	 10/11: Power-down mode */
	write_byte(MAG, me, CTRL_REG3_M, 0B00000000); // I2C enable, LP disable, SPI r/w operations enable, cont.-conv. mode (default)

	/* CTRL_REG4_M sets up Z axis operative mode, Endian data selection
	 Bits[7:0] - 0 0 0 0 OMZ1 OMZ0 BLE 0
	 OMZ[1:0] - Z-axis operative mode selection
	 00: low-power
	 01: medium-performance
	 10: high-performance
	 11: ultra-high performance
	 BLE - Big/Little Endian data selection
	 0: data LSB @ lower address, 1: data MSB @ lower address */
	write_byte(MAG, me, CTRL_REG4_M, 0B00000000); // low-power mode, data LSB @ lower address

	/* CTRL_REG5_M sets up block data for magnetic data
	 Bits[7:0] - 0 BDU 0 0 0 0 0 0
	 BDU - block data update for magnetic data
	 0: continuous update
	 1: output regs not updated until MSB adn LSB have been read */
	write_byte(MAG, me, CTRL_REG5_M, 0B00000000); // continuous update
}

void cal_lsm9ds1(lsm9ds1 *me) {
	cal_gyro(me);
	cal_mag_xy(me);
}

void cal_gyro(lsm9ds1 *me) {
	// Update raw ADC values of gyro sensor
	read_sensor(GYRO, me);
	// Use raw ADC values of gyro sensor to update calculated values of sensor
	conv_sensor(GYRO, me);

	me->gyro_dc_bias.x = -me->gyro_cdat.x;
	me->gyro_dc_bias.y = -me->gyro_cdat.y;
	me->gyro_dc_bias.z = -me->gyro_cdat.z;
}

void cal_mag_xy(lsm9ds1 *me) {
	uint32_t delta; // Time delta in us (must be multiple of TICK_TIME)
	float intg = 0; // Integral of gyro z
	int cal_deg = 360; // Necessary amount of rotation to calibrate (in degrees)
	uint32_t cal_deg_scale = 1000000; // Necessary scaling value for cal_lim. =1000 if delta in ms, =1000000 if delta in us, etc.
	uint32_t cal_lim = cal_deg * cal_deg_scale; // Value of gyro z integral to achieve necessary amount of rotation
	float mx_max, mx_min, my_max, my_min;

	update_sensor(MAG, me);
	mx_max = me->mag_cdat.x;
	mx_min = me->mag_cdat.x;
	my_max = me->mag_cdat.y;
	my_min = me->mag_cdat.y;

	HWM_get_time_diff_us(); // Start timer

	while (abs(intg) < cal_lim) {
		// Update delta
		delta = HWM_get_time_diff_us();

		// Update mag values and max/mins
		update_sensor(MAG, me);
		if (me->mag_cdat.x > mx_max)
			mx_max = me->mag_cdat.x;
		if (me->mag_cdat.x < mx_min)
			mx_min = me->mag_cdat.x;
		if (me->mag_cdat.y > my_max)
			my_max = me->mag_cdat.y;
		if (me->mag_cdat.y < my_min)
			my_min = me->mag_cdat.y;

		// Update gyro values and filter out negligible values with deadzone. Apply significant values to calculation of gyro z integral.
		update_sensor(GYRO, me);
		if (me->gyro_cdat.z)
			intg += (me->gyro_cdat.z * delta);
	}

	// Apply calibration biases
	update_sensor(ACCEL, me);
	me->mag_dc_bias.x = -((mx_max - mx_min) / 2.0 + mx_min);
	me->mag_scale_bias.x = (sign(me->accel_cdat.z) * 1.0)
			/ (mx_max + me->mag_dc_bias.x);
	me->mag_dc_bias.y = -((my_max - my_min) / 2.0 + my_min);
	me->mag_scale_bias.y = 1.0 / (my_max + me->mag_dc_bias.y);
}

///////////////////////////
// SENSOR DATA FUNCTIONS //
// - update_sensor       //
// - read_sensor         //
// - conv_sensor         //
// - fix_sensor          //
// - calc_sensor_res     //
///////////////////////////

void update_gam(lsm9ds1 *me) {
	update_sensor(GYRO, me);
	update_sensor(ACCEL, me);
	update_sensor(MAG, me);
}

void update_pry(lsm9ds1 *me) {
	update_pitch(me);
	update_roll(me);
	update_yaw(me);
}

void update_sensor(SENSOR_TYPE sensor, lsm9ds1 *me) {
	// Update raw ADC values of lsm9ds1 sensor
	read_sensor(sensor, me);
	// Use raw ADC values of lsm9ds1 sensor to update calculated values of lsm9ds1 sensor
	conv_sensor(sensor, me);
	// Update calculated values of lsm9ds1 sensor to adjust for baising and deadzoning
	fix_sensor(sensor, me);
}

void read_sensor(SENSOR_TYPE sensor, lsm9ds1 *me) {
	uint8_t temp[6] = { 0 };
	uint8_t reg;
	int16_t x, y, z;

	switch (sensor) {
	case GYRO:
		reg = OUT_X_L_G;
		break;
	case ACCEL:
		reg = OUT_X_L_XL;
		break;
	case MAG:
		reg = OUT_X_L_M;
		break;
	}

	read_bytes(sensor, me, reg, temp, 6);

	x = (temp[1] << 8) | temp[0];
	y = (temp[3] << 8) | temp[2];
	z = (temp[5] << 8) | temp[4];

	switch (sensor) {
	case GYRO:
		me->gyro_rdat.x = x;
		me->gyro_rdat.y = y;
		me->gyro_rdat.z = z;
		break;
	case ACCEL:
		me->accel_rdat.x = x;
		me->accel_rdat.y = y;
		me->accel_rdat.z = z;
		break;
	case MAG:
		me->mag_rdat.x = x;
		me->mag_rdat.y = y;
		me->mag_rdat.z = z;
		break;
	}
}

void conv_sensor(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		me->gyro_cdat.x = me->gyro_res * me->gyro_rdat.x;
		me->gyro_cdat.y = me->gyro_res * me->gyro_rdat.y;
		me->gyro_cdat.z = me->gyro_res * me->gyro_rdat.z;
		break;
	case ACCEL:
		me->accel_cdat.x = me->accel_res * me->accel_rdat.x;
		me->accel_cdat.y = me->accel_res * me->accel_rdat.y;
		me->accel_cdat.z = me->accel_res * me->accel_rdat.z;
		break;
	case MAG:
		me->mag_cdat.x = me->mag_res * me->mag_rdat.x;
		me->mag_cdat.y = me->mag_res * me->mag_rdat.y;
		me->mag_cdat.z = me->mag_res * me->mag_rdat.z;
		break;
	}
}

void fix_sensor(SENSOR_TYPE sensor, lsm9ds1 *me) {
	// Get LSM9DS1 member x/y/z values
	float x = get_calc_x(sensor, me);
	float y = get_calc_y(sensor, me);
	float z = get_calc_z(sensor, me);

	// Apply biases
	x = (x + get_x_dc_bias(sensor, me)) * get_x_scale_bias(sensor, me);
	y = (y + get_y_dc_bias(sensor, me)) * get_y_scale_bias(sensor, me);
	z = (z + get_z_dc_bias(sensor, me)) * get_z_scale_bias(sensor, me);

	// If gyro, filter out negligible values with deadzone
	if (sensor == GYRO) {
		if (x > -me->gyro_deadzone && x < me->gyro_deadzone)
			x = 0;
		if (y > -me->gyro_deadzone && y < me->gyro_deadzone)
			y = 0;
		if (z > -me->gyro_deadzone && z < me->gyro_deadzone)
			z = 0;
	}

	// Set LSM9DS1 member x/y/z values
	set_x(sensor, me, x);
	set_y(sensor, me, y);
	set_z(sensor, me, z);

	return;
}

void calc_sensor_res(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		switch (me->gyro_scale) {
		case G_SCALE_245DPS:
			me->gyro_res = 245.0 / 32768.0;
			break;
		case G_SCALE_500DPS:
			me->gyro_res = 500.0 / 32768.0;
			break;
		case G_SCALE_2000DPS:
			me->gyro_res = 2000.0 / 32768.0;
			break;
		}
		break;
	case ACCEL:
		switch (me->accel_scale) {
		case A_SCALE_2G:
			me->accel_res = 2.0 / 32768.0;
			break;
		case A_SCALE_4G:
			me->accel_res = 4.0 / 32768.0;
			break;
		case A_SCALE_8G:
			me->accel_res = 8.0 / 32768.0;
			break;
		case A_SCALE_16G:
			me->accel_res = 16.0 / 32768.0;
			break;
		}
		break;
	case MAG:
		switch (me->mag_scale) {
		case M_SCALE_4GS:
			me->mag_res = 4.0 / 32768.0;
			break;
		case M_SCALE_8GS:
			me->mag_res = 8.0 / 32768.0;
			break;
		case M_SCALE_12GS:
			me->mag_res = 12.0 / 32768.0;
			break;
		case M_SCALE_16GS:
			me->mag_res = 16.0 / 32768.0;
			break;
		}
		break;
	}
}

void update_pitch(lsm9ds1 *me) {
	float ay = get_calc_y(ACCEL, me);
	float az = get_calc_z(ACCEL, me);

	float pitch = atan2(ay, az);

	set_pitch(me, pitch);
	return;
}

void update_roll(lsm9ds1 *me) {
	float ax = get_calc_x(ACCEL, me);
	float ay = get_calc_y(ACCEL, me);
	float az = get_calc_z(ACCEL, me);
	float pitch = get_pitch(me);

	float roll = atan2(-ax, ay * sin(pitch) + az * cos(pitch));

	set_roll(me, roll);
	return;
}

void update_yaw(lsm9ds1 *me) {
	float mx = get_calc_x(MAG, me);
	float my = get_calc_y(MAG, me);
	float mz = get_calc_z(MAG, me);
	float pitch = get_pitch(me); // must call update_pitch beforehand to ensure accuracy
	float roll = get_roll(me); // must call update_roll beforehand to ensure accuracy

	float bfx = (mx) * cos(roll) + (my) * sin(pitch) * sin(roll)
			+ (mz) * cos(pitch) * sin(roll);
	float bfy = (my) * cos(pitch) - (mz) * sin(pitch);

	float yaw = atan2(-bfx, bfy);
	if (yaw < 0) {
		yaw += 2 * PI;
	}

	me->pry.z = yaw;
//	set_yaw(me, yaw);
	return;
}

//////////////////////
// GETTER FUNCTIONS //
// - get_calc_x     //
// - get_calc_y     //
// - get_calc_z     //
//////////////////////

float get_calc_x(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		return me->gyro_cdat.x;
		break;
	case ACCEL:
		return me->accel_cdat.x;
		break;
	case MAG:
		return me->mag_cdat.x;
		break;
	}
	return 0;
}

float get_calc_y(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		return me->gyro_cdat.y;
		break;
	case ACCEL:
		return me->accel_cdat.y;
		break;
	case MAG:
		return me->mag_cdat.y;
		break;
	}
	return 0;
}

float get_calc_z(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		return me->gyro_cdat.z;
		break;
	case ACCEL:
		return me->accel_cdat.z;
		break;
	case MAG:
		return me->mag_cdat.z;
		break;
	}
	return 0;
}

int16_t get_raw_x(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		return me->gyro_rdat.x;
		break;
	case ACCEL:
		return me->accel_rdat.x;
		break;
	case MAG:
		return me->mag_rdat.x;
		break;
	}
	return 0;
}

int16_t get_raw_y(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		return me->gyro_rdat.y;
		break;
	case ACCEL:
		return me->accel_rdat.y;
		break;
	case MAG:
		return me->mag_rdat.y;
		break;
	}
	return 0;
}

int16_t get_raw_z(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		return me->gyro_rdat.z;
		break;
	case ACCEL:
		return me->accel_rdat.z;
		break;
	case MAG:
		return me->mag_rdat.z;
		break;
	}
	return 0;
}

float get_x_dc_bias(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		return me->gyro_dc_bias.x;
		break;
	case ACCEL:
		return me->accel_dc_bias.x;
		break;
	case MAG:
		return me->mag_dc_bias.x;
		break;
	}
	return 0;
}

float get_y_dc_bias(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		return me->gyro_dc_bias.y;
		break;
	case ACCEL:
		return me->accel_dc_bias.y;
		break;
	case MAG:
		return me->mag_dc_bias.y;
		break;
	}
	return 0;
}

float get_z_dc_bias(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		return me->gyro_dc_bias.z;
		break;
	case ACCEL:
		return me->accel_dc_bias.z;
		break;
	case MAG:
		return me->mag_dc_bias.z;
		break;
	}
	return 0;
}

float get_x_scale_bias(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		return me->gyro_scale_bias.x;
		break;
	case ACCEL:
		return me->accel_scale_bias.x;
		break;
	case MAG:
		return me->mag_scale_bias.x;
		break;
	}
	return 0;
}

float get_y_scale_bias(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		return me->gyro_scale_bias.y;
		break;
	case ACCEL:
		return me->accel_scale_bias.y;
		break;
	case MAG:
		return me->mag_scale_bias.y;
		break;
	}
	return 0;
}

float get_z_scale_bias(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		return me->gyro_scale_bias.z;
		break;
	case ACCEL:
		return me->accel_scale_bias.z;
		break;
	case MAG:
		return me->mag_scale_bias.z;
		break;
	}
	return 0;
}

float get_sensor_res(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
		return me->gyro_res;
		break;
	case ACCEL:
		return me->accel_res;
		break;
	case MAG:
		return me->mag_res;
		break;
	}
	return 0;
}

float get_pitch(lsm9ds1 *me) {
	return me->pry.x;
}

float get_roll(lsm9ds1 *me) {
	return me->pry.y;
}

float get_yaw(lsm9ds1 *me) {
	return me->pry.z;
}

float get_heading(lsm9ds1 *me) {
	update_gam(me);
	update_pry(me);
	return get_yaw(me);
}

//////////////////////
// SETTER FUNCTIONS //
// - set_x          //
// - set_y          //
// - set_z          //
//////////////////////

void set_x(SENSOR_TYPE sensor, lsm9ds1 *me, float value) {
	switch (sensor) {
	case GYRO:
		me->gyro_cdat.x = value;
		break;
	case ACCEL:
		me->accel_cdat.x = value;
		break;
	case MAG:
		me->mag_cdat.x = value;
		break;
	}
	return;
}

void set_y(SENSOR_TYPE sensor, lsm9ds1 *me, float value) {
	switch (sensor) {
	case GYRO:
		me->gyro_cdat.y = value;
		break;
	case ACCEL:
		me->accel_cdat.y = value;
		break;
	case MAG:
		me->mag_cdat.y = value;
		break;
	}
	return;
}

void set_z(SENSOR_TYPE sensor, lsm9ds1 *me, float value) {
	switch (sensor) {
	case GYRO:
		me->gyro_cdat.z = value;
		break;
	case ACCEL:
		me->accel_cdat.z = value;
		break;
	case MAG:
		me->mag_cdat.z = value;
		break;
	}
	return;
}

void set_biases(lsm9ds1 *me) {
	me->gyro_dc_bias = (calcdata ) { .x = 0, .y = 0, .z = 0 };
	me->gyro_scale_bias = (calcdata ) { .x = 1, .y = 1, .z = 1 };
	me->accel_dc_bias = (calcdata ) { .x = 0, .y = 0, .z = 0 };
	me->accel_scale_bias = (calcdata ) { .x = 1, .y = -1, .z = 1 };
	me->mag_dc_bias = (calcdata ) { .x = 0.10, .y = -0.31, .z = 0.19 };
	me->mag_scale_bias = (calcdata ) { .x = 2.60, .y = 2.44, .z = -3.60 };
	//TODO: maybe set this in offset/orient HW regs
}

void set_pitch(lsm9ds1 *me, float value) {
	me->pry.x = value;
	return;
}

void set_roll(lsm9ds1 *me, float value) {
	me->pry.y = value;
	return;
}

void set_yaw(lsm9ds1 *me, float value) {
	me->pry.z = value;
	return;
}

////////////////////////
// I2C FUNCTIONS      //
// - get_sensor_addr  //
// - lsm9ds1_init_i2c //
// - write_byte       //
// - read_byte        //
// - read_bytes       //
////////////////////////

uint8_t get_sensor_addr(SENSOR_TYPE sensor, lsm9ds1 *me) {
	switch (sensor) {
	case GYRO:
	case ACCEL:
		return me->accelgyro_i2c_addr;
		break;
	case MAG:
		return me->mag_i2c_addr;
		break;
	}
	return 0;
}

void init_lsm9ds1_i2c() {
	i2c_init();
}

void write_byte(SENSOR_TYPE sensor, lsm9ds1 *me, uint8_t subaddr, uint8_t byte) {
	uint8_t addr = get_sensor_addr(sensor, me);
	i2c_write_byte(addr, subaddr, byte);
	return;
}

uint8_t read_byte(SENSOR_TYPE sensor, lsm9ds1 *me, uint8_t subaddr) {
	uint8_t addr = get_sensor_addr(sensor, me);
	uint8_t byte = i2c_read_byte(addr, subaddr);
	return byte;
}

void read_bytes(SENSOR_TYPE sensor, lsm9ds1 *me, uint8_t subaddr, uint8_t *dest,
		uint8_t count) {
	uint8_t addr = get_sensor_addr(sensor, me);
	i2c_read_bytes(addr, subaddr, dest, count);
	return;
}

int sign(float x) {
	return ((x > 0) - (x < 0));
}

#endif /* LSM9DS1_H_ */
