// Fortune - running code for Fortune cookie factory
// Adds external display and startup code to SensorwFileMenuSerial
// Provides a menu per docs below along with a filesystem to save files on Pico
// Communicates solely through Serial port (USB cable)

// A menu-based frame work for the following tasks
// p - print directory
// d - delete a file in the directory
// r - record numSamples number of samples with a delaySamples in between each sample
// s - show the contents of a sample file 
// The menu system uses a single character response, 
// so only A-Z/0-9 are available as responses


#include "Arduino.h"
#include "LittleFS.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Fonts/FreeSans9pt7b.h>

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

String line_1_noSerial = "No Serial Port";
String line_2_noSerial = "Logging to";
String line_3_noSerial ;

String line_1_Mono = "Mono 9pt";
String line_2_Mono = "abcd 567890";
String line_3_Mono = "11-12 chr";

String line_1_Sans_12 = "Sans 12";
String line_2_Sans_12 = "abcd 12345";

// slow blink routine to indicate an error, blink n times
void blink_error(unsigned int times);

// fast blink routine to indicate an OK, blink n times
void blink_ok(unsigned int times);

// boolean function to confirm choice
bool confirm();

// delete a file in the directory
void delFile();

// deletes ALL files in the directory
void delALLfiles();

// asks for a specific file (0-9) to display
// prints the file contents to the screen
void displaySamples();

// asks user for a single number to create a filename 
// returns an integer 0-9
unsigned int getNum();

// returns a alpha file name to be used for processing
String getAfileName();

// returns a numeric file name to be used for processing
String getNfileName();

// prints the menu
void printMenu();

// prints the directory(s) starting at the root /
void printRootDir();

// helper function to print a directory, recursive so be careful when modding
void printDirectory(File dir, int numTabs = 3);

// asks for a specific file to store data
// reads Sensorpin and converts value to a voltage
void readSamples();

// startup program, will execute upon a 5 second delay
// of the serial cable being attached
// reads Sensorpin and converts value to a voltage
void startup();

// build alpha name for testfile
String setNameA(unsigned int i);

// build numeric name for testfile
String setNameN(unsigned int i);

// converts a local file to a user file to be downloaded to PC
void userFile();

int sensorPin = A0;                 // input pin for ADC
unsigned int sensorValue = 0;       // value coming from the ADC
unsigned int numSamples = 20;       // number of samples to capture
unsigned int delaySamples = 100;    // milliseconds between each sample

unsigned int startupSamples = 50;       // number of samples to capture
unsigned int startupdelaySamples = 100; // milliseconds between each sample
unsigned int error_delay = 500;         // time between error LED blinks (slow)
unsigned int ok_delay = 100;            // time between OK LED blinks (fast)

double voltage = 0;                 // voltage calculated from ADC

File testFile;                      // File object for storing data
String dir = "/";                   // base directory for files
String basename = "File_";           // base of filename
String dayFileName;

int no_menu_delay = 50;
int choice = 0;                     // choice for menu and questions
int returnKey = 0;                  // dummy variable for return key

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Wire.setSDA(20);
    Wire.setSCL(21);

    LittleFS.begin();
    unsigned int timer = 0;

    delay(250); // wait for the OLED to power up
    if (!display.begin(0x3C, true))
    {
        blink_error(3);
    }
    else
    {
        // setup display parameters
        display.setRotation(1);
        display.setTextSize(1);
        display.setTextColor(SH110X_WHITE);

        // Three steps to display, all must be done
        // 1. Clear buffer and display
        display.clearDisplay();
        display.display();

        // 2. Set start location and font
        display.setCursor(0,8);
        display.setFont(&FreeSans9pt7b);
    }
    while (!Serial) 
    {
        delay(100);
        timer++;
        if (timer > no_menu_delay)
        {
            // 3. Build display buffer then display
            // Display if powered w/o Serial interface
            display.println(line_1_noSerial);
            display.println(line_2_noSerial);
            // display.display(); // display all of the above
            startup();

            break;
        }
    }
    
    analogReadResolution(12);

    printMenu();
}

// Use void loop() to print menu
void loop() 
{
    if (Serial.available() > 0) 
    {
    // read the incoming byte:
        choice = Serial.read();
        returnKey = Serial.read();
        // menu based on choice
        // do something depending on choice:
        switch (choice) 
        {
            case 33:  // ! to delete directory
                 Serial.println("Delete all files!");
                 delALLfiles();
                 break;
            case 112:  // p for print directory
                 Serial.println("Directory");
                 printRootDir();  
                 break;
            case 100:  // d for delete directory
                 Serial.println("DELETE a file");
                 delFile();
                 break;
            case 115:  // s for show samples
                 Serial.println("Show samples");
                 displaySamples();
                 break;
            case 114:  // r for record samples
                 Serial.println("Record samples");
                 readSamples();
                 break;

            default:
                 printMenu();
        }
        delay(10);  // delay in between reads for stability
    }    

}

// Startup**********************
void blink_error(unsigned int times)
{
    for (int i=0;i<times;i++)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(error_delay);
        digitalWrite(LED_BUILTIN, LOW);
        delay(error_delay);
    }
}

void blink_ok(unsigned int times)
{
    for (int i=0;i<times;i++)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(ok_delay);
        digitalWrite(LED_BUILTIN, LOW);
        delay(ok_delay);
    }
}
// Startup**********************END

bool confirm()
{
    Serial.print(" Confirm y or n:");
    while(true)
    {    
        if (Serial.available() > 0) 
        {
            choice = Serial.read();
            returnKey = Serial.read();
            if (choice == 'y')
            {
                Serial.println("\n\rAll files to be deleted");
                return true;
            }
            else
            {
                Serial.println("\n\rNo files will be deleted");
                return false;
            }
        }
    // from Arduino docs, rec'd for stability
    delay(1);
    }
}

void delFile() 
{
    testFile = LittleFS.open(getNfileName(), "r");
    if (LittleFS.exists(dayFileName))
    {
        Serial.print("DELETING file  ");
        Serial.println(dayFileName);
        LittleFS.remove(dayFileName);
    }
}

void delALLfiles() 
{
    Serial.print("Do you want to delete ALL files?");
    if (confirm())
    {
        Dir dir = LittleFS.openDir("/");
        while (dir.next()) 
        {
            Serial.print(dir.fileName());
            Serial.println(" deleted");
            LittleFS.remove(dir.fileName());
        }
    }
}

String getAfileName()
{
    char letter;
    letter = 'A';
    while(true)
    {
        dayFileName = setNameA(letter);
        if (!LittleFS.exists(dayFileName))
        {
            return dayFileName;
        }
        else
        {
            (int) ++letter;
        }
    }    
}

String getNfileName()
{
    
    unsigned int num = getNum();
    dayFileName = setNameN(num);
    Serial.println(dayFileName);
    return dayFileName;
}

String setNameA(char a)
{
    return dayFileName = dir + basename + a;
}

String setNameN(unsigned int i)
{
    return dayFileName = dir + basename + String(i);
}

unsigned int getNum()
{
    Serial.print("Enter number of file desired (0-9):");
    while(true)
    {    
        if (Serial.available() > 0) 
        {
            choice = Serial.read();
            returnKey = Serial.read();
            if ((choice > 47) && (choice < 58))
            {
                return choice - 48;
            }
            else
            {
                Serial.print("\n\rValue must be a number from 0-9, enter number:");
            }
        }
    // from Arduino docs, rec'd for stability
    delay(1);
    }
}

void displaySamples()
{
    testFile = LittleFS.open(getNfileName(), "r");
    if (testFile)
    {
        Serial.print("Reading samples file, ");
        Serial.println(testFile.name());
        Serial.println(testFile.readString());
        testFile.close();
    }
    else
    {
        Serial.print("Problem reading samples file! ");
        Serial.println(dayFileName);
    }
}


void readSamples()
{
    testFile = LittleFS.open(getNfileName(), "w");
    if (testFile)
    {
        Serial.print(F("Reading ADC..."));
        for (int i=0;i<numSamples;i++)
        {
            // read the value from the sensor:
            sensorValue = analogRead(sensorPin);

            // Convert ADC value into voltage
            voltage = sensorValue/4096.0 * 3.30;

            // Save value to a file
            testFile.print(sensorValue);
            testFile.print("\t");
            testFile.println(voltage);
            delay(delaySamples);
        }

        // Data read and stored, completed
        Serial.print(F(testFile.name()));
        Serial.println(F(" written."));
        testFile.close();
    }
    else
    {
        Serial.println("Problems creating file!");
    }
}

// Startup**********************
void startup()
{
    String startfilename = getAfileName();
    testFile = LittleFS.open(startfilename, "w");
    display.println(startfilename);
    display.display();
    if (testFile)
    {
        blink_ok(2);
        for (int i=0;i<startupSamples;i++)
        {
            // read the value from the sensor:
            sensorValue = analogRead(sensorPin);

            // Convert ADC value into voltage
            voltage = sensorValue/4096.0 * 3.30;

            // Save value to a file
            testFile.print(sensorValue);
            testFile.print("\t");
            testFile.println(voltage);
            delay(startupdelaySamples);
        }

        // Data read and stored, completed
        testFile.close();
    }
    else
    {
        blink_error(6);
    }
}
// Startup**********************END

void printRootDir()
{
    // Open root folder
    File dir = LittleFS.open("/", "r");
    // Cycle all the directories and files
    printDirectory(dir);
}

void printDirectory(File dir, int numTabs) {
  while (true) {
 
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.print(entry.size(), DEC);
      Serial.print("\t");
      Serial.println(" bytes");
 
    }
    entry.close();
  }
}

void printMenu()
{
    Serial.println("Enter one of the following:");
    Serial.println("\tp for Print directory");
    Serial.println("\td to Delete a file");
    Serial.println("\ts for Show samples");
    Serial.println("\tr for  Record samples");
    Serial.println("\t! to Delete ALL files");
    Serial.println("Followed by return.");
}
