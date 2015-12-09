// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// recieves base station commands using ip bsd UDP style sockets
//
// mrdt::rovWare

//TODO on URC 2016 OCTOBER_DEVELOPEMENT Protocol
#include "roveComm.h"


//Judah Dev16 Shorthand
//TODO Judah factor MRDT shorthand
typedef enum RoveCommShortHand {

    COMMS_ZERO_BYTES = 0
    , COMMS_SINGLE_BYTE = 1
    , COMMS_NDK_DEFAULTS_FLAG = 0

} RoveCommShortHand;

typedef enum RoveCommErrNo {

    COMMS_ERROR_FREE = 0

    //ndk itself has a positive errno = fdError()
    , COMMS_SOCKET_ERROR = -1

    //rovecomm itself has error
    , UNCAUGHT_NDK_ERRNO = 1
    , NO_RECV_BYTES = 2
    , NO_DATA_BYTES = 3
    , COMMS_PARSE_UDP_ERRNO = 4
    , COMMS_CATCH_ROVE_ERRNO = 5
    , COMMS_CATCH_NDK_ERRNO = 6

} RoveCommErrNo;



//TI socketndk functions return negative error
//to be clear this is not the same as = fdError() socket state lookup which only returns positive error defs
//TODO?? used by socket() and accept() :       INVALID_SOCKET (void *)0xFFFFFFFF
//#define COMMS_INVALID_SOCKET -1
//used by all other ti ndk functions:   SOCKET_ERROR   -1



//TODO Judah int32_t roveComm_UdpInit(rovecomm_socket* rove_socket, struct in_addr *local_device_ip,  unsigned short local_port){
//TODO Judah int32_t roveComm_TcpClientInit(rovecomm_socket* rove_socket, struct in_addr *local_device_ip,  unsigned short local_port){
//TODO Judah int32_t roveComm_TcpServertInit(rovecomm_socket* rove_socket, struct in_addr *local_device_ip,  unsigned short local_port){



///////////////::BEGIN//////RoveComm Private Functions//////////////
int32_t roveComm_ParseUdpMSG(rovecomm_protocol* rove_data);
int32_t roveComm_CatchRoveERRNO(int32_t rove_errno);
int32_t roveComm_CatchNdkERRNO(int32_t ndk_errno);



///////////////::BEGIN//////RoveComm Implementation//////////////

//initialize and config a udp listening port
int32_t roveComm_InitUdpCFG(rovecomm_socket* rove_socket, unsigned short local_port){

    rove_socket->ndk_fd_error = COMMS_ERROR_FREE;

    //construct a bsd udp ip datagram socket
    rove_socket->socket_fd =

        socket(

            AF_INET
            , SOCK_DGRAM
            , IPPROTO_UDP);

    if (rove_socket->socket_fd == COMMS_SOCKET_ERROR) {

        rove_socket->ndk_fd_error = fdError();
        return roveComm_CatchNdkERRNO(rove_socket->ndk_fd_error);
    }//endif

    memset(&(rove_socket->local_ip->sin_addr), 0, sizeof(struct in_addr));
    rove_socket->local_ip->sin_port = htons(local_port);

    rove_socket->local_ip->sin_family = AF_INET;
    rove_socket->local_ip->sin_addr.s_addr = htonl(INADDR_ANY);

    //bind the socket address
    rove_socket->ndk_fd_error =

        bind(

            rove_socket->socket_fd

            , (struct sockaddr*)&(rove_socket->local_ip->sin_addr)
            , sizeof(struct sockaddr_in));

    //TODO Rovecomm Error Bubbles are negative numbers in this model -1, -2,
    if (rove_socket->ndk_fd_error == COMMS_SOCKET_ERROR) {

        rove_socket->ndk_fd_error = fdError();
        return roveComm_CatchNdkERRNO(rove_socket->ndk_fd_error);
    }//endif

    return COMMS_ERROR_FREE;
}//endfnctn



int32_t roveComm_GetUdpMSG(rovecomm_socket* rove_socket, rovecomm_protocol* rove_data){

    rove_data->data_id = 0;
    rove_data->data_byte_cnt = 0;
    memset(&(rove_data->data_buffer), 0, COMMS_MAX_BUFF_BYTE_CNT);

    //default udp recvfrom gets data in a buffer along with the senders address
    rove_data->recv_byte_cnt =

        recvfrom(

            rove_socket->socket_fd
            , rove_data->data_buffer

            , COMMS_NDK_DEFAULTS_FLAG
            , COMMS_MAX_BUFF_BYTE_CNT
            //TODO subscribers[0]
            , (struct sockaddr*)&(rove_socket->rovecomm_ip_subscribers[0]->sin_addr )
            , (socklen_t*) &(rove_socket->rovecomm_ip_subscribers[0]->addr_len));

    if (rove_data->recv_byte_cnt == 0) {

        rove_data->data_error = NO_RECV_BYTES;
        return roveComm_CatchRoveERRNO(rove_data->data_error);
    }//end if

    if (rove_data->recv_byte_cnt) {

        rove_data->data_byte_cnt = roveComm_ParseUdpMSG(rove_data);

        if (rove_data->data_byte_cnt == 0) {

            rove_data->data_error = NO_DATA_BYTES;
            return roveComm_CatchRoveERRNO(rove_data->data_error);
        }//end if

        if (rove_data->data_byte_cnt) {

           return rove_data->data_id;
        }//end if
    }//end if

    //rove_data->recv_byte_cnt was negative therefore rrcvfrm ndk error
    rove_socket->ndk_fd_error = fdError();
    return roveComm_CatchNdkERRNO( rove_socket->ndk_fd_error);
}//end fnctn



//remove header bytes and populate rovecomm control bytes, fill rove_socket->data_buffer with the command data payload
int32_t roveComm_ParseUdpMSG(rovecomm_protocol* rove_data){

    //handle the protocol versioning
    switch(rove_data->data_buffer[0]) {

        case COMMS_VERSION_ONE:

            //TODO int32_t ??
            rove_data->data_id  = rove_data->data_buffer[3];
            rove_data->data_id = (rove_data->data_id << 8) | rove_data->data_buffer[4];

            rove_data->data_byte_cnt = rove_data->data_buffer[5];
            rove_data->data_byte_cnt = (rove_data->data_byte_cnt << 8) | rove_data->data_buffer[6];

            //returns count of the parsed data bytes recieved
            return rove_data->data_byte_cnt;

//TODO errno PARSE_ERROR
        default:
            printf("roveParse_UdpMsg unknown error \n\n");
            rove_data->data_error = COMMS_PARSE_UDP_ERRNO;
            return rove_data->data_error;
    }//switch
}//endfnctn


//TODO Reed Advice? JUDAH: Eliminate Switch
int32_t roveComm_CatchRoveERRNO(int32_t rove_errno) {

    if(rove_errno == COMMS_SOCKET_ERROR){

        printf("NDK error in roveComm_CatchERRNO UNCAUGHT_NDK_ERRNO : %d\n\n", rove_errno);
        return UNCAUGHT_NDK_ERRNO;
    }//endif

    switch(rove_errno) {

        case NO_RECV_BYTES:
            printf("roveComm_CatchRoveERRNO NO_RECV_BYTES : %d\n\n", rove_errno);
            return NO_RECV_BYTES;

        case NO_DATA_BYTES:
            printf("roveComm_CatchRoveERRNO NO_DATA_BYTES : %d\n\n", rove_errno);
            return NO_DATA_BYTES;

        case COMMS_PARSE_UDP_ERRNO:
            printf("roveComm_CatchRoveERRNO COMMS_PARSE_UDP_ERRNO : %d\n\n", rove_errno);
            return COMMS_PARSE_UDP_ERRNO;

        default:
            //TODO printf Errno Error? That's so Meta
            printf("roveComm_CatchRoveERRNO unknown error in COMMS_PRINTF_NDK_ERRNO : %d\n\n", rove_errno);
            return COMMS_CATCH_ROVE_ERRNO;
    } //endswitch
}//endfnctn

//TODO Reed Advice? JUDAH: Eliminate Switch
int32_t roveComm_CatchNdkERRNO(int32_t ndk_errno) {

    switch(ndk_errno) {

        case ENOMEM:
            printf("NDK cannot allocate memory ENOMEM : %d\n\n", ndk_errno);
            return ENOMEM;

        case ETIMEDOUT:
            printf("NDK operation timed out ETIMEDOUT : %d\n\n", ndk_errno);
            return ETIMEDOUT;

        case ECONNREFUSED:
            printf("NDK connection refused ECONNREFUSED : %d\n\n", ndk_errno);
            return ECONNREFUSED;

        case EHOSTDOWN:
            printf("NDK connection refused EHOSTDOWN : %d\n\n", ndk_errno);
            return EHOSTDOWN;

        default:
            //TODO printf Errno Error? That's so Meta
            printf("NDK unknown error in roveComm_CatchNdkERRNO  : %d\n\n", ndk_errno);
            return COMMS_CATCH_NDK_ERRNO;
    } //endswitch
}//endif
