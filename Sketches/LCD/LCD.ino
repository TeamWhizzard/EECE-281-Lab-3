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

int num = 0; // counts number of iterations of void loop() function
int moistureLast; // keeps track of last moisture reading
int history [13] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; // acts as circular array to keep track of past thirteen moisture reading for top line display
char block = 0xFF;

void setup()
{
  Serial.begin(115200); //Serial Port Initialization
  pinMode(pinMoisture, INPUT);  

  lcdInitialize();
  introMessaging();
  initializeGraph();
}

void loop()
{
  setCursor(0,0);
  int moisture = analogRead(pinMoisture); // moisture reading
  printLine(String(moisture));
  moistureHistory (moisture / 100); // division will pass an int within range 0 to 8
  moistureLive(moisture / 40); // division will pass an int within range 0 to 16 based on tested moisture thresholds
  delay(700);
}

// initializeGraph() - creates requested characters in LCD RAM
void initializeGraph ()
{ 
  byte graphChar[] = {ZEROS, ZEROS, ZEROS, ZEROS, ZEROS, ZEROS, ZEROS, ZEROS};
  byte line = B11111;
  
  for (int i; i < 8; i++ ) {
    graphChar[7 - i] = line; 
    createChar(i, graphChar);
  }
  setCursor(0,1);
  printLine((String) block);
}

// moistureHistory() - displays a bar graph of moisture history on top line of LCD display
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

// moistureLive() - displays bar representation of most recent moisture reading on bottom line of LCD display
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

void introMessaging()
{
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
        
  // Whizzard Message
  setCursor(0, 0);
  printLine(message_whizzard.substring(0,16)); // first 16 characters of message
  setCursor(0, 1);
  printLine(message_whizzard.substring(16)); // remaining characters of message
  delay(1000);
  clear();
  
  // Print final message flashing
  setCursor(1, 1);
  printLine(message_title);
  blink(3, 700);
  clear();
}
