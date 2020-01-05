#include "tim.h"
#include "sys.h"
void init_tim(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//APB1 42MHz  此时TIM3做定时器使用，频率变成了84MHz
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//APB2 84MHz  此时TIM3做定时器使用，频率变成了168MHz
	TIM_TimeBaseInitStruct.TIM_Period = 10000-1;//重装载寄存器     TIM3是16位，所以最大值为65536   10000就是1s
	TIM_TimeBaseInitStruct.TIM_Prescaler = 8400-1;//预分频器  16位，所以最大值为65536   84MHZ/8400=10000Hz
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//二次分频不分频，此时够了
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;//TIM3
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;//响应优先级
	NVIC_Init(&NVIC_InitStruct);	
	/*********************************************************************************/
	TIM_TimeBaseInitStruct.TIM_Period = 1000-1;//重装载寄存器     TIM3是16位，所以最大值为65536   1000就是100ms
	TIM_TimeBaseInitStruct.TIM_Prescaler = 16800-1;//预分频器  16位，所以最大值为65536   168MHZ/16800=10000Hz
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//二次分频不分频，此时够了
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
  TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;//TIM1
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;//响应优先级
	NVIC_Init(&NVIC_InitStruct);	
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//使能中断
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//使能中断
	//开启定时器开始计数
	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM1,ENABLE);
}

//中断服务函数   在startup_stm32f40_41xxx.s汇编文件里面找
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		PAout(6)=~PAout(6);
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}
//中断服务函数   在startup_stm32f40_41xxx.s汇编文件里面找
void TIM1_UP_TIM10_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
	{
		PAout(7)=~PAout(7);
	}
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
}