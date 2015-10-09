///////////////////////////////////////////////////////////////////////FOR

//NEW_MEMBER_READ_ME.txt

//Open roveDeviceTemplate_Thread

//Scroll to:

//END HORIZON RECIEVE

//TCP IP LAN SOCKET MESSAGE HAS BEEN RECIEVED FROM RED BASE STATION

//YOU NOW HAVE A FULL CHARACTER BYTE BUFFER: FULL OF BYTES:


////////////////////////////////////////////////////////////////////////

//NEW MEMBER CHALLENGE:

// watch these video:  https://www.youtube.com/watch?v=GzTPa0UL6vo






//EXPERT MEMBER CODE BONUS CHALLENGE (optional, not required):


//MAKE A NEW GIT BRANCH OF THIS REPO (git checkout -b <whatever_you_call_your-branch>)

//WRITE YOUR OWN LOGIC FUNCTION THAT YOU CAN USE TO SPIN A SERIES OF INCREASING DISCRETE VALUES INTO A PWM Pin

//WRITE THESE ASCENDING INCREMENTS of MICROSECONDS IN A PATTERN OF YOUR CHOICE, RANGING FROM MAX PWM TO MIN PWM

//THIS FUNCTION SHOULD SPIN THESE VAUES THROUGH SOME COMBINATION OF ALL SIX MOTORS IN ANY LOGIC/MATH/OR COUNTING PATTERN OF YOUR CHOICE

//AND ALSO PRINTS OUT THE VALUES TO THE CONSOLE

// THIS CAN ADDED AT BEGIN HORIZON COMMANDS IN roveDeviceTemplate_Thread.c

////////////////////////////////////////////////////////////////////////

//HINTS:

//YOU MAY WANT TO USE printf(), PWM_setDutyrovePrintf_ByteBuffer(), rovePWM_Write rovePWM_Write(), roveDriveMotor_ByPWM()

//....from the roveWare_tivaWrappers folder hidden in the roveDeviceTemplate - > roveWare folder in project explorer

//....different implementations if this function may be hidden among many of the assorted commits in Deprecated-Motherboard Repo

// just play in your branch with something along the lines of

// void rovePWM_Test(tiva_pin motor);


////////////////////////////////////////////////////////////////////////


// Bonus: add your function definitions to roveWare_NewUtils.h and implementations to roveWare_NewUtils.c

// Byte Buffer Wrapper for printF is shows a simple example of how to wrap up a standard function with a mars rover buffer iteration



/*

//defined in roveWare_tivaWrappers.h

void rovePrintf_ByteBuffer(char* buffer, int buffer_size);




//implemented in roveWare_tivaWrappers.c

void rovePrintf_ByteBuffer(char* buffer, int buffer_size) {

    int printf_cnt = 0;

    printf("Buffer holds: ");

    while (printf_cnt < buffer_size) {

        printf(" %d", buffer[printf_cnt]);

        printf_cnt++;

    } //end while

    printf("\n\n");

    return;

}//endfnctn rovePrintf_ByteBuffer




//used in roveDeviceTemplate_Thread.c
 *

rovePrintf_ByteBuffer(command_msg_buffer, command_msg.post_recv_byte_cnt);

// Double Super Secret Bonus:

// Add a RED_TcpMock_Tester_Thread.h and RED_TcpMock_Tester_Thread.c files and bind the function to a rtos Thread  

// Add a TCP_Mock_command_msg_mailbox

// Post to the mailbox in RED_TcpMock_Tester_Thread with the logic to fill the command_msg_buffer with the command data algorithm from your function

// (hint: use tivaRTSC.cfg to add an Tiva rtos TASK handle and a Tiva rtos MAILBOX handle)

// Your task should generate a fake message from base station, your output should be the THE PATTERN OF YOUR CHOICE, RANGING FROM MAX PWM TO MIN PWM


*/


//END NEW MEMBER_READ_ME.txt

