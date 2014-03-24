//
//  main.c
//  struct_transfer
//
//  Created by Mike Fanger on 3/23/14.
//  Copyright (c) 2014 MRDT. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>

#define start_byte1 0x06
#define start_byte2 0x85

enum peripheral_devices{motor_controller1, motor_controller2, robotic_arm};


struct example_struct
{
    int x;
    int y;
    int z;
};

void send_struct(void* my_struct, enum peripheral_devices device)
{
    uint8_t size;
    
    switch(device)
    {
        case motor_controller1:
        case motor_controller2:
            size = sizeof(*((struct example_struct*)my_struct));
            break;
        case robotic_arm:
            size = sizeof(*((struct example_struct*)my_struct));
            break;
    }
    
    uint8_t* address = (uint8_t*) my_struct;
    uint8_t* rx_buffer = (uint8_t*) malloc(size);
    uint8_t CS = size;
    
    //serial.write(start_byte1);
    //serial.write(start_byte2);
    //serial.write(size);
    for(int i = 0; i<size; i++)
    {
        CS^=*(address+i);
        //serial.write(*(address+i));
    }
    //serial.write(CS);
    
};



int main(int argc, const char * argv[])
{
    
    
    printf("Hello, World!\n");
    
    struct example_struct dog;
    
    
    void* test = &dog;
    uint8_t size = sizeof(*((struct example_struct*)test));
    
    
    
    printf("Value of size: %d \n", size);
    
    
    
    return 0;
}

