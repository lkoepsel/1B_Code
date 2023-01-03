/*
  EEPROM Read

  Reads the values in EEPROM based an AnalogSave.
  These values will stay in the EEPROM when the board is
  turned off and may be retrieved later by another sketch.

  If a value has not changed in the EEPROM, it is not overwritten
  which would reduce the life span of the EEPROM unnecessarily.
***/

#include <EEPROM.h>

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int address = 0;

unsigned int sensorValue;  // variable to store the value coming from the EEPROM
unsigned int now;  // time stamp for data
int memorySize = EEPROM.length()/(sizeof(sensorValue) + sizeof(now));
//int memorySize = 10;

void stop()
{
    while(1) {};
}

void setup() {
  Serial.begin(115200);
  Serial.println("Address\tTime\tData");
}

void loop() {
  // read the value from the EEPROM:
  Serial.print(address);
  EEPROM.get(address, now);
  address += sizeof(now);
  EEPROM.get(address, sensorValue);
  address += sizeof(sensorValue);

  Serial.print("\t");
  Serial.print(now);
  Serial.print("\t");
  Serial.println(sensorValue);

  if (address >= memorySize) {
    Serial.println("Out of memory");
    stop();
  }

  delay(50);
}
