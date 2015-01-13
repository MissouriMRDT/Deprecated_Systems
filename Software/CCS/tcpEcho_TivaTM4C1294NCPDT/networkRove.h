/*
 * networkRove.h
 *
 *  Created on: Jan 12, 2015
 *      Author: Owen, Judah and Ghost of Zeus
 */

#ifndef NETWORKROVE_H_
#define NETWORKROVE_H_

//const UINT32 RED_IP_ADDR = inet_addr("192.168.1..tbd....");
const short ROVE_LISTEN_PORT = 4500;
const int MAX_PACKET_SIZE = 1024;
const int RECV_BUFFER_SIZE = 1024;
//max size of connection request queue to hold pending conn rqst
const int MAXCONN = 3;

Void networkFncRove(UArg arg0, UArg arg1);

#endif /* NETWORKROVE_H_ */
