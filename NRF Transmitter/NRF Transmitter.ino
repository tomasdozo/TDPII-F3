#include "dht11.h"
#include "RF24.h"

dht11 DHT11;

// Pin connected to dht data
#define DHT11_PIN 2

// Create an RF24 object, used to manipulate the communication between NRF modules
RF24 radio(9, 8);  // Pin numbers for CE and CSN

// Address through which two modules communicate. Any 5-character string
const byte address[6] = "tomas";

// Variables for data
char text[32];
char temperature[4];
char humidity [2]="10";
unsigned int counter = 1;

void setup() {

  // Initialize device.
  while (!radio.begin()) {}

  /* Set power level for NRF transmitter. Availables are:
    - 0. RF24_PA_MIN: -18 dBm
    - 1. RF24_PA_LOW: -12 dBm
    - 2. RF24_PA_HIGH: -6 dBm
    - 3. RF24_PA_MAX: 0 dBm
  */
  radio.setPALevel(RF24_PA_HIGH);  // RF24_PA_MAX is default.

  // Set module as transmitter
  radio.stopListening();
  // Set the address
  radio.openWritingPipe(address);

}

void loop() {
  // Delay between measurements.
  delay(1000);

  // Read data from DHT sensor. Return value is 1 for error and 0 for success
  int chk = DHT11.read(DHT11_PIN);
  
  // Check if data is valid before process it
  if (!chk) {
    // Save temperature read in variable
    dtostrf(DHT11.temperature,4,1,temperature);
    // Save humidity read in variable
    dtostrf(DHT11.humidity,2,0,humidity);

    // Send temperature, humidity and counter to the receiver
    sprintf(text,"Temp: %s C. Hum: %s%%, n: %i",temperature, humidity, counter);
    radio.write(&text, sizeof(text));

    // Increment counter in order to track missing messages
    counter++;
  }

}
