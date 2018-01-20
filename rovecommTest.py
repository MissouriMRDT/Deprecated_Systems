from RoveComm import RoveComm
import time
import sys

print(sys.version)
mine = RoveComm(1, 1)
data_id = 2
sendData = 3

while True:

    mine.roveComm_SendTo(127, 0, 0, 1, data_id, len(bytes(sendData)), sendData)
    data_id, data_byte_count, data = mine.roveComm_Recieve()
    print(data_id, data_byte_count, data)
    sendData = 81
    data_id = 7
    time.sleep(0.5)
