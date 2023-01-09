/*
 *  Raspberry Pi Pico (or generic rp2040)
 *  LittleFS write, read and seek file
 *  by Mischianti Renzo <https://www.mischianti.org>
 *
 *  https://www.mischianti.org/
 *
 */
#include "Arduino.h"
#include "LittleFS.h"
 
void setup()
{
  Serial.begin(115200);
 
  while (!Serial) {delay(100);}
 
  Serial.println(F("Inizializing FS..."));
  if (LittleFS.begin()){
    Serial.println(F("done."));
  }else{
    Serial.println(F("fail."));
  }
 
  // To remove previous test
  // LittleFS.remove(F("/testCreate.txt"));
 
  File testFile = LittleFS.open(F("/testCreate.txt"), "w");
 
  if (testFile){
    Serial.println("Write file content!");
    testFile.print("Here the test text www.mischianti.org!!");
 
    testFile.close();
  }else{
    Serial.println("Problem on create file!");
  }
 
  testFile = LittleFS.open(F("/test.txt"), "r");
  if (testFile){
    Serial.println("Read file content!");
    /**
     * File derivate from Stream so you can use all Stream method
     * readBytes, findUntil, parseInt, println etc
     */
    Serial.println(testFile.readString());
    testFile.close();
  }else{
    Serial.println("Problem on read file!");
  }
 
  testFile = LittleFS.open(F("/testCreate.txt"), "r");
  if (testFile){
    /**
     * mode is SeekSet, position is set to offset bytes from the beginning.
     * mode is SeekCur, current position is moved by offset bytes.
     * mode is SeekEnd, position is set to offset bytes from the end of the file.
     * Returns true if position was set successfully.
     */
    Serial.println("Position inside the file at 19 byte!");
    testFile.seek(19, SeekSet);
 
    Serial.println("Read file content!");
    Serial.println(testFile.readString());
    testFile.close();
  }else{
    Serial.println("Problem on read file!");
  }
}
 
void loop()
{
 
}
