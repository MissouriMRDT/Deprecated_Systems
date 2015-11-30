// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// recieves base station commands using ip bsd UDP style sockets
//
// mrdt::rovWare

//TODO on URC 2016 OCTOBER_DEVELOPEMENT Protocol
#include "roveComm.h"

// initialize and config a udp listening port
int32_t roveComm_Init(rove_udp_socket* rove_socket) {

    //TODO Comment BSD CONFIG
    rove_socket->socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (rove_socket->socket_fd < COMMS_ERROR_FREE) {
        return rovePrintf_Errno( fdError() );
    }//endif

    memset(&rove_socket->local_addr, 0, sizeof(struct sockaddr_in));
    rove_socket->local_addr.sin_family = AF_INET;
    rove_socket->local_addr.sin_port = htons(COMMS_PORT_11000);
    rove_socket->local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ( bind(rove_socket->socket_fd, (PSA) &(rove_socket->local_addr), sizeof(struct sockaddr_in) ) < 0) {
        return rovePrintf_Errno( fdError() );
    }//endif
    return COMMS_ERROR_FREE;
}//endfnctn roveComm_Init

int32_t roveGet_UdpMsg(rove_protocol* rove_data, rove_udp_socket* rove_socket) {

    //TODO (PSA) &(rove_udp_socket->local_server_addr)
    rove_data->data_byte_cnt = recvfrom(rove_socket->socket_fd , rove_data->data_buffer, COMMS_MAX_BUFF_BYTE_CNT, COMMS_NDK_DEFAULTS_FLAG , (struct sockaddr *) &(rove_socket->remote_addr), (socklen_t*) &(rove_socket->remote_addr_length) );

    //TODO
    if (rove_data->data_byte_cnt < COMMS_SINGLE_BYTE) {
        return rovePrintf_Errno( fdError() );
    }//endif

    roveParse_UdpMsg(rove_data, rove_socket);
    return rove_data->data_id;
}//end fnctn rovecommInit

//remove header bytes and populate rovecomm control bytes, fill rove_socket->data_buffer with the command data payload
int32_t roveParse_UdpMsg(rove_protocol* rove_data, rove_udp_socket* rove_socket) {

    //handle the protocol versioning
    switch(rove_data->data_buffer[0]) {

        case COMMS_VERSION_ONE:

            //TODO int32_t ??
            rove_data->data_id  = rove_data->data_buffer[3];
            rove_data->data_id = (rove_data->data_id << 8) | rove_data->data_buffer[4];
            rove_data->data_byte_cnt = rove_data->data_buffer[5];
            rove_data->data_byte_cnt = (rove_data->data_byte_cnt << 8) | rove_data->data_buffer[6];
            return rove_data->data_id;
        //TODO errno PARSE_ERROR
        default:
            printf("roveParse_UdpMsg unknown error \n\n");
            return COMMS_PARSE_UDP_ERRNO;
    }//switch
}//endfnctn parseUdpMsg










//TODO UglyDev hack
int32_t rovePrintf_Errno(int32_t ndk_error) {

    switch(ndk_error) {

        case ENOMEM:
            printf("NDK cannot allocate memory ENOMEM %d\n\n", ndk_error);
            return ENOMEM;

        case ETIMEDOUT:
            printf("NDK operation timed out ETIMEDOUT %d\n\n", ndk_error);
            return ETIMEDOUT;

        case ECONNREFUSED:
            printf("NDK connection refused ECONNREFUSED %d\n\n", ndk_error);
            return ECONNREFUSED;

        case EHOSTDOWN:
            printf("NDK connection refused EHOSTDOWN %d\n\n", ndk_error);
            return EHOSTDOWN;

        default:
            //TODO printf Errno Error? That's so Meta
            printf("NDK unknown error %d\n\n", ndk_error);
            return COMMS_PRINTF_NDK_ERRNO;
    } //endswitch
}//endfnctn rovePrintf_Errno

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


////////////////////////////////////////////////////////////////////////Judah Debugging ONLY:

void rovePrintf_Protocol(rove_udp_socket* rove_socket) {

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
}//endfnctn rovePrintf_IPMessage

//RoveComm::RoveComm(){


//};//end construction

//RoveComm::~RoveComm(){

//};//end destruction

//RoveComm private functions
int16_t RoveComm::roveComm_Init(rove_udp_socket* rove_socket){
    return rovePrintf_Errno( fdError() );
}//end fnctn

int16_t RoveComm::roveGet_UdpMsg(rove_protocol* rove_data, rove_udp_socket* rove_socket){
    return rovePrintf_Errno( fdError() );
}//end fnctn

int16_t RoveComm:: roveParse_UdpMsg(rove_protocol* rove_data, rove_udp_socket* rove_socket){
    return rovePrintf_Errno( fdError() );
}//end fnctn

int16_t RoveComm::begin(){
    return rovePrintf_Errno( fdError() );
}//end fnctn

int16_t RoveComm:: read(){
    return rovePrintf_Errno( fdError() );
}//end fnctn

int16_t RoveComm:: write(){
    return rovePrintf_Errno( fdError() );
}//end fnctn*/
