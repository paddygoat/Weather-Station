#include <Arduino.h>

int addingDirection[]=
  {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,
  40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
  80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
  120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
  160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,
  200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
  240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,
  280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,
  320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362};
int degree =0;
const int analogInPin = A0;  // Analog input pin that the vane potentiometer is attached to.
int p=0;
int outputValue =0;
float maxSensorValue =1020.0001;
float minSensorValue = 0.0001;
int finalDirection=0;
float rawDirection =0;
int c=0;
int modeSize=0;
float vaneValue =0.00;

void setupWindVane()
{
  pinMode (12,OUTPUT);         // This provides short pulses of power to the wind vane from pin 12 for power saving.
  while (degree<362)           // Set all 362 values to zero.
  {
    addingDirection[degree] = 0;
    degree++;
  }
}
void windVane()
{
/////////////////////////////////////////////// Wind vane stuff:
  int g=0;
  int adc0; 
  p++;
  
  while (g<2)                             // Get 2 quick readings.
    {
    g++;  
    digitalWrite(12, HIGH);
    delay(10);
    // read the analog in value:
    adc0 = analogRead(A0);
    delay(100);
    } 
    
    int sensorValue=0;
    int sensorValue2=0;
    int sensorValue3=0; 
    int sensorValue4=0;     
    int big =0;
    int small =0;   
    g=0;
    
  while (g<11)                             // Get 10 quick readings. Must be an odd number or big could equal small.
    {
    g++;  
    // read the analog in value:
    adc0 = analogRead(A0);
    sensorValue2 = sensorValue2 + adc0;

    
// This bit of code below takes care of the instance where the weather vane is hovering around north (hovering zone) and picking up big values and small values in the same batch of 11:
// Total range is about 0 to 24000.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                                                              
     if (adc0 < 100)
      {
       sensorValue4 = sensorValue4 + adc0;
       small++;
      }
     if (adc0 >= 100)                                    
      {
       sensorValue3 = sensorValue3 + adc0;
       big++;                                          
      }
     if (big > small)
      {
       sensorValue = sensorValue3 / big;     
      }
     if (big < small)
      {
       sensorValue = sensorValue4 / small;
      }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
    delay(50);
    }                                                   // End of while loop.
  if (sensorValue == 0)                                 
    {
    sensorValue = (sensorValue2/g);                     // We're not in the hovering zone as no sensorValue has been picked up yet so we make a normal calculation of the mean.
    }
    
  digitalWrite(12, LOW);
  delay(50);                            // set this to 500 so total delay = 1 second.

  

  // assume that dead band starts at 356.5 and ends at 0
  // and values of zero correspond to 360 or 0 degrees:
  // The maximum analogue reading I am getting on the wiper is 24,000
  // out of a possible range of 65,536 (16 bits)
  
  
  if (sensorValue == 0)
  {
    outputValue =0;
  }
  
  outputValue = ((sensorValue-minSensorValue)*356.5/maxSensorValue)+1.75;
  
  // selfCalibrate();                         // Checks the maximum range of the analoue readings when sensor comes out of dead band.

////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Non linearity calculations:
  // Now assume that max non linearity is at 240 degrees and is +0.53
  // Also, assume non linearity itself is linear, not a curve:

  if (outputValue<240 || outputValue==240)
  {
    rawDirection = outputValue*0.53/240 + outputValue;
  }
  if (outputValue>240)
  {
    rawDirection = 0.53*(358-outputValue)/118 + outputValue;
  }
  if (sensorValue == minSensorValue) 
  {
  rawDirection=360;
  }
////////////////////////////////////////////////////////////////////////////////////////////////////// 
  //Serial.print("sensor = ");
  //Serial.print(sensorValue);
  //Serial.print("\t output = ");
  //Serial.print(outputValue,2);
  //Serial.print("\t adjusted output = ");
  //Serial.print(rawDirection,2);
  //Serial.print("\t Max sensor value = ");
  //Serial.print(maxSensorValue,2);
  //Serial.print("\t Min sensor value = ");
  //Serial.print(minSensorValue,2);
  //Serial.print("\t n = ");
  //Serial.println(p);  

  digitalWrite(12, LOW);

 degree = (int)rawDirection;

/////////////////////////////////////////////////////////////////////////////////// 
 // Special case for rawDirection = 360:
 if (rawDirection ==360)
 {
  degree = 359 + c;
  c++;
 }
 if (c>2)
 {
  c=0;
 }
 if (degree==361)
 {
  degree=1;
 }
/////////////////////////////////////////////////////////////////////////////////////  
// Calculate the running mode (Some of these variables will need to be reset by a call back from main processor).

 addingDirection[degree] = addingDirection[degree] +1;
if (addingDirection[degree] > modeSize)
{
  modeSize = modeSize +1;
  finalDirection = degree;
}

//////////////////////////////////////////////////////////////////////////////////////
if (finalDirection==359 || finalDirection==360 || finalDirection==1)
{
  finalDirection=360;
}
  //Serial.print("Mode size = ");
  //Serial.print(modeSize);
  //Serial.print("\t Degree = ");
  //Serial.print(degree);
  //Serial.print("\t Final Mode Direction = ");
  Serial.print("Final Direction =  ");Serial.println(finalDirection);
  //Serial.print("\t Adding direction[degree] = ");
  //Serial.println(addingDirection[degree]);
  //Serial.print("Small = ");
  //Serial.println(small);
  //Serial.print("Big = ");
  //Serial.println(big);
  // variation();  
  vaneValue=finalDirection;
  //Serial.println(""); 

// 30 days = 2592000 seconds
// Each loop of n x 10 is ten seconds
// Every ten seconds max sensor value is reduced by 0.0001
// Every 30 days max sensor values reduced by 2592000 / 10 * 0.00001 = 25.92 degrees
// In 3 days of northerly winds max sensor value will adjust by as much as 2.592 degrees.
// During northerly winds the sensor will self calibrate:
//////////////////////////////////////////////////////////////////////////////////////////////////////  
}

