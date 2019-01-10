
#include <Arduino.h>

  int ledStateYellow = LOW;
  int ledStateBlue = LOW;
  int ledStateRed = LOW;
  unsigned long previousMillisYellow = 0;
  unsigned long previousMillisBlue = 0;
  unsigned long previousMillisRed = 0;
  const long intervalYellow = 1000;
  const long intervalBlue = 1900;
  const long intervalRed = 2700;

void setupLEDs()
{
  pinMode(8, OUTPUT);  // Yellow
  pinMode(9, OUTPUT);  // Blue
  pinMode(10, OUTPUT); // Red
}

void flashYellowLED()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisYellow >= intervalYellow) 
  {
    previousMillisYellow = currentMillis;
    if (ledStateYellow == LOW) {
      ledStateYellow = HIGH;
    }
    else 
    {
      ledStateYellow = LOW;
    }
    digitalWrite(8, ledStateYellow);
  }
  
  if (currentMillis - previousMillisBlue >= intervalBlue) 
  {
    previousMillisBlue = currentMillis;
    if (ledStateBlue == LOW) {
      ledStateBlue = HIGH;
    }
    else 
    {
      ledStateBlue = LOW;
    }
    digitalWrite(9, ledStateBlue);
  }
}
void flashRedLED()
{
  digitalWrite(10, HIGH);
  previousMillisRed =  millis();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisRed >= intervalRed) 
  {
    previousMillisRed = currentMillis;
    digitalWrite(10, LOW);
  } 
}



