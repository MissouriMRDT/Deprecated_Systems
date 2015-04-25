//
// roveTcpSendTester.h
//
//  Created on: Apr 25, 2015
//  Author: judah_schad
//

#ifndef ROVETCPSENDTESTER_H_
#define ROVETCPSENDTESTER_H_

// globally scoped Texas Instruments (TI) headers

#include "../RoverMotherboardMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../mrdtRoveWare.h"

// when data is recieved it comes from fromBaseStationMailbox as RoveNet recieve struct base_station_msg_struct

// when data is sent it goes into the TODO

Void roveTcpSendTester(UArg arg0, UArg arg1);

#endif /* ROVETCPSENDTESTER_H_ */
