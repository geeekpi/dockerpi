# How to install 
<pre> NOTE: Please install wiringpi package before compiling the source code!!! </pre>
## for 32bit compatible system
```bash
sudo ./install.sh
```
## for 64bit only 
```bash
sudo apt update
sudo apt upgrade -y
sudo apt -y install build-essential gcc g++ cmake
cd powerboard/powerboard/
sudo gcc powerboard_daemon.c -lwiringPi -O3 -O /usr/bin/powerboard_daemon64
```
