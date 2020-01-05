#include "delay.h"

void delay_us(uint32_t nus)
{
	SysTick->LOAD = (168000000/8/1000000)*nus;//��װ�ؼĴ���ֵ�������پ���ʱ����us
	SysTick->CTRL |=1;//���ƺ�״̬�Ĵ���ʹ�ܣ���ʼ����
	SysTick->VAL =0;
	
	while((SysTick->CTRL &(1<<16)) == 0);
	SysTick->VAL =0;
}
//��ʱ���뼶�����ֵΪ798.915ms
void delay_ms(uint32_t nms)
{
	SysTick->LOAD = (168000000/8/1000)*nms;//��װ�ؼĴ���ֵ�������پ���ʱ����us
	SysTick->CTRL |=1;//���ƺ�״̬�Ĵ���ʹ�ܣ���ʼ����
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
