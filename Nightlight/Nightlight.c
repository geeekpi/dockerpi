#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define BUTTON_REG_ADDR 0x19

int main(){
        int fd;
        int is_press = 1;
        int is_draw = 0;
        int i = 0;

        fd = wiringPiI2CSetup(0x15);

        for(i = 1;i<25;i++) wiringPiI2CWriteReg8(fd,i,0x00);

        for(;;)
        {
                if (wiringPiI2CReadReg8(fd, BUTTON_REG_ADDR) == 0x01 )
                {
                        is_press++;
                        is_draw = 1;
                        wiringPiI2CWriteReg8(fd,BUTTON_REG_ADDR, 0x0);
                }
                if(is_press && is_draw){
                        is_draw = 0;
                        for(i = 1;i<25;i++){
                                if(is_press > 3) is_press = 1;
                                if(((i + is_press) % 3) == 0)
                                {
                                        wiringPiI2CWriteReg8(fd,i,0xff);
                                }else{
                                        wiringPiI2CWriteReg8(fd,i,0x00);
                                }
                                delay(100);
                        }

                        wiringPiI2CWriteReg8(fd,BUTTON_REG_ADDR, 0x0);
                }
        }
}

