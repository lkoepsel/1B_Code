// SensorwFilesMenu

// A menu-based frame work for the following tasks
// p - print directory
// d - delete ALL files in the directory
// r - record numSamples number of samples with a delaySamples in between each sample
// s - show the contents of a sample file 
// The menu system uses a single character response, 
// so only A-Z/0-9 are available as responses


#include "Arduino.h"
#include "LittleFS.h"


// asks for a specific file (0-9) to display
// prints the file contents to the screen
void displaySamples();

// asks user for a single number to create a filename 
// returns an integer 0-9
unsigned int getNum();

// prints the directory(s) starting at the root /
void printRootDir();

// helper function to print a directory, recursive so be careful
void printDirectory(File dir, int numTabs = 3);

// asks for a specific file to store data
// reads Sensorpin and converts value to a voltage
void readSamples();

// build name for testfile
String setName(unsigned int i);

// deletes ALL files in the directory
void delFiles();

// prints the menu
void printMenu();

int sensorPin = A0;                 // input pin for ADC
unsigned int sensorValue = 0;       // value coming from the ADC
unsigned int numSamples = 20;       // number of samples to capture
unsigned int delaySamples = 100;    // milliseconds between each sample
double voltage = 0;                 // voltage calculated from ADC
File testFile;                      // File object for storing data
String dir = "/";                   // base directory for files
String basename = "File_";           // base of filename
String dayFileName;


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
                 Serial.println("Deleting directory");
                 delFiles();
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

void displaySamples()
{
    // 5. Display values from a file
    Serial.print("Enter number of file desired (0-9):");
    unsigned int num = getNum();
    dayFileName = setName(num);
    Serial.println(dayFileName);
    testFile = LittleFS.open(dayFileName, "r");
    if (testFile)
    {
        Serial.print("Reading samples file, ");
        Serial.println(testFile.name());
        Serial.println(testFile.readString());
        testFile.close();
    }
    else
    {
        Serial.print("Problem reading samples file!");
        Serial.println(dayFileName);
    }
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
            sensorValue = analogRead(sensorPin);


            // Convert ADC value into voltage
            voltage = sensorValue/4096.0 * 3.30;


            // Save value to a file
            testFile.print(sensorValue);
            testFile.print("\t");
            testFile.print(voltage);
            testFile.print("\n");
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

// deletes ALL files in the directory
void delFiles() 
{
    Dir dir = LittleFS.openDir("/");
    while (dir.next()) 
    {
        Serial.print(dir.fileName());
        Serial.println(" deleted");
        LittleFS.remove(dir.fileName());
    }
}

// prints the menu
void printMenu()
{
    Serial.println("Enter one of the following:");
    Serial.println("\tp for Print directory");
    Serial.println("\td for Delete directory(DELETES ALL FILES!!)");
    Serial.println("\ts for Show samples");
    Serial.println("\tr for  record samples");
    Serial.println("Followed by return.");
}
