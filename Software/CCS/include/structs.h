/*
 * structs.h
 *
 *  Created on: May 8, 2014
 *      Author: Keenan Johnson
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

struct base_station_cmd_struct
{
	uint16_t  id;
    uint8_t value;
}__attribute__((packed));

struct motor_struct
{
	uint8_t value; // 0 for open loop control, non-zero for closed-loop
}__attribute__((packed));

struct gps_data_struct
{
  uint8_t fix;
  float latitude, longitude, altitude, speed;
  uint8_t lat, lon;
  uint8_t hour, minute, seconds, fixquality, satellites;
}__attribute__((packed));

struct bms_data_struct
{
  uint16_t volt0;
  uint16_t temp0;
  uint16_t volt1;
  uint16_t temp1;
  uint16_t volt2;
  uint16_t temp2;
  uint16_t volt3;
  uint16_t temp3;
  uint16_t volt4;
  uint16_t temp4;
  uint16_t volt5;
  uint16_t temp5;
  uint16_t volt6;
  uint16_t temp6;
  uint16_t main_bat_cur;
  uint16_t main_bat_volt;
}__attribute__((packed));

struct arm_control_struct
{
	uint8_t wristUp;
	uint8_t wristDown;
	uint8_t wristClockWise;
	uint8_t wristCounterClockWise;
	uint8_t elbowUp;
	uint8_t elbowDown;
	uint8_t elbowClockWise;
	uint8_t elbowCounterClockWise;
	uint8_t actuatorForward;
	uint8_t actuatorReverse;
	uint8_t baseClockWise;
	uint8_t baseCounterClockWise;
}__attribute__((packed));

struct gripper_control_struct
{
	uint8_t grip_cmd;
}__attribute__((packed));

struct drill_Controls
{
  //Drill Ctrl
  uint8_t goalSpeed;
  uint8_t direction;

  //Thermo Ctrl
  uint8_t heaterPower;
  uint8_t thermoReadings;

  //Gas Ctrl
  uint8_t sensorPower;
  uint8_t gasReadings; //Readings will only be updated when true
}__attribute__((packed));

struct drill_Telemetry
{
    //Gas Data
  uint16_t hydrogenReading;
  uint16_t methaneReading;
  uint16_t ammoniaReading;

  //Thermo Data
  float temp;

  //Drill Data
  uint8_t actualSpeed;
  uint16_t goalCurrent;
  uint16_t actualCurrent;

}__attribute__((packed));

struct science_payload_control_struct
{
  //1 for on, 0 for off
  uint8_t lb395;

  //1 for on, 0 for off
  uint8_t lb440;

  //position. 255 for open, 0 for close
  uint8_t doorserv;
}__attribute__((packed));

#endif /* STRUCTS_H_ */
