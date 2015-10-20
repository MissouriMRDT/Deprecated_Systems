//includes IPAddress, EthernetClient, EthernetServer
#include "Ethernet.h"

//hard code base stations port
#define REDS_IP_PORT 11000

//hardcode base stations IP address
#define REDS_IP_ADDR 192,168,1,2

//hardcode base stations IP address
#define HORIZONS_IP_ADDR 192,168,1,22

//hardcode max base station message size
#define MOTOR_SPEED_BYTE_CNT 5

//horizon struct_id protocol
#define motor_drive_left_cmd 100
#define motor_drive_right_cmd 101

//change this to your own shields mac address from the back sticker labeled MAC ADDR
byte judahs_TivaC_MAC_ADDR[] = { 0x00, 0x1A, 0xB6, 0x02, 0xE7, 0x50 }; 

//hard code rover IP address
IPAddress Rover_IP_ADDR(HORIZONS_IP_ADDR);

//hard code base stations IP address
IPAddress BaseStation_IP_ADDR(REDS_IP_ADDR);
 
EthernetClient BaseStation;

boolean connected_flag;

char motor_speed_buffer[MOTOR_SPEED_BYTE_CNT];

char message_cntrl_id;

char struct_id;

int32_t motor_speed;
  
//execute once
void setup(){
  
  //uart_2
  Serial.begin(9600);
  
  //tcp client
  Ethernet.begin(judahs_TivaC_MAC_ADDR, Rover_IP_ADDR);
  
  //debug to Energia serial monitor
  Serial.println("Horizon Device Init");
  
}//endsetup

//loop forever
void loop(){
   
  // wait for a thousand milliseconds (one second)
  delay(1000);  
  
  //printf a debug message
  Serial.println("Attempt to Connect");
  
  if(BaseStation.connect(BaseStation_IP_ADDR, REDS_IP_PORT) ){
    
    connected_flag = true;
    
  }else{
    
    connected_flag = false;
   
  }//endif 
 
  while(connected_flag == true) {
    
    //printf a debug message
    Serial.println("Connected");
    
    message_cntrl_id = 0;
    struct_id = 0;
    
    if( BaseStation.available() ){
      
      Serial.println("Available");
      
      //work around from the old protocol
      message_cntrl_id = BaseStation.read();
      
      Serial.print("message_cntrl_id byte: ");
      Serial.println(message_cntrl_id, DEC);
            
      //work around from the old protocol
      struct_id = BaseStation.read();
      
      Serial.print("struct_id byte: ");
      Serial.println(struct_id, DEC);
      
      motor_speed_buffer[0]= BaseStation.read();
      motor_speed_buffer[1]= BaseStation.read();
      motor_speed_buffer[2]= BaseStation.read();
      motor_speed_buffer[3]= BaseStation.read();
      motor_speed_buffer[4]= '\0';
          
      //BaseStation.read((unit8_t*)motor_speed_buffer;
      //motor_speed = atoi((char*)motor_speed_buffer);
      
      Serial.print("motor_speed_buffer bytes: ");
      Serial.println(motor_speed_buffer);
      
      motor_speed = (motor_speed_buffer[0] << 24) | (motor_speed_buffer[1] << 16) | (motor_speed_buffer[2] << 8) | motor_speed_buffer[3];

      //BaseStation.read((unit8_t*)motor_speed_buffer;
      //motor_speed = atoi((char*)motor_speed_buffer);
      
      Serial.print("motor_speed: ");
      Serial.println(motor_speed, DEC);
  
  
    }//end if
       
    if(!BaseStation.connected() ){
    
      connected_flag = false;
    
    }//endif
    
  }//end while
    
  Serial.println("Connection failed, Attempt to retry connect in 5 seconds");
    
  delay(5000);
  
}//endloop
/*

//void roveDriveMotor_ByPWM(PWM_Handle tivaPin, int motor_speed);

void roveDriveMotor_ByPWM(PWM_Handle tivaPin, int motor_speed){
  
    int16_t microseconds;

    //scale down to the final range to be between 1000 and 2000
    microseconds = motor_speed / 2;

    //offset so that 1500 is neutral
    microseconds += 1500;

    //protect the upper bound on motor pulse width
    if (microseconds > 2000) {

        microseconds = 2000;

    }//endif

    //protect the lower bound on motor pulse width
    if (microseconds < 1000) {

        microseconds = 1000;

    }//endif
  
    PWM_setDuty(tiva_pin, duty_in_microseconds);
    
    return;
  
}//end function
*/
