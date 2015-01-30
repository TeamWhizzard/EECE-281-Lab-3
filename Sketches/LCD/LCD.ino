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

byte frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};

byte heart[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};


void setup()
{
  Serial.begin(115200); //Serial Port Initialization
  
  lcdInitialize();
  pinMode(pinMoisture, INPUT);

  // Print startup message to LCD
  setCursor(0, 0);
  printLine(message_one.substring(0,16)); // first 16 characters of message
  setCursor(0, 1);
  printLine(message_one.substring(16)); // remaining characters of message
  delay(1000);
  clear();
        
  // Displays second message and scroll off screen to left
  setCursor(0, 0);
  printLine(message_two);
  delay(1000);
  for (int i = 0; i < message_two.length() - 16; i++) { // scroll to end of message
    scrollDisplayLeft();
    delay (1000);
    }
  delay(2000);
  clear();
        
  // Custom message
  setCursor(0, 0);
  printLine(message_whizzard.substring(0,16)); // first 16 characters of message
  setCursor(0, 1);
  printLine(message_whizzard.substring(16)); // remaining characters of message
  delay(1000);
  clear();
        
  setCursor(2, 0);
  printLine(message_title);
  blink(5, 500);
  delay(1000);
  clear();
}

void loop()
{
  printLine(String(analogRead(pinMoisture)));
  delay(1000);
  clear();
}
