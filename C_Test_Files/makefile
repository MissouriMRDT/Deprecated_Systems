all: server client
	echo "Making all..."

server: roveComm_Server.o RoveComm.o
	gcc roveComm_Server.o RoveComm.o roveBoard.o -o server

client: roveComm_Client.o RoveComm.o
	gcc roveComm_Client.o RoveComm.o roveBoard.o -o client

RoveComm.o: RoveComm.c roveBoard.c
	gcc -c RoveComm.c roveBoard.c

roveComm_Server.o: roveComm_Server.c 
	gcc -c roveComm_Server.c

roveComm_Client.o: roveComm_Client.c
	gcc -c roveComm_Client.c

clean:
	rm *.o server client

