#include "stm32f10x.h"  
#include "i2c.h"

void i2c_init(void)
{
	// PB6,7, SDA-PB7, SCL-PB6
	RCC->APB2ENR |= (1 << 3);
	// Mode AF_OD, max speed 50Mhz
	GPIOB->CRL |= 0xFF000000;
	
	// clock I2C1 
	RCC->APB1ENR |= (1 << 21);

	// cau hinh I2C
	I2C1->CR2 = 0x0010; //  Peripheral clock frequency 16Mhz
	I2C1->CCR = 0x0050; // f = 16Mhz, SCL frequency = 100kHz-> T = 80(0x0050)*(1000/16)ns = 5000ns
	I2C1->TRISE = 0x0011; // 1000 ns / (1000 /16)ns = 16 + 1
	I2C1->CR1 |= (1 << 0); // Peripheral enable	
}

void i2c_start(void) 
	{
     I2C1->CR1 |= (1 << 8);	//I2C Start
     while (!(I2C1->SR1 & 0x0001));	// wait start bit 
  }	
	
 void	i2c_stop (void) 
	{
     I2C1->CR1 |= (1 << 9); //I2C Stop
     while (I2C1->SR2 & 0x0002);	//wait BUSY 
	}
	
void i2c_Write (unsigned char c) {

	  I2C1->DR = c;
  	while ((I2C1->SR1 & (1<<7)));   // Wait TxE bit set 
 }

unsigned char i2c_Read (int ack) {
  
	  if (ack) I2C1->CR1 |=  0x0400;	
    else     I2C1->CR1 &= ~0x0400;	
    while ((I2C1->SR1 & 0x00000040));    // Wait until RxNE bit set 
	 
	  return (I2C1->DR);
}
