// roveStructTransfer.c MST MRDT 2015
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad_jrs6w7@mst.edu

#include "../roveWareHeaders/roveStructTransfer.h"

// rove struct transfer to fill a buffer with a rove transfer frame
int buildSerialStructMessage(void* my_struct, char* buffer) {

    uint8_t size;
    uint8_t start_byte1 = 0x06;
    uint8_t start_byte2 = 0x85;
    uint8_t checkSum;

    int totalSize = -1;

    size = getStructSize(((struct rovecom_id_cast*) my_struct)->struct_id);

    if (size <= 0) {

        printf(
                "Error in function: buildSerialStructMessage() - struct size is not valid");
        return -1;

    } //endif

    // checkSum = size;

    buffer[0] = start_byte1;
    buffer[1] = start_byte2;
    buffer[2] = size;

    // copy the struct into the buffer starting at byte 3
    memcpy(buffer + 3, my_struct, size);

    checkSum = calcCheckSum(my_struct, size);

    // 3 for two start bytes and size byte plus size of struct to get final position
    buffer[3 + size] = checkSum;

    totalSize = 3 + size + 1;

    return totalSize;

} //end fnctn buildSerialStructMessage

uint8_t calcCheckSum(const void* my_struct, uint8_t size) {

    uint8_t checkSum = size;
    uint8_t i;

    for (i = 0; i < size; i++)
        checkSum ^= *((char*) my_struct + i);

    return checkSum;

} //end fnctn

bool recvSerialStructMessage(int deviceJack, char* buffer) {

    uint8_t rx_len = 0;
    uint8_t startByte = 0x06;
    uint8_t secondByte = 0x85;

    int bytesRead = 0;
    char receiveBuffer[40];

    // This is used to decide how much pre-data to discard before quitting
    uint8_t garbageCount = 10;
    bool startReceived = false;

    //testing
    //int debug_rx_cnt = 0;

    if (rx_len == 0) {

        while (!startReceived) {
            bytesRead = deviceRead(deviceJack, receiveBuffer, 1, 500);
            if (bytesRead == 1) {
                if (receiveBuffer[0] == startByte) {
                    startReceived = true;
                } else {
                    garbageCount--;
                    if (garbageCount <= 0)
                        return false;
                } //endif
            } //endif
              //debug_rx_cnt++;
        } //endwhile

//		System_printf("Looped through the rx debug_rx_cnt: %d\n", debug_rx_cnt);
//		System_flush();

        if ((bytesRead = deviceRead(deviceJack, receiveBuffer, 1, 500)) == 1) {
            if (receiveBuffer[0] != secondByte) {
                return false;
            } else {
                bytesRead = deviceRead(deviceJack, receiveBuffer, 1, 500);
                if (bytesRead == 1) {
                    rx_len = receiveBuffer[0];
                    if (rx_len == 0) {
                        return false;
                    } //endif
                } else {
                    return false;
                }
            } //endif

        } //endif
        else {
            return false;
        }

//		System_printf("bytesRead: %d\n", bytesRead);
//		System_flush();

    } //end if (rx_len == 0)

    if (rx_len > 0) {
        bytesRead = deviceRead(deviceJack, receiveBuffer, rx_len + 1, 2000);
        //rx_len + 1 for the checksum byte at the end
        if (bytesRead != (rx_len + 1))
            return false;

        uint8_t calcCS = calcCheckSum(receiveBuffer, rx_len);

        if (calcCS != receiveBuffer[rx_len]) {
            // Checksum error
            return false;
        } //end if

        memcpy(buffer, receiveBuffer, rx_len);
        return true;
    } //end if

    return false;
} //end recvSerialStructMessage
