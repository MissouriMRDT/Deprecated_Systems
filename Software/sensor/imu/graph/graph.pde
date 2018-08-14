// Processing code for this example

// Graphing sketch


// This program takes ASCII-encoded strings
// from the serial port at 9600 baud and graphs them. It expects values in the
// range 0 to 1023, followed by a newline, or newline and carriage return

// Created 20 Apr 2005
// Updated 18 Jan 2008
// by Tom Igoe
// This example code is in the public domain.

import processing.serial.*;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
int count;
int numdata = 1;
float maxtarget = 1.1;
float mintarget = -maxtarget;

void setup () {
  // set the window size:
  size(400, 300);        

  // List all the available serial ports
  println(Serial.list());
  // I know that the first port in the serial list on my mac
  // is always my  Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[2], 115200);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  background(0);
  
  count = 0;
}
void draw () {
  // everything happens in the serialEvent()
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n'); // expects 1 to 3 float outputs

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // convert to an int and map to the screen height:
    float inByte = float(inString); 
    inByte = map(inByte, mintarget, maxtarget, 0, height);
    
    // draw the line:
    if(count%numdata==0){
      stroke(127, 34, 255);
    }
    if(count%numdata==1){
      stroke(34, 255, 127);
    }
    if(count%numdata==2){
      stroke(255, 127, 34);
    }
    
//    line(xPos, height/2, xPos, height - inByte); // draw filled in line plot
    strokeWeight(4); line(xPos-1, height - inByte, xPos, height - inByte); // draw unfilled line plot
    
    stroke(255,255,255); strokeWeight(1); line(1, height/2, width, height/2); // draw zero line

    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      count = 0;
      background(0);
    } else {
      // increment the horizontal position:
      xPos = count/numdata;
    }
    count++;  
    println(inString);
  }

}

