//	TODO: Port To Fresh Build (using TI example:			This version educational practice not for distro)

// roveJson.c
//
// first created:
//
// 04_20_2015_Keenan_Johnson
//
// last edited:
//
//02_25_2015_Judah_Schad_jrs6w7@mst.edu

#include "../roveWareHeaders/roveJson.h"

//TODO

//reverse:  reverse string s in place

void reverse(char s[]) {

	int i, j;
	char c;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {

		c = s[i];
		s[i] = s[j];
		s[j] = c;

	} //endfor:		(i = 0, j = strlen(s)-1; i<j; i++, j--)

} //endfnctn:		reverse(char s[]

//TODO

//itoa:  convert n to characters in s

void itoa(int n, char s[]) {

	int i, sign;

	//record sign and make n positive

	if ((sign = n) < 0)

		n = -n;
	i = 0;

	//generate digits in reverse order

	do {

		//get next digit

		s[i++] = n % 10 + '0';

		// delete it

	} while ((n /= 10) > 0);

	if (sign < 0)

		s[i++] = '-';
	s[i] = '\0';

	reverse(s);

} //endfnctn:		itoa(int n, char s[])

//TODO

void generate_json_int(char *string_buf, const char *id, const int value) {

	//add beginning of json

	strcpy(string_buf, "{'Id':");

	//add id

	strcat(string_buf, id);
	strcat(string_buf, ",'Value':");

	//convert value to string and add it

	char value_buf[10];
	itoa(value, value_buf);
	strcat(string_buf, value_buf);

	//add ending closing brace

	strcat(string_buf, "}");

} //endfnctn:			generate_json_int(char *string_buf, const char *id, const int value

//TODO

void generate_json_strings(char *string_buf, const char *id, const char *value) {

	//add beginning of json

	strcpy(string_buf, "{'Id':");

	//add id

	strcat(string_buf, id);
	strcat(string_buf, ",'Value':'");

	//add string to value

	strcat(string_buf, value);

	//add ending closing brace

	strcat(string_buf, "'}");

} //endfnctn:		 generate_json_strings(char *string_buf, const char *id, const char *value)

//TODO

void generate_json_float(char *string_buf, const char *id, const float value) {

	//add beginning of json

	strcpy(string_buf, "{'Id':");

	//add id

	strcat(string_buf, id);
	strcat(string_buf, ",'Value':");

	//convert float to string

	int whole_value;
	int fractional_value;

	whole_value = value;
	fractional_value = (whole_value - value) * 1000;

	//add whole value

	char whole_value_buf[10];
	itoa(whole_value, whole_value_buf);
	strcat(string_buf, whole_value_buf);

	//add dot

	strcat(string_buf, ".");

	//add fractional value

	char frac_value_buf[10];
	itoa(fractional_value, frac_value_buf);
	strcat(string_buf, frac_value_buf);

	//add ending closing brace

	strcat(string_buf, "}");

} //endfnctn:		generate_json_float(char *string_buf, const char *id, const float value

//TODO

void generate_gps_json(char *string_buf, const char *id, const int whole_number,
		const int frac_number, const uint8_t direction) {

	//add beginning of json

	strcpy(string_buf, "{'Id':");

	//add id

	strcat(string_buf, id);
	strcat(string_buf, ",'Value':'");

	//add whole value

	char whole_value_buf[10];
	itoa(whole_number, whole_value_buf);
	strcat(string_buf, whole_value_buf);

	//add dot

	strcat(string_buf, ".");

	//add fractional value

	char frac_value_buf[10];
	itoa(frac_number, frac_value_buf);
	strcat(string_buf, frac_value_buf);

	char direction_buf[2];
	direction_buf[0] = direction;
	direction_buf[1] = 0;

	//add direction character

	strcat(string_buf, direction_buf);

	//add ending closing brace

	strcat(string_buf, "'}");

} //endfnctn:		generate_gps_json(char *string_buf, const char *id, const int whole_number, const int frac_number, const uint8_t direction)

//TODO

void generate_altitude_json(char *string_buf, const char *id,
		const int whole_number, const int frac_number) {

	//add beginning of json

	strcpy(string_buf, "{'Id':");

	//add id

	strcat(string_buf, id);
	strcat(string_buf, ",'Value':'");

	//add whole value

	char whole_value_buf[10];
	itoa(whole_number, whole_value_buf);
	strcat(string_buf, whole_value_buf);

	//add dot

	strcat(string_buf, ".");

	//add fractional value

	char frac_value_buf[10];
	itoa(frac_number, frac_value_buf);
	strcat(string_buf, frac_value_buf);

	//add ending closing brace

	strcat(string_buf, "'}");

} //endfnctn:		generate_altitude_json(char *string_buf, const char *id, const int whole_number, const int frac_number)

//TODO

void write_json(UART_Handle uart, char *json_string) {

	//get size of JSON string

	int size = strlen(json_string);

	//write data out UART

	UART_write(uart, json_string, size + 1);

} //endfnct:		write_json(UART_Handle uart, char *json_string
