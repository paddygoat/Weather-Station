#include <SPI.h>
#include <LoRa.h>
#include <ros.h>
#include <std_msgs/String.h>

// ros::NodeHandle  nh;
// std_msgs::String str_msg;
// ros::Publisher chatter("correction_data_from_nest", &str_msg);

const long frequency = 433.5E6;  // LoRa Frequency
int spreading = 12;             // spreading factor ranges from 6-12,default 7 see API docs
const int csPin = 39;          // LoRa radio chip select
const int resetPin = 18;        // LoRa radio reset
const int irqPin = 20;          // change for your board; must be a hardware interrupt pin

int ledState_03 = LOW;
unsigned long prevMillis_03 = 0;
const long interval_03 = 1400;

int ledState_green = LOW;
unsigned long prevMillis_green = 0;
const long interval_green = 1000;

int ledState_orange = LOW;
unsigned long prevMillis_orange = 0;
const long interval_orange = 500;

int ledState_red = LOW;
unsigned long prevMillis_red = 0;
const long interval_red = 100;

String correction_data = "";

String outgoing;              // outgoing message
byte msgCount = 0x00;            // count of outgoing messages
byte localAddress = 0xBB;     // address of this device
byte destination = 0xFF;      // destination to send to
long lastSendTime = 0;        // last send time
byte previous_incomingMsgId = 0x00;

char inChar[256];
char inChar_temp[8];
char inChar_mois[8];
int tempInt =0;
int j = 0;
int k = 0;
bool started = false;

void setup() 
{
  Serial.begin(57600);
  // while (!Serial);

  // nh.initNode();
  // nh.advertise(chatter);

  tone(4, 2000, 200);
  delay(200);
  tone(4, 1000, 200);
  delay(200);

  pinMode(16, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);

  digitalWrite(16,LOW);
  digitalWrite(14,LOW);
  digitalWrite(12,LOW);
  // digitalWrite(6,HIGH);
  // digitalWrite(7,HIGH);
  // digitalWrite(8,HIGH);
  // delay(500);
  // digitalWrite(16,LOW);
  // digitalWrite(6,LOW);
  // digitalWrite(7,LOW);
  // digitalWrite(8,LOW);

  // Serial.println("LoRa Receiver Callback");

  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  if (!LoRa.begin(frequency)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setSpreadingFactor(spreading);           // ranges from 6-12,default 7 see API docs
  LoRa.setSyncWord(0x34);
  // Serial.println("LoRa init succeeded.");
  // LoRa.setGain(6);   // Ranges from 0 to 6 where 6 is max.
  // LoRa.writeRegister(0x0C,0x23);  // This should be max LNA gain.
  
  // Serial.println("LoRa init succeeded.");
  // Serial.println("LoRa.setSignalBandwidth: ");
  LoRa.setSignalBandwidth(500000);
  // Serial.print("LoRa.getSignalBandwidth: ");Serial.println(LoRa.getSignalBandwidth());
  // Serial.print("LoRa.getSpreadingFactor: ");Serial.println(LoRa.getSpreadingFactor());
  // Serial.print("LoRa.readRegister RegModemConfig1(0x1d): ");Serial.print("B");Serial.println(LoRa.readRegister(0x1d),BIN);
  // Serial.print("LoRa.readRegister RegPaDac(high power)(0x4d): "); Serial.print("0x");Serial.println(LoRa.readRegister(0x4d),HEX);
  // Serial.print("LoRa.readRegister RegLna(0x0C): ");Serial.print("B");Serial.println(LoRa.readRegister(0x0C),BIN);
  byte b = B00100011; // = "00100011";
  // Serial.print("Convert b to hex value: ");Serial.print("0x");Serial.println (b, HEX); // comes to 0x23.
  
  // Uncomment the next line to disable the default AGC and set LNA gain, values between 1 - 6 are supported
  // LoRa.setGain(6);
  
  // register the receive callback
  LoRa.onReceive(onReceive);

  // put the radio into receive mode
  LoRa.receive();
}

void loop() 
{
  delay(50);
  if ((tempInt > 20) && (tempInt < 31) && (started == true))
  {
    blinkGreenLED_16();
    // digitalWrite(16,LOW);
    digitalWrite(14,LOW);
    digitalWrite(12,LOW);
  }
  if (((tempInt > 30) && (tempInt < 41) && (started == true))||((tempInt > 10) && (tempInt < 21) && (started == true)))
  {
    blinkOrangeLED_14();
    digitalWrite(16,LOW);
    // digitalWrite(14,LOW);
    digitalWrite(12,LOW);
  }
  if ((tempInt > 40) || (tempInt < 11) && (started == true))
  {
    blinkRedLED_12();
    digitalWrite(16,LOW);
    digitalWrite(14,LOW);
    // digitalWrite(12,LOW);
  }
}

void onReceive(int packetSize) 
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

  float tempFloat = tempStr.toFloat();
  int moisInt = moisStr.toInt();
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
  tone(4, int(tempFloatCubed), 200);
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
}


void blinkLED_5() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_03 >= interval_03) 
  {
    prevMillis_03 = currentMillis;
    if (ledState_03 == LOW) 
    {
      ledState_03 = HIGH;
    } else {
      ledState_03 = LOW;
    }
    digitalWrite(13, ledState_03);
  }
}

void blinkGreenLED_16() 
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
    digitalWrite(16, ledState_green);
  }
}

void blinkOrangeLED_14() 
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
    digitalWrite(14, ledState_orange);
  }
}

void blinkRedLED_12() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis_red >= interval_red) 
  {
    prevMillis_red = currentMillis;
    if (ledState_red == LOW) 
    {
      ledState_red = HIGH;
    } else {
      ledState_red = LOW;
    }
    digitalWrite(12, ledState_red);
  }
}
