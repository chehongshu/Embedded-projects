#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"


#define KEY  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)     //读取按键  低电平则被按下



void KEY_Init(void);//IO初始化

#endif
