#include <SPI.h>
#include <LoRa.h>
#include "soil.h"
#include "BME280.h"
#include "counters.h"
#include <Arduino.h>
#include "batteryVolts.h"
#include "windSpeed.h"
#include "windVane.h"
#include "soilTemp.h"


const long frequency = 869E6;  // LoRa Frequency

const int csPin = 8;          // LoRa radio chip select
const int resetPin = 4;        // LoRa radio reset
const int irqPin = 3;          // change for your board; must be a hardware interrupt pin

void loraSetup()
{
  LoRa.setPins(csPin, resetPin, irqPin);

  if (!LoRa.begin(frequency)) 
  {
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }
  Serial.println("LoRa init succeeded.");
  Serial.println();
}
void loraSendData()
{ 

}

