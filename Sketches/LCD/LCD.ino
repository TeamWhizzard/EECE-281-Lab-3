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
const String message_whizzard = "Team Whizzard presents:";
const String message_title = "Moisture Meter";

int history [13] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int num = 0;
int moistureLast;

char block = 0xFF;

void setup()
{
  Serial.begin(115200); //Serial Port Initialization
  
  lcdInitialize();
  initializeGraph();
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
    delay (500);
    }
  delay(1000);
  clear();
        
  // Custom message
  setCursor(0, 0);
  printLine(message_whizzard.substring(0,16)); // first 16 characters of message
  setCursor(0, 1);
  printLine(message_whizzard.substring(16)); // remaining characters of message
  delay(1000);
  clear();
        
  setCursor(1, 1);
  printLine(message_title);
  blink(3, 700);
  clear();

  setCursor(0,1);
  printLine((String) block);
}

void loop()
{
  setCursor(0,0);
  int moisture = analogRead(pinMoisture);
  printLine(String(moisture));
  moistureHistory (moisture / 100);
  moistureLive(moisture / 40);
  delay(700);
}

void initializeGraph ()
{ 
  byte graphChar[] = {ZEROS, ZEROS, ZEROS, ZEROS, ZEROS, ZEROS, ZEROS, ZEROS};
  byte line = B11111;
  
  for (int i; i < 8; i++ ) {
    graphChar[7 - i] = line; 
    createChar(i, graphChar);
  }
  setCursor(0,0);
}

void moistureHistory (int moisture)
{
  setCursor(3,0);
  history[num % 13] = moisture;
  for (int i = (num % 13) + 13; i > (num % 13); i--) {
    if (history[i % 13] == -1) {
      printLine(" ");
    } else {
      write(history[i % 13]);
    }
  }
  num++;
}

void moistureLive (int moisture)
{ 
  if (moisture > moistureLast) {
    setCursor(0,1);
    printLine((String) block); // minimum level
    for (int i = 0; i < moisture; i++) {
      printLine((String) block);
      delay(30);
    }
  } else if (moisture < moistureLast) {
    for (int i = moistureLast; i > moisture; i--) {
      setCursor(i,1);
      printLine(" ");
      delay(30);
    }
  }
  
  moistureLast = moisture;
}
