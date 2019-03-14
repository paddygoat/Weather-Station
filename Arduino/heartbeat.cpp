#include <Arduino.h>
unsigned long  previousMillisBeat;
int intervalBeat = 500;
int beatState = LOW;

void setupHeartBeat()
{
  pinMode(8, OUTPUT);    // Pulse watchdog
  pinMode(9, OUTPUT);    // LOW enables watchdog
  digitalWrite(9, HIGH);  // LOW enables watchdog
}

void heartBeat()
{
  digitalWrite(9, LOW);  // LOW enables watchdog
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisBeat >= intervalBeat) 
  {
    previousMillisBeat = currentMillis;
    if (beatState == LOW) 
    {
      beatState = HIGH;
      //Serial.println(".. BEAT ..");
    }
    else 
    {
      beatState = LOW;
    }
    digitalWrite(8, beatState);
    digitalWrite(6, beatState);  // Red LED.
    //tone(8,100,100);
  }

}

void beat()
{
  digitalWrite(9, LOW);  // LOW enables watchdog
  if (beatState == LOW) 
  {
    beatState = HIGH;
  }
  else 
  {
    beatState = LOW;
  }
  digitalWrite(8, beatState);
}







