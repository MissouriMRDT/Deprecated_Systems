/*
 * lts_talker.h
 *
 * Created: 4/14/2015 1:33:14 AM
 *  Author: Spencer Vogel
 */ 


#ifndef LTC_TALKER_H
#define LTC_TALKER_H

#include "bms_defines.h"

#define	STCVAD_PEC			0xB0
#define WRCFG_PEC			0xC7
#define RDCV_PEC			0xDC
// LTC6802-2 Command Codes

#define WRCFG  0x01  // Write Configuration Registers
#define RDCFG  0x02  // Read Configuration
#define RDCV   0x04  // Read Cell Voltages without discharge

#define RDFLG  0x06  // Read Flags
#define RDTMP  0x08  // Read Temps

#define STCVAD 0x10  // Start all A/D's - Poll Status
#define STCVDC 0x60  // A/D Conversions and Poll Status, with Discharge Permitted
#define STOWAD 0x20  // Start testing all open wire - poll status
#define STTMPAD 0x30 // Start temperature A/D's - Poll Status

#define CFGR0 0b01111111
#define CFGR1 0x00 //0bXXXXXXXX
#define CFGR2 0x00 //0bXXXXXXXX
#define CFGR3 0bXXXXXXXX
#define CFGR4 0bXXXXXXXX
#define CFGR5 0bXXXXXXXX

void getLtsResponse();
void decodeVoltage();
void ltc6803PEC(uint8_t val);

#endif /* LTC_TALKER_H */