// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// roveWare_UDPSocket.c
//
// jrs6w7@mst.edu
//
// recieves base station commands using ip bsd UDP style sockets
//
// mrdt::rovWare

//TODO on URC 2016 OCTOBER_DEVELOPEMENT Protocol

#include "roveWare_UDPSocket.h"

// initialize and config a udp listening port
void rovecommInit(rove_udp_socket* rove_socket) {

    rove_socket->socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (rove_socket->socket_fd < SUCCESS) {

        printf("Failed socket() with socket_fd: %d \n\n" , rove_socket->socket_fd);
        roveCatch_NdkErrors( fdError() );
        return;

    }//endif

    //TODO VALIDATE CONFIG
        memset(&rove_socket->local_addr, 0, sizeof(struct sockaddr_in));
        rove_socket->local_addr.sin_family = AF_INET;
        rove_socket->local_addr.sin_port = htons(LISTEN_PORT);
        rove_socket->local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        //rove_socket->local_addr.sin_addr = SOME_BYTES

    if ( bind(rove_socket->socket_fd, (PSA) &(rove_socket->local_addr), sizeof(struct sockaddr_in) ) < 0) {

        printf("Failed bind() with socket_fd: %d \n\n" , rove_socket->socket_fd);
        roveCatch_NdkErrors( fdError() );

    }//endif

    return;

 }//endfnctn

uint16_t getUdpMsg(uint16_t* data_id, uint16_t* data_byte_cnt, rove_udp_socket* rove_socket) {

    //temporary work buffer to include header parsing
    uint8_t recv_buffer[MAX_DATA_BYTE_CNT + HEADER_BYTE_COUNT];

    //TODO (PSA) &(rove_udp_socket->local_server_addr)
    *data_byte_cnt = recvfrom(rove_socket->socket_fd , recv_buffer, MAX_DATA_BYTE_CNT, DEFAULT_FLAG , (struct sockaddr *) &(rove_socket->remote_addr), (socklen_t*) &(rove_socket->remote_addr_length) );

    //TODO
    if (*data_byte_cnt < 1) {

        printf("Failed recvfrom() with socket_fd: %d data_byte_cnt: %d\n\n", rove_socket->socket_fd, *data_byte_cnt);
        roveCatch_NdkErrors( fdError() );
        return ZERO_BYTES;

    }//endif

    parseUdpMsg(recv_buffer, data_id, data_byte_cnt, rove_socket);

    return *data_byte_cnt;

}//end fnctn rovecommInit

//remove header bytes and populate rovecomm control bytes, fill rove_socket->data_buffer with the command data payload
void parseUdpMsg(uint8_t* recv_buffer, uint16_t* data_id, uint16_t* data_byte_cnt, rove_udp_socket* rove_socket) {

    uint8_t proto_version = recv_buffer[0];

    //handle the protocol versioning
    if(proto_version == VERSION_ONE) {

        uint8_t data_id_high_byte = recv_buffer[3];

        *data_id = data_id_high_byte;
        *data_id = (*data_id << 8) | recv_buffer[4];

        uint8_t byte_count_high = recv_buffer[5];

        *data_byte_cnt = byte_count_high;
        *data_byte_cnt = (*data_byte_cnt << 8) | recv_buffer[6];

        int packet_byte_count = 0;

        while( packet_byte_count < (*data_byte_cnt) ) {

            rove_socket->data_buffer[packet_byte_count] = recv_buffer[packet_byte_count + HEADER_BYTE_COUNT];

            packet_byte_count++;

        }//endwhile

    }//endif

    return;

}//endfnctn parseUdpMsg

void roveCatch_NdkErrors(int16_t ndk_error) {

    switch(ndk_error) {

        case ENOMEM:
            printf("NDK cannot allocate memory ENOMEM %d\n\n", ndk_error);
            break;

        case ETIMEDOUT:
            printf("NDK operation timed out ETIMEDOUT %d\n\n", ndk_error);
            break;

        case ECONNREFUSED:
            printf("NDK connection refused ECONNREFUSED %d\n\n", ndk_error);
            break;

        case EHOSTDOWN:
            printf("NDK connection refused EHOSTDOWN %d\n\n", ndk_error);
            break;

        default:
            printf("NDK unknown error %d\n\n", ndk_error);
            break;

    } //endswitch

    return;

}//endfnctn roveCatch_NdkErrors

//HORIZON command CONFIG protocol
#define DRIVE_RIGHT_MOTORS 100
#define DRIVE_LEFT_MOTORS 101

//Left Over from Horizon protocol//positive is clockwise, negative is counterclockwise
#define WRIST_ROTATE 201
#define WRIST_VERTICAL 202
#define ELBOW_ROTATE 203
#define ELBOW_VERTICAL 204
#define BASE_ROTATE 205
#define E_STOP_ARM 206
#define ACTUATOR_INCREMENT 207
#define GRIPPER_OPEN 208


void rovePrintf_IPMessage(rove_udp_socket* rove_socket) {

    switch(rove_socket->data_id){

        case DRIVE_RIGHT_MOTORS:
            printf("Rover drive right : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
            break;

        case DRIVE_LEFT_MOTORS:
            printf("Rover drive left : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
            break;

        case WRIST_ROTATE:
            printf("Rover wrist rotate : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
            break;

        case WRIST_VERTICAL:
            printf("Rover wrist vertical : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
            break;

        case ELBOW_ROTATE:
            printf("Rover elbow rotate : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
            break;

        case ELBOW_VERTICAL:
           printf("Rover elbow vertical : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
           break;

        case BASE_ROTATE:
           printf("Rover base rotate : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
           break;

        case E_STOP_ARM:
           printf("Rover e stop arm : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
           break;

        case ACTUATOR_INCREMENT:
           printf("Rover actuator increment : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
           break;

        case GRIPPER_OPEN:
           printf("Rover gripper open : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
           break;

        default:
            printf("Unknown Command Error\n");
            break;

    }//endswitch

    return;

}//endfnctn rovePrintf_RoveStructs


//TODO
/*
    if (*dataID < 0x65) {
      Serial.print("RoveComm function received with dataID: ");
      Serial.println(*dataID, HEX);
      if (rovecommSubscribers[0] == INADDR_NONE) { //if this is running during rovecommInit();
        rovecommControl(dataID, size, data, remote_ip, remote_port);
      } else {
       rovecommControl(dataID, size, data, remote_ip, remote_port);
        getUdpMsg(dataID, size, data);
      }
    }
    Serial.println();
  }
}

void rovecommControl(uint16_t* data_id, uint16_t* data_byte_count, uint32_t remote_ip_address, int remote_port, rove_udp_socket* rove_udp_socket,) {

  switch (*data_id) {
    case ADD_SUBSCRIBER:
        rovecommAddSubscribers(rove_udp_socket->subscribers[0].remote_ip_addr);
        return;
    default:
        printf("Failed rovecommControl remote_ip_addr: %d \n\n" , rove_udp_socket->subscribers[0].remote_ip_addr);
       return;
  }//endswitch
}//endfnctn rovecommControl

int rovecommAddSubscribers(char* remote_ip_address, rove_udp_socket* rove_udp_socket) {

  int added_subscribers_count = 0;
  while(added_subscribers_count < MAX_SUBSCRIBER_CNT
          && !(rove_udp_socket->subscribers[added_subscribers_count] == INADDR_NONE
                  || rove_udp_socket->subscribers[added_subscribers_count] == remote_ip_address)) {
      added_subscribers_count++;
  }//endwhile

  //handle exceed the subscribers array
  if (added_subscribers_count == MAX_SUBSCRIBER_CNT) {
    printf("Subscriber failed");
    return false;
  }//endif
  rove_udp_socket->subscribers[added_subscribers_count] == remote_ip_address;
  printf("Subscriber added");
  return true;
}//end fnctn rovecommAddSubscriber
*/
