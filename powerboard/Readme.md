# How to install 
## Readme
The shell script will detect the platform of your Raspberry Pi from Raspberry Pi 4B and Raspberry Pi 5, and also detect the architechture of your CPU from 32bit to 64bit. and will install the right binary file to /usr/sbin location. 
## Pre-install 
```bash
sudo apt update
sudo apt upgrade -y
sudo apt -y install build-essential gcc g++ cmake
```
## Download repository  
```bash
git clone https://github.com/geeekpi/dockerpi.git
cd dockerpi/powerboard/
sudo ./install.sh
```
## Checking Method
Please make sure the blue color LED has been light up for a while, it means that the MCU on powerboard has detected and communicated with Raspberry Pi properly. 
* Click Power button to initializing shutdown processure. 
If the operating system has been shutdown properly after clicking the power button once. it means that the driver has been installed properly. 
otherwise, you need to reinstall the driver again. 

