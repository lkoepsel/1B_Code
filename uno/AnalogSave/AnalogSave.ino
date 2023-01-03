/*
  Analog Save

  Reads an analog pin and saves the value to EEPROM.
  These values will stay in the EEPROM when the board is
  turned off and may be retrieved later by another sketch.

  If a value has not changed in the EEPROM, it is not overwritten
  which would reduce the life span of the EEPROM unnecessarily.
***/

#include <EEPROM.h>

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int address = 0;
int sensorPin = A0;    // select the input pin for the potentiometer
unsigned int sensorValue = 0;  // variable to store the value coming from the sensor
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
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  unsigned int now = millis();

  Serial.print(address);
  EEPROM.put(address, now);
  address += sizeof(now);

  EEPROM.put(address, sensorValue);
  address += sizeof(sensorValue);

  Serial.print("\t");
  Serial.print(now);
  Serial.print("\t ");
  Serial.println(sensorValue);

  if (address >= memorySize) {
    Serial.println("Out of memory");
    stop();
  }

  delay(50);
}
