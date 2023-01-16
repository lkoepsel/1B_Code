// TEST PROGRAM ONLY DO NOT USE!!!

#include <LittleFS.h>
#include <SingleFileDrive.h>

// asks for a specific file to store data
// reads Sensorpin and converts value to a voltage
void readSamples();

// asks user for a single number to create a filename 
// returns an integer 0-9
unsigned int getNum();

// Called when the USB stick connected to a PC and the drive opened
// Note this is from a USB IRQ so no printing to SerialUSB/etc.
void myPlugSF(uint32_t i);

// Called when the USB is ejected or removed from a PC
// Note this is from a USB IRQ so no printing to SerialUSB/etc.
void myUnplugSF(uint32_t i);

// Called when the PC tries to delete the single file
// Note this is from a USB IRQ so no printing to SerialUSB/etc.
void myDeleteSF(uint32_t i);

bool okayToWrite = true;
int sensorPin = A0;                 // input pin for ADC
unsigned int sensorValue = 0;       // value coming from the ADC
unsigned int numSamples = 20;       // number of samples to capture
unsigned int delaySamples = 100;    // milliseconds between each sample
File testFile;                      // File object for storing data
String dir = "/";                   // base directory for files
String basename = "File_";           // base of filename
String dayFileName;

int choice = 0;                     // choice for menu and questions
int returnKey = 0;                  // dummy variable for return key

void setup() {
    Serial.begin(115200);
    while (!Serial) {delay(100);}

    Serial.println("Single File Test");

    if (!LittleFS.begin())
    {
        Serial.println("LittleFS not found!");
    }
    else
    {
        Serial.println("Single File Test begun");
        singleFileDrive.onPlug(myPlugSF);
        singleFileDrive.onUnplug(myUnplugSF);
        singleFileDrive.onDelete(myDeleteSF);
        // readSamples();
        if (!singleFileDrive.begin("File_1", "DataRecorder.csv"))
        {
            Serial.println("Problem with files for singleFileDrive");
        }
        else
        {
            Serial.println("Success! Wait for PICODRIVE to appear in File Manager");
        }
    }
}

void loop() {
    // Take some measurements, delay, etc.
}

void myPlugSF(uint32_t i) {
    // Tell my app not to write to flash, we're connected
  (void) i;
  okayToWrite = false;
}

void myUnplugSF(uint32_t i) {
    (void) i;
    okayToWrite = true;
}

void myDeleteSF(uint32_t i) {
    (void) i;
    LittleFS.remove("data.csv");
}

