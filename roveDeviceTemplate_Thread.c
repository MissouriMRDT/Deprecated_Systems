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
    fdOpenSession(  TaskSelf() );

    //init Horizon protocol for command_msg_buffer
    rove_tcp_socket command_msg;

    //handle tcp connection state
    command_msg.connected_flag = DISCONNECTED;
    command_msg.error_code = ERROR_FREE;

    //HORIZON command protocol
    command_msg.message_id = 0;
    command_msg.struct_id = 0;

    //TODO debug
    int dbg_zero_recv_byte_cnt = 0;

//BEGIN NEW EXPERT MEMBER CHALLENGE:

    //Horizon is a forever Client and she calls RED Base Station server forever repeatedly on disconnects
    while (FOREVER) {

        printf("Attempting to connect\n\n");

        command_msg.connected_flag = roveTCP_Connect(&command_msg);

        // loop to recieve cmds and send telem from and to the base station: if socket breaks, loop breaks and we attempt to reconnect
       while (command_msg.connected_flag == CONNECTED) {

            printf("Connected\n");

            //TODO debug
            if( (roveTCP_HorizonProtocol_Recv(&command_msg)) < SINGLE_BYTE ) {

                printf("ZERO bytes from roveTCP_HorizonProtocol_Recv : %d\n", dbg_zero_recv_byte_cnt);

                dbg_zero_recv_byte_cnt++;

            }//endwhile
            //TODO
            dbg_zero_recv_byte_cnt++;

            printf("roveTCP_HorizonProtocol_Recv cnt: %d\n", dbg_zero_recv_byte_cnt);


///////////////END HORIZON RECIEVE/////////////////



///////////////BEGIN HORIZON SEND COMMANDS/////////


            rovePrintf_TCPCmdMsg(&command_msg);

        }//endwhile

        printf("Connection Lost\n");

        close(command_msg.socket_fd);

        command_msg.message_id = 0;

        command_msg.struct_id = 0;

    }//endwhile FOREVER

}//endfnctnTask roveDeviceTemplateThread
