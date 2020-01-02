#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"

int main(void)
{
	init_led();
	init_key();
	init_exti();
	while(1)
	{
		
	}
}
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																										