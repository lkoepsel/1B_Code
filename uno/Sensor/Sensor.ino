// Sensor

// Reads an analog pin, convert to another value  and save to filesystem


#include "Arduino.h"
#include "LittleFS.h"

int sensorPin = A0;                 // input pin for ADC
unsigned int sensorValue = 0;       // value coming from the ADC
unsigned int numSamples = 10;       // number of samples to capture
unsigned int delaySamples = 100;    // milliseconds between each sample
char filename[] = "/samples.txt";   // file to store sample data


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

    File testFile = LittleFS.open(filename, "w");

    // 2. Read ADC (get )
    if (testFile)
    {
        Serial.print(F("Reading ADC..."));
        for (int i=0;i<numSamples;i++)
        {
            // read the value from the sensor:
            sensorValue = analogRead(sensorPin);


            // 3. Convert ADC value into a measureable, voltage, temp, moisture
            
            // 4. Save value to a file
            testFile.print("\nSensor Value: \t");
            testFile.print(sensorValue);
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
    testFile = LittleFS.open(filename, "r");
    if (testFile)
    {
        Serial.println("Reading samples file");
        Serial.println(testFile.readString());
        testFile.close();
    }
    else
    {
        Serial.println("Problem reading samples file!");
    }

}

// an empty void loop() is the same as a stop() function
void loop() 
{
  
}
