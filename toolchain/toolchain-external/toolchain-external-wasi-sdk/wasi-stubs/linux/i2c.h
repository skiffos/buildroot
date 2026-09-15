#ifndef _LINUX_I2C_H
#define _LINUX_I2C_H
#include <asm/types.h>
#define I2C_SLAVE       0x0703
#define I2C_SLAVE_FORCE 0x0706
#define I2C_FUNCS       0x0705
#define I2C_RDWR        0x0707
#define I2C_SMBUS       0x0720
#define I2C_M_RD  0x0001
#define I2C_M_TEN 0x0010
#define I2C_FUNC_I2C              0x00000001
#define I2C_FUNC_10BIT_ADDR       0x00000002
#define I2C_FUNC_SMBUS_READ_BYTE  0x00020000
#define I2C_FUNC_SMBUS_WRITE_BYTE 0x00040000
#define I2C_SMBUS_BYTE      1
#define I2C_SMBUS_BYTE_DATA 2
#define I2C_SMBUS_WORD_DATA 3
#define I2C_SMBUS_BLOCK_DATA 5
#define I2C_SMBUS_I2C_BLOCK_DATA 8
#define I2C_SMBUS_READ  1
#define I2C_SMBUS_WRITE 0
struct i2c_msg { __u16 addr; __u16 flags; __u16 len; __u8 *buf; };
#endif
