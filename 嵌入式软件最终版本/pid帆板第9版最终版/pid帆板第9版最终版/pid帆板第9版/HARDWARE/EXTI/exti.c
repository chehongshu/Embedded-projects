#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
extern int angle; 
extern int speed;
extern int t_angle;
extern int distance;
extern int page;
extern int arrow;
int flag=0;
//外部中断0服务程序
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟

	  KEY_Init();//初始化按键对应io模式

    //GPIOC.5 中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOA.15	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOA.0	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
 
 
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
 
}


//外部中断0服务程序 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖

	if(WK_UP==1)	 	 //WK_UP按键
	{				 
				if(page==1)
		{
			LCD_Clear(WHITE);
			
			if(arrow<=1)
			{
			
			arrow=3;
			LCD_Clear(WHITE);
			}
			else
			arrow--;
			LCD_Clear(WHITE);
		}
		if(page==2)
		{
			speed++;
			if(speed>10)
			{speed=0;}
		}
		if(page==3)
		{
				t_angle++;	
			if(t_angle>60)
			{t_angle=0;}
	
		}		
				if(page==4)
		{
			distance++;	
			if(distance >15)
			{distance=7;}
		}		
	}
	LCD_Clear(WHITE);
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}
 
//外部中断2服务程序
//void EXTI2_IRQHandler(void)
//{
//	delay_ms(10);//消抖
//	LCD_Clear(WHITE);
//	if(KEY2==0)	  //按键KEY2 返回
//	{
//		if(page==2||page==3||page==4)
//		{
//			page=1;
//		}
//	}		 
//	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE2上的中断标志位  
//}
//外部中断3服务程序
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);//消抖

	if(KEY1==0)	 //按键KEY1
	{				 
		if(page==1)
		{
			LCD_Clear(WHITE);
			
			if(arrow>=3)
				
			{
			LCD_Clear(WHITE);
			arrow=1;}
			
			else arrow++;
		}
		if(page==2)
		{
			speed--;
			if(speed<0)
			{speed=10;}
		}
		if(page==3)
		{
			t_angle--;	
			if(t_angle<0)
			{t_angle=60;}
		}		
				if(page==4)
		{
			distance--;	
			if(distance <7)
			{distance=15;}
		}		
		
	}		 
		LCD_Clear(WHITE);
 EXTI_ClearITPendingBit(EXTI_Line15);  //清除LINE15线路挂起位
}

 void  EXTI9_5_IRQHandler(void)
{
	delay_ms(10);//消抖
	LCD_Clear(WHITE);
	if(KEY0==0)	 //按键KEY0
	{
		
		if (page==2||page==3||page==4)
		{  flag=1;
		   
		}
			

		if(page==1)
		{
			if(arrow==1)
			{page=2;}
			
			if(arrow==2)
			{page=3;}
			
			if(arrow==3)
			{page=4;}			

	}		
if (flag==1)
			page=1;
			flag=0;
	
		}		
	LCD_Clear(WHITE);
  EXTI_ClearITPendingBit(EXTI_Line5);    //清除LINE5上的中断标志位  
}
 
