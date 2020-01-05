#include "pwm.h"

void init_pwm(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;//PA6  PA7
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;//复用模式
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//将PA6复用到TIM3
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
	TIM_TimeBaseInitStruct.TIM_Period = 100-1;//重装载寄存器     TIM3是16位，所以最大值为65536   100就是10ms
	TIM_TimeBaseInitStruct.TIM_Prescaler = 8400-1;//预分频器  16位，所以最大值为65536   84MHZ/8400=10000Hz
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//二次分频不分频，此时够了
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//PWM1  模式1
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;//低电平有效
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
	
	//允许重装载,持续输出PWM脉冲
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	//允许自动重载
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	//开启定时器开始计数
	TIM_Cmd(TIM3,ENABLE);
}
