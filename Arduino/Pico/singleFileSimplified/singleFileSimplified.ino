// TEST PROGRAM ONLY
// Used to simplify the SingleFileDrive API to the minimum

#include <LittleFS.h>
#include <SingleFileDrive.h>

unsigned int dTime = 2000;

void myPlugSF(uint32_t data) {
    // Tell my app not to write to flash, we're connected
    dTime=50;
}

void myUnplugSF(uint32_t data) {
    // I can start writing to flash again
        dTime=2000;
}

void myDeleteSF(uint32_t data) {
    // Maybe LittleFS.remove("myfile.txt")?  or do nothing
        dTime=5000;
}

void setup() {

    pinMode(LED_BUILTIN, OUTPUT);

    LittleFS.begin();
    singleFileDrive.onPlug(myPlugSF);
    singleFileDrive.onUnplug(myUnplugSF);
    singleFileDrive.onDelete(myDeleteSF);
    
    singleFileDrive.begin("File_1", "DataRecorder.csv");
    dTime=10;
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(dTime);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(dTime);                       // wait for a second
}
