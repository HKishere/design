#include "usart.h"

void Usart_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_9 | GPIO_Pin_10;//PA9  PA10
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;//����ģʽ
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//����
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;//100MHZ
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	USART_InitStruct.USART_BaudRate = 115200;//������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�����շ�
	USART_InitStruct.USART_Parity = USART_Parity_No;//��У��
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//ֹͣλ1λ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//8λ����λ
	USART_Init(USART1,&USART_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;//USART1
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;//��Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStruct);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
	
	USART_ReceiveData(USART1);
	
}
