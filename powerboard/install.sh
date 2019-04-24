#!/bin/bash

if [ $(id -u) -ne 0 ]; then #使用root权限
  printf "Script must be run as root. Try 'sudo raspi-config'\n"
  exit 1
fi

#开启I2C外设
if grep -q "^dtparam=i2c_arm=off" /boot/config.txt; then
	sed -i "s|^dtparam=i2c_arm=off|dtparam=i2c_arm=on|" /boot/config.txt &> /dev/null
elif grep -q "^#dtparam=i2c_arm=on" /boot/config.txt; then
	sed -i "s|^#dtparam=i2c_arm=on|dtparam=i2c_arm=on|" /boot/config.txt &> /dev/null
else
	echo "dtparam=i2c_arm=on" | sudo tee -a /boot/config.txt &> /dev/null
fi

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
    
wget -O /etc/systemd/system/powerboard_daemon.service  https://www.lijingquan.net/test/powerboard_daemon.service
wget -O /usr/sbin/powerboard_daemon https://www.lijingquan.net/test/powerboard_daemon

chmod 755 /etc/systemd/system/powerboard_daemon.service
chmod 755 /usr/sbin/powerboard_daemon

chown root:root /etc/systemd/system/powerboard_daemon.service
chown root:root /usr/sbin/powerboard_daemon

systemctl enable powerboard_daemon 
systemctl start powerboard_daemon &