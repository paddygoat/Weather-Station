#include <Wire.h>
#include "SparkFunBME280.h"
BME280 mySensor;

float BME280Temperature =0;
float pressure =0;
float humidity =0;

void setupBME280()
{
  Wire.begin();
  mySensor.setI2CAddress(0x76);           // This could possibly also be (0x77)
  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }
}
void BME280Readings()
{
  //Serial.print("Humidity: ");
  //Serial.println(mySensor.readFloatHumidity(), 0);
  humidity = mySensor.readFloatHumidity();
  
  //Serial.print("Pressure: ");
  //Serial.println(mySensor.readFloatPressure(), 0);
  pressure = mySensor.readFloatPressure();
  
  //Serial.print("Alt: ");
  //Serial.print(mySensor.readFloatAltitudeMeters(), 1);
  //Serial.println(mySensor.readFloatAltitudeFeet(), 1);
  
  //Serial.print("BME 260 temp: ");
  //Serial.print(mySensor.readTempC(), 2);
  //Serial.println(mySensor.readTempC(), 2);
  BME280Temperature = mySensor.readTempC();
}
