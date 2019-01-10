#include <Arduino.h>
#include "counters.h"

int frequency;
//int z =-1;
float correction =0;
float runningTotal =0.1;

float knots =0.00;
float knotsMax =0.00;
float knotsAv =0.00;

float knotsDec =0.1;
float knotsMaxDec =0.1;
float knotsAvDec =0.1;

int frequencyInt;
int knotsInt;
int knotsAvInt;
int knotsMaxInt; 

int knotsDecInt;
int knotsMaxDecInt;
int knotsAvDecInt;

float calibration = 1.0047;    // (46.62 / 46.4)

void windSpeedSetup()
{
  
}
    
void windSpeed()
{
  z++;
  frequency = 500000/pulseIn(4,HIGH,5000000);
  if (frequency < 0){frequency=0;}    
  int correction =0;
  int adjustments();
  knots = (frequency * calibration /10) + correction; 
  if (knots > knotsMax)
  {
    knotsMax = knots;
  }
  runningTotal = runningTotal + knots;
  knotsAv = runningTotal / z;

}
void adjustments()
{   
    if ((frequency >=1) && (frequency <=100)) {correction = 0.20;}
    if ((frequency >100) && (frequency <=200)) {correction = 0.10;}
    if ((frequency >200) && (frequency <=300)) {correction = -0.25;}
    if ((frequency >300) && (frequency <=400)) {correction = -0.60;}
    if ((frequency >400) && (frequency <=500)) {correction = -1;}
    if ((frequency >500) && (frequency <=600)) {correction = -1.4;}
    if ((frequency >600) && (frequency <=700)) {correction = -1.75;}
    if ((frequency >700) && (frequency <=800)) {correction = -2;}
    if ((frequency >800) && (frequency <=900)) {correction = -2.20;}
    if ((frequency >900) && (frequency <=1000)) {correction = -2.35;}
    if ((frequency >1000) && (frequency <=1100)) {correction = -2.40;}
    if ((frequency >1100) && (frequency <=1200)) {correction = -2.50;}
    if ((frequency >1200) && (frequency <=1300)) {correction = -2.50;}
    if ((frequency >1300) && (frequency <=1400)) {correction = -2.50;}
    if ((frequency >1400) && (frequency <=1500)) {correction = -2.45;}
    if ((frequency >1500) && (frequency <=1600)) {correction = -2.40;}  
}
