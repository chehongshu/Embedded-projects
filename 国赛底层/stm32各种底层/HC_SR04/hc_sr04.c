#include "hc_sr04.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include <math.h>

/**************
*Echo   PB11
*Trigle  PB12
***************/

/*****************
* 使用方式
* 改  两个	   trig(控制端)  		echo(接收端)  的IO  
*  初始化+ 直接读取数据。
*****************/
int overflow;   //用于检测是否定时器已经溢出
void RCC_Configuration(void)
{
			/*system clock enable*/
			SystemInit();  //  系统时钟 初始化
}
void delay(void)   //   延时
{ 
			u32 i;
			i=100000;
			while(i--);
}
 // 优先级 设置
void NVIC_Configuration(void)   
{
			/*CAN receive interrupt enable*/
			NVIC_InitTypeDef NVIC_InitStructure;
			
			NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
}
// IO  设置  VCC电源			trig(控制端)  		echo(接收端)     GND
void GPIO_Configuration(void)
{
	
			GPIO_InitTypeDef GPIO_InitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			
			/*Echo pin define*/
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //  浮空输入
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			
			/*Trigle pin define*/
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  							// 推完输出
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
  
 
}
// 时钟设置
void TIM_Configuration(void)
{
				TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
				
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

				TIM_DeInit(TIM2);            //   复位  TIM2

				TIM_TimeBaseStructure.TIM_Period=5000;
				TIM_TimeBaseStructure.TIM_Prescaler=0;
				TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
				TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
				TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
					
				////  使用 捕获
				TIM_PrescalerConfig(TIM2,359,TIM_PSCReloadMode_Immediate);//时钟频率为72MHz/(359+1)=200000
				TIM_ARRPreloadConfig(TIM2, DISABLE);
				TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  //  到达arr的值之后 更新  中断

				TIM_Cmd(TIM2, DISABLE);
}

///  TIM2的  中断函数
void TIM2_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
  {
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    overflow++;
  }
}
/*******************
**  HC SR04和05一样的
** 初始化
********************/
void HC_SR_Init()
{
				/*system clock init*/
			RCC_Configuration();
			
			/*interrupt init*/
			NVIC_Configuration();
			
			/*I\O init*/
			GPIO_Configuration();
			
			/*TIM初始化*/
			TIM_Configuration();
}
/*返回值为毫米级*/
/**
// 测试距离 = （高电平时间*声速（340）） /    2
***/
float Sensor_using(void)
{
				float distance=0;
				u16 TIM=0;
			
					//  Trig 至少来个20us 高电平  作为触发
				GPIO_SetBits(GPIOB,GPIO_Pin_12);
				delay_ms(20);
				GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			
					TIM_Cmd(TIM2, ENABLE); 					//  开定时器
					while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) && overflow==0);  //  等待 B11 拉高
					TIM2->CNT=0;// 清空 计数  从0开始计数
					while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) && overflow==0);  // 等待B11拉低  所以中间记录为B11拉高时间
					TIM_Cmd(TIM2, DISABLE); //  计数 完成
					
					if(overflow!=0)   //这个  有点没看明白  干啥的？
					{
					overflow=0;
					return 0.0;
					}
					TIM=TIM_GetCounter(TIM2);
					distance=(float)sqrt((TIM/20.0*17)*(TIM/20.0*17)-module_interval*module_interval/4.0)+12.0; //12.0为误差补偿
			
			return(distance);
	
}

