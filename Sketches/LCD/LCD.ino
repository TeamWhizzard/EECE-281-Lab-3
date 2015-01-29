/*	January 27, 2015
 *	University of British Columbia
 *	EECE 281
 *	Team 7B
 *	Lab 3
 */
 
#include "lab3LCD.h"

void setup()
{
	Serial.begin(115200); //Serial Port Initialization
	DDRB = B111111; // Enable Port B as output
	pinMode(RS, OUTPUT); // Pin Mapping RS as Output
	pinMode(ENABLE, OUTPUT); // Pin Mapping Enable as Output
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

void loop()
{
	char line[] = "Whizzards Rule";
	printLine(line, ARRAY_SIZE(line));
	delay(1000);
	clear();
}