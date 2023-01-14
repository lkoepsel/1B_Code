# Engr 1B Makerspace

## Introduction
This repository contains the coding examples used in the Engr 1B Makerspace class. 

## Blink Speeds (Remove delays and measure toggle only)
* Pi 3B (*python*) 11.5kHz
* Pi 2B (*python*) 4.4kHz
* Pico (*Micropython*) 33kHz
* Pico (*Arduino*) 605kHz
* Uno (*Arduino*) 47kHz
* Uno (Arduino/Native C bit toggle) 1.33MHz


## Possible Errors
While attempting to upload code to a Pico, you get this error:
```bash
Error opening serial port '/dev/cu.usbmodem3101'.
```
Be sure to press the Boot/Sel button while plugging in a Pi Pico, or press Reset while holding the Boot/Sel button on the Adafruit Feather. This will put the Pico board in the proper state to accept a new program.


## Pico Sketches
### Adafruit OLED
Simple test the Adafruit 4650 128x64 OLED display.

### DeleteFiles
Demonstrates how to print a directory and delete all the files in the directory.

### folderinfo
Demonstrates how to print statistics as the LittleFS filesystem

### LCD
Simple test for the GEEEKPi LCD Display, display is old technology and the display quality is quite bad.

### lilFS
Demonstration program for using the LittleFS filesystem on the RP2040

### menu
Demonstration for creating a menu program

### seesaw
Test program for using Adafruit Seesaw library for measuring moisture

### SensorEnhanced
Initial sensor program to demonstrate a good technique for reading sensor data

### SensorwFiles
Update to SensorEnhanced to allow for the storage of sensor data

### SensorwFilesMenu
Update to SensorwFiles where a menu is used to guide using the program

### serialRead
Simple program to demonstrate reading sensor data

## SH110_Test
Uses an Adafruit GFX Examples program modified to work with the 128x64 OLED display