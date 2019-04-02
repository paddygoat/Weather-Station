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

void loraSetup()
{
  Serial.println("LoRa Sender");
  if (!LoRa.begin(869E6))                        // This is where frequency is set.
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}
void loraSendData()
{ 

}

