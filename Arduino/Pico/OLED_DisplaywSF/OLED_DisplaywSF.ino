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
#include <LittleFS.h>
#include <SingleFileDrive.h>

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

String line_1_plug = "Plug Callback";
String line_1_unplug = "Unplug Callback";
String line_1_delete = "Delete Callback";

void setup() {
    // Serial.begin(115200);
    // while (!Serial) {delay(100);}
    Wire.setSDA(20);
    Wire.setSCL(21);

    // Serial.println("128x64 OLED FeatherWing test");
    delay(250); // wait for the OLED to power up
    // display.begin(0x3C, true); // Address 0x3C default
    if (!display.begin(0x3C, true))
    {
        // Serial.println("Display not found!");
    }
    else
    {
        // Serial.println("OLED begun");

        // setup display parameters
        display.setRotation(1);
        display.setTextSize(1);
        display.setTextColor(SH110X_WHITE);

        LittleFS.begin();
        singleFileDrive.onPlug(SFplug);
        singleFileDrive.onUnplug(SFunplug);
        singleFileDrive.onDelete(SFdelete);
        
        singleFileDrive.begin("File_1", "DataRecorder.csv");
    }    
}

void loop() {

}

void SFplug(uint32_t data) {
    // Tell my app not to write to flash, we're connected
    // 1. Clear buffer and display
    display.clearDisplay();
    display.display();
    
    // 2. Set start location and font
    display.setCursor(0,24);
    display.setFont(&FreeSans9pt7b);

    // 3. Build display buffer then display
    display.println(line_1_plug);
    display.display(); // actually display all of the above
}

void SFunplug(uint32_t data) {
    // I can start writing to flash again
    // 1. Clear buffer and display
    display.clearDisplay();
    display.display();
    
    // 2. Set start location and font
    display.setCursor(0,24);
    display.setFont(&FreeSans9pt7b);

    // 3. Build display buffer then display
    display.println(line_1_unplug);
    display.display(); // actually display all of the above
}

void SFdelete(uint32_t data) {
    // Maybe LittleFS.remove("myfile.txt")?  or do nothing
    // 1. Clear buffer and display
    display.clearDisplay();
    display.display();
    
    // 2. Set start location and font
    display.setCursor(0,24);
    display.setFont(&FreeSans9pt7b);

    // 3. Build display buffer then display
    display.println(line_1_delete);
    display.display(); // actually display all of the above
}
