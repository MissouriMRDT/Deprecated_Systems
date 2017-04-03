#include "Dynamixel.h"

void Dynamixel::setRegister(unsigned char ID, unsigned char ins, unsigned char data)
{
    unsigned char Checksum = (~(ID + 4 + 3 + ins + data))&0xFF;
    serial.write(0xff);
    serial.write(0xff);
    serial.write(ID);
    serial.write(4);//length
    serial.write(0x03);//write
    serial.write(ins);
    serial.write(data);
    serial.write(Checksum);
    delay(4);
}

void Dynamixel::factoryReset(unsigned char id)
{
    serial.write(0xff);
    serial.write(0xff);
    serial.write(id);
    serial.write(2);//len
    serial.write(0x06);//reset instruction
    serial.write(~(id + 2+ 0x06));//checksum
    delay(4);
}

void Dynamixel::setRegister2(unsigned char ID, unsigned char ins, int data)
{
    unsigned char dataH = data >> 8;
    unsigned char dataL = data;
    unsigned char Checksum = (~(ID + 5 + 3 + ins + dataH + dataL))&0xFF;
    serial.write(0xff);
    serial.write(0xff);
    serial.write(ID);
    serial.write(5);//length
    serial.write(0x03);//write
    serial.write(ins);
    serial.write(dataL);
    serial.write(dataH);
    serial.write(Checksum);
    delay(4);
}

unsigned int Dynamixel::readRegister2(unsigned char ID, unsigned char ins){
   while(serial.available()>0){
      serial.read();
   }
    boolean valid = false;
    unsigned char Checksum = (~(ID + 4  + 0x02 + ins + 2));
    serial.write(0xff);
    serial.write(0xff);
    serial.write(ID);
    serial.write(4);//length
    serial.write(0x02);//read
    serial.write(ins);
    serial.write(2);
    serial.write(Checksum);

    for(int i=0;i<8;i++)serial.read();
    delay(5);


    byte buf[8];
    while((serial.available() > 0)){
      if(serial.read()==255 && serial.peek()){
        //possible packet found
        buf[0]=0xff;//ff
        buf[1]=serial.read();//ff
        buf[2]=serial.read();//id
        buf[3]=serial.read();//len
        buf[4]=serial.read();//err
        buf[5]=serial.read();//par
        buf[6]=serial.read();//par
        buf[7]=serial.read();//check
        unsigned char checksum = ~(buf[2] + buf[3] + buf[4] + buf[5] + buf[6]);
        if(checksum==buf[7]){
          valid=true;
        }
        else{
          valid=false;
        }
      }
      else{
        serial.read();
      }
    }

	unsigned int num = buf[6];
	num = num<<8;
	num+=buf[5];

    if(valid)
      return num;
    else
      return -1;
}

int Dynamixel::readRegister(unsigned char ID, unsigned char ins){
   while(serial.available()>0){
      serial.read();
   }
    boolean valid = false;
    unsigned char Checksum = (~(ID + 4  + 0x02 + ins + 1));
    serial.write(0xff);
    serial.write(0xff);
    serial.write(ID);
    serial.write(4);//length
    serial.write(0x02);//read
    serial.write(ins);
    serial.write(1);
    serial.write(Checksum);

    for(int i=0;i<7;i++)serial.read();
    delay(10);


    byte buf[7];
    while((serial.available() > 0)){
      if(serial.read()==255 && serial.peek()){
        //possible packet found
        buf[0]=0xff;//ff
        buf[1]=serial.read();//ff
        buf[2]=serial.read();//id
        buf[3]=serial.read();//len
        buf[4]=serial.read();//err
        buf[5]=serial.read();//par
        buf[6]=serial.read();//check
        unsigned char checksum = ~(buf[2] + buf[3] + buf[4] + buf[5]);
        if(checksum==buf[6]){
          valid=true;
        }
        else{
          valid=false;
        }
      }
      else{
        serial.read();
      }
    }

    if(valid)
      return buf[5];
    else
      return -1;
}
