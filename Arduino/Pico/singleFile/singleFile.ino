#include <LittleFS.h>
#include <SingleFileDrive.h>

// asks for a specific file to store data
// reads Sensorpin and converts value to a voltage
void readSamples();

// asks user for a single number to create a filename 
// returns an integer 0-9
unsigned int getNum();



void myPlugSF(uint32_t data) {
    // Tell my app not to write to flash, we're connected
    Serial.println("DO NOT write to Flash");
}

void myUnplugSF(uint32_t data) {
    // I can start writing to flash again
    Serial.println("You may write to Flash");

}

void myDeleteSF(uint32_t data) {
    // Maybe LittleFS.remove("myfile.txt")?  or do nothing
    Serial.println("User would like to delete the file");
}

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
        if (!singleFileDrive.begin("/File_1", "DataRecorder.csv"))
        {
            Serial.println("Problem with files for singleFileDrive");
        }
        else
        {
            Serial.println("Success! Do you see it?");
        }
    }
}

void loop() {
    // Take some measurements, delay, etc.
}

// asks user for a single number to create a filename 
// returns an integer 0-9
unsigned int getNum()
{
    while(true)
    {    
        if (Serial.available() > 0) 
        {
            choice = Serial.read();
            returnKey = Serial.read();
            return choice - 48;
        }
    // from Arduino docs, rec'd for stability
    delay(1);
    }
}

String setName(unsigned int i)
{
    return dayFileName = dir + basename + String(i);
}

void readSamples()
{
    // 2. Read ADC
    Serial.print("Enter number of file desired (0-9):");
    unsigned int num = getNum();
    dayFileName = setName(num);
    Serial.println(dayFileName);
    testFile = LittleFS.open(dayFileName, "w");
    if (testFile)
    {
        Serial.print(F("Reading ADC..."));
        for (int i=0;i<numSamples;i++)
        {
            // read the value from the sensor:
            sensorValue = analogRead(13);

            // Save value to a file
            testFile.print(sensorValue);
            testFile.print("\t");
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
