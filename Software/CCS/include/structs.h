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

#endif /* STRUCTS_H_ */
