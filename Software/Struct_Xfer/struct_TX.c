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

struct example_struct
{
    //struct example_struct* address;
    uint8_t* address;
    uint8_t size;
    uint8_t* rx_buffer;
    uint8_t rx_len;
    
    int x;
    int y;
    int z;
};


//could create a init struct within each peripheral struct. The init struct for each periph would be identical, containing address, size and rx_buffer members
void example_init(struct example_struct* my_struct)
{
    //my_struct->address = my_struct;
    my_struct->address = (uint8_t*) my_struct;
    my_struct->size = sizeof(*my_struct);
    my_struct->rx_buffer = (uint8_t*) malloc(my_struct->size); //malloc returns a pointer to a block of memory of "size" bytes long
};


//can we declare address,size,rx_buffer etc in this function
void send_struct(void* my_struct, uint8_t size,uint8_t* address)
{
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
    
    example_init(&dog);
    
    
    printf("Value of pointer: %p \n", dog.address);
    printf("Value of size: %d \n", dog.size);
    
    
    
    return 0;
}

