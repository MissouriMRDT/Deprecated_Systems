//Super Lightweight Dynamixel AX-12 Library
//by Andrew Bischoff

#include "dyna.h"



void setRegister(unsigned char ID, unsigned char ins, unsigned char data)
{
    unsigned char Checksum = (~(ID + 4 + 3 + ins + data))&0xFF;
    Serial7.write(0xff);                
    Serial7.write(0xff);
    Serial7.write(ID);
    Serial7.write(4);//length
    Serial7.write(0x03);//write
    Serial7.write(ins);
    Serial7.write(data);
    Serial7.write(Checksum);
    delay(4);        
}

void factoryReset(unsigned char id)
{
    Serial7.write(0xff);                
    Serial7.write(0xff);
    Serial7.write(id);
    Serial7.write(2);//len
    Serial7.write(0x06);//reset instruction
    Serial7.write(~(id + 2+ 0x06));//checksum
    delay(4);        
}

void setRegister2(unsigned char ID, unsigned char ins, int data)
{
    unsigned char dataH = data >> 8;  
    unsigned char dataL = data;
    unsigned char Checksum = (~(ID + 5 + 3 + ins + dataH + dataL))&0xFF;
    Serial7.write(0xff);                
    Serial7.write(0xff);
    Serial7.write(ID);
    Serial7.write(5);//length
    Serial7.write(0x03);//write
    Serial7.write(ins);
    Serial7.write(dataL);
    Serial7.write(dataH);
    Serial7.write(Checksum);
    delay(4);              
}

unsigned int readRegister2(unsigned char ID, unsigned char ins){	
   while(Serial7.available()>0){
      Serial7.read();
   }
    boolean valid = false;
    unsigned char Checksum = (~(ID + 4  + 0x02 + ins + 2));
    Serial7.write(0xff);
    Serial7.write(0xff);
    Serial7.write(ID);
    Serial7.write(4);//length
    Serial7.write(0x02);//read
    Serial7.write(ins);
    Serial7.write(2);
    Serial7.write(Checksum);
    
    for(int i=0;i<8;i++)Serial7.read();
    delay(5);
    
    
    byte buf[8];
    while((Serial7.available() > 0)){
      if(Serial7.read()==255 && Serial7.peek()){
        //possible packet found
        buf[0]=0xff;//ff
        buf[1]=Serial7.read();//ff
        buf[2]=Serial7.read();//id
        buf[3]=Serial7.read();//len
        buf[4]=Serial7.read();//err
        buf[5]=Serial7.read();//par
        buf[6]=Serial7.read();//par
        buf[7]=Serial7.read();//check
        unsigned char checksum = ~(buf[2] + buf[3] + buf[4] + buf[5] + buf[6]);
        if(checksum==buf[7]){
          valid=true;
        }
        else{
          valid=false;
        }
      }
      else{
        Serial7.read();
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

int readRegister(unsigned char ID, unsigned char ins){	
   while(Serial7.available()>0){
      Serial7.read();
   }
    boolean valid = false;
    unsigned char Checksum = (~(ID + 4  + 0x02 + ins + 1));
    Serial7.write(0xff);
    Serial7.write(0xff);
    Serial7.write(ID);
    Serial7.write(4);//length
    Serial7.write(0x02);//read
    Serial7.write(ins);
    Serial7.write(1);
    Serial7.write(Checksum);
    
    for(int i=0;i<7;i++)Serial7.read();
    delay(10);
    
    
    byte buf[7];
    while((Serial7.available() > 0)){
      if(Serial7.read()==255 && Serial7.peek()){
        //possible packet found
        buf[0]=0xff;//ff
        buf[1]=Serial7.read();//ff
        buf[2]=Serial7.read();//id
        buf[3]=Serial7.read();//len
        buf[4]=Serial7.read();//err
        buf[5]=Serial7.read();//par
        buf[6]=Serial7.read();//check
        unsigned char checksum = ~(buf[2] + buf[3] + buf[4] + buf[5]);
        if(checksum==buf[6]){
          valid=true;
        }
        else{
          valid=false;
        }
      }
      else{
        Serial7.read();
      }      
    } 
    
    if(valid)
      return (buf[5]);
    else
      return -1;
}




