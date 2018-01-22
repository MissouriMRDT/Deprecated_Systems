from RoveComm import RoveComm
import time
import sys

print(sys.version)
mine = RoveComm(1, 1)
data_id = 2
sendData = 10000
length = len(bytes(sendData))
print("len: ", len(bytes(sendData)))
while True:
    mine.roveComm_SendTo(127, 0, 0, 1, data_id, sendData)
    data_id, data_byte_count, data = mine.roveComm_Recieve()
    #print(data_id, data_byte_count, data)
    #print(sendData)
    #print(hex(30))
    data_id += 1
    sendData += 1
    time.sleep(.1)

