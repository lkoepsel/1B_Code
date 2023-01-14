// Simple Test of the GEEEKPI LCD with Backlight Display
// After using, I've determined the display isn't worth the effort
// This test works, however, the display is quite dim and old technology

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27, if new version please use 0x3F instead.

void setup()
{
  Wire.setSDA(20);
  Wire.setSCL(21);
  // Wire.begin();

  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight
}

void loop()
{
  lcd.setCursor(0, 0); // set the cursor to column 3, line 0
  lcd.print("ABCDEFGHIJKLMNOPNOPQR");  // Print a message to the LCD
  
  lcd.setCursor(0, 1); // set the cursor to column 2, line 1
  lcd.print("QRSTUVWXYZ012345");  // Print a message to the LCD.
}
