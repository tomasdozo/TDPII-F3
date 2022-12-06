// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>
#include "RF24.h"

#define DHTPIN 2  // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE DHT11  // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);
//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
const byte address[6] = "tomas";
char text[32];
char temperature[4];
char humidity [2]="10";
unsigned int counter = 1;


uint32_t delayMS;

void setup() {

  // Initialize device.
  if (!radio.begin()) {
    while (1) {}    
  }
  //Set module as transmitter
  radio.stopListening();
  //set the address
  radio.openWritingPipe(address);

  dht.begin();

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);

  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 500;
}

void loop() {
  // Delay between measurements.
  delay(delayMS);

  // Get temperature event and save its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    dtostrf(event.temperature,4,1,temperature);
  }

  // Get humidity event and save its value.
  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) {
    dtostrf(event.relative_humidity,2,0,humidity);
  }

  sprintf(text,"Temp: %s C. Hum: %s%%, n: %i",temperature,humidity, counter);
  counter++;
}