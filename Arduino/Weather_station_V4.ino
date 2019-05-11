#include <SPI.h>
#include <LoRa.h>
#include "LEDs.h"
#include "soil.h"
#include "BME280.h"
#include "soilTemp.h"
#include "counters.h"
#include <Arduino.h>
#include "batteryVolts.h"
#include "windSpeed.h"
#include "windVane.h"
#include "loraUtil.h"
#include "heartbeat.h"
#include "rain.h"
#include <Adafruit_SleepyDog.h>

float hours = 0;
int count = 0;
unsigned long previousMillisSensors = 0;
const long intervalSensors = 300000;              // Interval to take reading on all sensors other than wind.
unsigned long previousMillisWind = 0;
long intervalWind = 10000;                        // Interval to take reading on wind speed sensors.
unsigned long previousMillisVane = 0;
const long intervalVane = 6000;                  // Interval to take reading on wind vane sensors.
unsigned long previousMillisCallBack = 0;
const long intervalCallBack = 10000;              // Interval to allow time for callback to occurr before next wind reading thus preventing interrupt conficts.
unsigned long previousMillisSlowPrint = 0;
const long intervalSlowPrint = 100;
const int watchdogEnablePin = 12;                // HIGH = enabled.
const int watchdogPulsePin = 11;

int rainValue = 0;
//float soilTemp =0;
String initiator = "";
//int z = -1;                     // This is the cycle counter and gets reset to zero on successful call back from the server recieving the data.
int callBackListeningStatus = 0;
int sleepStatus = 0;
unsigned long currentMillis = 0;
////////////////////////////////////////////////////////////////////////////
  
void setup()
{
  setupHeartBeat();
  pauseWithBeats();                       // Pause allows new code to be uploaded without deep sleep fouling up the upload.
  
  Serial.begin(96000);
  Serial.println("Starting ..... ");
  heartBeat();
  
  setupSoilTemp();
  setupRain();
  

  
  soilTempFunction();
  Serial.print("soilTemp = ");Serial.println(soilTemp);

  loraSetup();
  Serial.println("lora setup done");
  LoRa.sleep();              // Sends the radio to sleep
  Serial.println("Lora set to sleep");
  
  setupLEDs();
  Serial.println("LEDs have been set up");
  setupBME280();
  Serial.println("BME280 has been set up");
  soilSetup();
  Serial.println("Soil has been set up");
  setupWindVane();
  Serial.println("Windvane has been set up");
  windSpeedSetup();
  Serial.println("Windspeed has been set up");
    
  Serial.println(" ..... All is good ..... Continuing  .....");
  Serial.println(" ");
  digitalWrite(watchdogEnablePin, HIGH);  // HIGH enables watchdog.
  // Some delays for the watchdog timing:
  Serial.println("0");
  delay(1000);
  Serial.println("1");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("3");
  delay(1000);
  //Serial.println("4");
  //delay(1000);
} // setup

void loop()
{
  heartBeat();
  count++;
  Serial.print("count: ");Serial.println(count);
  
  windSpeed();
  windVane();

  rainDetect();
  flashRedLED();       // Charges capacitor for raingage
  
///////////////////////////////////////////////////////////////////////////
  // Uncomment one of the below:
    //int sleepMS = Watchdog.sleep(6000); // This will disable Serial console.
    delay(6000);   // Should be 6000.
//////////////////////////////////////////////////////////////////////////

  flashBuiltinLED();
  
  if ( z==0)
  {
    rainValuex1 =0;
    rainValue =0;
  }

  if (count > 60)        // Need relatively low number of samples of temperatures, humidity etc as they dont change quickly.
  {
    hours = hours + 0.083;
    Serial.print("Hours:  ");Serial.println(hours,3);
    count = 0;
    Serial.print("..1..");
    Serial.println("..2..");

    soilTempFunction();
    Serial.print("soilTemp = ");Serial.println(soilTemp);

    Serial.print("..3..");
    soil();            // Read soil moisture.
    moisture = moisture - (moisture*soilTemp*0.0040);  // Calibrate moisture sensor against temperatures. Formerly 0.0065.
    Serial.print("..4..");

    //delay(1000);

    BME280Readings();

    heartBeat(); 
    Serial.print("..5..");
    batteryVolts();
    rainValue = rainValuex1;                  // The software used to read the rain gauge twice. But no more, due to behaviour of capacitor.
    Serial.println("..6.. ");
    printToSerial();
    //const char webAddress[100] = "http://www.goatindustries.co.uk/weather2/send.php?";
    String dataString = "";
    dataString = initiator + "tempout="+BME280Temperature + "&tempsoil="+soilTemp + "&windgust="+knotsMax + "&windspeed="+knotsAv + "&rain="+rainValue + "&moisture="+moisture + "&tempint="+hours + "&pressure="+pressure + "&humidity="+humidity + "&volts="+batteryVoltsValue + "&windway="+vaneValue + "&END_OF_MESSAGE";
    Serial.print("Sending packet: ");
    Serial.print(dataString);
    //Serial.print("  ");
    //Serial.println(count);
    //Serial.println("");
    // send packet
    String message = "";
    message = dataString;
    Serial.println(" ..7.. ");
    LoRa_sendMessage(dataString); // send a message
    Serial.println(" ..8.. ");
    Serial.println("");
    callBackListeningStatus = 1;                                         // Allow time to recieve callback.
    currentMillis = millis();
    previousMillisCallBack = currentMillis;
    Serial.println(" ..9.. ");
  } // End of 'count' loop.
// Now allow time to recieve callback:  

  int callBackBeat = 0;
  while ( (currentMillis - previousMillisCallBack <= intervalCallBack)   )  // On successful callback z is reset to 0. See: 'void onReceive(int packetSize)'.
  {
    if ( ( (currentMillis - previousMillisCallBack) > 5000 ) && (callBackBeat ==0) )
    {
      heartBeat();                   // In case call back takes too long.
      callBackBeat = 1;
      flashBuiltinLED();
      Serial.println("Call back Heart beat");
    }
    currentMillis = millis();
    onReceive(LoRa.parsePacket());
    callBackListeningStatus = 1;
    sleepStatus = 0;
    slowPrint();                                                     // Prints "... Listening ..." every so often.
  }
  callBackListeningStatus = 0;
  //delay(3000);

  if (  (sleepStatus == 0)&&(callBackListeningStatus == 0)  )
  {
    LoRa.sleep();              // Sends the radio to sleep
    sleepStatus = 1;
    Serial.println("LoRa sent to sleep.");
  }
} // loop


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printToSerial()
{
  unsigned long currentMillis = millis();
  Serial.println("");
  Serial.print("currentMillis / 1000: ");Serial.println(currentMillis/1000);
  Serial.print("Z: ");Serial.println(z); 
  Serial.print("Soil temp C: ");Serial.println(soilTemp);
  Serial.print("Soil moisture: "); Serial.print(moisture); Serial.println(" %");
  Serial.print("BME 260 temp: "); Serial.println(BME280Temperature);
  Serial.print("BME 260 pressure: "); Serial.println(pressure);
  Serial.print("BME 260 humidiy: "); Serial.println(humidity);
  Serial.print("Battery volts: ");Serial.println(batteryVoltsValue);
  Serial.print("Rain Value: ");Serial.println(rainValue);
  Serial.print("Average wind speed: ");Serial.println(knotsAv);
  Serial.print("Max wind gust: ");Serial.println(knotsMax);
  Serial.print("Wind vane value: ");Serial.println(vaneValue);
  Serial.println("");
}

void onReceive(int packetSize) 
{
  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length

  String incoming = "";
  String success = "success";

  while (LoRa.available()) 
  {
    incoming += (char)LoRa.read();
  }
  int foundpos = -1;
  for (int i = 0; i <= incoming.length() - success.length(); i++) 
  {
    if (incoming.substring(i,success.length()+i) == success) 
    {
      //heartBeat(); 
      foundpos = i;
      Serial.println("");
      Serial.print("callBackListeningStatus = ");
      Serial.println(callBackListeningStatus);
      Serial.println(".........................  Call back was successful !!!! .............................");

      z=0;           // Reset the main counter.
      rainValuex1 =0;
      rainValue =0;
      //tone(3,500,1500);
      //windVane();                    // This is here so that wind vane variables get reset quickly.
    }
  }

//  if (incomingLength != incoming.length()) 
//  {   // check length for error
//    Serial.println("error: message length does not match length");
//    return;                             // skip rest of function
//  }

  // if the recipient isn't this device or broadcast,
  //if (recipient != localAddress && recipient != 0xFF) 
  //{
  //  Serial.println("This message is not for me.");
  //  return;                             // skip rest of function
 // }

  // if message is for this device, or broadcast, print details:

  Serial.println("");
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
}
void slowPrint()
{
  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillisSlowPrint) > intervalSlowPrint)
  {
    Serial.print(". ");
    previousMillisSlowPrint = currentMillis;
  }
}
void pauseWithBeats()
{
  digitalWrite(1, HIGH);   // Yellow LED
  tone(5,1000,500);
  delay(5000);

  for(int j=0;j<12;j++ )
  {
    heartBeat();
    delay(100);
    tone(5,1000,500);
    Serial.print("Pause: ");Serial.println(j);
    delay(5000);
  }
  digitalWrite(1, LOW);
}
void LoRa_txMode()
{
  LoRa.idle();                          // set standby mode
  LoRa.disableInvertIQ();               // normal mode
}
void LoRa_sendMessage(String message) 
{
  LoRa_txMode();                        // set tx mode
  LoRa.beginPacket();                   // start packet
  LoRa.print(message);                  // add payload
  LoRa.endPacket();                     // finish packet and send it
}
