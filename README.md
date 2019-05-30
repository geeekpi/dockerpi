# Docker Pi Modules Demo Code
* Nightlight Hat Board For Raspberry Pi 
* 4 Channel Relay Hat Board For Raspberry Pi
* Powerboard 
* SensorHub
# Requirement
* i2c-tools 
* smbus2  
# How To Setup
## Install i2c-tools 
* sudo apt-get update 
* sudo apt-get -y install i2c-tools
* sudo apt-get -y install git
* pip3 install smbus2
## Detect Device Address
* i2cdetect -y 1 
## Clone Repository
* cd ~
* git clone https://github.com/geeekpi/dockerpi.git
* cd dockerpi/Nightlight/
* sudo ./Nightligh.sh  
or 
* sudo python ./Nightlight.py
or 
* gcc Nightlight.c -lwiringPi -o nightlight
* sudo ./nightlight
----
And the same way to 4 Channel Relay Hat Board.
Have Fun.

