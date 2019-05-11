
#include <Arduino.h>

  int ledStateYellow = LOW;
  int ledStateRed = LOW;


void setupLEDs()
{
  pinMode(1, OUTPUT);  // Yellow
  pinMode(0, OUTPUT);  // Red
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(0,LOW);
  digitalWrite(1,LOW);
  digitalWrite(LED_BUILTIN,LOW);
}

void flashYellowLED()
{
  digitalWrite(1,HIGH);
  delay(20);
  digitalWrite(1,LOW);
}
void flashRedLED()
{  
  digitalWrite(0,HIGH);
  delay(50);
  digitalWrite(0,LOW);
}
void flashBuiltinLED()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(10);
  digitalWrite(LED_BUILTIN, LOW);
  delay(10);
}

