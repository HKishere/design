#include "tim.h"
#include "sys.h"
void init_tim(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//APB1 42MHz  ��ʱTIM3����ʱ��ʹ�ã�Ƶ�ʱ����84MHz
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//APB2 84MHz  ��ʱTIM3����ʱ��ʹ�ã�Ƶ�ʱ����168MHz
	TIM_TimeBaseInitStruct.TIM_Period = 10000-1;//��װ�ؼĴ���     TIM3��16λ���������ֵΪ65536   10000����1s
	TIM_TimeBaseInitStruct.TIM_Prescaler = 8400-1;//Ԥ��Ƶ��  16λ���������ֵΪ65536   84MHZ/8400=10000Hz
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//���η�Ƶ����Ƶ����ʱ����
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;//TIM3
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;//��Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStruct);	
	/*********************************************************************************/
	TIM_TimeBaseInitStruct.TIM_Period = 1000-1;//��װ�ؼĴ���     TIM3��16λ���������ֵΪ65536   1000����100ms
	TIM_TimeBaseInitStruct.TIM_Prescaler = 16800-1;//Ԥ��Ƶ��  16λ���������ֵΪ65536   168MHZ/16800=10000Hz
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//���η�Ƶ����Ƶ����ʱ����
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
  TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;//TIM1
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;//��Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStruct);	
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//ʹ���ж�
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//ʹ���ж�
	//������ʱ����ʼ����
	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM1,ENABLE);
}

//�жϷ�����   ��startup_stm32f40_41xxx.s����ļ�������
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		PAout(6)=~PAout(6);
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}
//�жϷ�����   ��startup_stm32f40_41xxx.s����ļ�������
void TIM1_UP_TIM10_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
	{
		PAout(7)=~PAout(7);
	}
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
}