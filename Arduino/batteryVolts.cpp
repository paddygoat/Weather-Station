#include <Arduino.h>
#include "counters.h"

float volts=0;
float batteryVoltsValue =0;
float totalVolts;

//A2 is analogue in.

void batteryVolts()
{
    volts = analogRead(A2)/28.81;  
    if (z>0)
    {
      totalVolts = (totalVolts + volts);
      batteryVoltsValue = totalVolts/z;    
    }
    else
    {
      batteryVoltsValue = volts;
    }
    //Serial.print("Battery volts: ");Serial.println(batteryVoltsValue);
}
