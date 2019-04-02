
#include <Arduino.h>

  int ledStateYellow = LOW;
  int ledStateBlue = LOW;
  unsigned long previousMillisYellow = 0;
  unsigned long previousMillisBlue = 0;
  const long intervalYellow = 1000;
  const long intervalBlue = 50;

void setupLEDs()
{
  pinMode(6, OUTPUT);  // Yellow
  pinMode(1, OUTPUT);  // Blue
  pinMode(2, OUTPUT); // Red
}

void flashYellowLED()
{
  if (ledStateYellow == LOW) 
  {
    ledStateYellow = HIGH;
  }
  else 
  {
    ledStateYellow = LOW;
  }
  digitalWrite(2, ledStateYellow);
}
void flashBlueLED()
{  
  if (ledStateBlue == LOW) 
  {
    ledStateBlue = HIGH;
  }
  else 
  {
    ledStateBlue = LOW;
  }
  digitalWrite(1, ledStateBlue);
}
void flashRedLED()
{
  //digitalWrite(6, HIGH);
  //previousMillisRed =  millis();
  //unsigned long currentMillis = millis();
  //if (currentMillis - previousMillisRed >= intervalRed) 
  //{
  //  previousMillisRed = currentMillis;
  //  digitalWrite(10, LOW);
  //} 
}



