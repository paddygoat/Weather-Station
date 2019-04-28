#include <Arduino.h>
const int rainPin = A0;
int rainValuex1 = 0;

void setupRain()
{
  analogWrite(A0,500);
  delay(500);
  int rainReading = analogRead(rainPin);       // If rain detected, capacitor discharges.
  //Serial.println("");
  Serial.print("rainReading 0: ");  Serial.println(rainReading);
}

void rainDetect()
{
    int rainReading = analogRead(rainPin);       // If rain detected, capacitor discharges.
    //Serial.println("");
    Serial.print("rainReading 1: ");  Serial.print(rainReading);
    if (rainReading < 100)
    {
      rainValuex1++;
    }
    delay(100);
    analogWrite(A0,500);                         // Charge the capacitor.
    rainReading = analogRead(rainPin);
    Serial.print("    rainReading 2: ");  Serial.print(rainReading);
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
