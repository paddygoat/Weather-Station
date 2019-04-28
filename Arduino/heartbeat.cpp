#include <Arduino.h>
int beatState = LOW;
const int enablePin = 12;
const int pulsePin = 11;

void setupHeartBeat()
{
  pinMode(pulsePin, OUTPUT);      // Pulse watchdog
  pinMode(enablePin, OUTPUT);     // Enable watchdog
  digitalWrite(enablePin, HIGH);  // HIGH enables watchdog
}

void heartBeat()
{
  beatState = HIGH;
  digitalWrite(11, beatState);
  //digitalWrite(0, beatState);  // Red LED
  //tone(5,1300,10);
  delay(10);
  beatState = LOW;
  digitalWrite(11, beatState);
  digitalWrite(0, beatState);
  Serial.print(" ... BEAT ... ");
}
