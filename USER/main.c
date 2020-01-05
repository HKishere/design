#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "sys.h"
#include "motor.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "lcd1602.h"

uint16_t d;
uint16_t test_num = 0xf2;
unsigned char text[] = "set";
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		d = USART_ReceiveData(USART1);
		USART_SendData(USART1,d);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//USART_FLAG_TXE   register empty 清空文本框里面的数据然后再发
	  //while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);//USART_FLAG_TC   Complete将文本框里面的字符全部发送
	}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}

int main(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组
	init_led();
	//init_key();
	//init_motor();
	//init_exti();
	//init_tim();
	//init_pwm();
	Usart_init();
	lcd1602_init();
	while(1)
	{
		    if(d == '1')
				{
					PEout(2)=0;
				}
				if(d == '2')
				{
					PEout(2)=1;
				}
				USART_SendData(USART1,'g');
	    	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
			  USART_SendData(USART1,'4');
	    	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
				USART_SendData(USART1,'7');
	    	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
			  delay_s(1);
				
				LCD1602WriteSpeed(0xff,test_num);
				delay_s(1);
				test_num = test_num - 1;
				
	}
	
}

