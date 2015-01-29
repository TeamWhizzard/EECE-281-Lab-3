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

#define ZEROS 			B0000	// Empty port register for convenience
#define RS					2	// Register Select, 1: Data Register, 0: Instruction Register
#define ENABLE				3	// Enable signal for writing or reading data
#define INIT			B0011	// First initialization string sent 3 times to LCD
#define FOURBIT			B0010	// Interface set to 4 bit. High bits sent first, low bits second.
#define LCD_ON			B1111	// LCD on, precede with ZEROS command for high bits
#define LCD_OFF			B1000	// LCD off, precede with ZEROS
#define CLEAR			B0001	// LCD clear, precede with ZEROS
#define ENTRY_MODE		B0110	// ENTRY_MODE Mode, precede with ZEROS
#define FUNCTION_SET	B1000	// Set number of lines and FUNCTION_SET

const byte SETUP[] = {FOURBIT, B0010, FUNCTION_SET, ZEROS, LCD_OFF, ZEROS, CLEAR, ZEROS, ENTRY_MODE};

void setup()
{
	//Serial Port Init
	Serial.begin(115200);

	// Pin Mapping
	DDRB = B111111; // Enable Port B as output
	pinMode(RS, OUTPUT);
	pinMode(ENABLE, OUTPUT);
	//DDRD = DDRD | B11111100; // Enable Port D as output without touching pins 0, 1.

	// Initialize LCD
	delay(50); // 20 ms before LCD init
	pulse();

	digitalWrite(RS, LOW);
	PORTB = INIT;
	delayMicroseconds(4500);
	
	PORTB = INIT;
	delayMicroseconds(150);
	
	PORTB = INIT;
	delayMicroseconds(100);
	
	PORTB = FOURBIT;
	delayMicroseconds(100);

	PORTB = B0010;
	pulse();
	PORTB = FUNCTION_SET;
	pulse();
	
	PORTB = ZEROS;
	pulse();
	PORTB = LCD_OFF;
	pulse();

	PORTB = ZEROS;
	pulse();
	PORTB = CLEAR;
	pulse();
	delay(4);
	
	PORTB = ZEROS;
	pulse();
	PORTB = ENTRY_MODE;
	pulse();

	// LCD Done
	PORTB = ZEROS;
	pulse();
	PORTB = LCD_ON;
	pulse();

	PORTB = 0100;
	pulse();
	PORTB = 1101;
	pulse();
	PORTB = 0100;
	pulse();
	PORTB = 1101;
	pulse();
	PORTB = 0100;
	pulse();
	PORTB = 1101;
	pulse();
}

void loop()
{
	// PORTB = 0010;
	// pulse();
	// PORTB = 0001;
	// pulse();
	//delay(1000);
}

void pulse()
{
	delayMicroseconds(1);
	digitalWrite(ENABLE, HIGH);
	delayMicroseconds(1);
	digitalWrite(ENABLE, LOW);	
	delayMicroseconds(100);
}