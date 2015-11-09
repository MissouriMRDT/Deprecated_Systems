# RoveComm-Software
Distributed Internet Protocol for Embedded Device 

#### Using these files
This folder has source files for a UDP server and a UDP client written in C. 
You can use the makefile to compile.

##### The Client
The test client sends a single UDP packet based on the arguments as shown below:

    ./client DataID Data [Dest_IP [Dest_Port [Sequence_Number]]]

 - DataID - The Data ID of the packet. Can be entered as a decimal number or 
preceded with 0x to enter a hex number.
 - Data - The Bytes of data to send in hexadecimal. You can only input 8 bytes 
to send. If you try more, incorrect data will be sent.
 - Dest_IP - The IP address to send your data to
 - Dest_Port - The Port to send you data to as a decimal integer.
 - Sequence_Number - The Sequence Number to be put in the packet

##### The Server
The server is pretty straightforward. It listens on port 11000 and mirrors 
back every message it receives to the device it receives from, but to port
11000 instead of the port the message came from.
