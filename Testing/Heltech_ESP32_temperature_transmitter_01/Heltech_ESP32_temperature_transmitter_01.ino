/*
  This is a simple example show the Heltec.LoRa sended data in OLED.

  The onboard OLED display is SSD1306 driver and I2C interface. In order to make the
  OLED correctly operation, you should output a high-low-high(1-0-1) signal by soft-
  ware to OLED's reset pin, the low-level signal at least 5ms.

  OLED pins to ESP32 GPIOs via this connecthin:
  OLED_SDA -- GPIO4
  OLED_SCL -- GPIO15
  OLED_RST -- GPIO16
  
  by Aaron.Lee from HelTec AutoMation, ChengDu, China
  成都惠利特自动化科技有限公司6u
  https://heltec.org
  
  this project also realess in GitHub:
  https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series
*/
#include <OneWire.h>
#include <DallasTemperature.h>

int ledState_03 = LOW;
unsigned long prevMillis_03 = 0;
const long interval_03 = 1400;

// Data wire is plugged TO GPIO 17
// address: 28FF26B35816044C

// GPIO where the DS18B20 is connected to
const int oneWireBus = 17;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

int spreading = 12;

#include "heltec.h"
#include "images.h"
#include "soil.h"

#define BAND    433.5E6  //you can set band here directly,e.g. 868E6,915E6

unsigned int counter = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet ;

void logo()
{
  Heltec.display->clear();
  Heltec.display->drawXbm(0,5,logo_width,logo_height,logo_bits);
  Heltec.display->display();
}

void setup()
{
  soilSetup();
  // pinMode(23, OUTPUT);
  // digitalWrite(23, HIGH);
  Serial.begin(57600);
    // Start the DS18B20 sensor
  sensors.begin();
   //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  LoRa.setSpreadingFactor(spreading);           // ranges from 6-12,default 7 see API docs
  LoRa.setSyncWord(0x34);
  Serial.println("LoRa.setSignalBandwidth: ");
  LoRa.setSignalBandwidth(500000);
  // Serial.print("LoRa.getSignalBandwidth: ");Serial.println(LoRa.getSignalBandwidth());
  // Serial.print("LoRa.getSpreadingFactor: ");Serial.println(LoRa.getSpreadingFactor());

  
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  logo();
  delay(1500);
  Heltec.display->clear();
  
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display();
  delay(1000);
}

void loop()
{
  soil();            // Read soil moisture.
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");

  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  
  Heltec.display->drawString(0, 0, "Temp: ");
  Heltec.display->drawString(40, 0, String(temperatureC));
  Heltec.display->drawString(80, 0, "ºC");
  Heltec.display->drawString(0, 15, "Soil moisture: ");
  Heltec.display->drawString(70, 15, String(moisture));
  Heltec.display->display();

  // send packet
  LoRa.beginPacket();
  
/*
 * LoRa.setTxPower(txPower,RFOUT_pin);
 * txPower -- 0 ~ 20
 * RFOUT_pin could be RF_PACONFIG_PASELECT_PABOOST or RF_PACONFIG_PASELECT_RFO
 *   - RF_PACONFIG_PASELECT_PABOOST -- LoRa single output via PABOOST, maximum output 20dBm
 *   - RF_PACONFIG_PASELECT_RFO     -- LoRa single output via RFO_HF / RFO_LF, maximum output 14dBm
*/
  LoRa.setTxPower(15,RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print("temp: ");
  LoRa.print(temperatureC);
  LoRa.print(" mois: ");
  LoRa.print(moisture);
  LoRa.endPacket();

  counter++;
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  // digitalWrite(22, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  // digitalWrite(22, LOW);    // turn the LED off by making the voltage LOW
  delay(59000);                       // wait for a second
  // delay(1000);                       // wait for a second
}
