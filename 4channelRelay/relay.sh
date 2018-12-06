#!/bin/bash
# create a loop to turn each relay on and off.
while true
do 
   for i in `seq 1 4`
   do
      i2cset -y 1 0x10 $i 0xff
      sleep 1 
      i2cset -y 1 0x10 $i 0x00
      sleep 1 
   done 
done 
