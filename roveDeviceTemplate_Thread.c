// Missouri Science and Technology Mars Rover Design Team 2015
//
// Judah Schad jrs6w7@mst.edu
//
// recieves base station commands using ip bsd style sockets
//
// mrdt::rovWare

// BEGIN TCP HORIZON RECIEVE

// DEVICE TEAM : YOU MAY START THIS CHALLENG BY SKIPPING PAST THIS TCP LOGIC ON DOWN TO LINE 50ish : "BEGIN HORIZON COMMANDS"

#include "roveDeviceTemplate_Thread.h"

void roveDeviceTemplateThread(UArg arg0, UArg arg1) {

    printf("Init roveDevice_TemplateThread\n\n\n");

    //open a tiva ndk socket session in this task stack
    fdOpenSession((void*) TaskSelf());

    //init Horizon tcp socket
    rove_tcp_socket rove_tcp_socket;

    //handle tcp connection state
    rove_tcp_socket.connected_flag = false;

    //init Horizon protocol for command_msg_buffer
    message_cfg command_msg;

    //temp working memory slot for commands while recv/send
    char command_msg_buffer[MAX_CMD_BYTE_CNT];


//BEGIN NEW EXPERT MEMBER CHALLENGE:

    //Horizon is a forever Client and she calls RED Base Station server forever repeatedly on disconnects
    while (FOREVER) {

        printf("Attempting to connect\n\n");

        roveTCP_Connect(&rove_tcp_socket);

        // loop to recieve cmds and send telem from and to the base station: if socket breaks, loop breaks and we attempt to reconnect
       while (rove_tcp_socket.connected_flag == CONNECTED) {

            printf("Connected\n");

            command_msg.post_recv_byte_cnt = roveHorizon_Recv(&rove_tcp_socket, &command_msg, command_msg_buffer);

            if(command_msg.post_recv_byte_cnt > 0 ) {



///////////////END HORIZON RECIEVE/////////////////



///////////////BEGIN HORIZON SEND COMMANDS/////////

                rovePrintf_ByteBuffer(command_msg_buffer, command_msg.post_recv_byte_cnt);

            }//endif

        }//endwhile

        printf("Connection Lost\n");

        close(rove_tcp_socket.socket_fd);

    }//endwhile FOREVER

}//endfnctnTask roveDeviceTemplateThread
