#include "Hall_element.h"

/*
/霍尔原件   
/用法： 读取io的电平   电平高是  接触    电平低为未接触
*/  
void Hall_element_Init()
{
		 GPIO_InitTypeDef  GPIO_InitStructure;
			
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
			
		 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_5;				 //LED1-->PB.3 端口配置 LED2-->PB.5 端口配置
		 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
		 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
		 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.3
		 GPIO_SetBits(GPIOB,GPIO_Pin_3);						 //PB.3 输出高
		 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出高
}

