# blink.py - blink a pin
# identify the pin to blink on line 6
from machine import Pin
from time import sleep_ms

pin = 14
delay = 25
freq = (1 / (delay * 2)) * 1000
led = Pin(pin, Pin.OUT)

print("toggle: pin", pin, "will blink with a delay of",
      delay, "ms at a frequency of", freq, "kHz.")

# with a delay of 100, the pin will have a 5Hz frequency
while True:
    led.toggle()
    sleep_ms(delay)
