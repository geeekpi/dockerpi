#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define TEMP_REG 0x01
#define LIGHT_REG_L 0x02
#define LIGHT_REG_H 0x03
#define STATUS_REG 0x04
#define ON_BOARD_TEMP_REG 0x05
#define ON_BOARD_HUMIDITY_REG 0x06
#define ON_BOARD_SENSOR_ERROR 0x07
#define BMP280_TEMP_REG 0x08
#define BMP280_PRESSURE_REG_L 0x09
#define BMP280_PRESSURE_REG_M 0x0A
#define BMP280_PRESSURE_REG_H 0x0B
#define BMP280_STATUS 0x0C
#define HUMAN_DETECT 0x0D

uint8_t aReceiveBuf[0x0D + 1];

int main(void)
{

    int fd;
    int i = 0;
    fd = wiringPiI2CSetup(0x17);

    if (fd < 0)
        printf("Extend board Can not be initialized, please enable I2C and try again!\n", fd);

    for (i = TEMP_REG; i <= HUMAN_DETECT; i++)
    {
        aReceiveBuf[i] = wiringPiI2CReadReg8(fd, i);
    }

    if (aReceiveBuf[STATUS_REG] & 0x01)
    {
        printf("Off-chip temperature sensor overrange!\n");
    }
    else if (aReceiveBuf[STATUS_REG] & 0x02)
    {
        printf("No external temperature sensor!\n");
    }
    else
    {
        printf("Current external Sensor Temperature = %d Celsius\n", (int)aReceiveBuf[TEMP_REG]);
    }

    if (aReceiveBuf[STATUS_REG] & 0x04)
    {
        printf("Onboard brightness sensor overrange!\n");
    }
    else if (aReceiveBuf[STATUS_REG] & 0x08)
    {
        printf("Onboard brightness sensor failure!\n");
    }
    else
    {
        printf("Current onboard sensor brightness = %d Lux\n", (int)(aReceiveBuf[LIGHT_REG_H] << 8) | (aReceiveBuf[LIGHT_REG_L]));
    }

    printf("Current onboard sensor temperature = %d Celsius\n", (int)aReceiveBuf[ON_BOARD_TEMP_REG]);
    printf("Current onboard sensor humidity = %d %%\n", (int)aReceiveBuf[ON_BOARD_HUMIDITY_REG]);
    if (aReceiveBuf[ON_BOARD_SENSOR_ERROR] != 0)
    {
        printf("Onboard temperature and humidity sensor data may not be up to date!\n");
    }

    if (aReceiveBuf[BMP280_STATUS] == 0)
    {

        printf("Current barometer temperature = %d Celsius\n", (int)aReceiveBuf[BMP280_TEMP_REG]);
        printf("Current barometer pressure = %d Pascal\n", (int)aReceiveBuf[BMP280_PRESSURE_REG_L] | (int)aReceiveBuf[BMP280_PRESSURE_REG_M] << 8 | (int)aReceiveBuf[BMP280_PRESSURE_REG_H] << 16);
    }
    else
    {
        printf("Onboard barometer works abnormally!\n");
    }

    if (aReceiveBuf[HUMAN_DETECT] == 1)
    {
        printf("Live body detected within 5 seconds!\n");
    }
    else
    {
        printf("No humans detecte!\n");
    }

    return 0;
}
