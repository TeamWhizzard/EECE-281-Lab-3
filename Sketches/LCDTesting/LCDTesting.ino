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
#define LCD_ON			B1100	// LCD on, precede with ZEROS command for high bits
#define LCD_OFF			B1000	// LCD off, precede with ZEROS
#define CLEAR			B0001	// LCD clear, precede with ZEROS
#define ENTRY_MODE		B0110	// ENTRY_MODE Mode, precede with ZEROS
#define FUNCTION_SET	B1000	// Set number of lines and font
#define SETUP_STEPS		   14	// Number of commands that are carried out during LCD initilization

const byte setupCmds[SETUP_STEPS] = {INIT, INIT, INIT, FOURBIT, B0010, FUNCTION_SET, ZEROS, LCD_OFF,
									ZEROS, CLEAR, ZEROS, ENTRY_MODE, ZEROS, LCD_ON};
const int setupDelays[SETUP_STEPS] = {4500, 150, 100, 100, 0, 100, 0, 100, 0, 2500, 0, 100, 0, 100};

void setup()
{
	//Serial Port Init
	//Serial.begin(115200);

	// Pin Mapping
	DDRB = B111111; // Enable Port B as output
	pinMode(RS, OUTPUT);
	pinMode(ENABLE, OUTPUT);

	// Initialize LCD
	delay(50); // 20 ms before LCD init

	commandMode();
	digitalWrite(ENABLE, LOW);

	for (int i = 0; i < SETUP_STEPS; i++) // Initialize LCD
	{
		command(setupCmds[i]);
		delayMicroseconds(setupDelays[i]);
	}

	characterMode();
}

void loop()
{
	command(B1011);
	command(B1011);
	delay(700);
	command(B1101);
	command(B1100);
	delay(700);
	command(B1111);
	command(B1101);
	delay(700);
	clear();
	delay(700);
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

void clear()
{
	commandMode();
	command(ZEROS);
	command(CLEAR);
	delayMicroseconds(2500);
	characterMode();
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