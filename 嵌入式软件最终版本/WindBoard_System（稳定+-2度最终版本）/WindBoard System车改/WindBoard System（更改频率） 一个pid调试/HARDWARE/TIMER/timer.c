# include "timer.h"
# include "usart.h"
# include "led.h"
# include "sysvalue.h"
# include "pid.h"
# include "key.h"

//当前系统状态
extern u8 sysCurrentStyle;

//初始化定时3中断
void TIM2_INT_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//使能定时器3时钟源
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//初始化定时器3
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	//开启定时器
	TIM_Cmd(TIM2, ENABLE);
	
	//设置中断向量分组
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//开启中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

//定时器3中断服务函数
void TIM2_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM2, TIM_IT_Update)!=RESET )
	{
		switch( KEY_Scan() )
		{
			case KEY1_PRES: KEY1_Fun(); break;
			case KEY2_PRES: KEY2_Fun(); break;
			case KEY3_PRES: KEY3_Fun(); break;
			case KEY4_PRES: KEY4_Fun(); break;
			case KEY5_PRES: KEY5_Fun(); break;
			case KEY6_PRES: KEY6_Fun(); break;
			default: break;
		}
	}
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}





