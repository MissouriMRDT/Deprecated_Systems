import processing.serial.*;

Serial port;
String input;

void setup()
{
  size(1024, 768);
  println(Serial.list());
  port = new Serial(this, Serial.list()[2], 115200);
  port.clear();
  
  //serialEvent gets called when a '\n' is recvd
  port.bufferUntil('\n');
  
  background(0);
}

void draw()
{
  
}

void serialEvent (Serial port)
{
  background(0);
  int xpos = 0;
  int deltaX = 0;
  input = port.readStringUntil('\n');
  //Check for null data
  if(input == null)
    return;  
 
  String valueStrings[] = split(input, ','); 
  deltaX = width / valueStrings.length;
  
  float val;
  stroke(127, 34, 255);
  strokeWeight(2);
  for(int i = 0; i < valueStrings.length; i++)
  {
    valueStrings[i] = trim(valueStrings[i]);
    val = float(valueStrings[i]);
    val = map(val, 0, 4096, 0, height);
    //probably wrong
    line(xpos, height, xpos, val);
    xpos+=deltaX;
  }
}
  

