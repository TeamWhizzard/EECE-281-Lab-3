/*	January 30, 2015
 *	University of British Columbia
 *	EECE 281
 *	Team 7B
 *	Lab 3
 */
 
#include "lab3LCD.h"

const int pinMoisture = A0;

const String message_one = "Hello and welcome to our demo!";
const String message_two = "EECE 281 section 202 Team L2D-7B";
const String message_whizzard = "Whizzard is proud to present:";
const String message_title = "CRAPPY BIRD!";

int history [13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
int num = 0;

void setup()
{
  Serial.begin(115200); //Serial Port Initialization
  
  lcdInitialize();
  initializeGraph();
  pinMode(pinMoisture, INPUT);

//  // Print startup message to LCD
//  setCursor(0, 0);
//  printLine(message_one.substring(0,16)); // first 16 characters of message
//  setCursor(0, 1);
//  printLine(message_one.substring(16)); // remaining characters of message
//  delay(1000);
//  clear();
//        
//  // Displays second message and scroll off screen to left
//  setCursor(0, 0);
//  printLine(message_two);
//  delay(1000);
//  for (int i = 0; i < message_two.length() - 16; i++) { // scroll to end of message
//    scrollDisplayLeft();
//    delay (1000);
//    }
//  delay(2000);
//  clear();
//        
//  // Custom message
//  setCursor(0, 0);
//  printLine(message_whizzard.substring(0,16)); // first 16 characters of message
//  setCursor(0, 1);
//  printLine(message_whizzard.substring(16)); // remaining characters of message
//  delay(1000);
//  clear();
//        
//  setCursor(2, 0);
//  printLine(message_title);
//  blink(5, 500);
//  delay(1000);
//  clear();
}

void loop()
{
  int moisture = analogRead(pinMoisture);
  printLine(String(moisture));
  moistureHistory (moisture / 100);
  delay(1000);
  clear();
}

void initializeGraph ()
{
  byte h = B11111;
  byte l = B00000;
  byte graphChar[][8] = {{l,l,l,l,l,l,l,h},
  {l,l,l,l,l,l,h,h},
  {l,l,l,l,l,h,h,h},
  {l,l,l,l,h,h,h,h},
  {l,l,l,h,h,h,h,h},
  {l,l,h,h,h,h,h,h},
  {l,h,h,h,h,h,h,h},
  {h,h,h,h,h,h,h,h}};
  createChar(0, graphChar[0]);
  createChar(1, graphChar[1]);
  createChar(2, graphChar[2]);
  createChar(3, graphChar[3]);
  createChar(4, graphChar[4]);
  createChar(5, graphChar[5]);
  createChar(6, graphChar[6]);
  createChar(7, graphChar[7]);
}

void moistureHistory (int moisture)
{
  setCursor(3,0);
  history[num % 13] = moisture;
  
  for (int i = (num % 13) + 13; i > (num % 13); i--) {
    write(history[i % 13]);
  }
  num++;
}
