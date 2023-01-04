#include <EEPROM.h>

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int address = 0;
unsigned int Value;  // variable to store the value coming from the EEPROM
unsigned int eepromValue;  // variable to store the value coming from the EEPROM
//int memorySize = EEPROM.length()/sizeof(Value);
int memorySize = 8;


void stop()
{
    while(1) {};
}

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(115200);

}

void loop() {
  Value = 0;
  EEPROM.put(address, Value);
  EEPROM.get(address, eepromValue);
  Serial.print(address);
  Serial.print(" ");
  Serial.print(Value);
  Serial.print(" ");
  Serial.println(eepromValue);
  delay(50);

  address += sizeof(Value);
  if (address >= memorySize) {
    Serial.println("Out of memory");
    stop();
  }

  Value = 1234;
  EEPROM.put(address, Value);
  EEPROM.get(address, eepromValue);
  Serial.print(address);
  Serial.print(" ");
  Serial.print(Value);
  Serial.print(" ");
  Serial.println(eepromValue);
  delay(50);

  address += sizeof(Value);
  if (address >= memorySize) {
    Serial.println("Out of memory");
    stop();
  }
  Value = 65535;
  EEPROM.put(address, Value);
  EEPROM.get(address, eepromValue);
  Serial.print(address);
  Serial.print(" ");
  Serial.print(Value);
  Serial.print(" ");
  Serial.println(eepromValue);
  delay(50);

  address += sizeof(Value);
  if (address >= memorySize) {
    Serial.println("Out of memory");
    stop();
  }


}
