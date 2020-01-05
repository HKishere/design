#ifndef _MOTOR_H_
#define _MOTOR_H_
#include "stm32f4xx.h"
void init_motor(void);
void run(void);
void back(void);
void left(void);
void right(void);
void stop(void);
#endif
