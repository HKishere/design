#include "motor.h"
#include "sys.h"

void init_motor(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//���ģʽ
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//����
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOD,&GPIO_InitStruct);	
}

//ǰ��
void run(void)
{
	//��������ת
	PDout(1)=1;//IN1
	PDout(2)=0;//IN2
	//��������ת
  PDout(3)=1;
	PDout(4)=0;
}
//����
void back(void)
{
	//�����ַ�ת
	PDout(1)=0;//IN1
	PDout(2)=1;//IN2
	//�����ַ�ת
  PDout(3)=0;
	PDout(4)=1;
}
//��ת
void left(void)
{
	//�����ַ�ת
	PDout(1)=0;//IN1
	PDout(2)=1;//IN2
  //��������ת
  PDout(3)=1;
	PDout(4)=0;
}
//��ת
void right(void)
{
	//��������ת
	PDout(1)=1;//IN1
	PDout(2)=0;//IN2
  //�����ַ�ת
  PDout(3)=0;
	PDout(4)=1;
}
//ֹͣ
void stop(void)
{
	//�����ֲ�ת
	PDout(1)=0;//IN1
	PDout(2)=0;//IN2
  //�����ֲ�ת
  PDout(3)=0;
	PDout(4)=0;
}
