#include "stm32f4xx.h"
#include "led.h"
int main(void)
{
	init_led();
	init_key();
	
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0)
			{
				GPIO_ResetBits(GPIOF,GPIO_Pin_9);
				
		}
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)
			{
				GPIO_ResetBits(GPIOF,GPIO_Pin_10);
				
		}
		
		GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10); 
		
	}
	
}
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																											