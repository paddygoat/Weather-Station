
#include <Arduino.h>


int moisturePowerPin = A4;
int sensorPin = A2;    
int moisture = 0;  // variable to store the value coming from the moisture sensor


void soilSetup()
{
  pinMode(moisturePowerPin, OUTPUT);
  digitalWrite(moisturePowerPin, LOW); 
}

void soil()
{
  digitalWrite(moisturePowerPin, HIGH);              // Powers up the moisture sensor for 0.1 seconds to prevent corrosion.
  delay (20);
  int i = 0;
  moisture = 0;
  while(i <5)
  {
    moisture = moisture +(analogRead(sensorPin)*0.120)-19;
    delay(10);
    i++;
  }
  moisture = moisture / i;
  digitalWrite(moisturePowerPin, LOW);               // Powers down the moisture sensor
  //Serial.print("Soil moisture: "); Serial.print(moisture); Serial.println(" %");
}

