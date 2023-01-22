#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

static inline int set_address(int fd, int addr) {
   return ioctl(fd, I2C_SLAVE, addr);
}
