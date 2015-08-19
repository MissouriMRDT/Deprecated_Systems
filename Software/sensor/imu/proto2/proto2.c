#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "i2c.c"
#include "LSM9DS1.h"

// Create an instance of the LSM9DS1 library
// Parameters: [SPI or I2C Mode declaration],[accel/gyro I2C address],[mag I2C address]
LSM9DS1 dof(MODE_I2C, LSM9DS1_AG, LSM9DS1_M);

int main(){
	// Initialize LSM9DS1 object
	uint16_t status = dof.begin(dof.G_SCALE_245DPS, dof.A_SCALE_2G, dof.M_SCALE_4GS,
								dof.G_ODR_119_BW_14, dof.A_ODR_50, M_ODR_40);

	while( status != WHO_AM_I ); // does not continue unless WHO_AM_I values match (successful I2C communication)
	
	if( !dof.calibrated );// dof.calibrate();

	while(1){ // do stuff
	
	}

	return 0;
}