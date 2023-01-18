unsigned int incomingByte; // for incoming serial data
int returnKey = 0; // for incoming serial data

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    Serial.print("Initial Value is: ");
    Serial.println(incomingByte);
    Serial.print("Next Value is: ");
    Serial.println(++incomingByte);
    // read the incoming byte:
    incomingByte = Serial.read();
    returnKey = Serial.read();

    // say what you got:
    // Serial.print("I received: ");
    // Serial.println(incomingByte-48, DEC);
    Serial.print("I received: ");
    Serial.print(incomingByte);
    Serial.print(" the next letter is:  ");
    Serial.println((char)++incomingByte);

  }
}
