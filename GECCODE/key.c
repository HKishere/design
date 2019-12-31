#include "key.h"

void init_key(void)
 {
	GPIO_InitTypeDef GPIO_InitStruct;
	//初始化时钟
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;//输入模式
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//推挽
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE,&GPIO_InitStruct);
 }