#include "Mega.h"
#include "LEDs.h"
//#include "soil.h"
#include "BME280.h"
//#include "rain.h"
#include <Arduino.h>
////////////////////////////////////////////////////////////////////////////
  //int ledState = LOW; 
  //unsigned long previousMillis = 0;  
  //const long interval = 1000;   
void setup()
{
  //pinMode(8, OUTPUT);
  Serial.begin(96000);
  delay(2000);
  Serial.println("Starting ..... ");
  setupLEDs();
  setupBME280();
  
} // setup

void loop()
{
  flashYellowLED();
  tone(3,1000,100);
  BME280Readings();
  delay(500);
} // loop
