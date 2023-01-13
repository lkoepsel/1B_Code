#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;

#define MOISTURE_ADDRESS 0x36

void setup() {
    Serial.begin(115200);
    while (!Serial) {delay(100);}

    Serial.println("seesaw Soil Sensor example!");
    Wire.setSDA(20);
    Wire.setSCL(21);
    Wire.begin();

    if (!ss.begin(MOISTURE_ADDRESS)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
    } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
    }
}

void loop() {
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
  Serial.print("Capacitive: "); Serial.println(capread);
  delay(100);
}
