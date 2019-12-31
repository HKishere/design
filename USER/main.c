#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
int main(void)
{
	int value = 0;
	int flag_1 = 0;
	int flag_2 = 0;
	init_led();
	init_key();
	
	while(1)
	{
		value = Key_Scaning();
		switch (value)
		{
		case 1:
			if (flag_1 == 0)
			{
				flag_1 = 1;
				GPIO_ResetBits(GPIOF, GPIO_Pin_9);
			}
			else
			{
				flag_1 = 0;
				GPIO_SetBits(GPIOF, GPIO_Pin_9);
			}
			break;
		case 2:
			if (flag_2 == 0)
			{
				flag_2 = 1;
				GPIO_ResetBits(GPIOF, GPIO_Pin_10);
			}
			else
			{
				flag_2 = 0;
				GPIO_SetBits(GPIOF, GPIO_Pin_10);
			}
			break;
		default:
			break;
		}
		value = 0;
	}
}
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																											