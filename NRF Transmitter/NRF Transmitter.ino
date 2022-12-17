#include <SPI.h>
#include "RF24.h"

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
const byte address[6] = "tomas";
char text[32];
unsigned int counter = 1;
unsigned int level = 3;
int input;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // testing Serial monitor with a welcome message
  Serial.println("Hello World!");

  // Initialize device.
  if (!radio.begin()) {
    Serial.println("radio hardware is not responding!!");
    while (1) {}    
  }

  // To set the PA level via the Serial monitor on startup
  Serial.println(F("Ingrese el número del nivel de potencia deseado:"));
  Serial.println("0. RF24_PA_MIN");
  Serial.println("1. RF24_PA_LOW");
  Serial.println("2. RF24_PA_HIGH");
  Serial.println("3. RF24_PA_MAX");
  Serial.println("RF24_PA_MAX por defecto");

  bool timeout = false;
  unsigned long now = millis();
  while (!Serial.available() && !timeout) {
    // wait for user input
    timeout = millis() > now + 10000;
  }

  if (!Serial.available()) {
    Serial.println("Se acabó el tiempo, se usa potencia por defecto RF24_PA_MAX");
  } else {
    input = Serial.parseInt(); // Aca seria conveniente chequear que sea un numero antes de parsearlo
    Serial.print(F("Valor ingresado = "));
    if (input >= 0 && input <= 3) {
      level = input;
      Serial.println(input);
    } else {
      Serial.print(input);
      Serial.println(" es incorrecto, se usa potencia por defecto RF24_PA_MAX");
    }
  }

  Serial.print(F("Nivel de potencia inicial = "));
  Serial.println(radio.getPALevel());

  radio.setPALevel(level);  // RF24_PA_MAX is default.

  Serial.print(F("Nivel de potencia configurado = "));
  Serial.println(radio.getPALevel());

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