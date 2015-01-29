/*	
 *	Note: This file has the extension .cpp, but needs to be as workaround for C libraries.
 *	For something more formal, you would wrap your header file in preprocessor commands
 *	that force C over CPP, as Arduino expects C++ libraries by default.
 *
 */

#include "Arduino.h"
#include "lab3LCD.h"

const byte setupCmds[] = {INIT, INIT, INIT, FOURBIT, B0010, FUNCTION_SET, ZEROS, LCD_OFF, ZEROS, CLEAR, ZEROS, ENTRY_MODE, ZEROS, LCD_ON};
const int setupDelays[] = {4500, 150, 100, 100, 0, 100, 0, 100, 0, 2500, 0, 100, 0, 100};

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

void printLine(char alphanumeric[], int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		command(alphanumeric[i] >> 4);
		command(alphanumeric[i]);	
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

void clear()
{
	commandMode();
	command(ZEROS);
	command(CLEAR);
	delayMicroseconds(2500);
	characterMode();
}
