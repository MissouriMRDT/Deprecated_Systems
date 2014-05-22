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
  uint8_t joint1Forward;
  uint8_t joint1Backward;
  uint8_t joint2Forward;
  uint8_t joint2Backward;
  uint8_t joint3Forward;
  uint8_t joint3Backward;
  uint8_t joint4Forward;
  uint8_t joint4Backward;
  uint8_t joint5Forward;
  uint8_t joint5Backward;
  uint8_t joint6Forward;
  uint8_t joint6Backward;
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
