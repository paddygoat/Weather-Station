/*
*/
#include "heltec.h" 
#include "images.h"

#define BAND    433.5E6  //you can set band here directly,e.g. 868E6,915E6


int ledState_pink = LOW;
int pink_pin = 0;
unsigned long prevMillis_pink = 0;
const long interval_pink = 300;

int ledState_blue = LOW;
int blue_pin = 23;
unsigned long prevMillis_blue = 0;
const long interval_blue = 700;

int ledState_green = LOW;
int green_pin = 17;
unsigned long prevMillis_green = 0;
const long interval_green = 1000;

int ledState_yellow = LOW;
int yellow_pin = 13;
unsigned long prevMillis_yellow = 0;
const long interval_yellow = 600;

int ledState_orange = LOW;
int orange_pin = 12;
unsigned long prevMillis_orange = 0;
const long interval_orange = 500;

int ledState_red = LOW;
int red_pin = 33;
unsigned long prevMillis_red = 0;
const long interval_red = 1000;

String rssi = "RSSI --";
String packSize = "--";
String packet ;
int spreading = 12;

char inChar[256];
char inChar_temp[8];
char inChar_mois[8];
int tempInt =0;
int j = 0;
int k = 0;
bool started = false;

String tempStr;
char tempChar[60];
String moisStr;
char moisChar[60];
float tempFloat = 999.0;
int moisInt;
int count = 1000;
int detection = false;

int serialState = LOW;
unsigned long prevMillis_Serial = 0;
unsigned long interval_serial_check = 1.5 * 60 * 1000;

String glasshouseHeader = "#<~";
String detectionHeader = "@>#";
char header[50];
char threeDArray[2][6][50];
int glasshouse = 0;
char dataToSendArray[256][64];
int serial_unavailable_count =0;

void logo(){
  Heltec.display->clear();
  Heltec.display->drawXbm(0,5,logo_width,logo_height,logo_bits);
  Heltec.display->display();
}
void display_results() 
{
  // unsigned long currentMillis_display = millis();
  // if ((currentMillis_display - prevMillis_display >= interval_display) && (tempFloat != 999.0))
  // {
    Heltec.display->clear();
    // Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    // Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(0, 0, "Temp: ");
    Heltec.display->drawString(40, 0, String(tempFloat));
    Heltec.display->drawString(80, 0, "ºC");
    Heltec.display->drawString(0, 15, "Soil moisture: ");
    Heltec.display->drawString(70, 15, String(moisInt));
    Heltec.display->display();
    // prevMillis_display = currentMillis_display;
}
void LoRaData()
{
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0 , 15 , "Received "+ packSize + " bytes");
  Heltec.display->drawStringMaxWidth(0 , 26 , 128, packet);
  Heltec.display->drawString(0, 0, rssi);  
  Heltec.display->display();
}

char parseIncoming(int packetSize)
{
  // Serial.print("inChar: ");Serial.println(inChar);
  glasshouseHeader.toCharArray(header, 50);
  if ((inChar[0]==header[0])&&(inChar[1]==header[1])&&(inChar[2]==header[2]))
  {
    glasshouse = 1;
  }
  if (glasshouse == 1)
  {
    int digit = 0;
    int space = 0;
    int period = 0;
    int brackets = 0;
    int colons = 0;
    int underScore = 0;
    // Serial.println();
    // Serial.println("Correct header was detected.");

    // Serial.println("parse begin:    ");
    int i = 4;
    int j = 0;
    int k = 0;
    int iAdjust = 4;
    int underScoreCount = 0;
    
    for (i = 4 ; i < (packetSize); i++) 
    {
      period = 0;
      brackets = 0;
      colons = 0;
      underScore = 0;
      space = isSpace(inChar[i]);
      digit = isdigit(inChar[i]);
      if (inChar[i]=='.'){period = 1;}
      if (inChar[i]=='_'){underScore = 1;}
      if ((inChar[i]=='[')||(inChar[i]==']')){brackets = 1;}
      if ((inChar[i]==':')||(inChar[i]==';')){colons = 1;}

      if (underScore == 1)
      {
        // Serial.print("underScore_i: ");Serial.println(i);
        underScoreCount++;
        iAdjust = i+1;
      }

      if ((digit == 0)&&(period == 0))
      {
        if (underScoreCount == 0){j=0;}
        if (underScoreCount == 2){j=1;}
        if (underScoreCount == 4){j=2;}
        if (underScore == 0)
        {
          threeDArray[k][j][i-iAdjust] = inChar[i];
        }
      }
      
      if ((digit == 1)||(period == 1))
      {
        if (underScoreCount == 1){j=0;}
        if (underScoreCount == 3){j=1;}
        if (underScoreCount == 5){j=2;}
        if (underScore == 0)
        {
          threeDArray[k+1][j][i-iAdjust] = inChar[i];
        }
      }
    }
    return threeDArray[2][6][50];
    // Serial.print("underScoreCount: ");Serial.println(underScoreCount);
  }
}
void cbk(int packetSize) 
{
  memset (inChar, 0, sizeof(inChar));
  // read packet
  for (int i = 0; i < (packetSize); i++) 
  {
    inChar[i] = (char)LoRa.read();
  } 

  detection = false;
  if (inChar[0] == '@')
  {
  detection = true;
  }

  if (detection != true)
  {
  threeDArray[2][6][50] = parseIncoming(packetSize);
  }
/*
  Serial.print("threeDArray[0][0][i]: ");
  for (int i = 0; i < (packetSize); i++) 
  {
    Serial.print(".");
    Serial.print(threeDArray[0][0][i]);
  }
  Serial.println();
  Serial.print("threeDArray[0][1][i]: ");
  for (int i = 0; i < (packetSize); i++) 
  {
    // threeDArray[0][1][i] = threeDArray[0][1][i+12];
    Serial.print(".");
    Serial.print(threeDArray[0][1][i]);
  }
  Serial.println();
  Serial.print("threeDArray[0][2][i]: ");
  for (int i = 0; i < (packetSize); i++) 
  {
    // threeDArray[0][2][i] = threeDArray[0][2][i+23];
    Serial.print(".");
    Serial.print(threeDArray[0][2][i]);
  }
  Serial.println();

  Serial.print("threeDArray[1][0][i]: ");
  for (int i = 0; i < (packetSize); i++) 
  {
    Serial.print(".");
    // threeDArray[1][0][i] = threeDArray[1][0][i+6];
    Serial.print(threeDArray[1][0][i]);
  }
  Serial.println();
  Serial.print("threeDArray[1][1][i]: ");
  for (int i = 0; i < (packetSize); i++) 
  {
    Serial.print(".");
    // threeDArray[1][1][i] = threeDArray[1][1][i+18];
    Serial.print(threeDArray[1][1][i]);
  }
  Serial.println();
  Serial.print("threeDArray[1][2][i]: ");
  for (int i = 0; i < (packetSize); i++) 
  {
    // threeDArray[1][2][i] = threeDArray[1][2][i+30];
    Serial.print(".");
    Serial.print(threeDArray[1][2][i]);
  }
  Serial.println();Serial.println();
*/
  String tempStr = threeDArray[1][0];  // Note that the last dimension is not given !!
  String moisStr = threeDArray[1][1];

  // Serial.print("tempStr: ");Serial.println(tempStr);
  if (detection != true)
  {
    tempInt = tempStr.toInt();
    tempFloat = tempStr.toFloat();
    moisInt = moisStr.toInt();
  }
  // Serial.print(" tempFloat: ");Serial.print(tempFloat);Serial.print(" ");
  float tempFloatCubed = tempFloat*tempFloat*tempFloat*tempFloat/450;
  // if (detection != true)
  // {
    // Serial.print("");
    // Serial.print("tempFloat: ");Serial.print(tempFloat); // Serial.print(", ");
    // Serial.print(" moisInt: ");Serial.print(moisInt); // Serial.print(", ");
    // Serial.print(" detection: ");Serial.println(detection); // Serial.print(", ");


    // String data_to_send = inChar;
    // Serial.println(data_to_send);
  // }
  // Serial.println("");
  // Serial.print(" tempFloatCubed: ");Serial.print(tempFloatCubed);Serial.print("");
  if (tempFloatCubed < 100)
  {
    tempFloatCubed = 100;
  }
  // tone(4, int(tempFloatCubed), 200);
  delay(200);
  
  started = true;
  buzz_high();
  display_results();
  check_serial_exists();
}

void check_serial_exists()
{
  // Check for a serial connection by way of the transmitted call back:
  // Serial.println("Check for serial connection ....");
  if (Serial.available()) 
  {
    String data_to_send = inChar;
    Serial.println(data_to_send);
    // Serial.println("A serial call back was received.");
    serialState = HIGH;
    digitalWrite(pink_pin,HIGH);
    delay(1000);
    digitalWrite(pink_pin,LOW);
    unsigned long currentMillisSerial = millis();
    prevMillis_Serial = currentMillisSerial;
    serial_unavailable_count = 0;
    // memset (dataToSendArray, 0, sizeof(dataToSendArray));
  }
  if (!Serial.available())
  {
    // Serial.println("No serial call back was received.");
    unsigned long currentMillisSerial = millis();
    if (currentMillisSerial - prevMillis_Serial >= interval_serial_check)
    {
      dataToSendArray[serial_unavailable_count][] = inChar;
      serialState = LOW;
      // No serial was detected in the last interval_serial_check.
      digitalWrite(blue_pin,HIGH);
      delay(1000);
      digitalWrite(blue_pin,LOW);
      serial_unavailable_count = serial_unavailable_count +1;
    }
  }
}

void setup() 
{
  pinMode(32, OUTPUT);
  buzz();
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  LoRa.setSpreadingFactor(spreading);           // ranges from 6-12,default 7 see API docs
  LoRa.setSyncWord(0x34);
  // Serial.println("LoRa.setSignalBandwidth: ");
  LoRa.setSignalBandwidth(500000);
  Heltec.display->init();
  // Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  logo();
  delay(1500);
  Heltec.display->clear();
  
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->drawString(0, 10, "Wait for incoming data...");
  Heltec.display->display();
  
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
  //LoRa.onReceive(cbk);
  Serial.println();
  LoRa.receive();
}

void loop() 
{
  int packetSize = LoRa.parsePacket();
  if (packetSize) { cbk(packetSize);  }
  delay(10);

  if ((tempInt < 16) && (started == true))
  {
    blinkPinkLED();
    // digitalWrite(pink_pin,LOW);
    digitalWrite(blue_pin,LOW);
    digitalWrite(green_pin,LOW);
    digitalWrite(yellow_pin,LOW);
    digitalWrite(orange_pin,LOW);
    digitalWrite(red_pin,LOW);
  }
  if ((tempInt > 15) && (tempInt < 21) && (started == true))
  {
    blinkBlueLED();
    digitalWrite(pink_pin,LOW);
    // digitalWrite(blue_pin,LOW);
    digitalWrite(green_pin,LOW);
    digitalWrite(yellow_pin,LOW);
    digitalWrite(orange_pin,LOW);
    digitalWrite(red_pin,LOW);
  }
  if ((tempInt > 20) && (tempInt < 26) && (started == true))
  {
    blinkGreenLED();
    digitalWrite(pink_pin,LOW);
    digitalWrite(blue_pin,LOW);
    // digitalWrite(green_pin,LOW);
    digitalWrite(yellow_pin,LOW);
    digitalWrite(orange_pin,LOW);
    digitalWrite(red_pin,LOW);
  }
  if ((tempInt > 25) && (tempInt < 31) && (started == true))
  {
    blinkYellowLED();
    digitalWrite(pink_pin,LOW);
    digitalWrite(blue_pin,LOW);
    digitalWrite(green_pin,LOW);
    // digitalWrite(yellow_pin,LOW);
    digitalWrite(orange_pin,LOW);
    digitalWrite(red_pin,LOW);
  }
  if ((tempInt > 30) && (tempInt < 36) && (started == true))
  {
    blinkOrangeLED();
    digitalWrite(pink_pin,LOW);
    digitalWrite(blue_pin,LOW);
    digitalWrite(green_pin,LOW);
    digitalWrite(yellow_pin,LOW);
    // digitalWrite(orange_pin,LOW);
    digitalWrite(red_pin,LOW);
  }
  if ((tempInt > 35) && (started == true))
  {
    blinkRedLED();
    digitalWrite(pink_pin,LOW);
    digitalWrite(blue_pin,LOW);
    digitalWrite(green_pin,LOW);
    digitalWrite(yellow_pin,LOW);
    digitalWrite(orange_pin,LOW);
    // digitalWrite(red_pin,LOW);
  }
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
