// The SFE_LSM9DS1 requires both the SPI and Wire libraries.
// Unfortunately, you'll need to include both in the Arduino
// sketch, before including the SFE_LSM9DS1 library.
#include <SPI.h> // Included for SFE_LSM9DS1 library
#include <Wire.h>
#include "EVAL_LSM9DS1_proto2.h"

///////////////////////
// Example I2C Setup //
///////////////////////
// Comment out this section if you're using SPI
// SDO_XM and SDO_G are both grounded, so our addresses are:
#define LSM9DS1_M  0B0011100 // Would be 0x1D if SDO_XM is HIGH
#define LSM9DS1_AG 0B1101010 // Would be 0x6B if SDO_G is HIGH
// Create an instance of the LSM9DS1 library called `dof` the
// parameters for this constructor are:
// [SPI or I2C Mode declaration],[accel/gyro I2C address],[mag I2C add.]
LSM9DS1 dof(MODE_I2C, LSM9DS1_AG, LSM9DS1_M);

const float RAD2DEG = 180/PI;
float gx, gy, gz, ax, ay, az, mx, my, mz;


float ax_dcbias = 0, ay_dcbias = 0, az_dcbias = 0;
float ax_scalebias = 1, ay_scalebias = -1, az_scalebias = 1;

//float mx_dcbias = 0, my_dcbias = 0, mz_dcbias = 0;
//float mx_scalebias = 1, my_scalebias = 1, mz_scalebias = 1;
float mx_dcbias = 0.10, my_dcbias = -0.31, mz_dcbias = 0.19;
float mx_scalebias = 2.62, my_scalebias = 2.44, mz_scalebias = -3.60;

///////////////////////
// Example SPI Setup //
///////////////////////
/* // Uncomment this section if you're using SPI
#define LSM9DS1_CSG  9  // CSG connected to Arduino pin 9
#define LSM9DS1_CSXM 10 // CSXM connected to Arduino pin 10
LSM9DS1 dof(MODE_SPI, LSM9DS1_CSG, LSM9DS1_CSXM);
*/

// Do you want to print calculated values or raw ADC ticks read
// from the sensor? Comment out ONE of the two #defines below
// to pick:
#define PRINT_CALCULATED
//#define PRINT_RAW

#define PRINT_SPEED 50 // ms between prints

void setup()
{
  Serial.begin(115200); // Start serial at 115200 bps
  // Use the begin() function to initialize the LSM9DS1 library.
  // You can either call it with no parameters (the easy way):
  uint16_t status = dof.begin();
  // Or call it with declarations for sensor scales and data rates:  
  //uint16_t status = dof.begin(dof.G_SCALE_2000DPS, 
  //                            dof.A_SCALE_6G, dof.M_SCALE_2GS);

  
  // begin() returns a 16-bit value which includes both the gyro 
  // and accelerometers WHO_AM_I response. You can check this to
  // make sure communication was successful.
//  Serial.print("LSM9DS1 WHO_AM_I's returned: 0x");
//  Serial.println(status, HEX);
//  Serial.println("Should be 0x3D68"); // WHO_AM_I_M should return 0x3D, WHO_AM_I_AG should return 0x68
//  Serial.println();

/*** Calibrate accel and gyro ***/
//  dof.agCal(&gbias, &abias);
//  Serial.println(gbias); Serial.println(abias);
/*** Calibrate mag ***/
//  dof.mCal(&mbias);
//  Serial.println(mbias);

//  calMagXY(mx, my);
//  calMagZ(mz);
}

void loop()
{  
//  dof.readMag();
//  Serial.println(dof.calcMag(dof.mx+750), 2); //+750
//  Serial.println(dof.calcMag(dof.my-2450), 2); //-2450
//  Serial.println(dof.calcMag(dof.mz), 2);

  mathGyro(gx, gy, gz);
  mathAccel(ax, ay, az);
  mathMag(mx, my, mz);

//  printGyro(gx,gy,gz);
//  printAccel(ax,ay,az);
//  printMag(mx,my,mz);
//  Serial.println();

//  Serial.println(mx);
//  Serial.println(my);
//  Serial.println(mz);

  float heading = calcHeadingAngle(mx, my);
//  printHeadingAngle(heading);
//  Serial.println(heading); delay(PRINT_SPEED);

//    printHeadingCompass(mx, my);

//  float pitch = calcPitch(ax, ay, az);
//  printPitch(pitch);
////  Serial.println(pitch);
//  
//  float roll = calcRoll(ax, ay, az);
//  printRoll(roll);

  float yaw = calcYaw(ax, ay, az, mx, my, mz);
//  printYaw(yaw);
//  Serial.println(yaw);

  Serial.print(heading); Serial.print(","); Serial.println(yaw);
  
  delay(PRINT_SPEED);
}

void calMagXY(float & mx, float & my)
{  
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

  while(intg < calLim)
  {
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
void calMagZ(float & mz)
{  
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
float calMagZLim(float & mz)
{
  dof.readMag();
  mz = dof.mz;
  #ifdef PRINT_CALCULATED
    mz = dof.calcMag(mz);
  #endif

  return mz;
}

void mathGyro(float & gx, float & gy, float & gz)
{
  float deadzone = 3.0;

  // To read from the gyroscope, you must first call the
  // readGyro() function. When this exits, it'll update the
  // gx, gy, and gz variables with the most current data.
  dof.readGyro();

  gx = dof.gx;
  gy = dof.gy;
  gz = dof.gz;
  
#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcGyro helper function to convert a raw ADC value to
  // DPS. Give the function the value that you want to convert.
  gx = dof.calcGyro(gx);
  gy = dof.calcGyro(gy);
  gz = dof.calcGyro(gz);
#endif

  if(gx>-deadzone && gx<deadzone)
    gx = 0;
  if(gy>-deadzone && gy<deadzone)
    gy = 0;
  if(gz>-deadzone && gz<deadzone)
    gz = 0;
}
void printGyro(float gx, float gy, float gz)
{  
  // Now we can use the gx, gy, and gz variables as we please.
  // Either print them as raw ADC values, or calculated in DPS.
  Serial.print("G: ");
  Serial.print(gx);
  Serial.print(", ");
  Serial.print(gy);
  Serial.print(", ");
  Serial.println(gz);
}

void mathAccel(float & ax, float & ay, float & az)
{
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
  ax = (ax + ax_dcbias)*ax_scalebias;
  ay = (ay + ay_dcbias)*ay_scalebias;
  az = (az + az_dcbias)*az_scalebias;
#endif
}
void printAccel(float ax, float ay, float az)
{
  // Now we can use the ax, ay, and az variables as we please.
  // Either print them as raw ADC values, or calculated in g's.
  Serial.print("A: ");
  Serial.print(ax);
  Serial.print(", ");
  Serial.print(ay);
  Serial.print(", ");
  Serial.println(az);
}

void mathMag(float & mx, float & my, float & mz)
{
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
  mx = (mx + mx_dcbias)*mx_scalebias;
  my = (my + my_dcbias)*my_scalebias;
  mz = (mz + mz_dcbias)*mz_scalebias;
#endif
}
void printMag(float mx, float my, float mz)
{
  // Now we can use the mx, my, and mz variables as we please.
  // Either print them as raw ADC values, or calculated in Gauss.
  Serial.print("M: ");
  Serial.print(mx);
  Serial.print(", ");
  Serial.print(my);
  Serial.print(", ");
  Serial.println(mz);
}

// Here's a fun function to calculate your heading, using Earth's
// magnetic field.
// It only works if the sensor is flat (z-axis normal to Earth).
// Additionally, you may need to add or subtract a declination
// angle to get the heading normalized to your location.
// See: http://www.ngdc.noaa.gov/geomag/declination.shtml
// hx is the x component and hy is the y component of the mag sensor
// E is 0/360, S is 90, W is 180, N is 270
float calcHeadingAngle(float hx, float hy)
{  
  float heading;
  
//  if (hy > 0)
//  {
//    heading = 90 - (atan(hx / hy) * (180 / PI));
//  }
//  else if (hy < 0)
//  {
//    heading = - (atan(hx / hy) * (180 / PI));
//  }
//  else // hy = 0
//  {
//    if (hx < 0) heading = 180;
//    else heading = 0;
//  }

  if (hx > 0 && hy > 0){ // Quadrant I
    heading = atan(hx / hy);
  }
  else if (hx < 0 && hy > 0){ // Quadrant II
    heading = atan(hx / hy);
  }
  else if (hx < 0 && hy < 0){ // Quadrant III
    heading = -PI + atan(hx / hy);
  }
  else if (hx > 0 && hy < 0){ // Quadrant IV
    heading = PI + atan(hx / hy);
  }
  else{ // On axis
    if (hx == 0){
      if (hy > 0) heading = 0; // On +y axis
      else heading = PI; // On -y axis
    }
    else{ // hy = 0
      if (hx > 0) heading = PI/2; // On +x axis
      else heading = -PI/2; // On -x axis
    }
  }

  return -heading;
}
void printHeadingAngle(float heading)
{
  Serial.print("Heading: "); 
  Serial.println(heading*RAD2DEG);
}
char printHeadingCompass(float hx, float hy)
{
  char c;
  float heading = calcHeadingAngle(hx, hy);
  
}

// Tilt-compensated heading
float calcCompHeading(float mx, float my, float mz, float ax, float ay, float az)
{
  float hcx, hcy, hcz, compheading;
}

// Another fun function that does calculations based on the
// acclerometer data. This function will print your LSM9DS1's
// orientation -- it's roll and pitch angles IN RADIANS (multiply by RAD2DEG to convert to degrees).
float calcPitch(float ax, float ay, float az)
{
//  float pitch = -atan2(y, sqrt((y * y) + (z * z)));
  float pitch = atan2( ay , -az );
  return pitch;
}
void printPitch(float pitch)
{
  Serial.print("Pitch: ");
  Serial.println(pitch*RAD2DEG);
}
float calcRoll(float ax, float ay, float az)
{
//  float roll = -atan2(x, sqrt((x * x) + (z * z)));
  float pitch = calcPitch(ax,ay,az);
  float roll = atan2( ax , -ay*sin(pitch) + az*cos(pitch) );

  return roll;
}
void printRoll(float roll)
{
  Serial.print("Roll: ");
  Serial.println(roll*RAD2DEG);
}
float calcYaw(float ax, float ay, float az, float mx, float my, float mz)
{
  float pitch = calcPitch(ax,ay,az);
  float roll = calcRoll(ax,ay,az);
//  
  float bfx = (mx)*cos(roll) + (my)*sin(pitch)*sin(roll) - (mz)*cos(pitch)*sin(roll);
  float bfy = (my)*cos(pitch) + (mz)*sin(pitch);
//  float yaw = atan2( -bfx , bfy );
  float yaw = atan2( bfx , -bfy );

  return yaw;
}
void printYaw(float yaw)
{
  Serial.print("Yaw: ");
  Serial.println(yaw*RAD2DEG);
}

int sign(float x)
{
  return ((x>0)-(x<0));
}



