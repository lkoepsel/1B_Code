// Sensor

// Reads an analog pin, convert to another value  and save to filesystem
// 1. Initialize - setup the sensor and filesystem
// 2. Read ADC pin - get the value from pin connected to the sensor
// 3. Convert - convert ADC value to temperature, voltage, capacitance etc
// 4. Save - save converted value along with optional time stamp tofile system. 
// 5. Display - show the values on local display or via a USB cable to a PC


#include "Arduino.h"
#include "LittleFS.h"

void printDirectory(File dir, int numTabs = 3);
void delFiles(File dir);

int sensorPin = A0;                 // input pin for ADC
unsigned int sensorValue = 0;       // value coming from the ADC
unsigned int numSamples = 20;       // number of samples to capture
unsigned int delaySamples = 1000;    // milliseconds between each sample
double voltage = 0;                 // voltage calculated from ADC
unsigned int numfiles = 7;
File testFile;
char filename[] = "/1";   // file to store sample data
String dayFileName;

void printDir()
{
    // Open dir folder
    File dir = LittleFS.open("/", "r");
    // Cycle all the content
    printDirectory(dir);
}
void setup() 
    {
    // 1. Initialize printing and filesystem
    Serial.begin(115200);
    while (!Serial) {delay(100);}

    Serial.print(F("Initializing filesystem..."));
    if (LittleFS.begin()){
        Serial.println(F("complete."));
    }else{
        Serial.println(F("failed."));
    }
    Serial.println(F("Current Directory"));
    printDir();

    // monthly, multiple file sampling
    Serial.println(F("Checking for Files, deleting if file exists"));
    for (int i = 1; i<=numfiles; i++)
    {
        dayFileName = "/" + String(i);
        if (LittleFS.exists(dayFileName))
        {
            Serial.print(dayFileName);
            Serial.println(" exists, deleted");
            LittleFS.remove(dayFileName);      
        }
    }
    Serial.println(F("Delete All Files"));
    delFiles();
    Serial.println(F("Remaining Files"));    
    printDir();
}

// an empty void loop() is the same as a stop() function
void loop() 
{
  
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
