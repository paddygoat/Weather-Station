#include <Wire.h>
#include "SparkFunBME280.h"
BME280 mySensor;

void setupBME280()
{
  Wire.begin();
  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }
}
void BME280Readings()
{
  Serial.print("Humidity: ");
  Serial.println(mySensor.readFloatHumidity(), 0);

  Serial.print("Pressure: ");
  Serial.println(mySensor.readFloatPressure(), 0);

  Serial.print("Alt: ");
  //Serial.print(mySensor.readFloatAltitudeMeters(), 1);
  Serial.println(mySensor.readFloatAltitudeFeet(), 1);

  Serial.print("Temp: ");
  //Serial.print(mySensor.readTempC(), 2);
  Serial.println(mySensor.readTempC(), 2);

}
