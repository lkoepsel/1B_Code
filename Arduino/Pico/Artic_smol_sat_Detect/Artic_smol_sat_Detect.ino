#include <Wire.h> //Needed for I2C to ARTIC R2 GPIO
#include <SPI.h>
#include "SparkFun_ARGOS_ARTIC_R2_Arduino_Library.h" // http://librarymanager/All#SparkFun_ARGOS_ARTIC_R2
ARTIC_R2 myARTIC;

// int CS_Pin = 5;            // smôl CS0 = ESP32 Pin 5
// int ARTIC_PWR_EN_Pin = 27; // smôl GPIO0 = ESP32 Pin 27
// Pin assignments for the smôl stack-up using the Pi Pico
int CS_Pin = 17;            // smôl CS0 = Pi Pico GP17 SPIO CSn
int ARTIC_PWR_EN_Pin = 22;  // smôl GPIO0 = Pi Pico GP22


void setup()
{
  // I2C and SPI  assignments for the smôl stack-up using the Pi Pico
  SPI.setRX(16);
  // SPI.setCS(17);
  SPI.setSCK(18);
  SPI.setTX(19);
  Wire.setSDA(20);            
  Wire.setSCL(21);

  Serial.begin(115200);
  while (!Serial) {delay(100);}

  Serial.println(F("ARGOS smôl ARTIC R2 Example"));

  Serial.println(F("ARTIC R2 is booting..."));

  Wire.begin(); // Needed to communicate with the I2C GPIO chip on the smôl ARTIC R2
  SPI.begin();

  //myARTIC.enableDebugging(); // Uncomment this line to enable debug messages on Serial

  // Begin the ARTIC: enable power and boot from flash
  if (myARTIC.beginSmol(CS_Pin, ARTIC_PWR_EN_Pin) == false)
  {
    Serial.println("ARTIC R2 not detected. Please check the smôl stack-up and flexible circuits. Freezing...");
    while (1)
      ; // Do nothing more
  }

  Serial.println(F("ARTIC R2 boot was successful."));

  myARTIC.setTCXOControl(1.8, true); // Set the TCXO voltage to 1.8V and autoDisable to 1

  myARTIC.setSatelliteDetectionTimeout(600); // Set the satellite detection timeout to 600 seconds

  Serial.println(F("Starting satellite detection..."));

  // Start satellite detection
  // The ARTIC will start looking for a satellite for the specified amount of time.
  myARTIC.sendMCUinstruction(INST_SATELLITE_DETECTION);
}

void loop()
{
  delay(1000);

  // Read the ARTIC R2 status register
  ARTIC_R2_Firmware_Status status;
  myARTIC.readStatusRegister(&status);

  // Check the interrupt 2 flag. This will go high if satellite detection times out
  if (status.STATUS_REGISTER_BITS.DSP2MCU_INT2)
  {
    Serial.println(F("INT2 pin is high. Satellite detection has timed out!"));
  }
  // Check the interrupt 1 flag. This will go high when a satellite is detected
  else if (status.STATUS_REGISTER_BITS.DSP2MCU_INT1)
  {
    Serial.println(F("INT1 pin is high. Satellite detected!"));
  }

  // Check the instruction progress
  // checkMCUinstructionProgress will return true if the instruction is complete
  ARTIC_R2_MCU_Instruction_Progress progress;
  boolean instructionComplete = myARTIC.checkMCUinstructionProgress(&progress);

  if (instructionComplete)
  {
    Serial.println(F("Satellite detection is complete! Freezing..."));
    while (1)
      ; // Do nothing more
  }
}
