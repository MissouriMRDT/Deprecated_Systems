/*
 * json.h
 *
 *  Created on: May 11, 2014
 *      Author: Keenan
 */

#ifndef JSON_H_
#define JSON_H_

#include <stdlib.h>
#include <string.h>
#include <ti/drivers/UART.h>
#include <xdc/runtime/System.h>

// Reverses a string
 void reverse(char s[]);

 // Converts int to string
 void itoa(int n, char s[]);

// Generates a json string to
// send to the base station
// works with integer values
 void generate_json_int(char *string_buf, const char *id, const int value);

// Generates a json string to
// send to the base station
// works with strings
void generate_json_strings(char *string_buf, const char *id, const char *value);

// Generates a json string to
// send to base station
// for gps (lat & long) data
void generate_gps_json(char *string_buf, const char *id, const int whole_number, const int frac_number, const uint8_t direction);

// Generates a json string to
// send to base station
// for altitude data
void generate_altitude_json(char *string_buf, const char *id, const int whole_number, const int frac_number);

 // Writes json string out a given uart
 void write_json(UART_Handle uart, char *json_string);

#endif /* JSON_H_ */
