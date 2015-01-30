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

#define RS			2          // Register Select, 1: Data Register, 0: Instruction Register
#define ENABLE			3          // Enable signal for writing or reading data
#define INIT			B0011      // First initialization string sent 3 times to LCD
#define FOURBIT			B0010      // Interface set to 4 bit. High bits sent first, low bits second.
#define ZEROS 			B00000000  // Empty port register for convenience
#define LCD_ON			B00001100  // LCD on command
#define LCD_OFF			B00001000  // LCD off command
#define CLEAR			B00000001  // LCD clear command
#define ENTRY_MODE		B00000110  // ENTRY_MODE command
#define FUNCTION_SET  	        B00101000  // Set number of lines and font
#define CD_SHIFT_LEFT           B00011000  // Left Cursor or Display Shift command
#define CD_SHIFT_RIGHT          B00011100  // Right Cursor or Display Shift command
#define SET_CGRAM               B01000000  // CGRAM base address
#define SETUP_SIZE              9          // Array size of LCD setup commands
#define BLENGTH                 40         // Length of display plus extra for null string character
#define ROW_TOP                 B10000000  // High four bits for accessing top row
#define ROW_BOTTOM              B11000000  // High four bits for accessing bottom row

#define ARRAY_SIZE(x)	(sizeof(x) / sizeof(x[0]) - 1) // Array Size Macro for strings without null

void blink (int, int);
void characterMode(void);
void clear(void);
void command(byte x);
void commandMode(void);
void createChar (int, byte*);
void lcdInitialize();
void printLine(String);
void pulse(void);
void scrollDisplayLeft(void);
void scrollDisplayRight(void);
void setupCommand(byte x);
void setCursor(int, int);
void write(int);

#endif
