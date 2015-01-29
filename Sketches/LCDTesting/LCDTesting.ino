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
#define FUNCTION_SET	B1000	// Set number of lines and font
#define BUSY			4

const byte SETUP[] = {FOURBIT, B0010, FUNCTION_SET, ZEROS, LCD_OFF, ZEROS, CLEAR, ZEROS, ENTRY_MODE};

void setup()
{
	//Serial Port Init
	Serial.begin(115200);

	// Pin Mapping
	DDRB = B1111; // Enable Port B as output
	pinMode(RS, OUTPUT);
	pinMode(ENABLE, OUTPUT);
	pinMode(BUSY, INPUT);
	//DDRD = DDRD | B11111100; // Enable Port D as output without touching pins 0, 1.

	// Initialize LCD
	delay(50); // 20 ms before LCD init

	digitalWrite(RS, LOW); // Set RS Pin to low
	digitalWrite(ENABLE, LOW);
	
	command(INIT);
	delayMicroseconds(4500);
	
	command(INIT);
	delayMicroseconds(150);
	
	command(INIT);
	delayMicroseconds(100);
	
	command(FOURBIT);
	delayMicroseconds(100);

	command(FOURBIT);
	command(FUNCTION_SET);
	
	command(ZEROS);
	command(LCD_OFF);

	clear();
	
	command(ZEROS);
	command(ENTRY_MODE);

	// LCD Done
	command(ZEROS);
	command(LCD_ON);

	digitalWrite(RS, HIGH);
		
}

void loop()
{
	character(1011);
	character(1011);
	delay(1000);
	character(1101);
	character(1100);
	delay(1000);	
	character(1111);
	character(1101);
	delay(1000);
}

void pulseHigh()
{
	delayMicroseconds(1);
	digitalWrite(ENABLE, HIGH);
	delayMicroseconds(1);
}

void pulseLow()
{
	delayMicroseconds(100);
	digitalWrite(ENABLE, LOW);	
	delayMicroseconds(1);
}

void command(byte x)
{
	PORTB = x;
	pulseHigh();
	pulseLow();
}

void clear()
{
	digitalWrite(RS, LOW);
	delayMicroseconds(1);
	command(ZEROS);
	command(CLEAR);
	delayMicroseconds(3000);
}

void character(byte x)
{
	PORTB = x;
	pulseHigh();
	pulseLow();
}