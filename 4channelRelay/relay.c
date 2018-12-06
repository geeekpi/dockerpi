#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define DEVCIE_ADDR  0x10
#define RELAY1  0x01
#define RELAY2  0x02
#define RELAY3  0x03
#define RELAY4  0x04
#define ON      0xFF
#define OFF     0x00

int main(voide){
    printf("Turn on Relays in C\n");
    int fd;
    int i = 0;
    fd = wiringPiI2CSetup(DEVICE_ADDR);
    for(;;){
       for (i=1; i<=4; i++){
          printf("turn on relay No.$d", i);
          wiringPiI2CWriteReg8(fd, i, 0xFF);
          sleep(200);
          printf("turn off relay No.$d", i);
          wiringPiI2CWriteReg8(fd, i, 0x00);
          sleep(200);
       }
    }
    return 0;
} 
