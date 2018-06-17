/******************** (C) COPYRIGHT 2015 WYChen********************************
* File Name          : Encoder.c
* Author             : WYChen
* Version            : V1.0.2
* Date               : 06/25/2015
* Description        : The operation of Incremental_Encoder.
*                      This file provides all functions to operate Encoder.
*******************************************************************************/
#include "Encoder.h"

//A相 --> PB6
//B相 --> PB7(PB3不能用，原因不明)
//Z相 --> PA0


signed int Encoder_counter=0;


/**********************************************************
*函数：EXTI4_IRQHandler(void)
*功能：A相中断服务程序
*参数：无
*返回：无
*备注：无
**********************************************************/
void EXTI9_5_IRQHandler(void)			
{
	if(Encoder_B==1)	
	{
		Encoder_counter--;
	}
	else
	{
		Encoder_counter++;
	}
	EXTI_ClearITPendingBit(EXTI_Line7);  //清除EXTI4线路挂起位 
}

/**********************************************************
*函数：EXTI0_IRQHandler(void)
*功能：Z相中断服务程序，校准零点
*参数：无
*返回：无
*备注：无
**********************************************************/
void EXTI0_IRQHandler(void)			
{
	Encoder_counter = 0;									//零点校准
	EXTI_ClearITPendingBit(EXTI_Line0);  	//清除EXTI4线路挂起位 
}


/**********************************************************
*函数：Encoder_GPIO_Init(void)
*功能：增量式编码器GPIO初始化
*参数：无
*返回：无
*备注：无
**********************************************************/
void Encoder_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);//使能PORTB时钟

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，JTAG会用到PB3/PB4
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;//PAO
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;//PA3
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.3
//  
//	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;//PB4
//	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; //设置成上拉输入
//	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.4
}


/**********************************************************
*函数：Encoder_EXTIX_Init(void)
*功能：IO中断初始化
*参数：无
*返回：无
*备注：设置A相中断，在中断函数中检测B相电平状态
**********************************************************/
void Encoder_EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
	
//	Encoder_GPIO_Init();//初始化GPIO
	
	//GPIOB.4 A.0中断线以及中断初始化配置
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);//A相中断
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);//Z相中断

	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}


/**********************************************************
*函数：Encoder_Init(void)
*功能：增量式编码器初始化
*参数：无
*返回：无
*备注：无
**********************************************************/
void Encoder_Init(void)
{
	Encoder_GPIO_Init();
	Encoder_EXTIX_Init();
}


/**********************************************************
*函数：update_angle(void)
*功能：处理编码器数据得到角度值
*参数：无
*返回：角度值
*备注：Encoder_BM=360分辨率1度
**********************************************************/
signed int update_angle(void)
{
	double angle=0;
	
	//处理角度
	while(Encoder_counter >=  (Encoder_BM/2))		{Encoder_counter -= Encoder_BM;}
	while(Encoder_counter <= -(Encoder_BM/2))		{Encoder_counter += Encoder_BM;}
	
	angle = Encoder_counter*360/Encoder_BM;
	
	return angle;
}

