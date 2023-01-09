# analogRead.py - read an analog to digital pin

import machine
import time


def volt_convert(p):
    conversion_factor = 3.3 / (65535)
    reading = p * conversion_factor
    return reading


pot = machine.ADC(0)

for i in range(100):
    pot_value = volt_convert(pot.read_u16())
    print(pot_value)
    time.sleep_ms(1000)
