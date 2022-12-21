//Include Libraries
#include <SPI.h>
#include "RF24.h"


// Create an RF24 object, used to manipulate the communication between NRF modules
RF24 radio(9, 8);  // Pin numbers for CE and CSN

// Address through which two modules communicate. Any 5-character string
const byte address[6] = "tomas";

void setup()
{
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Testing Serial monitor with a welcome message
  Serial.println("Hello World!");

  // Initialize device.
  if (!radio.begin()) {
    Serial.println("radio hardware is not responding!!");
    while (1) {}    
  }
  
  Serial.println("radio initialized");

  // Set the address. The first argument is the number of the stream, we only created one
  radio.openReadingPipe(0, address);
  
  // Set module as receiver
  radio.startListening();

  Serial.println("radio listening");
  Serial.println("-----------------------------");
}

void loop()
{
  // Read the data if available in buffer
  if (radio.available())
  {
    // Create an array of 32 characters filled with zeros 
    char text[32] = {0};
    // Read data from the buffer and store it in the character array
    radio.read(&text, sizeof(text));
    // Print data on the Serial monitor
    Serial.println(text);
    Serial.println("-----------------------------");
  }
}