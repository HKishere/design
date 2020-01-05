#ifndef __LCD1602_H_
#define __LCD1602_H_
#include "stm32f4xx.h"
//#include "common.h"
//#include "sys_stick.h"

//LCD1602 IO
//LCD-RS PB10   
#define LCDRS_PIN         GPIO_Pin_10
#define LCDRS_GPIO        GPIOB
#define LCDRS_SET         GPIO_SetBits(LCDRS_GPIO , LCDRS_PIN)
#define LCDRS_RESET       GPIO_ResetBits(LCDRS_GPIO , LCDRS_PIN)

//LCD-WR PB12   
#define LCDWR_PIN         GPIO_Pin_12
#define LCDWR_GPIO        GPIOB
#define LCDWR_SET         GPIO_SetBits(LCDWR_GPIO , LCDWR_PIN)
#define LCDWR_RESET       GPIO_ResetBits(LCDWR_GPIO , LCDWR_PIN)

//LCD-EN PB14  
#define LCDEN_PIN         GPIO_Pin_14
#define LCDEN_GPIO        GPIOB
#define LCDEN_SET         GPIO_SetBits(LCDEN_GPIO , LCDEN_PIN)
#define LCDEN_RESET       GPIO_ResetBits(LCDEN_GPIO , LCDEN_PIN)

//LCD-PORT PD0-PD7
#define LCD_PORT_PIN        (uint16_t)0x00ff//GPIO_Pin_0|GPIO_Pin_1...|GPIO_Pin_7
#define LCD_GPIO        GPIOD
#define LCD_WRITE_DAT(data)   LCD_GPIO->BSRRH = 0x00ff;LCD_GPIO->BSRRL = (data)//先复位再置位     

void lcd1602_init(void);
void lcd1602_write_command(char comm);
void LCD1602WriteSpeed(unsigned char fl,unsigned char fr);
void LCD_Display_string(int row, int col, unsigned char data[]);
void LCD1602Write_In_A_Row(int row, int col, unsigned char data);

#endif
