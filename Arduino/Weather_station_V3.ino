#include <SPI.h>
#include <LoRa.h>
#include "LEDs.h"
#include "soil.h"
#include "BME280.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "counters.h"
#include <Arduino.h>
#include "batteryVolts.h"
#include "windSpeed.h"
#include "windVane.h"


int count = 0;
unsigned long previousMillisSensors = 0;
const long intervalSensors = 10000;              // Interval to take reading on all sensors other than wind.
unsigned long previousMillisWind = 0;
const long intervalWind = 200;                  // Interval to take reading on wind speed sensors.
unsigned long previousMillisVane = 0;
const long intervalVane = 5000;                  // Interval to take reading on wind vane sensors.
const byte interruptPinA = 1;
int rainValue = 0;
int rainValuex2 =0;
float soilTemp =0;
String initiator = "";
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
  Serial.println("LoRa Sender");
  if (!LoRa.begin(868E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
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
  Serial.println("");

  setupLEDs();
  setupBME280();
  soilSetup();
  setupWindVane();
  tone(3,1000,100);
  Serial.println(" ..... All is good ..... Continuing  .....");
  Serial.println("");
} // setup

void loop()
{
  // dataString =  initiator + webAddress + "tempout="+result102 + "&tempsoil="+result101 + "&windgust="+result103 + "&windspeed="+result104 + "&rain="+result106 + "&moisture="+moisture + "&tempint="+BME280Temperature + "&pressure="+pressure + "&humidity="+humidity + "&volts="+result108 + "&windway="+result107;
  // To add another temperature reading we would need: +"&tempB="+tempB 
  flashYellowLED();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisSensors >= intervalSensors)        // Need relatively low number of samples of temperatures, humidity etc as they dont change quickly.
  {
    previousMillisSensors = currentMillis;
    tone(3,1000,100);
    sensors.requestTemperatures(); // Send the command to get temperatures
    printTemperature(soilThermometer);
    soil();            // Read soil moisture.
    BME280Readings();
    batteryVolts();
    rainValue = rainValuex2/2;
    printToSerial();
    
    String dataString = initiator + "tempout="+BME280Temperature + "&tempsoil="+soilTemp + "&windgust="+knotsMax + "&windspeed="+knotsAv + "&rain="+rainValue + "&moisture="+moisture + "&tempint="+BME280Temperature + "&pressure="+pressure + "&humidity="+humidity + "&volts="+batteryVoltsValue + "&windway="+vaneValue;
    Serial.print("Sending packet: ");
    Serial.print(dataString);
    Serial.print("  ");
    Serial.println(count);
    Serial.println("");
    // send packet
    LoRa.beginPacket();
    LoRa.print(dataString);
    LoRa.print(count);
    LoRa.endPacket();

    count++;
    
  }
  if (currentMillis - previousMillisWind >= intervalWind)             // Need relatively high number of wind samples to catch high wind gusts.
  {
    previousMillisWind = currentMillis;
    windSpeed();
    counter();
  }
  if (currentMillis - previousMillisVane >= intervalVane)             // Need relatively moderate number of wind vane samples as too many wastes power.
  {
    previousMillisVane = currentMillis;
    windVane();
    //counter();
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
  soilTemp = sensors.getTempC(deviceAddress);
  //Serial.print("Soil temp C: ");  Serial.println(soilTemp);
}
void rain()
{
  //flashRedLED(); .... Cant use millis.
  rainValuex2 ++;
  Serial.print("Rain interupt: ");Serial.println(rainValuex2);
}
void printToSerial()
{
  Serial.println("");
  Serial.print("Z: ");Serial.println(z); 
  Serial.print("Soil temp C: ");Serial.println(soilTemp);
  Serial.print("Soil moisture: "); Serial.print(moisture); Serial.println(" %");
  Serial.print("BME 260 temp: "); Serial.println(BME280Temperature);
  Serial.print("BME 260 pressure: "); Serial.println(pressure);
  Serial.print("BME 260 humidiy: "); Serial.println(humidity);
  Serial.print("Battery volts: ");Serial.println(batteryVoltsValue);
  Serial.print("Rain Value: ");Serial.println(rainValue);
  Serial.print("Average wind speed: ");Serial.println(knotsAv);
  Serial.print("Max wind gust: ");Serial.println(knotsMax);
  Serial.print("Wind vane value: ");Serial.println(vaneValue);
  Serial.println("");
}

