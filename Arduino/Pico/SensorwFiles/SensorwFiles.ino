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

int sensorPin = A0;                 // input pin for ADC
unsigned int sensorValue = 0;       // value coming from the ADC
unsigned int numSamples = 20;       // number of samples to capture
unsigned int delaySamples = 100;    // milliseconds between each sample
double voltage = 0;                 // voltage calculated from ADC
unsigned int numfiles = 7;
File testFile;
String dir = "/";   // file to store sample data
String basename = "Day_";   // file to store sample data
String dayFileName;

String setName(unsigned int i)
{
    return dayFileName = dir + basename + String(i);
}

void printRootDir()
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

    Serial.println("Current Directory");
    printRootDir();
    
    analogReadResolution(12);

    // monthly, multiple file sampling
    for (int i = 1; i<=numfiles; i++)
    {
        setName(i);
        if (!LittleFS.exists(dayFileName))
        {
            Serial.print(dayFileName);
            Serial.println(" does not exist...created");
            testFile = LittleFS.open(dayFileName, "w");
            break;      
        }
    }
    // 2. Read ADC
    if (testFile)
    {
        Serial.print(F("Reading ADC..."));
        for (int i=0;i<numSamples;i++)
        {
            // read the value from the sensor:
            sensorValue = analogRead(sensorPin);


            // 3. Convert ADC value into voltage
            voltage = sensorValue/4096.0 * 3.30;


            // 4. Save value to a file
            testFile.print(sensorValue);
            testFile.print("\t");
            testFile.print(voltage);
            testFile.print("\n");
            delay(delaySamples);
        }

        Serial.println(F("complete."));
        testFile.close();
    }
    else
    {
        Serial.println("Problems creating file!");
    }

    // 5. Display values 
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
        Serial.println("Problem reading samples file!");
    }
    
    Serial.println("Updated Directory");
    printRootDir();

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
