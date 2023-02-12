// Display program for using Adafruit FeatherWing OLED 128x64
// Setup to OL_display 3 lines of 12-14 characters per line
// If using Pico, default of GP06 for SDA and GP07 for SCL
// Or change appropriately using the Wire commands below
// Uses Arduino String class for text 

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <SparkFun_Alphanumeric_Display.h>

Adafruit_SH1107 OL_display = Adafruit_SH1107(64, 128, &Wire);
//SparkFun Qwiic Alphanumeric Display - Green COM-18566
// https://learn.sparkfun.com/tutorials/sparkfun-qwiic-alphanumeric-display-hookup-guide
// Connect via QWIC connector to pin cable
// SDA to pin SDA (above AREF)
// SCLK to pin SCL (above SDA)
// 5V to 5V 
// GND to GND
HT16K33 AN_display;

String line_1_Sans_9 = "Sans 9pt";
String line_2_Sans_9 = "abcdefg 78901";
String line_3_Sans_9 = "12-14 chr/line";
unsigned int start_delay = 2;       // n seconds before logging data
unsigned int start_blinks = 1;      // n/2 blinks per second, indicate ADC read
unsigned int error_delay = 2;       // n seconds before logging data
unsigned int error_blinks = 8;      // n/2 blinks per second, indicate ADC read
unsigned int success_delay = 2;       // n seconds before logging data
unsigned int success_blinks = 4;      // n/2 blinks per second, indicate ADC read

// blink: delay for n seconds, blinking n/2 times per second
void blink(unsigned int seconds, unsigned int times);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    blink(start_delay, start_blinks);

    delay(250); // wait for the OLED to power up
    if (!OL_display.begin(0x3C, true))
    {
        blink(error_delay, error_blinks);
    }
    else if (AN_display.begin() == false)
    {
      blink(error_delay, error_blinks);
    }
    else
    {
        // setup OL_display parameters
        OL_display.setRotation(3);
        OL_display.setTextSize(1);
        OL_display.setTextColor(SH110X_WHITE);

        // Three steps to OL_display, all must be done
        // 1. Clear buffer and OL_display
        OL_display.clearDisplay();
        OL_display.display();

        // 2. Set start location and font
        OL_display.setCursor(0,10);
        OL_display.setFont(&FreeSans9pt7b);

        // 3. Build OL_display buffer then OL_display
        OL_display.println(line_1_Sans_9);
        OL_display.println(line_2_Sans_9);
        OL_display.println(line_3_Sans_9);
        OL_display.display(); // OL_display all of the above
        AN_display.print("SCSS");
        blink(success_delay, success_blinks);
    }    
}

void loop() {

}

void blink(unsigned int seconds, unsigned int times)
{
    for (unsigned int i = 0; i < seconds; i++) 
    {
        for (unsigned int j = 0; j < times; j++) 
        {    
            digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(1000/times/2); // wait for a second, blinking 
            digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
            delay(1000/times/2); // wait for a second, blinking
        }
    }
}
