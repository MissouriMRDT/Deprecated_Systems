// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// recieves base station commands using ip bsd UDP style sockets
//
// mrdt::rovWare

//TODO on URC 2016 OCTOBER_DEVELOPEMENT Protocol
#include "roveComm.h"

// TODO Judah Factor Out Dev Shorthand
//Public
typedef enum ROVECOM_DEV {

    COMMS_NULL_int32_t= 0
    , COMMS_SET_NDK_DEFAULT = 0
    , COMMS_ZERO_BYTES = 0
    , COMMS_SINGLE_BYTE = 1
} ROVECOM_DEV;

// TODO Reed NDK vs IP vs PROTO Error model advice??
//see eof for roveComm_CatchRoveERRNO, roveComm_CatchNdkERRNO, Tiva Ndk Developement Notes as of Dec16
typedef enum ROVECOMM_ERRNO {

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
} ROVECOMM_ERRNO;



///////////////::BEGIN//////RoveComm Private Functions//////////////
static int32_t roveComm_ParseUdpMSG(rovecomm_protocol* rove_data);
static int32_t roveComm_CatchRoveERRNO(int32_t rove_errno);
static int32_t roveComm_CatchNdkERRNO(int32_t ndk_errno);

///////////////::BEGIN//////RoveComm Implementation//////////////

//public: initialize and config a udp listening port
int32_t roveComm_InitUdpCFG(rovecomm_socket* rove_socket, uint8_t* local_ip_address, int32_t local_port) {

    rove_socket->ndk_fd_error = COMMS_ERROR_FREE;

    //TODO ip6 support with ip4 default? if (rove_socket->ip_family)

    //construct a bsd udp ip datagram socket
    rove_socket->socket_fd =

        socket(

            AF_INET
            , SOCK_DGRAM
            , IPPROTO_UDP);

    if (rove_socket->socket_fd == COMMS_SOCKET_ERROR) {

        return roveComm_CatchNdkERRNO(rove_socket->ndk_fd_error =

                fdError() );
    }//endif

    //TODO macro vs runtime check ip address memory size?
    //address_byte_cnt = 16 = roveGet_IpByetCnt_ByStrPtr(ipv4??);
    rove_socket->local_ip.address_byte_cnt = 16;


    //clear memory to all zeros in rove socket address structure
    //TODO be very careful with memset args
    memset(

            &(rove_socket->local_ip.address)

            , COMMS_NULL_int32_t
            , rove_socket->local_ip.address_byte_cnt );

    //TODO ip6 support with ip4 default?
    rove_socket->local_ip.ip_family = AF_INET;

    //set rove socket address structure ipv4 (casting embedded types, to bsd types)
    rove_socket->local_ip.port = htons( (unsigned short)local_port);
    rove_socket->local_ip.address = inet_addr( (char*)local_ip_address );

    //bind the socket address

    //TODO fix the  typdef/args casting chain here
    //address != struct sock_addr != struct in_addr != sin_addr != null_term....technicallyyyy
    rove_socket->ndk_fd_error =

        bind(

            rove_socket->socket_fd

            , (struct sockaddr*)&(rove_socket->local_ip.address)
            , rove_socket->local_ip.address_byte_cnt  );

    //TODO Rovecomm Error Bubbles are negative numbers in this model -1, -2,
    if (rove_socket->ndk_fd_error == COMMS_SOCKET_ERROR) {

        return roveComm_CatchNdkERRNO(rove_socket->ndk_fd_error =

                fdError() );
    }//endif

    return COMMS_ERROR_FREE;
}//endfnctn



//public: recv and parse a rovecomm message on a udp socket by protocol definition
int32_t roveComm_GetUdpMSG(rovecomm_socket* rove_socket, rovecomm_protocol* rove_data) {

    rove_data->data_id = 0;
    rove_data->data_byte_cnt = 0;

    //clear memory to all zeros in rove protocol data structure
    //TODO markup be very careful with type difference in c compilers when setting memset args
    memset(

            &(rove_data->data_buffer)

            , COMMS_NULL_int32_t
            , COMMS_MAX_BUFFER_BYTE_CNT );

    //defaults on ti ndk udp recvfrom gets data in a buffer along with the senders address as a new ip subscriber
    rove_data->recv_byte_cnt =

        recvfrom(

            rove_socket->socket_fd
            , rove_data->data_buffer

            , COMMS_SET_NDK_DEFAULT
            , COMMS_MAX_BUFFER_BYTE_CNT
            //TODO while subscribers[0++] < subcscriber_cnt etc
            //currently this will always just overwrite as address of last ip subscriber
            , (struct sockaddr*)&(rove_socket->ip_subscribers[0].address )
            , (socklen_t*) &(rove_socket->ip_subscribers[0].address_byte_cnt));
            //TODO roveComm_CatchNewSubscriber( subscribers[0++] ) < subcscriber_cnt etc

    if (rove_data->recv_byte_cnt == 0) {

        return roveComm_CatchRoveERRNO(rove_data->data_error =

                NO_RECV_BYTES);
    }//end if

    if (rove_data->recv_byte_cnt) {

        rove_data->data_byte_cnt =

                roveComm_ParseUdpMSG(rove_data);

        if (rove_data->data_byte_cnt == 0) {

            return roveComm_CatchRoveERRNO(rove_data->data_error =

                    NO_DATA_BYTES);
        }//end if

        if (rove_data->data_byte_cnt) {

           return rove_data->data_id;
        }//end if
    }//end if

    //rove_data->recv_byte_cnt was negative therefore rrcvfrm ndk error
    return roveComm_CatchNdkERRNO( rove_socket->ndk_fd_error =

            fdError() );
}//end fnctn



//remove header bytes and populate rovecomm control bytes, fill rove_socket->data_buffer with the command data payload
static int32_t roveComm_ParseUdpMSG(rovecomm_protocol* rove_data){

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
            return rove_data->data_error =

                    COMMS_PARSE_UDP_ERRNO;
    }//switch
}//endfnctn



// Begin Tiva Ndk Developement Notes as of Dec16

//TODO mark up on udp bsd cfg
//AF_INET
//SOCK_DGRAM
//IPPROTO_UDP);


//TI NDK socket APIs
// ======== socket.h ========
//tiva has a custom htonl()
//#define htonl(a) ((((a) & 0xff000000) >> 24) | (((a) & 0x00ff0000) >> 8) | \ (((a) & 0x0000ff00) << 8)  | (((a) & 0x000000ff) << 24) )
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//======== inetaddr.c ========
//tiva has standard address conversion function hooks
//inet_addr() Converts const character array to Network Byte IP address:: IPN inet_addr( const char *str )
// inet_ntop() Standard means of converting an IP address to a string:: const char *inet_ntop(int af, const void *src, char *dst, int cnt)
//////////////////////////////////////////////////////////////////////


/* Generic Socket address storage data structure.
struct sockaddr {

    // address family
    unsigned char sa_family;

    // socket data
    char sa_data[14];

};*/

/* AF_INET family (IPv4) Socket address data structure.
struct sockaddr_in {

// address family
    unsigned char  sin_family;

    // port
    unsigned short sin_port;
    struct in_addr sin_addr;

    // fixed length address value
    char sin_zero[8];

};
typedef struct sockaddr_in  SA_IN;
typedef struct sockaddr_in* PSA_IN
*/


// 32 bit long IP address, net order
/* Structure used by kernel to store most
struct in_addr {
    unsigned int s_addr;
};*/

//typedef (struct sockaddr*)&     cast_ip_address_ptr
//typedef (char*)                 cast_char_ptr


//TI socketndk functions return negative error
//to be clear this is not the same as = fdError() socket state lookup which only returns positive error defs
//TODO?? used by socket() and accept() :       INVALID_SOCKET (void *)0xFFFFFFFF
//#define COMMS_INVALID_SOCKET -1
//used by all other ti ndk functions:   SOCKET_ERROR   -1

//a pointer to a struct sockaddr_in can be cast to a pointer to a struct sockaddr and vice-versa.
//Socket() wants a struct sockaddr*, you can still use a struct sockaddr_in and cast it

//sin_family corresponds to sa_family in a struct sockaddr set to "AF_INET".
//sin_port and sin_addr must be in Network Byte Order

// End Tiva Ndk Developement Notes as of Dec16

//TODO Reed Advice? JUDAH: Eliminate Switch
static int32_t roveComm_CatchRoveERRNO(int32_t rove_errno) {

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
static int32_t roveComm_CatchNdkERRNO(int32_t ndk_errno) {

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
