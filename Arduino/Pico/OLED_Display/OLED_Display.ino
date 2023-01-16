// Display program for using Adafruit FeatherWing OLED 128x64
// Setup to display 3 lines of 12-14 characters per line
// If using Pico, use GP20 for SDA and GP21 for SCL
// Or change appropriately using the Wire commands below
// Uses Arduino String class for text 

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

String line_1_Sans_9 = "Sans 9pt";
String line_2_Sans_9 = "abcdefg 78901";
String line_3_Sans_9 = "12-14 chr/line";

String line_1_Mono = "Mono 9pt";
String line_2_Mono = "abcd 567890";
String line_3_Mono = "11-12 chr";

String line_1_Sans_12 = "Sans 12";
String line_2_Sans_12 = "abcd 12345";

void setup() {
    Serial.begin(115200);
    while (!Serial) {delay(100);}
    Wire.setSDA(02);
    Wire.setSCL(03);

    Serial.println("128x64 OLED FeatherWing test");
    delay(250); // wait for the OLED to power up
    // display.begin(0x3C, true); // Address 0x3C default
    if (!display.begin(0x3C, true))
    {
        Serial.println("Display not found!");
    }
    else
    {
        Serial.println("OLED begun");

        // setup display parameters
        display.setRotation(1);
        display.setTextSize(1);
        display.setTextColor(SH110X_WHITE);

        // Three steps to display, all must be done
        // 1. Clear buffer and display
        display.clearDisplay();
        display.display();

        // 2. Set start location and font
        display.setCursor(0,10);
        display.setFont(&FreeSans9pt7b);

        // 3. Build display buffer then display
        display.println(line_1_Sans_9);
        display.println(line_2_Sans_9);
        display.println(line_3_Sans_9);
        display.display(); // display all of the above

        delay(4000);

        // 1. Clear buffer and display
        display.clearDisplay();
        display.display();
        
        // 2. Set start location and font
        display.setCursor(0,18);
        display.setFont(&FreeMono9pt7b);

        /// 3. Build display buffer then display
        display.println(line_1_Mono);
        display.println(line_2_Mono);
        display.println(line_3_Mono);
        display.display(); // actually display all of the above

        delay(4000);

        // 1. Clear buffer and display
        display.clearDisplay();
        display.display();
        
        // 2. Set start location and font
        display.setCursor(0,24);
        display.setFont(&FreeSans12pt7b);

        // 3. Build display buffer then display
        display.println(line_1_Sans_12);
        display.println(line_2_Sans_12);
        display.display(); // actually display all of the above
    }    
}

void loop() {

}
