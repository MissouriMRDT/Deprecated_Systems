const byte DS18B20_ENABLE = 1;
const byte DS18B20_DISABLE = 2;
const byte SHT10_T_ENABLE = 3; 
const byte SHT10_T_DISABLE = 4;

const byte XD28_ENABLE = 9;
const byte XD28_DISABLE = 10;
const byte SHT10_H_ENABLE = 11;
const byte SHT10_H_DISABLE = 12; 
const byte FC28_ENABLE = 13;
const byte FC28_DISABLE = 14;

const int SCI_CMD = 1808;

void setup(){
  roveComm_Begin(192, 168, 1, 135); // predetermined science board IP
  bool xd28_on = false;
  bool sht10_h_on = false;
  bool fc28_on = false;
  bool ds18b20_on = false;
  bool sht10_t_on = false;
  Serial6.begin(9600);
}

void loop(){
   float dataRead;
   int dataID = 0;
   size_t size = 0;
   byte receivedMsg[1];
   
   // Get command from base station
   roveComm_GetMsg(&dataID, &size, receivedMsg);
   
   
   if(dataID == SCI_CMD)
   {
     //////////////////////////  
     // enable devices block //
     //////////////////////////
     switch(receivedMsg[0]){
       case XD28_ENABLE:
         xd28_on = true;
         break; 
       case XD28_DISABLE:
         grove_on = false;
         break;
       case SHT10_H_ENABLE:
         sht10_h_on = true;
         break;
       case SHT10_H_DISABLE:
         sht10_h_on = false;
         break;
       case FC28_ENABLE:
         fc28_on = true;
         break;
       case FC28_DISABLE:
         fc28_on = false;
         break;
       case DS18B20_ENABLE:
-         ds18b20_on = true;
         break;
       case DS18B20_DISABLE:
         ds18b20_on = true;
         break;
       case SHT10_T_ENABLE:
         sht10_t_on = true;
         break;
       case SHT10_T_DISABLE:
         sht10_t_on = false;
         break;
       case DRILL_FWD:
        drill_on = true;
        break;
       case DRILL_STOP: 
        drill_on = false;
        break;
     }
   }
   
   // tell drill to send reading back
   // create delay (while(!available)? handle infs
   // take reading back from drill
   // send back to base station
   
   
   ///////////////////////////
   // Sensor controls block //
   ///////////////////////////
   if(xd28_on) {   
     Serial6.write(XD28_ENABLE);
     dataRead = Serial6.read();
     roveComm_SendMsg(0x728, sizeof(dataRead), dataRead);
   } 
   if(sht10_h_on) {
     Serial6.write(SHT10_H_ENABLE);     
     dataRead = Serial6.read();
     roveComm_SendMsg(0x729, sizeof(dataRead), dataRead);
   }
   if(fc28_on) {
     Serial6.write(FC28_ENABLE);
     dataRead = Serial6.read();
     roveComm_SendMsg(0x72A, sizeof(dataRead), dataRead);
   }
   if(ds18b20_on) {
     Serial6.write(DS18B20_ENABLE);
     dataRead = Serial6.parseFloat();
     roveComm_SendMsg(0x720, sizeof(dataRead), dataRead);
   }
   if(sht10_t_on) {
     Serial6.write(SHT10_T_ENABLE);
     dataRead = Serial6.parseFloat();
     roveComm_SendMsg(0x721, sizeof(dataRead), dataRead);
   }
   
   //////////////////////////
   // Drill controls block //
   //////////////////////////
   if(drill_on) {
     
   }
   else if(!drill_on) {
     
   } 
}

