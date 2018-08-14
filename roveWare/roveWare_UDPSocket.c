// Missouri Science and Technology Mars Rover Design Team 2015
//
// Judah Schad jrs6w7@mst.edu
//
// recieves base station commands using ip bsd UDP style sockets
//
// mrdt::rovWare

//TODO on URC 2016 OCTOBER_DEVELOPEMENT Protocol

#include "roveWare_UDPSocket.h"

// initialize and config a udp listening port
int rovecommInit(uint32_t port, rove_udp_socket* rove_socket) {

    rove_socket->error_code = ERROR_FREE;

    rove_socket->socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (rove_socket->socket_fd < SUCCESS) {

        printf("Failed socket() with socket_fd: %d \n\n" , rove_socket->socket_fd);
        roveCatch_NdkErrors( fdError() );
        return ERROR;

    }//endif

    memset(&rove_socket->local_addr, 0, sizeof(struct sockaddr_in));
    rove_socket->local_addr.sin_family = AF_INET;
    rove_socket->local_addr.sin_port = htons(port);

    //TODO
    inet_pton(AF_INET, LOCAL_IP_ADDRESS, &(rove_socket->local_addr.sin_addr));

    if ( bind(rove_socket->socket_fd, (PSA) &(rove_socket->local_addr), sizeof(struct sockaddr_in) ) < 0) {

        printf("Failed bind() with socket_fd: %d \n\n" , rove_socket->socket_fd);
        roveCatch_NdkErrors( fdError() );
        return ERROR;

    } else {

        return SUCCESS;

     }//endif

 }//endfnctn

uint16_t getUdpMsg(uint16_t* data_id, uint16_t* data_byte_cnt, rove_udp_socket* rove_socket) {

    //temporary buffer to include header
    uint8_t recv_buffer[MAX_DATA_BYTE_CNT + HEADER_BYTE_COUNT];

    //TODO (PSA) &(rove_udp_socket->local_server_addr)
    *data_byte_cnt = recvfrom(rove_socket->socket_fd , recv_buffer, MAX_DATA_BYTE_CNT, DEFAULT_FLAG , (struct sockaddr *) &(rove_socket->remote_addr), (socklen_t*) &(rove_socket->remote_addr_length) );

    //TODO
    if (*data_byte_cnt < 1) {

        printf("Failed bind() with socket_fd: %d \n\n", rove_socket->socket_fd);
        roveCatch_NdkErrors( fdError() );
        return ZERO_BYTES;

    }//endif

    parseUdpMsg(recv_buffer, data_id, data_byte_cnt, rove_socket);

    return *data_byte_cnt;

}//end fnctn rovecommInit

//remove header bytes and populate rovecomm control bytes, fill rove_socket->data_buffer buffer with data payload
void parseUdpMsg(uint8_t* recv_buffer, uint16_t* data_id, uint16_t* data_byte_cnt, rove_udp_socket* rove_socket){

    uint8_t proto_version = recv_buffer[0];

    //handle the protocol versioning
    if (proto_version == 1) {

        uint8_t data_id_high_byte = recv_buffer[3];

        *data_id = data_id_high_byte;
        *data_id = (*data_id << 8) | recv_buffer[4];

        uint8_t byte_count_high = recv_buffer[5];

        *data_byte_cnt = byte_count_high;
        *data_byte_cnt = (*data_byte_cnt << 8) | recv_buffer[6];

        int packet_byte_count = 0;
        while( packet_byte_count < (*data_byte_cnt) ) {

            rove_socket->data_buffer[packet_byte_count] = recv_buffer[ packet_byte_count + HEADER_BYTE_COUNT];

            packet_byte_count++;

        }//endwhile

    }//endif

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

void rovePrintf_IPMessage(rove_udp_socket* rove_socket) {

    switch(rove_socket->data_id){

    case motor_drive_right_id:
        printf("Rover Drive Right : struct_id %d : speed %d\n",rove_socket->data_id, (*((int*)rove_socket->data_buffer)) );
        break;

    case motor_drive_left_id:
        printf("Rover Drive Left : struct_id %d : speed %d\n",rove_socket->data_id, (*((int*)rove_socket->data_buffer)) );
        break;

    default:
        printf("Unknown Command Error");
        break;

    }//endswitch

        return;

}//endfnctn rovePrintf_RoveStructs


/*
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




//TODO


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


When you call recv(), it will block until there is some data to
read. If you want to not block, set the socket to non-blocking
or check with select() or poll() to see if there is incoming data
before calling recv() or recvfrom().

int main(void)
{
  // Create a UDP Socket
  int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

  struct sockaddr_in sa;

  char buffer[1024];

  ssize_t recsize, sendsize;

  socklen_t fromlen;

  memset(&sa, 0, sizeof sa);

  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = htonl(INADDR_ANY);

  sa.sin_port = htons(11000);

  fromlen = sizeof(sa);

  if (-1 == bind(sock, (struct sockaddr *)&sa, sizeof sa)) {
    perror("error bind failed");
    close(sock);
    exit(EXIT_FAILURE);
  }

  for (;;) {

    recsize = recvfrom(sock, (void*)buffer, sizeof buffer, 0, (struct sockaddr*)&sa, &fromlen);

    if (recsize < 0) {
      fprintf(stderr, "%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }


    int i = 0;
    for (i=0; i<recsize; i++){
      printf("%X ", (uint8_t)buffer[i]);
    }

    printf("\n");

    printf("recsize: %d\n", (int)recsize);

    sa.sin_port = htons(11000);

    sendsize = sendto(sock, buffer, recsize, 0, (struct sockaddr*)&sa, sizeof(sa));

    printf("Sent %d bytes\n", (int)sendsize);

    sleep(1);
  }
}
*/
