# blink.py - blink a pin
# identify the pin to blink on line 6
from machine import Pin
from time import sleep_ms

R_pin = 18
G_pin = 19
B_pin = 20
delay = 25
freq = (1 / (delay * 2)) * 1000
R_led = Pin(R_pin, Pin.OUT)
G_led = Pin(G_pin, Pin.OUT)
B_led = Pin(B_pin, Pin.OUT)

print("blink: pin", R_pin, "will blink with a delay of",
      delay, "ms at a frequency of", freq, "kHz.")

# with a delay of 100, the pin will have a 5Hz frequency
while True:
    R_led.off()
    G_led.off()
    B_led.off()
    sleep_ms(delay)
    R_led.on()
    G_led.on()
    B_led.on()
    sleep_ms(delay)
