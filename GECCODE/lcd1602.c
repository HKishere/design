#include "lcd1602.h"
//#include "interface.h"
//#include "stm32f10x.h"
//#include <stdio.h>

//ȫ�ֱ�������
unsigned char const table1[]="     WELCOME    ";
unsigned char const table2[]="      SUST      ";



/*******************************************************************************
* �� �� �� ��LcdBusy
* �������� �����LCDæ״̬,LcdBusy Ϊ1ʱ��æ���ȴ���lcd-busyΪ0ʱ,�У���дָ��������
* ��    �� ����
* ��    �� ��״̬
*******************************************************************************/
//bit LcdBusy()
// {                          
//    bit result;
//    LCDRS_RESET;
//    LCDWR_SET;
//    LCDEN_SET;
//    Delay_us(1);
//    result = (bit)(P0&0x80);
//    LCDEN_RESET;
//    return(result); 
//}
void busy_wait(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	LCDRS_RESET;
	LCDWR_SET;
	LCDEN_RESET;
	delay_us(5);
	LCDEN_SET;
	delay_us(25);
	while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7) == 1);
	LCDEN_RESET;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
}
/*******************************************************************************
* �� �� �� ��write_com
* �������� ��LCD1602 дָ��
* ��    �� ����
* ��    �� ����
*******************************************************************************/
void LcdWriteCom(unsigned char com)
{
	//while(LcdBusy());
	busy_wait();
	delay_us(20);
	LCD_WRITE_DAT(com);
	LCDRS_RESET;
	LCDWR_RESET;
	LCDEN_RESET;
	delay_us(20);
	LCDEN_SET;
	delay_us(10);
	LCDEN_RESET;
	delay_us(10);
	//delay_ms(500);
	//printf("command %#hhx\r\n",com);
}

/*******************************************************************************
* �� �� �� ��write_com
* �������� ��LCD1602 д����
* ��    �� ����
* ��    �� ����
*******************************************************************************/
void lcd_write_dat(unsigned char dat)
{
	//while(LcdBusy());
	delay_us(20);
	LCD_WRITE_DAT(dat);
	LCDRS_SET;
	LCDWR_RESET;
	LCDEN_RESET;
	delay_us(10);
	LCDEN_SET;
	delay_us(10);
	LCDEN_RESET; 
	delay_us(10);	
}

void lcd1602_port_init()
{

  GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//important
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = LCDRS_PIN;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//����Ϊ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//����Ϊ����ģʽ��˵���˾�������������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//����IO�ڵ��ٶ�Ϊ100MHz
	
	GPIO_Init(LCDRS_GPIO , &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = LCDWR_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//����Ϊ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//����Ϊ����ģʽ��˵���˾�������������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//����IO�ڵ��ٶ�Ϊ100MHz
	GPIO_Init(LCDWR_GPIO , &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = LCDEN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//����Ϊ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//����Ϊ����ģʽ��˵���˾�������������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//����IO�ڵ��ٶ�Ϊ100MHz
	GPIO_Init(LCDEN_GPIO , &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = LCD_PORT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//����Ϊ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//����Ϊ����ģʽ��˵���˾�������������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//����IO�ڵ��ٶ�Ϊ100MHz
	GPIO_Init(LCD_GPIO , &GPIO_InitStructure);		
}

/*******************************************************************************
* �� �� �� ��LCD1602Init
* �������� ��LCD1602��ʼ��
* ��    �� ����
* ��    �� ����
*******************************************************************************/
void lcd1602_init(void)
{
	char index=0;
	lcd1602_port_init();
	
	delay_ms(100);
	LcdWriteCom(0x38);  //����16*2��ʾ��8λ���ݽӿ�
	LcdWriteCom(0x0c); //����ʾ����ʾ�������˸
	LcdWriteCom(0x06);//дһ��ָ���Զ���һ
	LcdWriteCom(0x01);//����  
	delay_ms(100);//��ʱһ��ʱ��ʱ�䣬�ȴ�LCD1602�ȶ�	
	
	LcdWriteCom(0x80);//���õ�һ�� ���ݵ�ַָ��
	for(index=0;index<16;index++)
	{
		lcd_write_dat(table1[index]);  //д������             
	}
	
	LcdWriteCom(0xc0);//���õڶ��� ���ݵ�ַָ��
	for(index=0;index<16;index++)
	{
		lcd_write_dat(table2[index]);  //д������             
	}
	delay_ms(100);//��ʱһ��ʱ��ʱ�䣬�ȴ�LCD1602�ȶ�	
	LcdWriteCom(0x01);//����  
}

/*******************************************************************************
* �� �� �� ��LCD1602WriteCommand
* �������� ����ʾָ���Ļ U D L R S 
* ��    �� ��comm �ַ���ʽ
* ��    �� ����
*******************************************************************************/
void LCD1602WriteCommand(char comm)
{
	LcdWriteCom(0xc0 + 14);
	lcd_write_dat(comm);  //д������   
}

void LCD1602WriteSpeed(unsigned char fl,unsigned char fr)
{
	char data_buf[4];
	int index = 0;

	data_buf[3] = 0;
	sprintf(data_buf, "%03d", (int)fl);
	LcdWriteCom(0x80+3);//���õ�һ�� ���ݵ�ַָ��
	for (index = 0; index < 3; index++)
	{
		lcd_write_dat(data_buf[index]); //д������
	}

	sprintf(data_buf, "%03d", (int)fr);
	LcdWriteCom(0xc0 + 3); //���õ�һ�� ���ݵ�ַָ��
	for (index = 0; index < 3; index++)
	{
		lcd_write_dat(data_buf[index]);  //д������             
	}
}
//show char to a confirm row
//row = 1 show in first row , row = 2 show in second row 
//col =[0~15], col is the Longitudinal offset
//int_data is data of temputrue or others
void LCD1602Write_In_A_Row(int row, int col, unsigned char data){
	if (row == 1)
	{
		unsigned char data_buf[4];
		int index = 0;

		data_buf[3] = 0;
		LcdWriteCom(0x80 + col);
		sprintf(data_buf, "%03d", (int)data);
		for (index = 0; index < 3; index++)
		{
			lcd_write_dat(data_buf[index]); //д������
		}
	}
	else if (row == 2)
	{
		unsigned char data_buf[4];
		int index = 0;

		data_buf[3] = 0;
		LcdWriteCom(0xc0 + col);
		sprintf(data_buf, "%03d", (int)data);
		for (index = 0; index < 3; index++)
		{
			lcd_write_dat(data_buf[index]); //д������
		}
	}
	else {
		lcd_write_dat((unsigned char)"E"); //д�����ݳ���
	}
}

//Display a string
void LCD_Display_string(int row, int col, unsigned char data[]){

	int len = 0;
	int index = 0;
	for (; data[len] != '\0'; len++);

	if (row == 1)
	{
		LcdWriteCom(0x80 + col); //���õ�һ�� ���ݵ�ַָ��
		for (index = 0; index < len; index++)
		{
			lcd_write_dat(data[index]); //д������
		}
	}
	else if (row == 2)
	{
		LcdWriteCom(0xc0 + col); //���õڶ��� ���ݵ�ַָ��
		for (index = 0; index < len; index++)
		{
			lcd_write_dat(data[index]); //д������
		}
	}
	else {
		lcd_write_dat((unsigned char)"E"); //д�����ݳ���
	}
}