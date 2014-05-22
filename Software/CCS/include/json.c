/*
 * json.c
 *
 *  Created on: May 11, 2014
 *      Author: Keenan
 */

#include "json.h"

/* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

 /* itoa:  convert n to characters in s */
  void itoa(int n, char s[])
  {
      int i, sign;

      if ((sign = n) < 0)  /* record sign */
          n = -n;          /* make n positive */
      i = 0;
      do {       /* generate digits in reverse order */
          s[i++] = n % 10 + '0';   /* get next digit */
      } while ((n /= 10) > 0);     /* delete it */
      if (sign < 0)
          s[i++] = '-';
      s[i] = '\0';
      reverse(s);
  }

 void generate_json_int(char *string_buf, const char *id, const int value)
 {
	 // Add beginning of json
	 strcpy(string_buf, "{'Id':");

	// Add id
	strcat(string_buf, id);
	strcat(string_buf, ",'Value':");

	// Convert value to string
	// and add it
	char value_buf[10];
	itoa(value, value_buf);
	strcat(string_buf, value_buf);

	// Add ending closing brace
	strcat(string_buf, "}");
 }

void generate_json_float(char *string_buf, const char *id, const float value)
{
	 // Add beginning of json
	 strcpy(string_buf, "{'Id':");

	// Add id
	strcat(string_buf, id);
	strcat(string_buf, ",'Value':");

	/*
	// Convert value to string
	// and add it
	char value_buf[15];
	// convert float to string
	System_sprinf();
	strcat(string_buf, value_buf);
	*/

	// Add ending closing brace
	strcat(string_buf, "}");
}

void write_json(UART_Handle uart, char *json_string)
{
	// Get size of JSON string
	int size = strlen(json_string);

	// Write data out UART
	UART_write(uart, json_string, size+1);

}
