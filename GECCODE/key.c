#include "key.h"

void DelayMs(void){
	int i;
	unsigned int time_1 = 100;

	while (time_1--){
		for (i = 0; i < 12000; i++);
	}
}

void init_key(void)
 {
	GPIO_InitTypeDef GPIO_InitStruct;
	//��ʼ��ʱ��
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;//����ģʽ
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//����
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOE,&GPIO_InitStruct);
 }
 
 int Key_Scaning(void){
	 int ret = 0;
	 if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0){
		 DelayMs();
		 ret = 1;
	 }
	 if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0){
		 DelayMs();
		 ret = 2;
	 }
	 return ret;
 }