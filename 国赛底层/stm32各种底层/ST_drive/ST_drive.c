#include "ST_drive.h"
//st188
/*************************
		  工作原理：
			两路 传感器   
			接触黑色线为   
			不接触黑色线   
	************************/
void ST_drive_Init()
{
	
			GPIO_InitTypeDef  GPIO_InitStructure;
				
			 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
				
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_5;				 //
			 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //  下拉输入
			 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
			 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.3
			 GPIO_SetBits(GPIOB,GPIO_Pin_3);						 //PB.3 输出高
			 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出高
	
}