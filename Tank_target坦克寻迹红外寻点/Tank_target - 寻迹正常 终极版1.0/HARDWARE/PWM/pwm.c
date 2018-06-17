# include "pwm.h"

/*
*********************************************************************************************************
*	函 数 名:     TIM3CH1_PWM_Init
*	功能说明:     定时器3通道1PWM输出初始化 （PA6 左轮）
*	形    参：    arr 装载值  psc 预分频
*	返 回 值:     void 
*********************************************************************************************************
*/
void TIM3CH1_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//使能GPIO外设时钟使能 使能定时器1时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  
	                                                                     	

   //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//初始化定时器模块
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

  //初始化PWM输出模块
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 100; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure); 

	//MOE 主输出使能	
  TIM_CtrlPWMOutputs(TIM3,ENABLE);	

	//CH1预装载使能	 
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  
	
	//使能TIMx在ARR上的预装载寄存器
	TIM_ARRPreloadConfig(TIM3, ENABLE); 
	 
	//不使能TIM3  即车轮不转动
	TIM_Cmd(TIM3, DISABLE);  
}

/*   
*********************************************************************************************************
*	函 数 名:     TIM1CH4_PWM_Init
*	功能说明:     定时器1通道4PWM输出初始化 ( PA11 右轮)
*	形    参：    arr 装载值  psc 预分频
*	返 回 值:     void 
*********************************************************************************************************
*/
void TIM1CH4_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//使能GPIO外设时钟使能 使能定时器1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  
	                                                                     	

   //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//初始化定时器模块
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 

  //初始化PWM输出模块
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 100; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC4Init(TIM1, &TIM_OCInitStructure); 

	//MOE 主输出使能	
  TIM_CtrlPWMOutputs(TIM1,ENABLE);	

	//CH4预装载使能	 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  
	
	//使能TIMx在ARR上的预装载寄存器
	TIM_ARRPreloadConfig(TIM1, ENABLE); 
	
	//不使能TIM1  即车轮不转动
	TIM_Cmd(TIM1, DISABLE);  
}



