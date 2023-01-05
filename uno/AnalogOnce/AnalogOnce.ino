/*
  Analog Once

  Reads an analog pin and saves the value to EEPROM.
  These values will stay in the EEPROM when the board is
  turned off and may be retrieved later by another sketch.

  If a value has not changed in the EEPROM, it is not overwritten
  which would reduce the life span of the EEPROM unnecessarily.
***/


/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int sensorPin = A0;    // select the input pin for the potentiometer
unsigned int sensorValue = 0;  // variable to store the value coming from the sensor

void stop()
{
    while(1) {};
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  unsigned int now = millis();

  Serial.print("Sensor Value: \t");
  Serial.println(sensorValue);

  stop();

//  delay(50);
}
