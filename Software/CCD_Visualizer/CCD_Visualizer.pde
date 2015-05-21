import processing.serial.*;

Serial port;
String input;

void setup()
{
  size(1280, 720);
  println(Serial.list());
  port = new Serial(this, Serial.list()[2], 115200);
  port.clear();
  
  //serialEvent gets called when a '\n' is recvd
  port.bufferUntil('\n');
  noSmooth();
  background(0);
}

void draw()
{
  
}

void serialEvent (Serial port)
{
  background(0);
  float xpos = width;
  float deltaX = 0;
  input = port.readStringUntil('\n');
  //Check for null data
  if(input == null)
    return;  
  String valueStrings[] = split(input, ','); 
  deltaX = float(width) / valueStrings.length;
  
  float val;
  stroke(120, 255, 10);
  strokeWeight(1);
  for(int i = 0; i < valueStrings.length; i++)
  {
    valueStrings[i] = trim(valueStrings[i]);
    val = float(valueStrings[i]);
    val = map(val, 0, 4096, 0, height);
    //probably wrong
    //line(int(xpos), height, int(xpos), int(val));
    point(int(xpos), int(val));
    xpos-=deltaX;
  }
}
  

