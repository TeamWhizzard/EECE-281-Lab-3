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
 
  byte setupCmds[] = {INIT, INIT, INIT, FOURBIT, FUNCTION_SET, LCD_OFF, CLEAR, ENTRY_MODE, LCD_ON};
  int setupDelays[] = {4500, 150, 100, 0, 0, 0, 2400, 0, 0};

  delay(20); // Initial delay before LCD init
  commandMode(); // Prep LCD to receive initialization commands
  digitalWrite(ENABLE, LOW); // Ensure Enable is set to low before LCD initialization

  for (int i = 0; i < SETUP_SIZE; i++) // Initialize LCD
  {
    if (i > 3)
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

void pulse()
{
  digitalWrite(ENABLE, HIGH);
  delayMicroseconds(1);
  digitalWrite(ENABLE, LOW);
  delayMicroseconds(1);
}

// 4 bit commands used only in the start of the setup are sent with this.
void setupCommand(byte four)
{
  PORTB = B001111 & four; // ensure we don't send data to pins 11/12 which aren't hooked up.
  pulse();
}

void command(byte eight)
{
  PORTB = eight >> 4;
  pulse();
  PORTB = 0x0F & eight  // ensure we don't send data to pins 11/12 which aren't hooked up.
  pulse();
  delayMicroseconds(100);
}

void printLine(String message)
{
  char stoaBuffer[BLENGTH];
  message.toCharArray(stoaBuffer, BLENGTH);
  
  for (int i = 0; i < message.length(); i++)
  {
    command(stoaBuffer[i]);	
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
    command(LCD_OFF);
    delay(time);
    command(LCD_ON);
    delay(time);
  }
  characterMode();  
}

void scrollDisplayLeft()
{
  commandMode();
  command(CD_SHIFT_LEFT);
  delayMicroseconds(2500);
  characterMode(); 
}

// TODO fix
void scrollDisplayRight()
{
  commandMode();
  command(CD_SHIFT_RIGHT);
  delayMicroseconds(2500);
  characterMode(); 
}

void createChar (int ramSpot, char * charMap) {
  byte address = SET_CGRAM | ramSpot << 3;
  
  commandMode();
  command(address);
  characterMode();
  for (int i = 0; i < 8; i++) {
    command(charMap[i]);	
  }  
}

void clear()
{
  commandMode();
  command(CLEAR);
  delayMicroseconds(2500);
  characterMode();
}
