/*
 * lcd44780_LP.h
 *		Header file for the lcd44780_LP.c
 *		Version 1.00
 *      Author: NYH
 *      Reference: Robot Head to Toe Vol. 11 - pg 35-36
 */

#ifndef ROVELCD_H_
#define ROVELCD_H_

#define LCDPORTD  		 GPIO_PORTD_BASE
#define LCDPORTF         GPIO_PORTF_BASE
#define LCDPORTENABLED   SYSCTL_PERIPH_GPIOD
#define LCDPORTENABLEF   SYSCTL_PERIPH_GPIOF
#define RS 		 		 GPIO_PIN_3
#define E 				 GPIO_PIN_0
#define D4 				 GPIO_PIN_1
#define D5 				 GPIO_PIN_2
#define D6				 GPIO_PIN_3
#define D7 				 GPIO_PIN_4
#define CLKSPEED		 80000000

void initLCD();
void LCDCommand(unsigned char);
void LCDWrite(unsigned char);
void LCDWriteText(char*);

#endif /* LCD44780_LP_H_ */
