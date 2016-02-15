//MS&T MRDT 2016
//Demo code used to control the rover's main camera using push buttons
//Andrew Bischoff



int PWM0 = 23, PWM1 = 24, PWM2 = 25, PWM3 = 26;



int xAxisPin,yAxisPin,centerButtonPin;//TODO

int stickDefault=1024/2,stickTolerance;//TODO


int inputX,inputY, pastX,pastY;
boolean inputCenter, pastCenter;



void setup() {
  Serial.begin(9600);
 // pinMode(pushButton, INPUT);
 
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(6,OUTPUT);
 
 pinMode(PWM0,OUTPUT);
 pinMode(PWM1,OUTPUT);
 pinMode(PWM2,OUTPUT);
 pinMode(PWM3,OUTPUT);
 


 delay(1000);

 
 
}

int mode = 0; // 0=zoom/focus, 1=menu
void loop() {
  
  updateInputs2();
  
  if(mode==0){//focus,zoom
    if(inputY==1 && pastY!=1){//zoom in
      generateSignal(2000,PWM0);
    }
    else if(inputY==-1 && pastY!=-1){//zoom out
      generateSignal(1000,PWM0);
    }
    else if(inputY==0 && pastY!=0){//stop zooming
      generateSignal(1500,PWM0);
    }
    
    if(inputX==1 && pastX!=1){//focus in
      generateSignal(2000,PWM1);
    }
    else if(inputX==-1 && pastX!=-1){//focus out
      generateSignal(1000,PWM1);
    }
    else if(inputX==0 && pastX!=0){//stop focus
      generateSignal(1500,PWM1);
    }
    
    if(inputCenter && !pastCenter){//enter menu
      generateSignal(1500,PWM2);
      generateSignal(2000,PWM2);
      mode=1;
    }
    
  }
  else if(mode==1){//menu
   if(inputY==1 && pastY!=1){//scroll up
     generateSignal(1500,PWM0);
     generateSignal(2000,PWM0);
   }
   if(inputY==-1 && pastY!=-1){//scroll down
     generateSignal(1500,PWM0);
     generateSignal(1000,PWM0);
   }
   if(inputX==1 && pastX!=1){//toggle selection
     generateSignal(1500,PWM1);
     generateSignal(2000,PWM1);
     mode=0;
   }
   if(inputCenter && !pastCenter){//exit menu
     generateSignal(1500,PWM2);
     generateSignal(2000,PWM2);
     mode=0;
     delay(10);
     generateSignal(1500,PWM0);
     generateSignal(1500,PWM1);
     generateSignal(1500,PWM2);
   }
    
  } 
  
  
  delay(50);
}

void updateInputs2(){//buttons
  pastX=inputX;
  pastY=inputY;
  pastCenter=inputCenter;
  
  
  if(digitalRead(5)) inputX=-1;//l
  else if(digitalRead(4)) inputX=1;//r
  else inputX=0;
  
  if(digitalRead(2)) inputY=-1;//d
  else if(digitalRead(3)) inputY=1;//u
  else inputY = 0;
  
  Serial.print("x: ");
  Serial.print(inputX);
  Serial.print(" y: ");
  Serial.print(inputY);
  inputCenter=digitalRead(6);
}

void updateInputs(){
  pastX=inputX;
  pastY=inputY;
  pastCenter=inputCenter;
  
  inputCenter=digitalRead(centerButtonPin);
  
  
  int xAxis = analogRead(xAxisPin);
  int yAxis = analogRead(yAxisPin);
  
  if(xAxis<stickDefault-stickTolerance){
    inputX=-1;
  }
  else if(xAxis>stickDefault+stickTolerance){
    inputX=1;
  }
  else{
    inputX=0;
  }
  
  
  
  if(yAxis<stickDefault-stickTolerance){
    inputX=-1;
  }
  else if(yAxis>stickDefault+stickTolerance){
    inputY=1;
  }
  else{
    inputY=0;
  }
}


void generateSignal(int amt, int pin){
     digitalWrite(pin,1);
    delayMicroseconds(amt);
    digitalWrite(pin,0);
    delayMicroseconds(20000-amt);
}



