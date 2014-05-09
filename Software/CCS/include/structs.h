/*
 * structs.h
 *
 *  Created on: May 8, 2014
 *      Author: Keenan Johnson
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

struct motor_struct
{
	unsigned char closedLoopMode; // 0 for open loop control, non-zero for closed-loop
	float setSpeed; // speed in km/hr for closed-loop control. This is intentionally redundant (for debug and production mode)
	unsigned char openPWM; // directly set the PWM value for open-loop control mode
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
}__attribute__((packed));

struct receive_test
{
	uint16_t data;
}__attribute__((packed));

#endif /* STRUCTS_H_ */
