/******************** (C) COPYRIGHT 2015 WYChen********************************
* File Name          : Encoder.h
* Author             : WYChen
* Version            : V1.0.2
* Date               : 06/25/2015
* Description        : The operation of Incremental_Encoder.
*                      This file provides all functions to operate Encoder.
*******************************************************************************/
#ifndef _Encoder_H
#define _Encoder_H
#include "stm32f10x.h"

#define Encoder_BM 390	//编码器每圈脉冲数
#define Encoder_A  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//读取A相电平状态
#define Encoder_B  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//读取B相电平状态
//#define Encoder_Z  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)//读取Z相电平状态


extern signed int Encoder_counter;	

	 
void Encoder_GPIO_Init(void);	//GPIO初始化
void Encoder_EXTIX_Init(void);//IO中断初始化	
void Encoder_Init(void);			//增量式编码器初始化
signed int update_angle(void);//计算角度


#endif


/******************************使用示例***************************
#include "stm32f10x.h"
#include "delay.h"
#include "12864.h"
#include "Encoder.h"

int main()
{
	double a=0;
	delay_init();
  LCD12864_init();//12864初始化
	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	Encoder_Init();
	
 while(1)
 {
//	 J12864_led_int(1,1,Encoder_counter);
//	 J12864_led_int(3,1,Encoder_B);
	 a = update_angle();
	 if(a >= 0)
	 {
		 J12864_led_double(1,1,a,1);
		 J12864_led_double(2,1,0,1);
	 }
	 else
	 {
		 J12864_led_double(1,1,0,1);
		 J12864_led_double(2,1,-a,1);
	 }
	 delay_ms(50);
 }
}	
******************************************************************/

