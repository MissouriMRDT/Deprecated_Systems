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

    //construct a bsd udp ip datagram socket
    rove_socket->socket_fd =

            socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (rove_socket->socket_fd < COMMS_ERROR_FREE) {
        return roveCatch_NdkErrno( fdError() );
    }//endif

    //config the socket address
    memset(&rove_socket->local_addr, 0, sizeof(struct sockaddr_in));
    rove_socket->local_addr.sin_family = AF_INET;
    rove_socket->local_addr.sin_port = htons(COMMS_PORT_11000);
    rove_socket->local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind the socket address
    rove_socket->fd_error =

            bind(rove_socket->socket_fd

                , (struct sockaddr*)&(rove_socket->local_addr)
                , sizeof(struct sockaddr_in)
            );//bind

    if (rove_socket->fd_error < COMMS_ERROR_FREE) {
        return roveCatch_NdkErrno( fdError() );
    }//endif

    return COMMS_ERROR_FREE;
}//endfnctn



int32_t roveGet_UdpMsg(rove_protocol* rove_data, rove_udp_socket* rove_socket) {

    //default udp recvfrom gets data in a buffer along with the senders address
    rove_data->data_byte_cnt =

            recvfrom(rove_socket->socket_fd

                , rove_data->data_buffer

                , COMMS_NDK_DEFAULTS_FLAG
                , COMMS_MAX_BUFF_BYTE_CNT
                , (struct sockaddr*)&(rove_socket->remote_addr)
                , (socklen_t*) &(rove_socket->remote_addr_length)
            );//end recvfrom

    if (rove_data->data_byte_cnt < COMMS_SINGLE_BYTE) {
        return roveCatch_NdkErrno( fdError() );
    }//endif

    //remove header bytes and populate rovecomm control byte
    roveParse_UdpMsg(rove_data, rove_socket);

    return rove_data->data_id;
}//end fnctn



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
}//endfnctn



//TODO REED:
int32_t roveCatch_NdkErrno(int32_t ndk_error) {

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
    } //endswitch*/
}//endfnctn
