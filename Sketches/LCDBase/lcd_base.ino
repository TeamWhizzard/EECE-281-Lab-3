/* TODO header */

#include <LiquidCrystal.h>

const int pinRS = 2;
const int pinE = 3;
const int pinD4 = 8;
const int pinD5 = 9;
const int pinD6 = 10;
const int pinD7 = 11;
const int pinMoisture = A0;

const String message_one = "Hello and welcome to out demo!";
const String message_two = "EECE 281 section 202 Team L2D-7B";
const String message_whizzard = "Whizzard is proud to present:";
const String message_title = "  CRAPPY BIRD!";

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(pinRS, pinE, pinD4, pinD5, pinD6, pinD7);

void setup() {
  lcd.begin(16, 2); // set up LCD's number of columns and rows
  
  // Print startup messages to LCD
  lcd.setCursor(0,0);
  lcd.print(message_one.substring(0,15)); // first 16 characters of message
  lcd.setCursor(0,1);
  lcd.print(message_one.substring(15)); // remaining characters of message
  delay(1000);
  lcd.clear();
  
  // displays second message
  lcd.setCursor(0,0);
  lcd.print(message_two);
  delay (1000);
  for (int i = 0; i < message_two.length() - 16; i++) { // scroll to end of message
    lcd.scrollDisplayLeft();
    delay (500);
  }
  delay(2000);
  lcd.clear();
  
  // Custom message
  lcd.setCursor(0,0);
  lcd.print(message_whizzard.substring(0,15)); // first 16 characters of message
  lcd.setCursor(0,1);
  lcd.print(message_whizzard.substring(15)); // remaining characters of message
  delay(1000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(message_title);
  delay(2000);
  
  for (int j = 0; j < 4; j++) {
    lcd.noDisplay();
    delay(500);
    lcd.display();
    delay(500);
  }
  
  lcd.clear();
}

void loop() {
  lcd.print(analogRead(pinMoisture));
  delay(1000); 
  lcd.clear();
}
