# Engr 1B Makerspace

## Introduction
This repository contains the coding examples used in the Engr 1B Makerspace class. 

## Pico Sketches, Recommended for Use:

### SensorwFilesMenuSerial
Complete program to do the following via the Serial port (USB cable):
```
p - print directory
d - delete a file in the directory
r - record numSamples number of samples with a delaySamples in between each sample
s - show the contents of a sample file 
```
The menu system uses a single character response, so only A-Z/0-9 are available as responses. Program automatically adds *File_* to the name so each file name would be *File_0*, *File_1*, *File_2* or *File_A*, *File_B* and so on.

Once the file contents are printed to the screen, one can use keyboard commands such as Select All (*Cntrl-A/Cmd-A*) and Copy (*Cntrl-C/Cmd-C*) to capture the data to use on the PC.

This program serves as a template only and requires customization to be used as a sensor project. It collects data from pin A0 and converts to a Voltage, however, this is of little value unless you attach a voltage-related object to pin A0.

### SensorwFilesMenuSerialStartup
Uses SensorwFilesMenuSerial and adds the ability to startup without a USB Serial connection. (You will still need to power the Pico.)

The code to add or change is marked by
```
// Startup*****************
   code to add or change
// Startup*****************END
```
Make the changes and confirm it works.
1) On power up, if the Serial Monitor does NOT connect in 5 seconds, the board will attempt to automatically enter data in to *File_9*. You can change the number of samples and delay between samples as noted in the variables section.
2) If the setup is successful and the board begins to collect samples, the LED will blink quickly **2** times
3) If the setup is not successful and the board is unable to collect samples, the LED will blink slowly **5** times
4) Once the board has collected the necessary number of samples, one can use the Serial Monitor and menu to examine *File_9* to view the data


## Pico Sketches, Partially Complete, Not suitable for Use

### OLED_Display
Code sample to use for projects, demonstrates how to use fonts and display varying lines of text
#### Sources of Information
* Display Board: https://www.adafruit.com/product/4650
* Display Board Primer: https://learn.adafruit.com/adafruit-128x64-oled-featherwing
* Fonts available: https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts
* Strint Class for Text to display: https://www.arduino.cc/reference/en/language/variables/data-types/stringobject/


## Argos Satellite Info
* [smôl ARTIC R2 Hookup Guide](https://learn.sparkfun.com/tutorials/sml-artic-r2-hookup-guide)
* [Github Sparkfun Artic Library](https://github.com/sparkfun/SparkFun_ARGOS_ARTIC_R2_Arduino_Library#sparkfun-argos-artic-r2-arduino-library)

### SingleFile Drive
This code will allow you to offer a single file to be transferred from the Pico as a USB file, it will show up in the PC's directory as a file

* Docs: https://arduino-pico.readthedocs.io/en/latest/singlefile.html
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

### SH110_Test
Uses an Adafruit GFX Examples program modified to work with the 128x64 OLED display

## Possible Errors
While attempting to upload code to a Pico, you get this error:
```bash
Error opening serial port '/dev/cu.usbmodem3101'.
```
Be sure to press the Boot/Sel button while plugging in a Pi Pico, or press Reset while holding the Boot/Sel button on the Adafruit Feather. This will put the Pico board in the proper state to accept a new program.

## Blink Speeds (Remove delays and measure toggle only)
* Pi 3B (*python*) 11.5kHz
* Pi 2B (*python*) 4.4kHz
* Pico (*Micropython*) 33kHz
* Pico (*Arduino*) 605kHz
* Uno (*Arduino*) 47kHz
* Uno (Arduino/Native C bit toggle) 1.33MHz

