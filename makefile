all: server client
	echo "Making all..."

server: roveComm_Server.o
	gcc roveComm_Server.o -o server

client: roveComm_Client.o
	gcc roveComm_Client.o -o client

roveComm_Server.o: roveComm_Server.c
	gcc -c roveComm_Server.c

roveComm_Client.o: roveComm_Client.c
	gcc -c roveComm_Client.c

clean:
	rm *.o server client

