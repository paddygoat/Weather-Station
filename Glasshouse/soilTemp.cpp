
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

float soilTemp =0;

// Data wire is plugged into port 0 on the Arduino
#define ONE_WIRE_BUS 0
 
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
// arrays to hold device address
DeviceAddress soilThermometer;

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
  soilTemp = sensors.getTempC(deviceAddress);
  //Serial.print("Soil temp C: ");  Serial.println(soilTemp);
}
void setupSoilTemp()
{

  delay(2000);
  Serial.println("Starting ..... ");

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
  Serial.println("");

} // setup

void soilTempFunction()
{
    tone(3,1000,100);
    sensors.requestTemperatures(); // Send the command to get temperatures
    printTemperature(soilThermometer);
    delay(2000);
} // loop
// function to print a device address



