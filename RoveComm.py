import socket
import struct
# import threading
# import logging

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

# 		Variable (0 ~ 1944) Byte:  Data

##############
# Reserved Data Id's
#
# 		Data Id 3~16383 (2^14) for unacked commands
# 		Data Id 16384~32767 (2^15) for acked commands
#		Data Id 32768~65535 (2^16) for system commands

ROVECOMM_SUBSCRIBE_DATA_ID = 1
ROVECOMM_UNSUBSCRIBE_DATA_ID = 2
ROVECOMM_REQUESTED_SUBSCRIBER_IP_ADDRESS_LIMIT_EXCEEDED = 65535
ROVECOMM_REQUESTED_SUBSCRIBER_DATA_ID_LIMIT_EXCEEDED = 65534
ROVECOMM_REQUESTED_SUBSCRIBER_DATA_ID_UNKNOWN = 65533
# ROVECOMM_UNREGISTERED_BOARD_ID  					        = 65532 Judah is unsure

#####################################

ROVECOMM_VERSION = 2
ROVECOMM_ROVER_ID = 1
ROVECOMM_PORT = 11000
ROVECOMM_MAX_SUBSCRIBERS_COUNT = 15
ROVECOMM_MAX_DATA_ID_COUNT = 15
UDP_TRANSMIT_PACKET_MAX_BYTE_COUNT = 2048
 

class RoveComm(object):
    def __init__(self, board_id, session_count):
        # self.session_count = 0
        self.Subscribers = {}      # Subscribers{“192.1.168.2”: [100, 101, 102], “192.1.168.2”: [100, 101, 102]}
        self.DataSequenceCounts = {}  # {100 : 1, 101: 5} data : numberSent
        self.PacketHeader = struct.pack(
                                        ">BBBH",
                                        ROVECOMM_VERSION,
                                        ROVECOMM_ROVER_ID,
                                        board_id,
                                        session_count)
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._socket.bind(("", ROVECOMM_PORT))

    # data_byte_count may be unnecessary in python but needed in C
    def roveComm_SendTo(self, ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4, data_id, data_byte_count, data):
        # packet_byte_count = len(data)
        if data_id in self.DataSequenceCounts.keys():
            self.DataSequenceCounts[data_id] += 1
        else:
            self.DataSequenceCounts[data_id] = 1
        print("data_id:", data_id)
        print("data_byte: ", data_byte_count)
        print("data: ", data)
        print("self.PacketHeader: ", self.PacketHeader)
        DataHeader = struct.pack(
                                 ">HLH",
                                 data_id,
                                 self.DataSequenceCounts[data_id],
                                 data_byte_count)
        print("dataheader: ", DataHeader)
        print("bytesData: ", bytes([data]))
        # print("bytes: ", chr(65000))
        #print(type(bytes(data)), type(chr(data)), type(int(data)), type(hex(data)))
        print(type(DataHeader), type(data))
        # print this is still bugged bytes(data)
        packet_buffer = self.PacketHeader + DataHeader + bytes(data)
        print("packet_buffer:", packet_buffer)
        if ip_octet_1 == 0 and ip_octet_2 == 0 and ip_octet_3 == 0 and ip_octet_4 == 0:
            for ip_address in self.Subscribers:
                if data_id in ip_address:
                    self._socket.sendto(bytes(packet_buffer), (ip_address, ROVECOMM_PORT))
        else:
            ip_address_send = str(ip_octet_1) + '.' + str(ip_octet_2) + '.' + str(ip_octet_3) + '.' + str(ip_octet_4)
            self._socket.sendto(bytes(packet_buffer), (ip_address_send, ROVECOMM_PORT))

    def roveComm_Recieve(self):
        packet_buffer, ip_address = self._socket.recvfrom(2048)
       # print("packet_buffer:", packet_buffer)
        # print("ip:", ip_address)
        packet_header = packet_buffer[0: ROVECOMM_PACKET_HEADER_BYTE_COUNT]
        data_header = packet_buffer[ROVECOMM_PACKET_HEADER_BYTE_COUNT: (ROVECOMM_PACKET_HEADER_BYTE_COUNT + ROVECOMM_DATA_HEADER_BYTE_COUNT)]
        data = packet_buffer[(ROVECOMM_PACKET_HEADER_BYTE_COUNT + ROVECOMM_DATA_HEADER_BYTE_COUNT):]
        (version, rover_id, board_id, session_count) = struct.unpack(">BBBH", packet_header)  # Database stuff
        (data_id, data_sequence_count, data_byte_count) = struct.unpack(">HLH", data_header)
        # if data_id is subscribe
        if data_id == ROVECOMM_SUBSCRIBE_DATA_ID:
            if ip_address in self.Subscribers:
                # data is a data id that the subscriber wants to subscribe to
                if data not in ip_address:
                    ip_address.append(data)
            else:
                self.Subscribers[ip_address] = [data]
            data_byte_count, data = 0, 0
        elif data_id == ROVECOMM_UNSUBSCRIBE_DATA_ID:
            if ip_address in self.Subscribers:
                # data is a data id that the subscriber wants to subscribe to
                if data in ip_address:
                    ip_address.remove(data)
                # if there are no data_ids with a subscribe remove the address
                if not self.Subscribers[ip_address]:
                    self.Subscribers.pop(ip_address, None)
            # keeping with the C code
            data_byte_count, data = 0, 0
        print(data)
        return data_id, data_byte_count, data
