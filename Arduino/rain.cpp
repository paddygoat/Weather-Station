#include <Arduino.h>
const int rainPin = A0;
int rainValuex1 = 0;
int rainReading =0;

void setupRain()
{
  rainReading = analogRead(rainPin);       // If rain detected, capacitor discharges.
  Serial.println("");
  Serial.print("rainReading 0: ");  Serial.println(rainReading);
}

void rainDetect()
{
    // Capacitor is charged from the red LED pin D0.
    delay(50);
    rainReading = analogRead(rainPin);       // If rain detected, capacitor discharges.
    Serial.println("");
    Serial.print("rainReading 1: ");  Serial.print(rainReading);

    if (rainReading < 80)
    {
      rainValuex1++;
    }
    Serial.print("    rainValuex1: ");  Serial.println(rainValuex1);
    Serial.println("");

    if(  rainValuex1 >0 )
    {
      digitalWrite(1,HIGH);      // Yellow LED
    }
    else
    {
      digitalWrite(1,LOW);      // Yellow LED
    }
}
