#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
 	 

#define KEY1    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)  //读取按键1
#define KEY2    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) //读取按键2
#define KEY3    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)  //读取按键3 
#define KEY4    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)  //读取按键4
#define KEY5    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) //读取按键5
#define KEY6    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)  //读取按键6 
 

#define KEY1_PRES	1		//KEY1  
#define KEY2_PRES	2		//KEY2 
#define KEY3_PRES	3		//KEY3  
#define KEY4_PRES 4   //KEY4
#define KEY5_PRES 5   //KEY5
#define	KEY6_PRES 6   //KEY6

void KEY_Init(void);   //IO初始化
u8 KEY_Scan(void);  	 //按键扫描函数			
void KEY1_Fun(void);   //按键1功能实现
void KEY2_Fun(void);   //按键2功能实现
void KEY3_Fun(void);   //按键3功能实现
void KEY4_Fun(void);   //按键4功能实现
void KEY5_Fun(void);   //按键5功能实现
void KEY6_Fun(void);   //按键6功能实现
void MenuSureKey_Fun(void);//菜单确认键功能实现
void changeTargetDataUp(u8 * data); //改变目标值函数（加）
void changeTargetDataDown(u8 * data);  //改变目标值函数（减）

#endif
