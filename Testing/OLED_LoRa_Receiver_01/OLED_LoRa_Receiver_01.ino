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
String moisStr;
float tempFloat = 999.0;
int moisInt;
int count = 1000;

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

void cbk(int packetSize) 
{
  memset (inChar, 0, sizeof(inChar));
  // digitalWrite(12, HIGH-digitalRead(12));   // toggle the led
  // digitalWrite(14, HIGH-digitalRead(14));   // toggle the led
  // digitalWrite(16, HIGH-digitalRead(16));   // toggle the led
  // received a packet
  // Serial.print("Received packet: '");

  // read packet header bytes:
  // int recipient = LoRa.read();          // recipient address
  // byte sender = LoRa.read();            // sender address
  // byte incomingMsgId = LoRa.read();     // incoming msg ID
  // byte incomingLength = LoRa.read();    // incoming msg length
  // byte crc = LoRa.read();    // incoming crc value

  // read packet
  j = 0;
  k = 0;
  for (int i = 0; i < (packetSize); i++) 
  {
    inChar[i] = (char)LoRa.read();
    // Serial.print(inChar[i]);
    // Look for the first gap:
    if (inChar[i] == ' ')
    {
      // Serial.print("i: ");Serial.print(i);Serial.print(" ");
      if (j == 0)
      {
        j = i;
      }
      else
      {
        k = i;
      }
    }
  }
  // Serial.println("");
  inChar_temp[0] = inChar[j+1];
  inChar_temp[1] = inChar[j+2];
  inChar_temp[2] = inChar[j+3];
  inChar_temp[3] = inChar[j+4];
  inChar_temp[4] = inChar[j+5];
  inChar_mois[0] = inChar[k+1];
  inChar_mois[1] = inChar[k+2];
  inChar_mois[2] = inChar[k+3];
  inChar_mois[3] = inChar[k+4];
  inChar_mois[4] = inChar[k+5];
  // Serial.print(" inChar_temp: ");Serial.print(inChar_temp);Serial.print(" ");
  String tempStr = inChar_temp;
  String moisStr = inChar_mois;
  tempInt = tempStr.toInt();

  tempFloat = tempStr.toFloat();
  moisInt = moisStr.toInt();
  // Serial.print(" tempFloat: ");Serial.print(tempFloat);Serial.print(" ");
  float tempFloatCubed = tempFloat*tempFloat*tempFloat*tempFloat/450;
  Serial.print("tempFloat: ");Serial.print(tempFloat); // Serial.print(", ");
  Serial.print(" moisInt: ");Serial.println(moisInt); // Serial.print(", ");
  // Serial.println("");
  // Serial.print(" tempFloatCubed: ");Serial.print(tempFloatCubed);Serial.print("");
  if (tempFloatCubed < 100)
  {
    tempFloatCubed = 100;
  }
  // tone(4, int(tempFloatCubed), 200);
  delay(200);
  
  // Serial.print("'");
  // print RSSI of packet
  // Serial.print(" with RSSI ");
  // Serial.println(LoRa.packetRssi());
  // Serial.println("Message recipient: " + String(recipient));
  // Serial.println("Message sender: " + String(sender));
  // Serial.println(" Message ID: " + String(incomingMsgId));
  // Serial.println("Message incomingLength: " + String(incomingLength));


  // str_msg.data = inChar;
  // char hello[13] = "hello world!";
  // str_msg.data = hello;
  // chatter.publish( &str_msg );
  // nh.spinOnce();
  started = true;
  // LoRaData();
  buzz_high();
  display_results();
}

void setup() 
{
  pinMode(32, OUTPUT);
  buzz();
   //WIFI Kit series V1 not support Vext control
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
