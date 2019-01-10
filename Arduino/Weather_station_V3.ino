
#include "LEDs.h"
#include "soil.h"
#include "BME280.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "counters.h"
#include <Arduino.h>
#include "batteryVolts.h"

unsigned long previousMillisSensors = 0;
const long intervalSensors = 10000;              // Interval to take reading on all sensors other than wind.
const byte interruptPinA = 1;
int rainValue = 0;
int rainValuex2 =0;
//int z = -1;                     // This is the cycle counter and gets reset to zero on successful call back from the server recieving the data.

// Data wire is plugged into port 7 on the Arduino
#define ONE_WIRE_BUS 7
 
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
// arrays to hold device address
DeviceAddress soilThermometer;
////////////////////////////////////////////////////////////////////////////
  
void setup()
{
  pinMode(interruptPinA, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPinA), rain, CHANGE);  // Triggers void rain().
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

  if (!sensors.getAddress(soilThermometer, 0)) Serial.println("Unable to find address for Device 0"); 

  // show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress(soilThermometer);
  Serial.println();

  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(soilThermometer, 12);
 
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(soilThermometer), DEC); 
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
    sensors.requestTemperatures(); // Send the command to get temperatures
    printTemperature(soilThermometer);
    tone(3,1000,100);
    BME280Readings();
    batteryVolts();
    Serial.print("Battery volts: ");Serial.println(batteryVoltsValue);
    soil();            // Read soil moisture.
    rainValue = rainValuex2/2;
    Serial.print("Rain Value: ");Serial.println(rainValue);
  }

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
void rain()
{
  //flashRedLED(); .... Cant use millis.
  rainValuex2 ++;
  Serial.print("Rain interupt: ");Serial.println(rainValuex2);
}

