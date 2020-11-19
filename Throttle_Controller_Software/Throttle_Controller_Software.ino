/*MCP4725 Example Waveform Sketch
Joel Bartlett
SparkFun Electronics
Sept. 11, 2014
https://github.com/sparkfun/MCP4725_Breakout

This sketch takes data from a lookup table to provide 
waveforms to be generated by the MCP4725 DAC. 

Development environment specifics:
Arduino 1.0+
Hardware Version V14

This code is beerware; if you see me (or any other SparkFun employee) at the local, 
and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given. 

This code builds off the sketch written by Mark VandeWettering, which can be found here:
http://brainwagon.org/2011/02/24/arduino-mcp4725-breakout-board/
*/

#include <Wire.h>//Include the Wire library to talk I2C

//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
//Please note that this breakout is for the MCP4725A0. 
#define MCP4725_ADDR 0x60   
//For devices with A0 pulled HIGH, use 0x61

//Sinewave Tables were generated using this calculator:
//http://www.daycounter.com/Calculators/Sine-Generator-Calculator.phtml


int lookup = 0;//varaible for navigating through the tables

int pedal_5_0v = A0;
int pedal_3_3v = A2;
int brakepedal = A7;

int x = 0;

int value5_0 = 0;
int value3_3 = 0;
int brakevalue = 0;

int scaled5_0 = 0;
int scaled3_3 = 0;


int sintab2[450] = 
{
500,
500,
500,
10,
20,
30,
40,
50,
60,
70,
80,
90,
100,
110,
120,
130,
140,
150,
160,
170,
180,
190,
200,
210,
220,
230,
240,
250,
260,
270,
280,
290,
300,
310,
320,
330,
340,
350,
360,
370,
380,
390,
400,
410,
420,
430,
440,
450,
460,
470,
480,
490,
500,
510,
520,
530,
540,
550,
560,
570,
580,
590,
600,
610,
620,
630,
640,
650,
660,
670,
680,
690,
700,
710,
720,
730,
740,
750,
760,
770,
780,
790,
800,
810,
820,
830,
840,
850,
860,
870,
880,
890,
900,
910,
920,
930,
940,
950,
960,
970,
980,
990,
1000,
1010,
1020,
1030,
1040,
1050,
1060,
1070,
1080,
1090,
1100,
1110,
1120,
1130,
1140,
1150,
1160,
1170,
1180,
1190,
1200,
1210,
1220,
1230,
1240,
1250,
1260,
1270,
1280,
1290,
1300,
1310,
1320,
1330,
1340,
1350,
1360,
1370,
1380,
1390,
1400,
1410,
1420,
1430,
1440,
1450,
1460,
1470,
1480,
1490,
1500,
1510,
1520,
1530,
1540,
1550,
1560,
1570,
1580,
1590,
1600,
1610,
1620,
1630,
1640,
1650,
1660,
1670,
1680,
1690,
1700,
1710,
1720,
1730,
1740,
1750,
1760,
1770,
1780,
1790,
1800,
1810,
1820,
1830,
1840,
1850,
1860,
1870,
1880,
1890,
1900,
1910,
1920,
1930,
1940,
1950,
1960,
1970,
1980,
1990,
2000,
2010,
2020,
2030,
2040,
2050,
2060,
2070,
2080,
2090,
2100,
2110,
2120,
2130,
2140,
2150,
2160,
2170,
2180,
2190,
2200,
2210,
2220,
2230,
2240,
2250,
2260,
2270,
2280,
2290,
2300,
2310,
2320,
2330,
2340,
2350,
2360,
2370,
2380,
2390,
2400,
2410,
2420,
2430,
2440,
2450,
2460,
2470,
2480,
2490,
2500,
2510,
2520,
2530,
2540,
2550,
2560,
2570,
2580,
2590,
2600,
2610,
2620,
2630,
2640,
2650,
2660,
2670,
2680,
2690,
2700,
2710,
2720,
2730,
2740,
2750,
2760,
2770,
2780,
2790,
2800,
2810,
2820,
2830,
2840,
2850,
2860,
2870,
2880,
2890,
2900,
2910,
2920,
2930,
2940,
2950,
2960,
2970,
2980,
2990,
3000,
3010,
3020,
3030,
3040,
3050,
3060,
3070,
3080,
3090,
3100,
3110,
3120,
3130,
3140,
3150,
3160,
3170,
3180,
3190,
3200,
3210,
3220,
3230,
3240,
3250,
3260,
3270,
3280,
3290,
3300,
3310,
3320,
3330,
3340,
3350,
3360,
3370,
3380,
3390,
3400,
3410,
3420,
3430,
3440,
3450,
3460,
3470,
3480,
3490,
3500,
3510,
3520,
3530,
3540,
3550,
3560,
3570,
3580,
3590,
3600,
3610,
3620,
3630,
3640,
3650,
3660,
3670,
3680,
3690,
3700,
3710,
3720,
3730,
3740,
3750,
3760,
3770,
3780,
3790,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,
3800,





};

uint16_t torqueTestVal = 0;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  
 
}
//---------------------------------------------------
void loop()
{
  

  brakevalue = analogRead(brakepedal);
  value5_0 = /*analogRead(pedal_5_0v);*/ 500;
  value3_3 = /* analogRead(pedal_3_3v); */ 500;

  
  scaled5_0 = map(value5_0, 0, 1023, 0, 450);
  scaled3_3 = map(value3_3, 0, 675, 0, 450);
    
  //Serial.println(value5_0);
  //Serial.println(value3_3);
  //Serial.println(brakevalue);
 
  if ((abs(scaled3_3 - scaled5_0) < 45 )){
    
  lookup  = scaled5_0;
  //Serial.println("GOOD");
  //Serial.println(lookup);
  }

  if ((abs(scaled3_3 - scaled5_0) > 45 )){
    
  lookup  = 0;
  Serial.println("BAD");
  Serial.println(value5_0);
  Serial.println(value3_3);
  }

  Wire.beginTransmission(MCP4725_ADDR);
  Serial.println("Writing to DAC");
  Wire.write(64);                     // cmd to update the DAC
  Wire.write(sintab2[lookup] >> 4);        // the 8 most significant bits...
  Wire.write((sintab2[lookup] & 15) << 4); // the 4 least significant bits...
  int error = Wire.endTransmission();
  if (error == 0)
  {
    Serial.println("Succesful");
  }
  else
  {
    Serial.print("Error: ");
    Serial.println(error);
  }
  
  
  
}
