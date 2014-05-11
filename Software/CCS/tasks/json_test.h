/*
 * tcp_task.h
 *
 */

#ifndef JSON_TEST_H_
#define JSON_TEST_H_

#include "../include/json.h"

extern Void json_test(UArg arg0, UArg arg1)
{
	System_printf("Starting json check");
	System_flush();

	char buf[75];
	char id[5] = "3022";


	while(1)
	{
		generate_json_int(buf, id, 14);
		System_printf("JSON: %s", buf);
		System_flush();
	}
}

#endif /* JSON_TEST_H_ */
