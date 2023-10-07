/* sudo gcc powerboard_daemon.c -lwiringPi -O3 -O /usr/sbin/powerboard_daemon */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <fcntl.h>

int main(void)
{
    int fd = -1;
    int val = 0;

    if((fd = open ("/dev/i2c-0", O_RDWR)) < 0)
    {
        if((fd = open ("/dev/i2c-1", O_RDWR)) < 0)
        {
            printf("Your I2C dev can not access!\n");
            return -1;/* i2c not active */
        }
    }
    close(fd);
    sleep(1);
    if ((fd = wiringPiI2CSetup (0x10)) < 0)
    {
        printf("Your I2C connect can not reliable!\n");

        close(fd);
        return -2; /* not device */
    }

    for(;;)
    {
        sleep(1);

        val = wiringPiI2CReadReg8 (fd, 0x32);
        if((val & 0x01 ) == 0x01)
        {
            printf("Request Halt\n");
            system("sudo sync");
            system("sudo halt");
        }

    }
}

