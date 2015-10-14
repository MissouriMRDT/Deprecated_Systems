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

    //init Horizon protocol for command_msg_buffer
    rove_tcp_socket command_msg;

    //handle tcp connection state
    command_msg.connected_flag = DISCONNECTED;
    command_msg.error_code = ERROR_FREE;

    //HORIZON command protocol
    command_msg.message_id = 0;
    command_msg.struct_id = 0;
    command_msg.command_value = 0;

//BEGIN NEW EXPERT MEMBER CHALLENGE:

    //Horizon is a forever Client and she calls RED Base Station server forever repeatedly on disconnects
    while (FOREVER) {

        printf("Attempting to connect\n\n");

        command_msg.connected_flag = roveTCP_Connect(&command_msg);

        // loop to recieve cmds and send telem from and to the base station: if socket breaks, loop breaks and we attempt to reconnect
       while (command_msg.connected_flag == CONNECTED) {

            printf("Connected\n");

            command_msg.post_recv_byte_cnt = roveTCP_Recv(&command_msg, &command_msg.message_id, SINGLE_BYTE);

            //Horizon message_id = 5 for a command, except Horizon only ever implemented commands
            if(command_msg.message_id > 0){

                command_msg.post_recv_byte_cnt = roveTCP_Recv(&command_msg, &command_msg.struct_id, SINGLE_BYTE);

            }//endif

            //Horizon used struct_id as the instruction set switch statement identifiers from base station
            if(command_msg.struct_id > 0){

                command_msg.post_recv_byte_cnt = roveTCP_Recv(&command_msg, (char*)&command_msg.command_value, sizeof(command_msg.command_value) );

            }//endif

            //TODO
            printf("FINISH roveHorizon_Recv\n");

///////////////END HORIZON RECIEVE/////////////////



///////////////BEGIN HORIZON SEND COMMANDS/////////

            if(command_msg.command_value > 0){

                rovePrintf_TCP_CmdMsg(&command_msg);

            }//endif

        }//endwhile

        printf("Connection Lost\n");

        close(command_msg.socket_fd);

        command_msg.message_id = 0;

        command_msg.struct_id = 0;

    }//endwhile FOREVER

}//endfnctnTask roveDeviceTemplateThread
