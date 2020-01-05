#include "motor.h"
#include "sys.h"

void init_motor(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//输出模式
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//推挽
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOD,&GPIO_InitStruct);	
}

//前进
void run(void)
{
	//后左轮正转
	PDout(1)=1;//IN1
	PDout(2)=0;//IN2
	//后右轮正转
  PDout(3)=1;
	PDout(4)=0;
}
//后退
void back(void)
{
	//后左轮反转
	PDout(1)=0;//IN1
	PDout(2)=1;//IN2
	//后右轮反转
  PDout(3)=0;
	PDout(4)=1;
}
//左转
void left(void)
{
	//后左轮反转
	PDout(1)=0;//IN1
	PDout(2)=1;//IN2
  //后右轮正转
  PDout(3)=1;
	PDout(4)=0;
}
//右转
void right(void)
{
	//后左轮正转
	PDout(1)=1;//IN1
	PDout(2)=0;//IN2
  //后右轮反转
  PDout(3)=0;
	PDout(4)=1;
}
//停止
void stop(void)
{
	//后左轮不转
	PDout(1)=0;//IN1
	PDout(2)=0;//IN2
  //后右轮不转
  PDout(3)=0;
	PDout(4)=0;
}
