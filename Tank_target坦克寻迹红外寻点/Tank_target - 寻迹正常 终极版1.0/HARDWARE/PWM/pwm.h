#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

//定时器3通道1PWM输出初始化
void TIM3CH1_PWM_Init(u16 arr,u16 psc);

//定时器1通道4PWM输出初始化
void  TIM1CH4_PWM_Init(u16 arr,u16 psc);

#endif
