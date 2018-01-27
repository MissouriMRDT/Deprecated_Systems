import socket  # IP Networking library for Udp layer
import struct  # Byte structure packing to emulate "type" support (uint8_t, etc ~ stdint.h)
import sqlite3

#####################################################################
# Todo => Move init config like this to a SqlLite database   
# Todo => Split Command, Telem, and System message type by Port 
#      => Add Priority bandwidth subnet masking support (Ubiquiti Rf)

###############################################################################################
# 2017 ~ 2018 Post Gryphon Dev (unamed as of jan 18)

ROVER_ID = 6
PORT = 11000
ROVECOMM_VERSION = 2
UDP_PACKET_BYTES_MAX = 2048
SUBSCRIBERS_MAX = 15
DATA_IDS_MAX = 15

############################################################################################################################
# Data Id's
#
# User Id's for Command Requests or Telemetry Broadcasts
#
#   => Data Id:      3 ~ 16,383 if the 3rd most significant bit is 1 reserved for unacked commands
#      Data Id: 16,384 ~ 32,767 if the 2nd most significant bit is 1 reserved for acked commands
#
# Non User Id's (reserved for future RoveComm Id system upgrade) 
#
#  => Data Id: 32,768 ~ 65,535 if the 1st most significant bit is 1 reserved for future systems

SUBSCRIBE_DATA_ID = 1  # RoveComm user system call Data Id's
UNSUBSCRIBE_DATA_ID = 2

REQUESTED_SUBSCRIBER_IP_ADDRESS_LIMIT_EXCEEDED = 65535  # Reserved system Id's start at max and allocate downwards
REQUESTED_SUBSCRIBER_DATA_ID_LIMIT_EXCEEDED = 65534  # ROVECOMM_UNREGISTERED_BOARD_ID = 65532 (unsure?)
REQUESTED_SUBSCRIBER_DATA_ID_UNKNOWN = 65533

########################################################
# RoveComm Packet Header: 5 Bytes
#
#   Statically populated by RoveManifest.h
#   
#   =>   1 Byte:  RoveComm Version Number
#      + 1 Byte:  Rover Id
#
#   Statically populated by board programmers themselves
#
#      +  1 Byte:  Board Id
#
#   Dynamically populated by RoveComm itself
#
#     + 2 Byte: Session Count

PACKET_HEADER_BYTE_COUNT = 1 + 1 + 1 + 2

###########################################################
# RoveComm Data Header:  8 Bytes
#
#   Dynamic payload populated by end users themselves
#
#   =>   2 Byte:    Data Id
#
#   Dynamically populated by RoveComm itself
#
#      + 4 Byte:    Data Sequence Count
#
#   Dynamic payload populated by end users themselves
#
#      + 2 Byte:    Data Byte Count

#      + 1944 Byte: Data (Variable => 0 Byte  ~ 1944 Bytes)

DATA_HEADER_BYTE_COUNT = 2 + 4 + 2


#####################################################################################################################
# MyBoardRoveCommHandle = RoveComm(board_id=1, session_count=1)

class RoveComm(object):

    # Nested list of Remote Ip Addresses, with each Ip Address containing a list of Remote requested Data Id's
    # subscriber_manifest{"192.1.168.2": [100, 101, 102], "192.1.168.3": [100, 101, 112]}
    # One count for each unique data id, increments on a new data, but not on multiple broadcasts of same data
    # DataSequenceCounts{100 : 1, 101: 24, 112: 5}

    # Pack the Python list into a Byte (8b) + Byte (8b) + Byte (8b) + Short (16b) "BBBH" structure (emulate C++ types)

    # AF_INET address family for IPv4 addresses, SOCK_DGRAM for Udp unreliable discrete datagram packets

    def __init__(self, board_id, session_count=1):  # Todo? => self.session_count = 0

        self.subscriber_manifest = {}
        self.data_sequence_count = {}

        self.packet_header = struct.pack(">BBBH", ROVECOMM_VERSION, ROVER_ID, board_id, session_count)

        self._socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._socket.bind(("", PORT))
        self.session_count()
    """end def"""

    #########################################################################################################

    # data_byte_count may be unnecessary in python but needed in C
    # ie: packet_byte_count = len(data)

    # If we have already seen the Data Id increment the count
    # Else begin a fresh count (new Data Id)

    # Pack the Python list into a Short (16b) + Long (32b) +  Short (16b) "HLH" structure (emulate C++ types)
    # The entire Udp packet has the Packet Header, the Data Header, and the Data

    # If the user passed the Ip Address 0, send a copy of the packet to ALL RoveComm subscribers
    # Else the user wants to send this to one, and only one, Ip address that may, or may not, be Subscribed

    def sendTo(self, ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4, data_id, data):
    
        print("################################################################################")       
        print("Begin roveComm_SendTo: \n")
        
        #if isinstance(data, struct.Struct): # Todo return values

        if data_id in self.data_sequence_count.keys():
        
            self.data_sequence_count[data_id] += 1
        else:
            self.data_sequence_count[data_id] = 1           
        """end if"""
            
        data_header   = struct.pack(">HLH", data_id, self.data_sequence_count[data_id], len(data))      
        packet_buffer = self.packet_header + data_header + data
        
        print("self.packet_header:", self.packet_header)
        print("self.packet_header:", [hex(i) for i in self.packet_header])
       
        print("data_header:", data_header)
        print("data_header:", [hex(i) for i in data_header])
        
        print("packet_buffer     :", packet_buffer, )
        print("packet_buffer     :", [hex(i) for i in packet_buffer])
       
        print("data              :", data)
        print("data              :", [hex(i) for i in data])
        
        if ip_octet_1 == 0 and ip_octet_2 == 0 and ip_octet_3 == 0 and ip_octet_4 == 0:
        
            for ip_address in self.subscriber_manifest:
        
                if data_id in ip_address:
                    self._socket.sendto(packet_buffer, (ip_address, ROVECOMM_PORT))
                """end if"""
            """end for"""
        else:
            ip_address_send = str(ip_octet_1) + '.' + str(ip_octet_2) + '.' + str(ip_octet_3) + '.' + str(ip_octet_4)
            self._socket.sendto(packet_buffer, (ip_address_send, PORT))
            """end else"""
        """end else"""       
        print("End roveComm_SendTo: \n")
    """end def"""

    ############################################################################################################################################

    # if data_id is subscribe
    # data is a data id that the subscriber wants to subscribe to
    # if there are no data_ids with a subscribe remove the address
    # keeping with the C code

    def recieveFrom(self):
    
        print("################################################################################") 
        print("\nBegin roveComm_Recieve:")
        
        packet_buffer, ip_address = self._socket.recvfrom(2048)

        packet_header = packet_buffer[0: PACKET_HEADER_BYTE_COUNT]
        data_header   = packet_buffer[PACKET_HEADER_BYTE_COUNT: (PACKET_HEADER_BYTE_COUNT + DATA_HEADER_BYTE_COUNT)]
        data          = packet_buffer[(PACKET_HEADER_BYTE_COUNT + DATA_HEADER_BYTE_COUNT):]

        (version, rover_id, board_id, session_count)    = struct.unpack(">BBBH", packet_header)  # Todo Database stuff
        (data_id, data_sequence_count, data_byte_count) = struct.unpack(">HLH", data_header)
      
        print("packet_buffer:", packet_buffer)
        print("packet_buffer:", [hex(i) for i in packet_buffer])
        
        print("packet_header:", packet_header)
        print("packet_header:", [hex(i) for i in packet_header])
        
        print("data_header:  ", data_header)     
        print("data_header:  ", [hex(i) for i in data_header])
        
        print("data:         ", data,)
        print("data:         ", [hex(i) for i in data]) 
        
        print("version:      ", version)
        print("rover_id:     ", rover_id)
        print("board_id:     ", board_id)
        print("session_count:", session_count)
                
        print("data_id:            ", data_id)
        print("data_sequence_count:", data_sequence_count)
        print("data_byte_count:    ", data_byte_count)
        
        print("data:               ", data)
  
        if data_id == SUBSCRIBE_DATA_ID:
        
            data_byte_count, data = 0, None

            if ip_address in self.subscriber_manifest:

                if data_subscription not in ip_address:
                    ip_address.append(data_subscription)
                """end if"""
                
            else:
                self.subscriber_manifest[ip_address] = [data_subscription]
            """end if"""
            
        elif data_id == UNSUBSCRIBE_DATA_ID:
        
            data_byte_count, data = 0, None
            
            if ip_address in self.subscriber_manifest:
            
                if data in ip_address:
                    ip_address.remove(data)

                if not self.subscriber_manifest[ip_address]:
                    self.subscriber_manifest.pop(ip_address, None)
                """end if"""
            """end if"""
        """end if"""
        
        print("End roveComm_Recieve: \n")

        return data_id, data_byte_count, data

    """end def"""

    def session_count(self):
        database = sqlite3.connect('session_count_table.db')
        database_cursor = database.cursor()
        
        database_cursor.execute('CREATE TABLE IF NOT EXISTS session_count_table( primary_key INTEGER PRIMARY KEY NOT NULL, session_count_column INTEGER NOT NULL DEFAULT 7 )')
        database_cursor.execute("SELECT session_count_column FROM session_count_table WHERE primary_key = 1")
        data = database_cursor.fetchall()
        print(data)
        if data == []:
            database_cursor.execute('INSERT INTO session_count_table values(1, 1)')
            database_cursor.execute('SELECT session_count_column FROM session_count_table')
            rows = database_cursor.fetchone()
            print("rows:", rows)
        else:
            database_cursor.execute('SELECT session_count_column FROM session_count_table')
            rows = database_cursor.fetchone()
            #print("rows:", rows)
            ##new = list(rows)
            #passer = new[0] + 1
            #database_cursor.execute('UPDATE INTO session_count_table values(1, passer)')
        #database.commit()