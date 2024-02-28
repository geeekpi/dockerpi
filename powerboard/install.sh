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
#if ! [ -e /etc/modprobe.d/raspi-blacklist.conf ]; then
#touch /etc/modprobe.d/raspi-blacklist.conf
#fi
#sed /etc/modprobe.d/raspi-blacklist.conf -i -e "s/^\(blacklist[[:space:]]*i2c[-_]bcm2708\)/#\1/"
#sed /etc/modules -i -e "s/^#[[:space:]]*\(i2c[-_]dev\)/\1/"
#if ! grep -q "^i2c[-_]dev" /etc/modules; then
#sh -c "echo i2c-dev >> /etc/modules"
#fi
#dtparam i2c_arm=on
#modprobe i2c-dev

# check the model of Raspberry Pi.
model=`cat /proc/cpuinfo | grep Model | awk -F: '{print $NF}' | awk '{print $3}'`

arch=`uname -m` 

# for Raspberry pi 5 and 64bit OS.
if [[ $model -eq 5 && $arch == 'aarch64' ]]; then
	cp -Rvf ./RPi5/64bit/powerboard64.service /etc/systemd/system/
	cp -Rvf ./RPi5/64bit/powerboard64 /usr/sbin/powerboard64 
	chmod 755 /etc/systemd/system/powerboard64.service
	chmod 755 /usr/sbin/powerboard64
	chown root:root /etc/systemd/system/powerboard64.service
	chown root:root /usr/sbin/powerboard64
	systemctl daemon-reload
	systemctl enable powerboard64.service
	systemctl start powerboard64.service &
fi


# for Raspberry pi 4B and 64bit OS.
if [[ $model -eq 4 && $arch == 'aarch64' ]]; then
	cp -Rvf ./RPi4B/64bit/powerboard64.service /etc/systemd/system/
	cp -Rvf ./RPi4B/64bit/powerboard64 /usr/sbin/powerboard64 
	chmod 755 /etc/systemd/system/powerboard64.service
	chmod 755 /usr/sbin/powerboard64
	chown root:root /etc/systemd/system/powerboard64.service
	chown root:root /usr/sbin/powerboard64
	systemctl daemon-reload
	systemctl enable powerboard64.service
	systemctl start powerboard64.service &
fi

# for Raspberry pi 5 and 32bit OS.
if [[ $model -eq 5 && $arch == 'aarch' ]]; then
	cp -Rvf ./RPi5/32bit/powerboard32.service /etc/systemd/system/
	cp -Rvf ./RPi5/32bit/powerboard32 /usr/sbin/powerboard32
	chmod 755 /etc/systemd/system/powerboard32.service
	chmod 755 /usr/sbin/powerboard32
	chown root:root /etc/systemd/system/powerboard32.service
	chown root:root /usr/sbin/powerboard32
	systemctl daemon-reload
	systemctl enable powerboard32.service
	systemctl start powerboard32.service &
fi

# for Raspberry pi 4 and 32bit OS.
if [[ $model -eq 4 && $arch == 'aarch' ]]; then
	cp -Rvf ./RPi4B/32bit/powerboard32.service /etc/systemd/system/
	cp -Rvf ./RPi4B/32bit/powerboard32 /usr/sbin/powerboard32
	chmod 755 /etc/systemd/system/powerboard32.service
	chmod 755 /usr/sbin/powerboard32
	chown root:root /etc/systemd/system/powerboard32.service
	chown root:root /usr/sbin/powerboard32
	systemctl daemon-reload
	systemctl enable powerboard32.service
	systemctl start powerboard32.service &
fi

echo -e "\e[32;40mInstallation has completed successfully!\e[0m"
echo -e "\e[32;40mSystem will reboot in 5 seconds!!!\e[0m"
sleep 5
sync && reboot 
