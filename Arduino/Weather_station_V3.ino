#include "Mega.h"
#include "LEDs.h"
#include "soil.h"
#include "BME280.h"
#include <OneWire.h>
#include <DallasTemperature.h>
//#include "rain.h"
#include <Arduino.h>

unsigned long previousMillisSensors = 0;
const long intervalSensors = 10000;              // Interval to take reading on all sensors other than wind.

// Data wire is plugged into port 7 on the Arduino
#define ONE_WIRE_BUS 7
 
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device address
DeviceAddress insideThermometer;
////////////////////////////////////////////////////////////////////////////
  
void setup()
{
  Serial.begin(96000);
  delay(2000);
  Serial.println("Starting ..... ");

  // locate devices on the bus
  Serial.print("Locating devices...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0"); 

  // show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();

  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(insideThermometer, 9);
 
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC); 
  Serial.println();

  setupLEDs();
  setupBME280();
  soilSetup();
  tone(3,1000,100);
  
} // setup

void loop()
{
  flashYellowLED();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisSensors >= intervalSensors)
  {
    previousMillisSensors = currentMillis;
    Serial.println("");
    // call sensors.requestTemperatures() to issue a global temperature 
    // request to all devices on the bus
    sensors.requestTemperatures(); // Send the command to get temperatures
  
   // It responds almost immediately. Let's print out the data
    printTemperature(insideThermometer); // Use a simple function to print out the data

    tone(3,1000,100);
    BME280Readings();
    soil();            // Read soil moisture.
  }
  //delay(500);
} // loop


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Soil temp C: ");
  Serial.println(tempC);
}
