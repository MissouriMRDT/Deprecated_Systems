#python C:\Users\T420\Desktop\Repos\RoveComm2-Developement\rovecommTest.py

import struct
import time
from RoveComm import RoveComm
##################################################################################################
# Todo    => Reallocate system message range to negative numbers, data_id uint16t => int16_t? 

# data_id => must be an unsigned integer between 0 and 65535
# data    => must be a struct.Struct instance

RoveComm = RoveComm(1)
telem_data_id_tx = 7
i = 0

#if __name__ == "__main__":

while True:

    telem_data_tx = struct.pack("BBHHLLHHBB", 1+i, 2+i, 7777+i, 8888+i, 123456789+i, 123456789+i, 6666+i, 5555+i, 4+i, 3+i)
    RoveComm.sendTo(127, 0, 0, 1, telem_data_id_tx+i, telem_data_tx)

    command_data_id_rx, command_data_byte_count_rx, command_data_rx = RoveComm.receiveFrom()
    command_data_rx = struct.unpack("BBHHLLHHBB", command_data_rx)

    print("################################################################################")
    #print("\n", "i", i, "\n")
    print("command_id_rx:      ", command_data_id_rx, "\n")
    print("command_byte_cnt_rx:", command_data_byte_count_rx, "\n")
    print("command_rx:         ", command_data_rx, "\n")

    time.sleep(2)
    i += 1