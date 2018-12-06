#!/usr/bin/env python
#
import time as t
import smbus

DEVICE_BUS = 1
DEVICE_ADDR = 0x15
bus = smbus.SMBus(DEVICE_BUS)

while True:
    try:
        for i in range(1,25):
            bus.write_byte_data(DEVICE_ADDR, i, 0xFF)
            t.sleep(0.2)
            bus.write_byte_data(DEVICE_ADDR, i, 0x00)
            t.sleep(0.2) 
    except KeyboardInterrupt as e:
        print("Quit the Loop")
