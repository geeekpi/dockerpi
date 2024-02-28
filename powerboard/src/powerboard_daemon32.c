#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define DEV_ADDR 0x14

int open_i2c_device(const char *device)
{
    int fd = open(device, O_RDWR);
    if (fd == -1)
    {
        perror(device);
        return -1;
    }
    return fd;
}

int pwr_get_state(int fd, uint8_t *buffer)
{
    uint8_t command[] = {0x32};
    struct i2c_msg messages[] = {
        {DEV_ADDR, 0, 1, command},
        {DEV_ADDR, I2C_M_RD, 1, buffer},
    };
    struct i2c_rdwr_ioctl_data ioctl_data = {messages, 2};
    int result = ioctl(fd, I2C_RDWR, &ioctl_data);
    if (result != 2)
    {
        perror("failed to get variables");
        return -1;
    }
    return 0;
}

int main()
{
    const char *device = "/dev/i2c-1";
    int result = 0;
    uint8_t buf;
    int fd = open_i2c_device(device);
    if (fd < 0)
    {
        return 1;
    }

    for (;;)
    {
        sleep(1);
        result = pwr_get_state(fd, &buf);
        if (fd < 0)
        {
            return 1;
        }

        if ((buf & 0x01) == 0x01)
        {
            printf("Request Halt\n");
            system("sudo sync");
            system("sudo halt");
        }
    }

    close(fd);
    return 0;
}
