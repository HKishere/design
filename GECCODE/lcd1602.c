#include "lcd1602.h"
//#include "interface.h"
//#include "stm32f10x.h"
//#include <stdio.h>

//全局变量定义
unsigned char const table1[]="     WELCOME    ";
unsigned char const table2[]="      SUST      ";



/*******************************************************************************
* 函 数 名 ：LcdBusy
* 函数功能 ：检查LCD忙状态,LcdBusy 为1时，忙，等待。lcd-busy为0时,闲，可写指令与数据
* 输    入 ：无
* 输    出 ：状态
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
* 函 数 名 ：write_com
* 函数功能 ：LCD1602 写指令
* 输    入 ：无
* 输    出 ：无
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
* 函 数 名 ：write_com
* 函数功能 ：LCD1602 写数据
* 输    入 ：无
* 输    出 ：无
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
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//设置为输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//设置为推挽模式，说白了就增加驱动电流
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置IO口的速度为100MHz
	
	GPIO_Init(LCDRS_GPIO , &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = LCDWR_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//设置为输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//设置为推挽模式，说白了就增加驱动电流
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置IO口的速度为100MHz
	GPIO_Init(LCDWR_GPIO , &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = LCDEN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//设置为输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//设置为推挽模式，说白了就增加驱动电流
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置IO口的速度为100MHz
	GPIO_Init(LCDEN_GPIO , &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = LCD_PORT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//设置为输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//设置为推挽模式，说白了就增加驱动电流
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置IO口的速度为100MHz
	GPIO_Init(LCD_GPIO , &GPIO_InitStructure);		
}

/*******************************************************************************
* 函 数 名 ：LCD1602Init
* 函数功能 ：LCD1602初始化
* 输    入 ：无
* 输    出 ：无
*******************************************************************************/
void lcd1602_init(void)
{
	char index=0;
	lcd1602_port_init();
	
	delay_ms(100);
	LcdWriteCom(0x38);  //设置16*2显示，8位数据接口
	LcdWriteCom(0x0c); //开显示，显示光标且闪烁
	LcdWriteCom(0x06);//写一个指针自动加一
	LcdWriteCom(0x01);//清屏  
	delay_ms(100);//延时一段时间时间，等待LCD1602稳定	
	
	LcdWriteCom(0x80);//设置第一行 数据地址指针
	for(index=0;index<16;index++)
	{
		lcd_write_dat(table1[index]);  //写入数据             
	}
	
	LcdWriteCom(0xc0);//设置第二行 数据地址指针
	for(index=0;index<16;index++)
	{
		lcd_write_dat(table2[index]);  //写入数据             
	}
	delay_ms(100);//延时一段时间时间，等待LCD1602稳定	
	LcdWriteCom(0x01);//清屏  
}

/*******************************************************************************
* 函 数 名 ：LCD1602WriteCommand
* 函数功能 ：显示指令到屏幕 U D L R S 
* 输    入 ：comm 字符格式
* 输    出 ：无
*******************************************************************************/
void LCD1602WriteCommand(char comm)
{
	LcdWriteCom(0xc0 + 14);
	lcd_write_dat(comm);  //写入数据   
}

void LCD1602WriteSpeed(unsigned char fl,unsigned char fr)
{
	char data_buf[4];
	int index = 0;

	data_buf[3] = 0;
	sprintf(data_buf, "%03d", (int)fl);
	LcdWriteCom(0x80+3);//设置第一行 数据地址指针
	for (index = 0; index < 3; index++)
	{
		lcd_write_dat(data_buf[index]); //写入数据
	}

	sprintf(data_buf, "%03d", (int)fr);
	LcdWriteCom(0xc0 + 3); //设置第一行 数据地址指针
	for (index = 0; index < 3; index++)
	{
		lcd_write_dat(data_buf[index]);  //写入数据             
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
			lcd_write_dat(data_buf[index]); //写入数据
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
			lcd_write_dat(data_buf[index]); //写入数据
		}
	}
	else {
		lcd_write_dat((unsigned char)"E"); //写入数据出错
	}
}

//Display a string
void LCD_Display_string(int row, int col, unsigned char data[]){

	int len = 0;
	int index = 0;
	for (; data[len] != '\0'; len++);

	if (row == 1)
	{
		LcdWriteCom(0x80 + col); //设置第一行 数据地址指针
		for (index = 0; index < len; index++)
		{
			lcd_write_dat(data[index]); //写入数据
		}
	}
	else if (row == 2)
	{
		LcdWriteCom(0xc0 + col); //设置第二行 数据地址指针
		for (index = 0; index < len; index++)
		{
			lcd_write_dat(data[index]); //写入数据
		}
	}
	else {
		lcd_write_dat((unsigned char)"E"); //写入数据出错
	}
}