#include "exti.h"
#include "sys.h"

void init_exti(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	//ʹ��SYSCFGʱ�ӣ� 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource3);
	EXTI_InitStruct.EXTI_Line = EXTI_Line3;//PE3
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;//ʹ��
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;//�ⲿ�жϴ���
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;//�����ش���
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;//PE3
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;//��Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStruct);	
}

//�жϷ�����   ��startup_stm32f40_41xxx.s����ļ�������
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3)==SET)
	{
		PEout(6) = ~PEout(6);
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}
	