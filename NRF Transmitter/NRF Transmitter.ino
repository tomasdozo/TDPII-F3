#include <SPI.h>
#include "RF24.h"

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
const byte address[6] = "tomas";
char text[32];
unsigned int counter = 1;

void setup() {
  Serial.begin(9600);

  // Initialize device.
  if (!radio.begin()) {
    Serial.println("radio hardware is not responding!!");
    while (1) {}    
  }

  //Set module as transmitter
  radio.stopListening();

  //set the address
  radio.openWritingPipe(address);
}

void loop() {
  // Delay 1 second between messages.
  delay(1000);
  sprintf(text,"Example message, n: %i", counter);
  if(radio.write(&text, sizeof(text))){
    // Mensaje recibido
    Serial.print("SUCCESS! n: ");
  } else {
    // Mensaje no recibido
    Serial.print("FAILURE! n: ");
  }

  Serial.println(counter);
  Serial.println("-----------------------------");
  counter++;
}