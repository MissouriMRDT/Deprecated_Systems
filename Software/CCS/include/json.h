/*
 * json.h
 *
 *  Created on: May 11, 2014
 *      Author: Keenan
 */

#ifndef JSON_H_
#define JSON_H_

// Reverses a string
 void reverse(char s[]);

 // Converts int to string
 void itoa(int n, char s[]);

// Generates a json string to
// send to the base station
// works with integer values
 void generate_json_int(char *string_buf, const char *id, const int value);

#endif /* JSON_H_ */
