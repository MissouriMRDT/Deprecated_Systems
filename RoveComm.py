import socket
import struct
import threading
import logging

# 5 Byte: RoveComm Packet Header:
#
# 		Statically populated by RoveManifest.h
#
# 			1 Byte:  RoveComm Version Number
# 			1 Byte:  Rover Id
#
# 		Statically populated by board programmers themselves
#
# 			1 Byte:  Board Id
#
# 		Dynamically populated by RoveComm itself
#
# 			2 Byte: Session Count

ROVECOMM_PACKET_HEADER_BYTE_COUNT = 1 + 1 + 1 + 2

##############
# 8 Byte: RoveComm Data Header:
#
# 		2 Byte: Data Id
# 		4 Byte: Data Sequence Count
# 		2 Byte: Data Byte Count
ROVECOMM_DATA_HEADER_BYTE_COUNT = 2 + 4 + 2

# 		Variable (0 ~ 912) Byte:  Data

##############
# Reserved Data Id's
#
# 		Data Id 3~16383 (2^14) for unacked commands
# 		Data Id 16384~32767 (2^15) for acked commands
#		Data Id 32768~65535 (2^16) for system commands

ROVECOMM_SUBSCRIBE_DATA_ID    								= 0
ROVECOMM_UNSUBSCRIBE_DATA_ID      							= 1
ROVECOMM_REQUESTED_SUBSCRIBER_IP_ADDRESS_LIMIT_EXCEEDED  	= 65535
ROVECOMM_REQUESTED_SUBSCRIBER_DATA_ID_LIMIT_EXCEEDED  		= 65534
ROVECOMM_REQUESTED_SUBSCRIBER_DATA_ID_UNKNOWN  				= 65533
#ROVECOMM_UNREGISTERED_BOARD_ID  							= 65532 Judah is unsure

#####################################

ROVECOMM_VERSION 					                      	= 2
ROVECOMM_PORT 						                        = 11000
ROVECOMM_MAX_SUBSCRIBERS_COUNT 	                        	= 15
ROVECOMM_MAX_DATA_ID_COUNT		 	                        = 15
UDP_TRANSMIT_PACKET_MAX_BYTE_COUNT                      	= 2048

class RoveComm(object):

    def __init__(self, board_id):
        self.session_count = 0
        self.RoveCommSubscribers = []
        self.data_sequence_counts = []
        self.data_sequence_ids = []
        self.RoveCommPacketHeader[0] = ROVECOMM_VERSION
	    self.RoveCommPacketHeader[1] = ROVER_ID
	    self.RoveCommPacketHeader[2] = board_id
	    self.RoveCommPacketHeader[3] = session_count

        #print([l for l in ([ip for ip in socket.gethostbyname_ex(socket.gethostname())[2] if not ip.startswith("127.")][:1], [[(s.connect(('8.8.8.8', 53)), s.getsockname()[0], s.close()) for s in [socket.socket(socket.AF_INET, socket.SOCK_DGRAM)]][0][1]]) if l][0][0])

        try:
            self._socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            self._socket.bind(("", PORT))
        except socket.error:
            raise Exception("Error: Could not claim port. "
                            "Either another program or another copy or rovecomm"
                            "is using port %d " % PORT)

        # start a thread to get messages in the background
        #self._monitoring_thread = threading.Thread(target=self.roveComm_Receive)
        #self._monitoring_thread.daemon = True
        #self._monitoring_thread.start()

    def roveComm_SendTo(self, ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4, data_id, data_byte_count, data):
        self.packet_byte_count = len(data)
        self.data_sequence_count = 0

        for index, data_sequence_id in enumerate(data_sequence_ids):
            if data_sequence_id == data_id:
                data_sequence_count[index] = data_sequence_count[index] + 1
        else:
            data_sequence_ids.append(data_id)
            data_sequence_counts.append(0)
