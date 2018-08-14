// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro(0x68);

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
//    accelgyro.getMag(&mx, &my, &mz);
    
    // these methods (and a few others) are also available
//    accelgyro.getAcceleration(&ax, &ay, &az);
//    delay(100);
//    accelgyro.getRotation(&gx, &gy, &gz);
//    delay(100);
//    accelgyro.getMag(&mx, &my, &mz);
//    delay(100);

    // display tab-separated accel/gyro x/y/z values
//    Serial.print("a/g/m:\t");
    if(ax>0){ Serial.print(" "); }
    Serial.print(ax); Serial.print("\t");
    if(ay>0){ Serial.print(" "); }
    Serial.print(ay); Serial.print("\t");
    if(az>0){ Serial.print(" "); }
    Serial.print(az); Serial.print("\t");
    if(gx>0){ Serial.print(" "); }
    Serial.print(gx); Serial.print("\t");
    if(gy>0){ Serial.print(" "); }
    Serial.print(gy); Serial.print("\t");
    if(gz>0){ Serial.print(" "); }
    Serial.print(gz); Serial.print("\t");
    if(mx>0){ Serial.print(" "); }
    Serial.print(mx); Serial.print("\t");
    if(my>0){ Serial.print(" "); }
    Serial.print(my); Serial.print("\t");
    if(mz>0){ Serial.print(" "); }
    Serial.println(mz);
//    delay(100);
}
