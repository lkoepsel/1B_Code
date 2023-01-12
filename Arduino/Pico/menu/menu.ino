int choice = 0; // for incoming serial data
int returnKey = 0; // for incoming serial data

void printMenu()
{
    Serial.println("Enter one of the following:");
    Serial.println("\tp for Print directory");
    Serial.println("\td for Delete directory");
    Serial.println("\ts for Show samples");
    Serial.println("\tr for  record samples");
    Serial.println("Followed by return.");
}

void setup() {
    Serial.begin(115200); // opens serial port, sets data rate to 115200 bps
    while (!Serial) {delay(100);}
    printMenu();
}

void loop() {
    if (Serial.available() > 0) 
    {
    // read the incoming byte:
        choice = Serial.read();
        returnKey = Serial.read();
        // menu based on choice
        // do something depending on choice:
        switch (choice) 
        {
            case 112:  // p for print directory
                 Serial.println("Print directory");
                 break;
            case 100:  // d for delete directory
                 Serial.println("Delete directory");
                 break;
            case 115:  // s for show samples
                 Serial.println("Show sampling");
                 break;
            case 114:  // r for record samples
                 Serial.println("Record samples");
                 break;
            default:
                 printMenu();
        }
        delay(10);  // delay in between reads for stability
    }
}
