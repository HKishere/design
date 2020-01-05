#include "pwm.h"

void init_pwm(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;//PA6  PA7
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;//����ģʽ
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//��PA6���õ�TIM3
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
	TIM_TimeBaseInitStruct.TIM_Period = 100-1;//��װ�ؼĴ���     TIM3��16λ���������ֵΪ65536   100����10ms
	TIM_TimeBaseInitStruct.TIM_Prescaler = 8400-1;//Ԥ��Ƶ��  16λ���������ֵΪ65536   84MHZ/8400=10000Hz
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//���η�Ƶ����Ƶ����ʱ����
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//PWM1  ģʽ1
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;//�͵�ƽ��Ч
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
	
	//������װ��,�������PWM����
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	//�����Զ�����
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	//������ʱ����ʼ����
	TIM_Cmd(TIM3,ENABLE);
}
