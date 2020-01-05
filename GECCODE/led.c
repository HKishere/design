#include "led.h"

void init_led(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;//PA6  PA7
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//输出模式
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//推挽
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;//PA6  PA7
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//输出模式
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//推挽
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	//为了确保灯是你开的，先用代码把灯关掉
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);
}
