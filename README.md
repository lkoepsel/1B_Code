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


