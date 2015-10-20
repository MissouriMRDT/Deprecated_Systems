//includes IPAddress, EthernetClient, EthernetServer
#include "Ethernet.h"

//hard code base stations port
#define REDS_IP_PORT 11000

//hardcode base stations IP address
#define REDS_IP_ADDR 192,168,1,2

//hardcode base stations IP address
#define HORIZONS_IP_ADDR 192,168,1,22

//horizon struct_id protocol
#define motor_drive_left_cmd 100
#define motor_drive_right_cmd 101

//void roveDriveMotor_ByPWM(PWM_Handle tivaPin, int motor_speed);

//change this to your own shields mac address from the back sticker labeled MAC ADDR
byte judahs_TivaC_MAC_ADDR[] = { 0x00, 0x1A, 0xB6, 0x02, 0xE7, 0x50 }; 

//hard code rover IP address
IPAddress Rover_IP_ADDR(HORIZONS_IP_ADDR);

//hard code base stations IP address
IPAddress BaseStation_IP_ADDR(REDS_IP_ADDR);
 
EthernetClient BaseStation;

boolean connected_flag;

char message_cntrl_id;

char struct_id;

int motor_speed;
  

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
    
    while( BaseStation.available() ){
      
      //work around from the old protocol
      message_cntrl_id = BaseStation.read();
      
      Serial.print("message_cntrl_id:");
      Serial.println(message_cntrl_id);
      
      struct_id = BaseStation.read();
      
      Serial.print("struct_id:");
      Serial.println(struct_id);
      
      motor_speed = BaseStation.read();
      
      switch(struct_id){
      
        case motor_drive_left_cmd:
        
          Serial.print("Motor drive left at:");
          Serial.println(motor_speed, DEC);
        
          break;
      
        case motor_drive_right_cmd: 
        
          Serial.print("Motor drive right at:");
          Serial.println(motor_speed, DEC);
          
          break; 
        
        default:
         
          Serial.print("Not a motor command:");
          Serial.println(struct_id, DEC);
 
   
          break;
        
      }//endswitch
      
      struct_id = NULL;
  
    }//end while
    
    Serial.println("No message available");
    
    if(!BaseStation.connected() ){
    
      connected_flag = false;
    
    }//endif
    
  }//end while
    
  Serial.println("Connection failed, Attempt to retry connect in 5 seconds");
    
  delay(5000);
  
}//endloop
/*
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
