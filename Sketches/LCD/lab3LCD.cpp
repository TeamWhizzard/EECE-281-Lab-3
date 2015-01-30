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
 
  byte setupCmds[] = {INIT, INIT, INIT, FOURBIT, FUNCTION_SET, LCD_OFF, CLEAR, ENTRY_MODE, LCD_ON};
  int setupDelays[] = {4500, 150, 100, 0, 0, 0, 2400, 0, 0};

  delay(20); // Initial delay before LCD init
  commandMode(); // Prep LCD to receive initialization commands
  digitalWrite(ENABLE, LOW); // Ensure Enable is set to low before LCD initialization

  for (int i = 0; i < SETUP_SIZE; i++) // Initialize LCD
  {
    if (i < 4)
    {
      setupCommand(setupCmds[i]); // 4 bit setup command
    }
    else
    {
      command(setupCmds[i]); // 8 bit setup command
    }
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

// 4 bit commands used only in the start of the setup are sent with this.
void setupCommand(byte four)
{
  PORTB = four; // ensure we don't send data to pins 11/12 which aren't hooked up.
  pulse();
}

void write(int cgRamCustom)
{
  command((byte) cgRamCustom);
}

void command(byte eight)
{
  PORTB = eight >> 4;
  pulse();
  PORTB = 0x0F & eight;  // ensure we don't send data to pins 11/12 which aren't hooked up.
  pulse();
  delayMicroseconds(100);
}

void printLine(String message) // prints passed message to LCD display
{
  char stoaBuffer[BLENGTH];
  message.toCharArray(stoaBuffer, BLENGTH);
  
  for (int i = 0; i < message.length(); i++)
  {
    command(stoaBuffer[i]);	
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
    command (ROW_TOP | (byte) column);
  } else if (row == 1) { // bottom row, set to DDRAM address 0xC0
    command (ROW_BOTTOM | (byte) column);
  } 
  characterMode(); 
}

void blink (int n, int time) // blinks LCD display n times. note that time is in miliseconds
{
  commandMode();
  for (int i = 0; i < n; i++) {
    command(LCD_OFF);
    delay(time);
    command(LCD_ON);
    delay(time);
  }
  characterMode();  
}

void scrollDisplayLeft() // scrolls LCD display one space to the left
{
  commandMode();
  command(CD_SHIFT_LEFT);
  delayMicroseconds(2500);
  characterMode(); 
}

void scrollDisplayRight() // scrolls LCD display one space to the right
{
  commandMode();
  command(CD_SHIFT_RIGHT);
  delayMicroseconds(2500);
  characterMode(); 
}

// create custom character in GRAM slot ramSpot.
// charMap should by an 8*8 byte array holding one row of the custom character per line
void createChar (int ramSpot, byte * charMap)
{
  byte address = SET_CGRAM | (((byte) ramSpot) << 3);
  
  commandMode();
  command(address);
  characterMode();
  for (int i = 0; i < 8; i++) {
    Serial.print(charMap[i]);
    Serial.print(" ");
    command(charMap[i]);
  }
  Serial.println("");
}

void clear() // clears LCD display
{
  commandMode();
  command(CLEAR);
  delayMicroseconds(2500);
  characterMode();
}
