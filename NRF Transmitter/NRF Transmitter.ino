#include "dht11.h"
#include "RF24.h"

dht11 DHT11;

#define DHT11_PIN 2

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
const byte address[6] = "tomas";
char text[32];
char temperature[4];
char humidity [2]="10";
unsigned int counter = 1;

void setup() {

  // Initialize device.
  if (!radio.begin()) {
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

  int chk = DHT11.read(DHT11_PIN);
  
  if (!chk) {
    Serial.print(F("Temperature: "));
    Serial.print((float)DHT11.temperature, 1);
    Serial.println(F("C"));
    dtostrf(DHT11.temperature,4,1,temperature);

    Serial.print(F("Humidity: "));
    Serial.print((float)DHT11.humidity, 0);
    Serial.println(F("%"));
    dtostrf(DHT11.humidity,2,0,humidity);

    sprintf(text,"Temp: %s C. Hum: %s%%, n: %i",temperature, humidity, counter);
    radio.write(&text, sizeof(text));
    counter++;
  }

}
