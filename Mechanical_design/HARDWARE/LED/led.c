#include "led.h"

//LED1--> PB5   LED2 --> PB6
void LED_Init(void)
{ 
 GPIO_InitTypeDef  GPIO_InitStructure;
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化LED1,LED2
	
 GPIO_ResetBits(GPIOB,GPIO_Pin_5);						 //PB.3 输出低
 GPIO_ResetBits(GPIOB,GPIO_Pin_6);						 //PB.5 输出低
	
}