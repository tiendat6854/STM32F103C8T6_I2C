#ifndef I2C_H
#define I2C_H

#include "stm32f10x.h"  

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_Write (unsigned char c);
unsigned char i2c_Read (int ack);
void i2c_Address (unsigned char adr);

#endif
