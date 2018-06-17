#include "led.h"

/*
*********************************************************************************************************
*	函 数 名:     LED_Init
*	功能说明:     LED初始化
*	形    参：    void 
*	返 回 值:     void 
*********************************************************************************************************
*/
void LED_Init(void)
{

 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 //使能PB端口时钟
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 
 
 //IO口初始化
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;			
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
 GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
 GPIO_ResetBits(GPIOC,GPIO_Pin_8);					
 GPIO_ResetBits(GPIOC,GPIO_Pin_9 | GPIO_Pin_10);					
}

/*
*********************************************************************************************************
*	函 数 名:     buzzer_Init
*	功能说明:     蜂鸣器初始化
*	形    参：    void 
*	返 回 值:     void 
*********************************************************************************************************
*/
void buzzer_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 //使能PB端口时钟
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 

 //IO口初始化	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 
 GPIO_ResetBits(GPIOC,GPIO_Pin_12);					
}

/*
*********************************************************************************************************
*	函 数 名:     Waring_Start
*	功能说明:     警告开始(灯亮 蜂鸣器响)
*	形    参：    void 
*	返 回 值:     void 
*********************************************************************************************************
*/
void Warning_Start(void)
{
	LED0 = 1;                                     //指示灯亮
	LED1 = 1;
	LED2 = 1;
	GPIO_SetBits(GPIOC, GPIO_Pin_12);              //蜂鸣器响
}

/*
*********************************************************************************************************
*	函 数 名:     Waring_Stop
*	功能说明:     警告停止(灯亮 蜂鸣器响)
*	形    参：    void 
*	返 回 值:     void 
*********************************************************************************************************
*/
void Warning_Stop(void)
{
	LED0 = 0;                                          //指示灯灭
	LED1 = 0;
	LED2 = 0;
	GPIO_ResetBits(GPIOC, GPIO_Pin_12);           //蜂鸣终止
}
 
