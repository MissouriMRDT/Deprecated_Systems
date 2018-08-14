/*
 ===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition

 Previous Version: proto1 - working (Arduino)
 This Version: Minimum changes necessary to achieve basic functionality on LPCXpresso LPC11C24
 ===============================================================================
 */

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

#include "i2c.h"
#include "LSM9DS1.h"
//#include "timer.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

// I2C setup
// SDO_XM and SDO_G are both grounded, so our addresses are:
#define LSM9DS1_M  0B0011100
#define LSM9DS1_AG 0B1101010

// Create an instance of the LSM9DS1 library called `dof` the
// parameters for this constructor are:
// [SPI or I2C Mode declaration],[accel/gyro I2C address],[mag I2C add.]
LSM9DS1 dof(MODE_I2C, LSM9DS1_AG, LSM9DS1_M);

const float RAD2DEG = 57.29577958;
float gx, gy, gz, ax, ay, az, mx, my, mz;

float ax_dcbias = 0, ay_dcbias = 0, az_dcbias = 0;
float ax_scalebias = 1, ay_scalebias = -1, az_scalebias = 1;

float mx_dcbias = 0.10, my_dcbias = -0.31, mz_dcbias = 0.19;
float mx_scalebias = 2.62, my_scalebias = 2.44, mz_scalebias = -3.60;

#define PRINT_CALCULATED
//#define PRINT_RAW

#define PRINT_SPEED 50 // ms between prints

/* Calibration
 void calMagXY(float & mx, float & my) {
 float delta = .001; // time delta in milliseconds
 float intg = 0;
 float calDeg = 360; // in degrees
 float calLim = (calDeg/3.0)*(1000.0*delta);
 float gz;
 float deadzone = 3.0;

 Serial.println("MagXY Calibration Started."); delay(1000);
 Serial.println("Set the device in mounting position."); delay(1000);
 Serial.print("Slowly move the device counter-clockwise "); Serial.print((int)calDeg); Serial.println(" degs to calibrate.");

 mathMag(mx, my, mz);
 float mx_max = mx, my_max = my, mx_min = mx, my_min = my;

 while(intg < calLim) {
 // set up mag
 mathMag(mx, my, mz);
 if(mx > mx_max) mx_max = mx;
 if(my > my_max) my_max = my;
 if(mx < mx_min) mx_min = mx;
 if(my < my_min) my_min = my;

 // set up gz
 dof.readGyro();
 gz = dof.gz;
 #ifdef PRINT_CALCULATED
 gz = dof.calcGyro(gz);
 #endif
 if(gz>-deadzone && gz<deadzone) gz = 0;

 // calc integral of gz
 intg += gz*delta;

 delay(delta);
 }

 // apply calibration biases
 mx_dcbias = -((mx_max - mx_min)/2.0 + mx_min);
 mx_scalebias = -sign(mz)*1.0/(mx_max + mx_dcbias);
 my_dcbias = -((my_max - my_min)/2.0 + my_min);
 my_scalebias = 1.0/(my_max + my_dcbias);

 Serial.println();
 Serial.println("MagXY Calibrated!");
 Serial.println();
 }
 void calMagZ(float & mz) {
 float mz_max, mz_min;

 Serial.println("MagZ Calibration Started."); delay(1000);
 Serial.println("Set the device rightside-up and do not touch it."); delay(1000);
 Serial.print("Calibrating in 3... "); delay(1000);
 Serial.print("2... "); delay(1000);
 Serial.println("1... "); delay(1000);

 mz_min = calMagZLim(mz);

 Serial.println();
 Serial.println("MagZ Part 1 Calibration Complete!");
 delay(1000);

 Serial.println();
 Serial.println("Set the device upside-down and do not touch it."); delay(1000);
 Serial.print("Calibrating in 3... "); delay(1000);
 Serial.print("2... "); delay(1000);
 Serial.println("1... "); delay(1000);

 mz_max = calMagZLim(mz);

 Serial.println();
 Serial.println("MagZ Part 2 Calibration Complete!");

 mz_dcbias = -((mz_max - mz_min)/2.0 + mz_min);
 mz_scalebias = -1.0/(mz_max + mz_dcbias);

 Serial.println();
 Serial.println("MagZ Calibrated!");
 Serial.println();
 }
 float calMagZLim(float & mz) {
 dof.readMag();
 mz = dof.mz;
 #ifdef PRINT_CALCULATED
 mz = dof.calcMag(mz);
 #endif

 return mz;
 }
 */

void mathGyro(float & gx, float & gy, float & gz) {
	float deadzone = 0.0;

	// To read from the gyroscope, you must first call the
	// readGyro() function. When this exits, it'll update the
	// gx, gy, and gz variables with the most current data.
	dof.readGyro();

	gx = dof.gx;  // & (0xFFFF - 0x007F);
	gy = dof.gy;  // & (0xFFFF - 0x007F);
	gz = dof.gz;

#ifdef PRINT_CALCULATED
	// If you want to print calculated values, you can use the
	// calcGyro helper function to convert a raw ADC value to
	// DPS. Give the function the value that you want to convert.
	gx = dof.calcGyro(gx);
	gy = dof.calcGyro(gy);
	gz = dof.calcGyro(gz);

	if (gx > -deadzone && gx < deadzone) gx = 0;
	if (gy > -deadzone && gy < deadzone) gy = 0;
	if (gz > -deadzone && gz < deadzone) gz = 0;
#endif
}
void printGyro(float gx, float gy, float gz) {
	// Now we can use the gx, gy, and gz variables as we please.
	// Either print them as raw ADC values, or calculated in DPS.
//  Serial.print("G: ");
//  Serial.print(gx);
//  Serial.print(", ");
//  Serial.print(gy);
//  Serial.print(", ");
//  Serial.println(gz);

}
void mathAccel(float & ax, float & ay, float & az) {
	// To read from the accelerometer, you must first call the
	// readAccel() function. When this exits, it'll update the
	// ax, ay, and az variables with the most current data.
	dof.readAccel();

	ax = dof.ax;
	ay = dof.ay;
	az = dof.az;

#ifdef PRINT_CALCULATED
	// If you want to print calculated values, you can use the
	// calcAccel helper function to convert a raw ADC value to
	// g's. Give the function the value that you want to convert.
	ax = dof.calcAccel(ax);
	ay = dof.calcAccel(ay);
	az = dof.calcAccel(az);
	// Apply calibration
	ax = (ax + ax_dcbias) * ax_scalebias;
	ay = (ay + ay_dcbias) * ay_scalebias;
	az = (az + az_dcbias) * az_scalebias;
#endif
}
/*void printAccel(float ax, float ay, float az) {
 // Now we can use the ax, ay, and az variables as we please.
 // Either print them as raw ADC values, or calculated in g's.
 Serial.print("A: ");
 Serial.print(ax);
 Serial.print(", ");
 Serial.print(ay);
 Serial.print(", ");
 Serial.println(az);
 }*/

void mathMag(float & mx, float & my, float & mz) {
	// To read from the accelerometer, you must first call the
	// readAccel() function. When this exits, it'll update the
	// mx, my, and mz variables with the most current data.
	dof.readMag();

	mx = dof.mx;
	my = dof.my;
	mz = dof.mz;

#ifdef PRINT_CALCULATED
	// If you want to print calculated values, you can use the
	// calcMag helper function to convert a raw ADC value to
	// Gauss. Give the function the value that you want to convert.
	mx = dof.calcMag(mx);
	my = dof.calcMag(my);
	mz = dof.calcMag(mz);
	// Apply calibration
	mx = (mx + mx_dcbias) * mx_scalebias;
	my = (my + my_dcbias) * my_scalebias;
	mz = (mz + mz_dcbias) * mz_scalebias;
#endif
}
/*void printMag(float mx, float my, float mz) {
 // Now we can use the mx, my, and mz variables as we please.
 // Either print them as raw ADC values, or calculated in Gauss.
 Serial.print("M: ");
 Serial.print(mx);
 Serial.print(", ");
 Serial.print(my);
 Serial.print(", ");
 Serial.println(mz);
 }*/

// Here's a fun function to calculate your heading, using Earth's
// magnetic field.
// It only works if the sensor is flat (z-axis normal to Earth).
// Additionally, you may need to add or subtract a declination
// angle to get the heading normalized to your location.
// See: http://www.ngdc.noaa.gov/geomag/declination.shtml
// hx is the x component and hy is the y component of the mag sensor
// E is 0/360, S is 90, W is 180, N is 270
/*float calcHeadingAngle(float hx, float hy) {
 float heading;

 if (hx > 0 && hy > 0) { // Quadrant I
 heading = atan(hx / hy);
 }
 else if (hx < 0 && hy > 0) { // Quadrant II
 heading = atan(hx / hy);
 }
 else if (hx < 0 && hy < 0) { // Quadrant III
 heading = -PI + atan(hx / hy);
 }
 else if (hx > 0 && hy < 0) { // Quadrant IV
 heading = PI + atan(hx / hy);
 }
 else { // On axis
 if (hx == 0) {
 if (hy > 0) heading = 0; // On +y axis
 else heading = PI; // On -y axis
 }
 else { // hy = 0
 if (hx > 0) heading = PI/2; // On +x axis
 else heading = -PI/2; // On -x axis
 }
 }

 return -heading;
 }
 void printHeadingAngle(float heading) {
 Serial.print("Heading: ");
 Serial.println(heading*RAD2DEG);
 }
 char printHeadingCompass(float hx, float hy) {
 char c;
 float heading = calcHeadingAngle(hx, hy);

 }*/

// Tilt-compensated heading
/*float calcCompHeading(float mx, float my, float mz, float ax, float ay, float az) {
 float hcx, hcy, hcz, compheading;
 }*/

// Another fun function that does calculations based on the
// acclerometer data. This function will print your LSM9DS1's
// orientation -- it's roll and pitch angles IN RADIANS (multiply by RAD2DEG to convert to degrees).
float calcPitch(float ax, float ay, float az) {
//  float pitch = -atan2(y, sqrt((y * y) + (z * z)));
	float pitch = atan2(ay, -az);
	return pitch;
}
/*void printPitch(float pitch) {
 Serial.print("Pitch: ");
 Serial.println(pitch*RAD2DEG);
 }*/
float calcRoll(float ax, float ay, float az) {
//  float roll = -atan2(x, sqrt((x * x) + (z * z)));
	float pitch = calcPitch(ax, ay, az);
	float roll = atan2(ax, -ay * sin(pitch) + az * cos(pitch));

	return roll;
}
/*void printRoll(float roll) {
 Serial.print("Roll: ");
 Serial.println(roll*RAD2DEG);
 }*/
float calcYaw(float ax, float ay, float az, float mx, float my, float mz) {
	float pitch = calcPitch(ax, ay, az);
	float roll = calcRoll(ax, ay, az);
//
	float bfx = (mx) * cos(roll) + (my) * sin(pitch) * sin(roll) - (mz) * cos(pitch) * sin(roll);
	float bfy = (my) * cos(pitch) + (mz) * sin(pitch);
//  float yaw = atan2( -bfx , bfy );
	float yaw = atan2(bfx, -bfy);

	return yaw;
}
/*void printYaw(float yaw) {
 Serial.print("Yaw: ");
 Serial.println(yaw*RAD2DEG);
 }*/

int sign(float x) {
	return ((x > 0) - (x < 0));
}

/********************************************************************************************/



/********************************************************************************************/

int main(void) {

#if defined (__USE_LPCOPEN)
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();
	// Set the LED to the state of "On"
	Board_LED_Set(0, true);
#endif
#endif

	dof.begin(dof.G_SCALE_245DPS, dof.A_SCALE_2G, dof.M_SCALE_4GS, dof.G_ODR_119_BW_14,
			dof.A_ODR_50, dof.M_ODR_40, dof.M_XY_OM_M, dof.M_Z_OM_M);

	while (1) {
		mathGyro(gx, gy, gz);
		mathAccel(ax, ay, az);
		mathMag(mx, my, mz);

		printGyro(gx, gy, gz);
	}

	// Force the counter to be placed into memory
	volatile static int i = 0;
	// Enter an infinite loop, just incrementing a counter
	while (1) {
		i++;
	}

	return 0;
}

