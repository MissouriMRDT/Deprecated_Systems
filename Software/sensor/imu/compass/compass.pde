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
float maxtarget = 1;
float mintarget = -maxtarget;
int windowsize = 800;
float radius = (.8*windowsize)/2;  

void setup () {
  // set the window size:
  size(windowsize, windowsize); 

  // List all the available serial ports
  println(Serial.list());
  // I know that the first port in the serial list on my mac
  // is always my  Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[0], 115200);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  background(0);
}
void draw () {
  // draw compass template
    translate(width/2, height/2);
    stroke(255,255,255); strokeWeight(1); 
    noFill();
    ellipseMode(RADIUS);
    ellipse(0, 0, radius, radius); // circle
    line(-width/2, 0, width/2, 0); // x axis
    line(0, -height/2, 0, height/2); // y axis
    char c; float cx; float cy;
    c = 'N'; cx = 0; cy = -radius; text(c, cx + .01*windowsize, cy - .01*windowsize);
    c = 'E'; cx = radius; cy = 0; text(c, cx + .01*windowsize, cy - .01*windowsize);
    c = 'S'; cx = 0; cy = radius; text(c, cx + .01*windowsize, cy - .01*windowsize);
    c = 'W'; cx = -radius; cy = 0; text(c, cx + .01*windowsize, cy - .01*windowsize);
    delay(10);
}

void serialEvent (Serial myPort) {
  background(0);
    
  // get the ASCII string:
  String theta_string = myPort.readStringUntil('\n'); // expects raw heading angle
  println(theta_string);

  if (theta_string != null) {
    
    // Expects serial out to be "[heading1 in rads],[heading2 in rads]"
    float[] thetas = float(split(theta_string,","));
//    String theta0_string = thetas[0];
//    String theta1_string = thetas[1];
//    println(thetas);
    // trim off any whitespace:
//    theta0_string = trim(theta0_string);
//    theta1_string = trim(theta1_string);
    float theta0 = thetas[0]; // heading
    float theta1 = thetas[1]; // yaw
    println(theta_string);
    theta0 -= PI/2;
    theta1 -= PI/2;
    
    // Convert polar to cartesian
    float x0 = radius * cos(theta0);
    float y0 = radius * sin(theta0);
    float x1 = radius * cos(theta1);
    float y1 = radius * sin(theta1);
    
    // draw the line:
    strokeWeight(4); 
    stroke(127, 34, 255); // purple = heading
    line(0, 0, x0, y0); // draw unfilled line plot - line(x1, y1, x2, y2)
    stroke(34, 255, 127); // green = yaw
    line(0, 0, x1, y1); // draw unfilled line plot - line(x1, y1, x2, y2)
  }
}

