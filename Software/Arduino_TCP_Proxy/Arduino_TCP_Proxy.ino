#include <SPI.h>
#include <Ethernet.h>
#include <EasyTransfer.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xAE, 0xEF, 0xFE, 0xE3 };
IPAddress ip(192,168,1,22);
char serverName[] = "";

// Enter the IP address of the server you're connecting to:
IPAddress server(192,168,1,2);
int port = 11000;

//create object
EasyTransfer ET;

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 23 is default for telnet;
// if you're using Processing's ChatServer, use  port 10002):
EthernetClient client;

// Data structure for
// Sending commands to the motherboard
struct cmd_struct{
  int  id;
  uint8_t value;
};

//give a name to the group of data
cmd_struct command;

void setup() {

  
  // start the Ethernet connection:
  Ethernet.begin(mac, ip);
 // Open serial communications and wait for port to open:
  Serial.begin(115200);
  
  // Start Easy Transfer
    ET.begin(details(command), &Serial);
  
  // give the Ethernet shield a second to initialize:
  delay(1000);
  //Attempt connection
  while(!client.connect(server, port));
}

bool end_bracket;
char JSON_string_buf[50] = "";

void loop()
{
  
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    
  ////////////////////////
  // JSON String Buffer
  ////////////////////////
  end_bracket = false;
  
  char tcp_input = client.read();

  //Check if start of JSON string
  if (tcp_input == '{')
  {
    int len=0;

    // Place  into buf
    JSON_string_buf[len] = tcp_input;
    JSON_string_buf[len+1] = '\0';

    // Place rest of JSON string into buf
    while( end_bracket == false )
   {
      // Read char
      tcp_input = client.read();

      // Place char in buf
      len++;
      JSON_string_buf[len] = tcp_input;
      JSON_string_buf[len+1] = '\0';

     // Check for end bracket
     if( tcp_input == '}')
     {
	end_bracket = true;
     }
	
   }
  }
	///////////////
	// JSON Parse
	//
	// Handwritten for now
	//
	// TODO: fix this and make it less brittle
	///////////////

	char Id[5];
	char Value[10];
				
	// Get Id
	Id[0] = JSON_string_buf[6];
	Id[1] = JSON_string_buf[7];
	Id[2] = JSON_string_buf[8];
	Id[3] = JSON_string_buf[9];
	Id[4] = '\0';
	
        // Convert cmd value
	int cmd_value = atoi( Id);

	// Get Value starting at 19
	Value[0] = '\0';
	bool is_end_of_value = false;

	int value_index = 0;
	int json_value_string_index = 19;

	while(is_end_of_value == false)
	{
		//Check for ending } which denotes end of value
		if( JSON_string_buf[json_value_string_index] == '}' )
		{
			is_end_of_value = true;
			Value[value_index] = '\0';
		}
		// this char is a digit of a value
		else
		{
			Value[value_index] = JSON_string_buf[json_value_string_index];
			value_index++;
			json_value_string_index++;
		}
    }
    
    // Convert string value to real value
    byte value_byte = atoi( Value );
    
    // Send data
    command.id = cmd_value;
    command.value = value_byte;
    ET.sendData();
}

// Look for data on serial port
// Send to the base station
if(Serial.available())
{
  while(Serial.available())
  {
     client.write(Serial.read());
  }
}

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    client.stop();
    // and reconnect
    while(!client.connect(server, port));
  }
  
}

