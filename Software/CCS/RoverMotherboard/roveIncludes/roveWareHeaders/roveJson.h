// roveJson.h MST MRDT 2015
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad jrs6w7@mst.edu

#pragma once

#ifndef ROVEJSON_H_
#define ROVEJSON_H_

//globally scoped Texas Instruments (TI) headers

#include "../RoverMotherboardMain.h"

//MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../mrdtRoveWare.h"

//reverses a string

void reverse(char s[]);

//converts int to string

void itoa(int n, char s[]);

//generates a json string to send to the base station works with integer values

void generate_json_int(char *string_buf, const char *id, const int value);

//generates a json string to send to the base station works with strings

void generate_json_strings(char *string_buf, const char *id, const char *value);

//generates a json string to send to the base station works with floats

void generate_json_float(char *string_buf, const char *id, const float value);

//generates a json string to send to base station for gps (lat & long) data

void generate_gps_json(char *string_buf, const char *id, const int whole_number,
        const int frac_number, const uint8_t direction);

//generates a json string to send to base station for altitude data

void generate_altitude_json(char *string_buf, const char *id,
        const int whole_number, const int frac_number);

//writes json string out a given uart

void write_json(UART_Handle uart, char *json_string);

#endif // ROVESJON_H_
