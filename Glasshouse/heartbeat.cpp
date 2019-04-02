#include <Arduino.h>
unsigned long  previousMillisBeat;
int intervalBeat = 1500;
int beatState = LOW;
int beats = 0;

void setupHeartBeat()
{
  pinMode(8, OUTPUT);    // Pulse watchdog
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);  // HIGH enables watchdog  
  delay(5000);           // Enables code to be uploaded
  digitalWrite(9, HIGH);  // HIGH enables watchdog
}

void heartBeat()
{
  digitalWrite(9, HIGH);
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisBeat >= intervalBeat) 
  {
    previousMillisBeat = currentMillis;
    if (beatState == LOW) 
    {
      beatState = HIGH;
      Serial.println(".. BEAT ..");
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







