/*	
 *	Note: This file has the extension .cpp, but needs to be as workaround for C libraries.
 *	For something more formal, you would wrap your header file in preprocessor commands
 *	that force C over CPP, as Arduino expects C++ libraries by default.
 *
 */

#include "Arduino.h"
#include "lab3LCD.h"

void lcdInitialize () // LCD initialization sequence
{
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

void pulse() // pulses enable pin to signal data byte send has complete
{
  digitalWrite(ENABLE, HIGH);
  delayMicroseconds(1);
  digitalWrite(ENABLE, LOW);
  delayMicroseconds(1);
}

void command(byte x)  // sends signal over 4 bit bus
{
  PORTB = B001111 & x;
  pulse();
}

void printLine(String message) // prints passed message to LCD display
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

void commandMode() // signals LCD to accept following bytes as commands
{
  digitalWrite(RS, LOW);
  delayMicroseconds(1);
}

void characterMode() // signals LCD to accept following bytes as character information
{
  digitalWrite(RS, HIGH);
  delayMicroseconds(1);	
}

void setCursor(int column, int row) // sets LCD cursor to specified row and column
{
  commandMode();
 
  if (row == 0) { // top row, set to DDRAM address 0x80
    command (ROW_TOP);
    command ((byte) column);
  } else if (row == 1) { // bottom row, set to DDRAM address 0xC0
    command (ROW_BOTTOM);
    command ((byte) column);
  }
 
  characterMode(); 
}

void blink (int n, int time) // blinks LCD display n times. note that time is in miliseconds
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

void scrollDisplayLeft() // scrolls LCD display one space to the left
{
  commandMode();
  command(CD_SHIFT);  // LCD cursor shift
  command(CD_SHIFT_LEFT);
  delayMicroseconds(2500);
  characterMode(); 
}

void scrollDisplayRight() // scrolls LCD display one space to the right
{
  commandMode();
  command(CD_SHIFT);  // LCD cursor shift
  command(CD_SHIFT_RIGHT);
  delayMicroseconds(2500);
  characterMode(); 
}


void createChar (int ramSpot, byte * charMap) // create custom character in GRAM slot ramSpot.
{ // charMap should by an 8*8 byte array holding one row of the custom character per line
  byte address = SET_CGRAM | ramSpot << 3;
  
  commandMode();
  command(address >> 4); // set one of eight ram locations
  command(address);
  characterMode();
  for (int i = 0; i < 8; i++) {
    command(charMap[i] >> 4);
    command(charMap[i]);	
    delayMicroseconds(100);
  }
  
}

void clear() // clears LCD display
{
  commandMode();
  command(ZEROS);
  command(CLEAR);
  delayMicroseconds(2500);
  characterMode();
}
