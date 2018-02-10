import socket  
import struct  
import sqlite3

ROVER_ID = 6
PORT = 11000
ROVECOMM_VERSION = 2
UDP_PACKET_BYTES_MAX = 2048
SUBSCRIBERS_MAX = 15
DATA_IDS_MAX = 15
SUBSCRIBE_DATA_ID = 1  
UNSUBSCRIBE_DATA_ID = 2
REQUESTED_SUBSCRIBER_IP_ADDRESS_LIMIT_EXCEEDED = 65535 
REQUESTED_SUBSCRIBER_DATA_ID_LIMIT_EXCEEDED = 65534  
REQUESTED_SUBSCRIBER_DATA_ID_UNKNOWN = 65533
PACKET_HEADER_BYTE_COUNT = 1 + 1 + 1 + 2
DATA_HEADER_BYTE_COUNT = 2 + 4 + 2

#######################################################################################################

class RoveComm(object):

    ####################################################################################################

    def __init__(self, board_id):

        self.subscriber_manifest = {}
        self.data_sequence_count = {}
        self.packet_header = struct.pack(">BBBH", ROVECOMM_VERSION, ROVER_ID, board_id, self.session_count())
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._socket.bind(("", PORT))
    """end def"""

    ###################################################################################################################
    
    def sendTo(self, ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4, data_id, data):
        
        if not isinstance(data, bytes): 
            raise TypeError(data, "Should be of Bytes type, consider using struct module.")

         # Todo return values
        if data_id in self.data_sequence_count.keys():        
            self.data_sequence_count[data_id] += 1
        else:
            self.data_sequence_count[data_id] = 1           
        """end if"""
            
        data_header   = struct.pack(">HLH", data_id, self.data_sequence_count[data_id], len(data))      
        packet_buffer = self.packet_header + data_header + data

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
    """end def"""

    #################################################################################################################
    
    def receiveFrom(self):
  
        packet_buffer, ip_address = self._socket.recvfrom(2048)

        packet_header = packet_buffer[0: PACKET_HEADER_BYTE_COUNT]
        data_header   = packet_buffer[PACKET_HEADER_BYTE_COUNT: (PACKET_HEADER_BYTE_COUNT + DATA_HEADER_BYTE_COUNT)]
        data          = packet_buffer[(PACKET_HEADER_BYTE_COUNT + DATA_HEADER_BYTE_COUNT):]

        (version, rover_id, board_id, session_count)    = struct.unpack(">BBBH", packet_header)  # Todo Database stuff
        (data_id, data_sequence_count, data_byte_count) = struct.unpack(">HLH", data_header)
      
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
        
        return data_id, data_byte_count, data
    """end def"""

    #####################################################################################################
    
    def session_count(self):
    
        database = sqlite3.connect('session_count_table.db')
        database_cursor = database.cursor()
        
        database_cursor.execute('CREATE TABLE IF NOT EXISTS session_count_table '
                                '(primary_key INTEGER PRIMARY KEY NOT NULL, session_count INTEGER NOT NULL)')   
        database_cursor.execute('SELECT session_count FROM session_count_table WHERE primary_key = 1')
        session_count_row = database_cursor.fetchone()
         
        if not session_count_row:
            session_count = 1
            database_cursor.execute('INSERT INTO session_count_table values(1, 1)')
        else:
            session_count = session_count_row[0] + 1
            database_cursor.execute('UPDATE session_count_table SET session_count = ? WHERE primary_key = 1', (session_count,) )
            
        database.commit()        
        return session_count
    """end def"""