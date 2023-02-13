// Display program for using both Adafruit FeatherWing OLED 128x64
// and Sparkfun 14 segment Alphanumeric display
// Setup to OL_display 3 lines of 12-14 characters per line
// For Pico, and uses both Wire and Wire1 interfaces
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

// Adafruit FeatherWing OLED 128x64 - 4650
// https://learn.adafruit.com/adafruit-128x64-oled-featherwing
Adafruit_SH1107 OL_display = Adafruit_SH1107(64, 128, &Wire);

//SparkFun Qwiic Alphanumeric Display - Green COM-18566
// https://learn.sparkfun.com/tutorials/sparkfun-qwiic-alphanumeric-display-hookup-guide
HT16K33 AN_display;

String line_1 = "Sans 9pt";
String line_2 = "abcdefg 78901";
String line_3 = "12-14 chr/line";
unsigned int start_delay = 2;       // 2 slow blinks to indicate successful boot
unsigned int start_blinks = 1;      
unsigned int error_delay = 2;       // 32 fast blinks to indicate error
unsigned int error_blinks = 16;     // in finding either display
unsigned int success_delay = 2;     // 4 medium blinks to indicate success
unsigned int success_blinks = 2;    // in running

// Adafruit - I2C interface and addresss
unsigned int SDA_0 = 8;
unsigned int SCL_0 = 9;
byte address_0 = 0x3C;

// Sparkfun - I2C interface and addresss
unsigned int SDA_1 = 14;
unsigned int SCL_1 = 15;
byte address_1 = 0x70;

// blink: delay for n seconds, blinking n/2 times per second
void blink(unsigned int seconds, unsigned int times);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    blink(start_delay, start_blinks);

    // init Adafruit I2C interface
    Wire.setSDA(SDA_0);
    Wire.setSCL(SCL_0);
    Wire.begin();

    // init Sparkfun I2C interface
    Wire1.setSDA(SDA_1);
    Wire1.setSCL(SCL_1);
    Wire1.begin();

    if (!OL_display.begin(address_0, true))
    {
        blink(error_delay, error_blinks);
    }
    else if (AN_display.begin(address_1,
                                DEFAULT_NOTHING_ATTACHED,
                                DEFAULT_NOTHING_ATTACHED,
                                DEFAULT_NOTHING_ATTACHED,
                                 Wire1) == false)
    {
      blink(error_delay, error_blinks);
    }
    // setup Adafruit parameters
    OL_display.setRotation(3);
    OL_display.setTextSize(1);
    OL_display.setTextColor(SH110X_WHITE);

    // Three steps to Adafruit, all must be done
    // 1. Clear buffer and diplay
    OL_display.clearDisplay();
    OL_display.display();

    // 2. Set start location and font
    OL_display.setCursor(0,10);
    OL_display.setFont(&FreeSans9pt7b);

    // 3. Build display buffer then display
    OL_display.println(line_1);
    OL_display.println(line_2);
    OL_display.println(line_3);

    // Finally, display lines above
    OL_display.display(); 

    // simple single line for Sparkfun
    AN_display.print("SCSS");

    // finish with success blink
    blink(success_delay, success_blinks);
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
            delay(1000/times/2); // wait for seconds/2, blinking n * 2 times
            digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
            delay(1000/times/2); // wait for seconds/2, blinking n * 2 times
        }
    }
}
