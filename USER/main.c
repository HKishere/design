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

char d_buff[7]={'0'};
char test_num = 255;
unsigned char text[] = "set";
unsigned char temp_buff[3] = {'0'};
unsigned char humi_buff[3] = {'0'};

char i=0;
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
   
		
		d_buff[i++] = USART_ReceiveData(USART1);
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		if(i==7)
		i=0;
		
//		USART_SendData(USART1,d);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//USART_FLAG_TXE   register empty 清空文本框里面的数据然后再发
	  //while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);//USART_FLAG_TC   Complete将文本框里面的字符全部发送
	}
	
	
//	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
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

//				USART_SendData(USART1,'g');
//	    	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
//			  USART_SendData(USART1,'4');
//	    	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
//				USART_SendData(USART1,'7');
//	    	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
//			  delay_s(1);


//				LCD1602WriteSpeed(d_buff,&test_num);
			temp_buff[0] = d_buff[1];
			temp_buff[1] = d_buff[2];
			temp_buff[2] = '\0';
			humi_buff[0] = d_buff[4];
			humi_buff[1] = d_buff[5];
			humi_buff[2] = '\0';
			LCD_Display_string(1, 0, "Temp:");
			LCD_Display_string(1, 5, temp_buff);
			LCD_Display_string(2, 0, "Humi:");
			LCD_Display_string(2, 5, humi_buff);
			delay_s(2);

			test_num = test_num - 1;
		}
	
}

