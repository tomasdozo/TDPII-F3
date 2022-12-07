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
  Serial.begin(9600);
  Serial.println("DHT11 SFE Electronics");

  // Initialize device.
  if (!radio.begin()) {
    Serial.println("radio hardware is not responding!!");
    while (1) {}    
  }
  //Set module as transmitter
  radio.stopListening();
  //set the address
  radio.openWritingPipe(address);

  int chk = DHT11.read(DHT11_PIN);
  Serial.println(chk);
}

void loop() {
  // Delay between measurements.
  delay(1000);

  int chk = DHT11.read(DHT11_PIN);
  
  if (chk) {
    Serial.println(F("Error reading sensor!"));
  } else {
    Serial.print(F("Temperature: "));
    Serial.print((float)DHT11.temperature, 1);
    Serial.println(F("C"));
    dtostrf(DHT11.temperature,4,1,temperature);

    Serial.print(F("Humidity: "));
    Serial.print((float)DHT11.humidity, 1);
    Serial.println(F("%"));
    dtostrf(DHT11.humidity,2,0,humidity);
  }

  sprintf(text,"Temp: %s C. Hum: %s%%, n: %i",temperature, humidity, counter);
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