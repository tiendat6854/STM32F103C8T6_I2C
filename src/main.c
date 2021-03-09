#include "stm32f10x.h"                  // Device header
#include"timer2.h"
#include "i2c.h"

void GPIO_Init_PC13(void)
{
  RCC->APB2ENR |= (1 << 4);
	GPIOC->CRH |= 0x00300000;
}

void delay_ms(uint32_t t)
{
  while(t)
	{
	  TIM2->CNT = 0; 
		while(TIM2->CNT < 1000) {}
	  --t;
	}
}

/*void delay_us(uint32_t delay)
{
	
	TIM2->CNT = 0;
	while (TIM2->CNT < delay) {
	}
}
*/
int main()
{
  GPIO_Init_PC13();
	
	timer2_Init();
	
	i2c_init();
	
	while(1)
	{
		i2c_start();		
    i2c_Write(0xAA);	
		i2c_start();
		i2c_Write(0x55);	
    i2c_Read(0);	
    i2c_stop();	
		
	  GPIOC->ODR |= (1 << 13);
		delay_ms(500);
		GPIOC->ODR &= ~(1 << 13);
		delay_ms(500);
	}
}
