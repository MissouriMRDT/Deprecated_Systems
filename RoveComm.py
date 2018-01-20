import socket    # IP Networking library for Udp layer
import struct    # Byte structure packing to emulate "type" support (uint8_t, etc ~ stdint.h)

#####################################################################
# Todo => Move init config like this to a SqlLite database   
# Todo => Split Command, Telem, and System message type by Port 
#      => Add Priority bandwidth subnet masking support (Ubiquiti Rf)

###############################################################################################
# 2017 ~ 2018 Post Gryphon Dev (unamed as of jan 18)

ROVECOMM_ROVER_ID = 6        
ROVECOMM_VERSION  = 2 
ROVECOMM_PORT     = 11000 

UDP_PACKET_BYTES_MAX      = 2048  
ROVECOMM_DATA_IDS_MAX     = 15
ROVECOMM_SUBSCRIBERS__MAX = 15


############################################################################################################################
# Data Id's
#
# User Id's for Command Requests or Telemetry Broadcasts
#
#   => 2^14 Bytes:  Data Id:      3 ~ 16,383 for unacked commands 
#      2^14 Bytes:  Data Id: 16,384 ~ 32,767 for acked   commands
#
# Non User Id's (reserved for future RoveComm Id system upgrade) 
#
#   => 2^15 Bytes:  Data Id: 32,768 ~ 65,535 for future system 

ROVECOMM_SUBSCRIBE_DATA_ID   = 1    # RoveComm user system call Data Id's
ROVECOMM_UNSUBSCRIBE_DATA_ID = 2

ROVECOMM_REQUESTED_SUBSCRIBER_IP_ADDRESS_LIMIT_EXCEEDED = 65535    # Reserved system Id's start at max and allocate downwards
ROVECOMM_REQUESTED_SUBSCRIBER_DATA_ID_LIMIT_EXCEEDED    = 65534    # ROVECOMM_UNREGISTERED_BOARD_ID = 65532 (unsure?)
ROVECOMM_REQUESTED_SUBSCRIBER_DATA_ID_UNKNOWN           = 65533    


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

ROVECOMM_PACKET_HEADER_BYTE_COUNT = 1 + 1 + 1 + 2


###########################################################
# RoveComm Data Header:  8 Bytes
#
#   Dynamic payload populated by end users themselves
#
#   =>   2 Byte:    Data Id
#      + 4 Byte:    Data Sequence Count
#      + 2 Byte:    Data Byte Count

#      + 1944 Byte: Data (Variable => 0 Byte  ~ 1944 Bytes)

ROVECOMM_DATA_HEADER_BYTE_COUNT  = 2 + 4 + 2
 
 
#####################################################################################################################
# MyBoardRoveCommHandle = RoveComm(board_id=1, session_count=1)

class RoveComm(object):

	# Nested list of Remote Ip Addresses, with each Ip Address containing a list of Remote requested Data Id's
	# Subscribers{"192.1.168.2": [100, 101, 102], "192.1.168.2": [100, 101, 102]}
	# One count for each unique data id, increments on a new data, but not on multiple broadcasts of same data
	# DataSequenceCounts{100 : 1, 101: 3, 101: 5}
	
	# Pack the Python list into a Byte (8b) + Byte (8b) + Byte (8b) + Short (16b) "BBBH" structure (emulate C++ types)
	
	# AF_INET address family for IPv4 addresses, SOCK_DGRAM for Udp unreliable discrete datagram packets  
	
	def __init__(self, board_id, session_count=1):     # Todo? => self.session_count = 0
	
		self.Subscribers        = {}
		self.DataSequenceCounts = {}
		
		self.PacketHeader = struct.pack(">BBBH", ROVECOMM_VERSION, ROVECOMM_ROVER_ID, board_id, session_count)
		
		self._socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		self._socket.bind(("", ROVECOMM_PORT))	
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
	
	def roveComm_SendTo(self, ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4, data_id, data_byte_count, data):
	
		if data_id in self.DataSequenceCounts.keys():
		
			self.DataSequenceCounts[data_id] += 1
		else:		
			self.DataSequenceCounts[data_id]  = 1 
			
			DataHeader    = struct.pack(">HLH", data_id, self.DataSequenceCounts[data_id], data_byte_count)
			packet_buffer = self.PacketHeader + DataHeader + bytes(data)
			
			#print("packet_buffer: ", packet_buffer) 
			#print ("data bytes: ", bytes(data))						
			#print("data_id:", data_id, "data_byte: ", data_byte_count, "data: ", data) 			
			#"self.PacketHeader: ", self.PacketHeader, "dataheader: ", DataHeader, "bytesData: ", 		
			#bytes([data]), "bytes: ", chr(65000)type(bytes(data)), type(chr(data)), type(int(data)), type(hex(data)), type(DataHeader), type(data))
			
			if ip_octet_1 == 0 and ip_octet_2 == 0 and ip_octet_3 == 0 and ip_octet_4 == 0:
			
				for ip_address in self.Subscribers:
				
					if data_id in ip_address:
					
						self._socket.sendto(bytes(packet_buffer), (ip_address, ROVECOMM_PORT)) # Todo debug here
					"""end if"""
				"""end for"""
			else:
				ip_address_send = str(ip_octet_1) + '.' + str(ip_octet_2) + '.' + str(ip_octet_3) + '.' + str(ip_octet_4)
				self._socket.sendto(bytes(packet_buffer), (ip_address_send, ROVECOMM_PORT)) # Todo debug here
			"""end else"""
		"""end else"""
	"""end def"""
		
	############################################################################################################################################
		
	# if data_id is subscribe	
	# data is a data id that the subscriber wants to subscribe to
	# if there are no data_ids with a subscribe remove the address	
	# keeping with the C code
	
	def roveComm_Recieve(self):
		
		packet_buffer, ip_address = self._socket.recvfrom(2048)	
		
		packet_header = packet_buffer[0: ROVECOMM_PACKET_HEADER_BYTE_COUNT] 
		data_header   = packet_buffer[ROVECOMM_PACKET_HEADER_BYTE_COUNT: (ROVECOMM_PACKET_HEADER_BYTE_COUNT + ROVECOMM_DATA_HEADER_BYTE_COUNT)]
		data          = packet_buffer[(ROVECOMM_PACKET_HEADER_BYTE_COUNT + ROVECOMM_DATA_HEADER_BYTE_COUNT):]
		
		(version, rover_id, board_id,  session_count)   = struct.unpack(">BBBH", packet_header)  # Todo Database stuff
		(data_id, data_sequence_count, data_byte_count) = struct.unpack(">HLH",  data_header)
		
		if data_id == ROVECOMM_SUBSCRIBE_DATA_ID:
		
			if ip_address in self.Subscribers:
			
				if data not in ip_address:
				
					ip_address.append(data)
				"""end if"""
			else:	
				self.Subscribers[ip_address] = [data]
				#data_byte_count, data = 0, 0 
			"""end if"""
		elif data_id == ROVECOMM_UNSUBSCRIBE_DATA_ID:
		
			if ip_address in self.Subscribers:
		
				if data in ip_address:
			
					ip_address.remove(data)
				
				if not self.Subscribers[ip_address]:
				
					self.Subscribers.pop(ip_address, None)
				"""end if""" 
			"""end if"""
					
			data_byte_count, data = 0, 0
		"""end if"""
		
		return data_id, data_byte_count, data
	"""end def"""