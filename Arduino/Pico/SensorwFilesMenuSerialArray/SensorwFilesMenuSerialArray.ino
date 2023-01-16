// SensorwFilesMenuSerial
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


// delete a file in the directory
void delFile();

// asks for a specific file (0-9) to display
// prints the file contents to the screen
void displaySamples();

// asks user for a single number to create a filename 
// returns an integer 0-9
unsigned int getNum();

// returns a file name to be used for processing
String getfileName();

// prints the menu
void printMenu();

// prints the directory(s) starting at the root /
void printRootDir();

// helper function to print a directory, recursive so be careful when modding
void printDirectory(File dir, int numTabs = 3);

// asks for a specific file to store data
// reads Sensorpin and converts value to a voltage
void readSamples();

// build name for testfile
String setName(unsigned int i);

// converts a local file to a user file to be downloaded to PC
void userFile();

int sensorPin = A0;                 // input pin for ADC
// Step_1 scalar values go away
// unsigned int sensorValue = 0;       // value coming from the ADC
// double voltage = 0;                 // voltage calculated from ADC
unsigned int numSamples = 360;       // number of samples to capture
unsigned int delaySamples = 10;    // milliseconds between each sample
File testFile;                      // File object for storing data
String dir = "/";                   // base directory for files
String basename = "File_";           // base of filename
String dayFileName;
char bufName[] = "File_0";
unsigned int bufLen = 6;
// Step_1 convert the two scalar values to arrays
double sensorValues[360];
double voltages[360];

int choice = 0;                     // choice for menu and questions
int returnKey = 0;                  // dummy variable for return key

void setup() {
    Serial.begin(115200); // opens serial port, sets data rate to 115200 bps
    while (!Serial) {delay(100);}
    // 1. Initialize filesystem

    Serial.print(F("Initializing filesystem..."));
    if (LittleFS.begin()){
        Serial.println(F("complete."));
    }else{
        Serial.println(F("failed."));
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

void delFile() 
{
    testFile = LittleFS.open(getfileName(), "r");
    if (LittleFS.exists(dayFileName))
    {
        Serial.print("DELETING file  ");
        Serial.println(dayFileName);
        LittleFS.remove(dayFileName);
    }
}

String getfileName()
{
    
    unsigned int num = getNum();
    dayFileName = setName(num);
    Serial.println(dayFileName);
    return dayFileName;
}

String setName(unsigned int i)
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
    testFile = LittleFS.open(getfileName(), "r");
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
    testFile = LittleFS.open(getfileName(), "w");
    if (testFile)
    {
        Serial.print(F("Reading ADC..."));
        for (int i=0;i<numSamples;i++)
        {
            // read the value from the sensor:
            // Step_2 Use the arrays to save the data
            sensorValues[i] = analogRead(sensorPin);

            // Convert ADC value into voltage
            // Step_2 Be sure you use an array everywhere its needed!
            voltages[i] = sensorValues[i]/4096.0 * 3.30;

            delay(delaySamples);
        }

        // Save values to a file
        // Step_3 Pull the saving of samples out of the reading section
        // and create a new loop which saves the array to the file
        for (int i=0;i<numSamples;i++)
        {
            testFile.print(sensorValues[i]);
            testFile.print("\t");
            testFile.println(voltages[i]);
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

// prints the directory(s) starting at the root /
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
    Serial.println("\td to DELETE a file");
    Serial.println("\ts for Show samples");
    Serial.println("\tr for  record samples");
    Serial.println("Followed by return.");
}
