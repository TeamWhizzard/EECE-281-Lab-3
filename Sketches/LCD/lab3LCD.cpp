/*	
 *	Note: This file has the extension .cpp, but needs to be as workaround for C libraries.
 *	For something more formal, you would wrap your header file in preprocessor commands
 *	that force C over CPP, as Arduino expects C++ libraries by default.
 *
 */

#include "Arduino.h"
#include "lab3LCD.h"

void lcdInitialize () {
  Serial.begin(115200); //Serial Port Initialization
  DDRB = B111111; // Enable Port B as output
  pinMode(RS, OUTPUT); // Pin Mapping RS as Output
  pinMode(ENABLE, OUTPUT); // Pin Mapping Enable as Output
 
  byte setupCmds[] = {INIT, INIT, INIT, FOURBIT, B0010, FUNCTION_SET, ZEROS, LCD_OFF, ZEROS, CLEAR, ZEROS, ENTRY_MODE, ZEROS, LCD_ON};
  int setupDelays[] = {4500, 150, 100, 100, 0, 100, 0, 100, 0, 2500, 0, 100, 0, 100};

  delay(20); // Initial delay before LCD init
  commandMode(); // Prep LCD to receive initialization commands
  digitalWrite(ENABLE, LOW); // Ensure Enable is set to low before LCD initialization

  for (int i = 0; i < SETUP_SIZE; i++) // Initialize LCD
  {
    command(setupCmds[i]);
    delayMicroseconds(setupDelays[i]);
  }
  characterMode(); // Set character input for loop()
}

void setCharacter()
{
   
}

void pulse()
{
  digitalWrite(ENABLE, HIGH);
  delayMicroseconds(1);
  digitalWrite(ENABLE, LOW);
  delayMicroseconds(1);
}

void command(byte x)
{
  PORTB = x;
  pulse();
}

void printLine(String message)
{
  char stoaBuffer[BLENGTH];

  message.toCharArray(stoaBuffer,BLENGTH);

  for (int i = 0; i < message.length(); i++)
  {
    command(stoaBuffer[i] >> 4);
    command(stoaBuffer[i]);	
    delayMicroseconds(100);
  }
}

void commandMode()
{
  digitalWrite(RS, LOW);
  delayMicroseconds(1);
}

void characterMode()
{
  digitalWrite(RS, HIGH);
  delayMicroseconds(1);	
}

void cursorPlace(int row)
{
  commandMode();
 
  if (row == 0) { // top row, set to DDRAM address 0x80
    command (B1000);
    command (B0000);
  } else if (row == 1) { // bottom row, set to DDRAM address 0xC0
    command (B1100);
    command (B0000);
  }
 
  characterMode(); 
}

void blink (int n, int time) // time in miliseconds
{
  commandMode();
  for (int i = 0; i < n; i++) {
    command(ZEROS);
    command(LCD_OFF);
    delay(time);
    command(ZEROS);
    command(LCD_ON);
    delay(time);
  }
  characterMode();  
}

void scrollDisplayLeft()
{
  commandMode();
  command(CD_SHIFT);  // LCD cursor shift
  command(CD_SHIFT_LEFT);
  delayMicroseconds(2500);
  characterMode(); 
}

// TODO fix
void scrollDisplayRight()
{
  commandMode();
  command(CD_SHIFT);  // LCD cursor shift
  command(CD_SHIFT_RIGHT);
  delayMicroseconds(2500);
  characterMode(); 
}

void clear()
{
  commandMode();
  command(ZEROS);
  command(CLEAR);
  delayMicroseconds(2500);
  characterMode();
}
