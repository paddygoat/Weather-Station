/*
*/
int ledState_pink = LOW;
int pink_pin = A1;
unsigned long prevMillis_pink = 0;
const long interval_pink = 300;

int ledState_blue = LOW;
int blue_pin = A0;
unsigned long prevMillis_blue = 0;
const long interval_blue = 400;

int ledState_green = LOW;
int green_pin = A3;
unsigned long prevMillis_green = 0;
const long interval_green = 500;

int ledState_yellow = LOW;
int yellow_pin = 13;
unsigned long prevMillis_yellow = 0;
const long interval_yellow = 600;

int ledState_orange = LOW;
int orange_pin = 2;
unsigned long prevMillis_orange = 0;
const long interval_orange = 700;

int ledState_red = LOW;
int red_pin = 4;
unsigned long prevMillis_red = 0;
const long interval_red = 800;

void setup() 
{
  pinMode(pink_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  pinMode(orange_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);

  digitalWrite(pink_pin,LOW);
  digitalWrite(blue_pin,LOW);
  digitalWrite(green_pin,LOW);
  digitalWrite(yellow_pin,LOW);
  digitalWrite(orange_pin,LOW);
  digitalWrite(red_pin,LOW);
  delay(5000);
}

void loop() 
{
  delay(100);
  blinkPinkLED();
  blinkBlueLED();
  blinkGreenLED();
  blinkYellowLED();
  blinkOrangeLED();
  blinkRedLED();
}

void blinkGreenLED() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_green >= interval_green) 
  {
    prevMillis_green = currentMillis;
    if (ledState_green == LOW) 
    {
      ledState_green = HIGH;
    } else {
      ledState_green = LOW;
    }
    digitalWrite(green_pin, ledState_green);
  }
}

void blinkOrangeLED() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_orange >= interval_orange) 
  {
    prevMillis_orange = currentMillis;
    if (ledState_orange == LOW) 
    {
      ledState_orange = HIGH;
    } else {
      ledState_orange = LOW;
    }
    digitalWrite(orange_pin, ledState_orange);
  }
}

void blinkRedLED() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_red >= interval_red) 
  {
    buzz_high();
    prevMillis_red = currentMillis;
    if (ledState_red == LOW) 
    {
      ledState_red = HIGH;
    } else {
      ledState_red = LOW;
    }
    digitalWrite(red_pin, ledState_red);
  }
}

void blinkPinkLED() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_pink >= interval_pink) 
  {
    prevMillis_pink = currentMillis;
    if (ledState_pink == LOW) 
    {
      ledState_pink = HIGH;
    } else {
      ledState_pink = LOW;
    }
    digitalWrite(pink_pin, ledState_pink);
  }
}
void blinkBlueLED() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_blue >= interval_blue) 
  {
    prevMillis_blue = currentMillis;
    if (ledState_blue == LOW) 
    {
      ledState_blue = HIGH;
    } else {
      ledState_blue = LOW;
    }
    digitalWrite(blue_pin, ledState_blue);
  }
}
void blinkYellowLED() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_yellow >= interval_yellow) 
  {
    prevMillis_yellow = currentMillis;
    if (ledState_yellow == LOW) 
    {
      ledState_yellow = HIGH;
    } else {
      ledState_yellow = LOW;
    }
    digitalWrite(yellow_pin, ledState_yellow);
  }
}
void buzz()
{
  for(int i = 350; i > 0 ; --i)
  {
    digitalWrite(32, HIGH);
    delayMicroseconds(400);
    digitalWrite(32, LOW);
    delayMicroseconds(400);
  }
  for(int i = 250; i > 0 ; --i)
  {
    digitalWrite(32, HIGH);
    delayMicroseconds(600);
    digitalWrite(32, LOW);
    delayMicroseconds(600);
  }
}
void buzz_high()
{
  for(int i = 250; i > 0 ; --i)
  {
    digitalWrite(32, HIGH);
    delayMicroseconds(400);
    digitalWrite(32, LOW);
    delayMicroseconds(400);
  }
}
