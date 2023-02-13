// I2C_Scanner - scans both Wire and Wire interfaces on Pico for devices
// Specific pins must be set for both interfaces
// Be sure to use GP# and not pin #!

#include <Wire.h>

byte error, address;
unsigned int nDevices;
unsigned int SDA_00 = 8;
unsigned int SCL_00 = 9;
unsigned int SDA_10 = 14;
unsigned int SCL_10 = 15;
unsigned int SDA_01 = 20;
unsigned int SCL_01 = 21;
unsigned int SDA_11 = 18;
unsigned int SCL_11 = 19;

void setup() {
    Serial.begin(115200);
    while (!Serial) {delay(100);}
    Serial.println("\nI2C One-Time Scan");

    // Wire Scanning Section, duplicate for each Wire channel setup
    Wire.setSDA(SDA_00);
    Wire.setSCL(SCL_00);
    Wire.begin();

    Serial.print("Scanning Wire  SDA: ");
    Serial.print(SDA_00);
    Serial.print(" SCL: ");
    Serial.println(SCL_00);

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
      Serial.println("Wire Scan Complete\n");
    }
    Wire.end();
    // End of Wire Scanning Section

    // Wire Scanning Section, duplicate for each Wire channel setup    
    Serial.print("Scanning Wire1 SDA: ");
    Serial.print(SDA_10);
    Serial.print(" SCL: ");
    Serial.println(SCL_10);

    Wire1.setSDA(SDA_10);
    Wire1.setSCL(SCL_10);
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
      Serial.println("Wire1 Scan Complete\n");
    }
    Wire1.end();
    // End of Wire Scanning Section

    // Wire Scanning Section, duplicate for each Wire channel setup    
    Serial.print("Scanning Wire SDA: ");
    Serial.print(SDA_01);
    Serial.print(" SCL:  ");
    Serial.println(SCL_01);

    Wire.setSDA(SDA_01);
    Wire.setSCL(SCL_01);
    Wire.begin();

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
      Serial.println("Wire Scan Complete\n");
    }
    Wire.end();
    // End of Wire Scanning Section

    // Wire Scanning Section, duplicate for each Wire channel setup    
    Serial.print("Scanning Wire1 SDA: ");
    Serial.print(SDA_11);
    Serial.print(" SCL: ");
    Serial.println(SCL_11);

    Wire1.setSDA(SDA_11);
    Wire1.setSCL(SCL_11);
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
      Serial.println("Wire1 Scan Complete\n");
    }
    Wire1.end();
    // End of Wire Scanning Section

    Serial.println("All Scans Successful!\n");
}


void loop() {

    ;
}
