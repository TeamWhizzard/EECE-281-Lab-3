#ifndef lab3LCD
#define lab3LCD
#include "Arduino.h"

/*
 SYM  LCD  UNO
 ================
 RS   4	   2
 E    6	   3
 DB7  14   11 } Accessible through
 DB6  13   10 } PortB for communication
 DB5  12   9  } and DDRB for pin
 DB4  11   8  } setup.
 */

#define ZEROS 			B0000	// Empty port register for convenience
#define RS			2	// Register Select, 1: Data Register, 0: Instruction Register
#define ENABLE			3	// Enable signal for writing or reading data
#define INIT			B0011	// First initialization string sent 3 times to LCD
#define FOURBIT			B0010	// Interface set to 4 bit. High bits sent first, low bits second.
#define LCD_ON			B1100	// LCD on, precede with ZEROS command for high bits
#define LCD_OFF			B1000	// LCD off, precede with ZEROS
#define CLEAR			B0001	// LCD clear, precede with ZEROS
#define ENTRY_MODE		B0110	// ENTRY_MODE Mode, precede with ZEROS
#define FUNCTION_SET  	        B1000	// Set number of lines and font
#define SETUP_SIZE		14	// Array size of both setup elements
#define BLENGTH                 40      // Length of display plus extra for null string character
#define CD_SHIFT                B0001   // First four bits of Cursor or Display Shift
#define CD_SHIFT_LEFT           B1000   // Second four bits of Left Cursor or Display Shift
#define CD_SHIFT_RIGHT          B1100   // Second four bits of Right Cursor or Display Shift
#define SET_CGRAM               B0100   // First for bits of Set CGRAM Address command
#define ROW_TOP                 B1000   // High four bits for accessing top row, followed with ZEROS
#define ROW_BOTTOM              B1100   // High four bits for accessing bottome row, followed with ZEROS

#define ARRAY_SIZE(x)	(sizeof(x) / sizeof(x[0]) - 1) // Array Size Macro for strings without null

void lcdInitialize ();
void printLine(String);
void setCursor(int, int);
void scrollDisplayLeft(void);
void scrollDisplayRight(void);
void blink (int, int);
void clear(void);
void createChar (int, char*);

void command(byte x);
void pulse(void);
void commandMode(void);
void characterMode(void);

#endif
