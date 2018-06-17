#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define S13  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) //读取按键1（WAKEUP）
#define S14  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//读取按键2（TAMPER）
#define S15  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//读取按键3（USER1）


 


#define KEY13_PRES 	1	//KEY1按下
#define KEY14_PRES	2	//KEY2按下
#define KEY15_PRES	3	//KEY3按下



void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数	


void buzzer_Init() ;
#endif
