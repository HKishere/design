#include "delay.h"

void delay_us(uint32_t nus)
{
	SysTick->LOAD = (168000000/8/1000000)*nus;//重装载寄存器值，传多少就延时多少us
	SysTick->CTRL |=1;//控制和状态寄存器使能，开始计数
	SysTick->VAL =0;
	
	while((SysTick->CTRL &(1<<16)) == 0);
	SysTick->VAL =0;
}
//延时毫秒级别最大值为798.915ms
void delay_ms(uint32_t nms)
{
	SysTick->LOAD = (168000000/8/1000)*nms;//重装载寄存器值，传多少就延时多少us
	SysTick->CTRL |=1;//控制和状态寄存器使能，开始计数
	SysTick->VAL =0;
	
	while((SysTick->CTRL &(1<<16)) == 0);
	SysTick->VAL =0;
	
}
void delay_s(uint32_t ns)
{
	while(ns--)
	{
		delay_ms(500);
		delay_ms(500);
	}	
}
