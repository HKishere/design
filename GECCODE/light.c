#include "light.h"
#include "stm32f4xx.h"

void init_led(void){

    GPIO_InitTypeDef gpio_init_struct;
    gpio_init_struct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_OUT;    
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init_struct.GPIO_OType = GPIO_OType_PP;
    gpio_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA,&gpio_init_struct);
	
		GPIO_SetBits(GPIOA, GPIO_Pin_6 | GPIO_Pin_7);
}
