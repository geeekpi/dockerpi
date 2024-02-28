#!/bin/bash

# check if the user have permission to execute the shell script.
if [ $(id -u) -ne 0 ]; then
  printf "Script must be run as root. Try 'sudo raspi-config'\n"
  exit 1
fi

# check if the i2c function has been enabled. 
if grep -q "^dtparam=i2c_arm=off" /boot/firmware/config.txt; then
	sudo sed -i "s|^dtparam=i2c_arm=off|dtparam=i2c_arm=on|" /boot/firmware/config.txt &> /dev/null
elif grep -q "^#dtparam=i2c_arm=on" /boot/firmware/config.txt; then
	sudo sed -i "s|^#dtparam=i2c_arm=on|dtparam=i2c_arm=on|" /boot/firmware/config.txt &> /dev/null
else
	echo "dtparam=i2c_arm=on" | sudo tee -a /boot/firmware/config.txt &> /dev/null
fi


# for 32bit or old system
#
if ! [ -e /etc/modprobe.d/raspi-blacklist.conf ]; then
touch /etc/modprobe.d/raspi-blacklist.conf
fi
sed /etc/modprobe.d/raspi-blacklist.conf -i -e "s/^\(blacklist[[:space:]]*i2c[-_]bcm2708\)/#\1/"
sed /etc/modules -i -e "s/^#[[:space:]]*\(i2c[-_]dev\)/\1/"
if ! grep -q "^i2c[-_]dev" /etc/modules; then
sh -c "echo i2c-dev >> /etc/modules"
fi
dtparam i2c_arm=on
modprobe i2c-dev

# check the model of Raspberry Pi.
model=`cat /proc/cpuinfo | awk -F: '{print $NF}' | awk '{print $3}'`

if [[ $model -eq 5 ]]; then
	wget -O /etc/systemd/system/powerboard64.service https://github.com/geeekpi/dockerpi/raw/master/powerboard/RPi5/64bit/powerboard64.service
fi

arch=`uname -m` 
if [[ $arch == 'aarch64' ]]; then
	wget -O /usr/sbin/powerboard64 https://github.com/geeekpi/dockerpi/raw/master/powerboard/RPI5/64bit/powerboard64
fi



chmod 755 /etc/systemd/system/powerboard_daemon.service
# chmod 755 /usr/sbin/powerboard

chown root:root /etc/systemd/system/powerboard_daemon.service
# chown root:root /usr/sbin/powerboard_daemon

systemctl daemon-reload
systemctl enable powerboard64
systemctl start powerboard64 &
