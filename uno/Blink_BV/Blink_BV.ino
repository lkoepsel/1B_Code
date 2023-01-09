// Blink_BV
// Blinks a pin as fast as possible using the _BV macro and writing to PIN register
// This function is specific to the AVR family (ATmega328P)

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(8, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  PINB |= (_BV(PORTB0));             // toggle the bit using C bit set code
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);                       // wait for a second
}
