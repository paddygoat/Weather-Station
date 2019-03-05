#include <Arduino.h>
unsigned long  previousMillisBeat;
int intervalBeat = 500;
int beatState = LOW;

void setupHeartBeat()
{
  pinMode(8, OUTPUT);  // HIGH disables watchdog
  pinMode(9, OUTPUT);  // pulse to enable
  digitalWrite(8, LOW);
}

void heartBeat()
{
  
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
    digitalWrite(9, beatState);
    digitalWrite(6, beatState);  // Red LED.
    //tone(8,100,100);
  }

}

void beat()
{
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







