# analogRead.py - read an analog to digital pin

import machine
import time


def temp_convert(t):
    conversion_factor = 3.3 / (65535)
    reading = t * conversion_factor
    celsius = 27 - (reading - 0.706) / 0.001721
    fahrenheit = celsius * (9 / 5) + 32
    return fahrenheit


file = open("temps.txt", "w")
sensor_temp = machine.ADC(machine.ADC.CORE_TEMP)

for i in range(10):
    temp = temp_convert(sensor_temp.read_u16())
    data = str(time.localtime()) + "\t" + str(temp) + "\n"
    file.write(str(data))
    print(data, end="")
    file.flush()
    time.sleep_ms(1000)

file.close
