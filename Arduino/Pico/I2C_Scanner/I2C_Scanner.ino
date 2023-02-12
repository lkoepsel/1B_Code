// I2C_Scanner - scans both Wire and Wire interfaces on Pico for devices
// Specific pins must be set for both interfaces
// Be sure to use GP# and not pin #!

#include <Wire.h>

// Set I2C bus to use: Wire, Wire1, etc.
// #define Wire Wire

byte error, address;
unsigned int nDevices;
unsigned int SDA_0 = 8;
unsigned int SCL_0 = 9;
unsigned int SDA_1 = 14;
unsigned int SCL_1 = 15;

void setup() {
    Wire.setSDA(SDA_0);
    Wire.setSCL(SCL_0);
    Wire.begin();

    Serial.begin(115200);
    while (!Serial) {delay(100);}
    Serial.println("\nI2C One-Time Scan");
    Serial.print("Scanning Wire 0 SDA ");
    Serial.print(SDA_0);
    Serial.print(" and SCL ");
    Serial.println(SCL_0);

    nDevices = 0;
    for(address = 1; address < 127; address++ ) 
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address<16) 
              Serial.print("0");
            Serial.println(address,HEX);
            nDevices++;
        }
        else if (error==4) 
        {
            Serial.print("Unknown error at address 0x");
            if (address<16)
            { 
                Serial.print("0");
            }
            Serial.println(address,HEX);
        }    
    }
    if (nDevices == 0)
    {    
        Serial.println("No I2C devices found\n");
    }
    else
    {
      Serial.println("Scan Complete\n");
    }

    Serial.print("Scanning Wire1 SDA ");
    Serial.print(SDA_1);
    Serial.print(" and SCL ");
    Serial.println(SCL_1);

    Wire1.setSDA(SDA_1);
    Wire1.setSCL(SCL_1);
    Wire1.begin();

    nDevices = 0;
    for(address = 1; address < 127; address++ ) 
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire1.beginTransmission(address);
        error = Wire1.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address<16) 
              Serial.print("0");
            Serial.println(address,HEX);
            nDevices++;
        }
        else if (error==4) 
        {
            Serial.print("Unknown error at address 0x");
            if (address<16)
            { 
                Serial.print("0");
            }
            Serial.println(address,HEX);
        }    
    }
    if (nDevices == 0)
    {    
        Serial.println("No I2C devices found\n");
    }
    else
    {
      Serial.println("Scan Complete\n");
    }
    Serial.println("All Scans Successful!\n");
}


void loop() {

    ;
}
