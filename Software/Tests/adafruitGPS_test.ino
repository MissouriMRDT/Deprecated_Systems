const short BUTTON_PIN = 4;
bool buttonDown;
bool buttonPressed();
void getData();

const short TAPELENGTH = 24;

const short TOTALPOINTS = 100;

int NLoc[TOTALPOINTS];
int ELoc[TOTALPOINTS];
short numPoints = 0;
short numCollected = 0;


void setup() {
  Serial.begin(9600);
  if((15+TAPELENGTH/3)*2 > TOTALPOINTS){
    while(true){
      Serial.write("INCREASE TOTALPOINTS. MUST BE GREATER THAN ");
      Serial.write((15+TAPELENGTH/3)*2);
      Serial.println();
    };
  }  
  
  //NOTE: The following is for keeping track of large number of data points,
  //Move due north/south for all N locations
  //Move due east/west for all E locations
  //This is to test N/S accuracy seperate from E/W accuracy since they are different
  
  for(int i=0;i<=15;i++){
    NLoc[numPoints] = i;
    ELoc[numPoints] = 0;
    numPoints ++;
  }
  for(int i=6;i<=TAPELENGTH/3;i++){
    NLoc[numPoints] = i*3;
    ELoc[numPoints] = 0;
    numPoints ++;
  }
  for(int i=1;i<=15;i++){
    NLoc[numPoints] = 0;
    ELoc[numPoints] = i;
    numPoints ++;
  }
  for(int i=6;i<=TAPELENGTH/3;i++){
    NLoc[numPoints] = 0;
    ELoc[numPoints] = i*3;
    numPoints ++;
  }
  
  Serial.println();
  Serial.println();
  Serial.write("Collect Data for the origin");
  Serial.println();
  
  pinMode(BUTTON_PIN,INPUT);
  buttonDown = false;
  
  //figure out the locations that need measured so they can be output by the data
  
}
     
void loop() {
  //use a button press to signal when a sample needs taken
  if(buttonPressed()){
      if (numCollected < numPoints){
        getData();
        
        delay(100);
        
        Serial.println();
        Serial.println();
        
        if(NLoc[numCollected] == 0 && ELoc[numCollected]==0){
           Serial.write("Collect Data for the origin");
        }
        else if(ELoc[numCollected]==0){
          Serial.write("Input for N ");
          Serial.print(NLoc[numCollected]);
        }
        else{
          Serial.write("Input for E ");
          Serial.print(ELoc[numCollected]);
        }
        Serial.println();
        
      }
      else{
        Serial.write("TOO MANY DATAPOINTS");
      }
  }
}

bool buttonPressed(){
 if(digitalRead(BUTTON_PIN))
  {
     buttonDown = true; 
  }
  else{
    if(buttonDown){
      buttonDown = false;
      return true;
    }
    buttonDown = false;
  }
  return false;
}

void getData(){
  //turn off serial communication from arduino to computer, so gps to computer can occur
      Serial.end();
      
      //allow 2 samples to be taken in case one is interrupted.
      delay(2000);
      
      //stop the gps-computer communication
      Serial.begin(9600);
      numCollected++;
}
