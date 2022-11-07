#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
const byte address[6] = "tomas";
char text[32]="Probando ando";

uint32_t delayMS;

void setup() {
  Serial.begin(9600);

  // initialize the transceiver on the SPI bus
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
  // Delay between measurements.
  delay(1000);

  if (radio.write(&text, sizeof(text))) {
    Serial.println("SUCCESS!");
  } else {
    Serial.println("FAILURE!");
  }
  Serial.println("----------");
}