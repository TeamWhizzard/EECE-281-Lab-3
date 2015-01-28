/*	January 27, 2015
 *	University of British Columbia
 *	EECE 281
 *	Team 7B
 *	Lab 3
 */
 
 /*
 SYM	LCD	  UNO
 ================
 RS		 4	    2
 RW		 G	  N/A
 E		 6	    3
 DB7	14     11 } Accessible through
 DB6	13	   10 } PortB for communication
 DB5	12		9 } and DDRB for pin
 DB4	11		8 } setup.
 */

#define ZEROS 	B0000	// Empty port register for convenience
#define RS		2		// Register Select, 1: Data Register, 0: Instruction Register
#define READY	3		// Enable signal for writing or reading data
#define INIT	B0011	// First initialization string sent 3 times to LCD
#define FOURBIT	B0010	// Interface set to 4 bit. High bits sent first, low bits second.
#define LCD_ON	B1100	// LCD on, precede with ZEROS command for high bits
#define LCD_OFF	B1000	// LCD off, precede with ZEROS
#define CLEAR	B0001	// LCD clear, precede with ZEROS
#define ENTRY	B0101	// Entry Mode, precede with ZEROS
#define FONT	B1000	// Set number of lines and font

const byte SETUP[] = {FOURBIT, B0010, FONT, ZEROS, LCD_OFF, ZEROS, CLEAR, ZEROS, ENTRY};

void setup()
{
	//Serial Port Init
	Serial.begin(115200);

	// Pin Mapping
	DDRB = B111111; // Enable Port C as output
	DDRD = DDRD | B11111100; // Enable Port D as output without touching pins 0, 1.

	// Initialize LCD
	while (millis() <= 60); // ensure 15 ms uptime before LCD init
	//Serial.println(millis());
	PORTB = INIT;
	delayMicroseconds(4500);
	PORTB = INIT;
	delayMicroseconds(150);
	PORTB = INIT;
	
	// Setup LCD
	for (int i = 0; i <= 8; i++) {
		PORTB = SETUP[i];
	}
	
	// LCD Done
	PORTB = ZEROS;
	delay(1);
	PORTB = LCD_ON;
}

void loop()
{
	PORTB = 0010;
	delay(1);
	PORTB = 0001;
	delay(1000);
}