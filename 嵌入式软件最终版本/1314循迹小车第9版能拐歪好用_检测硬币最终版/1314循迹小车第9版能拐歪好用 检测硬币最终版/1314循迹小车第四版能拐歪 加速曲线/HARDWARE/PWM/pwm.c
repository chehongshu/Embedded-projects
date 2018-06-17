#include "pwm.h"
#include "led.h"
/////////////        输出PWM
//  PB6    TIM4_CH1   左轮

//  PA1    TIM2_CH2    右轮
void TIM4_PWM_Init(u16 arr,u16 psc)      //  左轮  输出pwm控制  转动
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
    NVIC_InitTypeDef           N;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //使能定时器 4 时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIO外设时钟使能
	                                                                     	

   //设置该引脚为复用输出功能,输出TIM1 CH1 CH2 CH3 CH4的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM4_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出     B6    CH1    左轮
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx        CH_1
    
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1预装载使能	
    
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能TIM3更新中断（更新周期 比较值）
     N.NVIC_IRQChannel=TIM2_IRQn;
	 N.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级
	 N.NVIC_IRQChannelSubPriority=1;//响应优先级
	 N.NVIC_IRQChannelCmd=ENABLE;//使能中断2分组
	 NVIC_Init(&N);//初始化中断分组
    	
	TIM_Cmd(TIM4, ENABLE);  //使能TIM4
 
   
}
void TIM2_PWM_Init(u16 arr,u16 psc)      //   右轮输出pwm控制  转动
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
    NVIC_InitTypeDef           N;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //使能定时器 2 时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设时钟使能
	                                                                     	

   //设置该引脚为复用输出功能,输出TIM1 CH1 CH2 CH3 CH4的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM4_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出     B5     CH1    左轮
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx        CH_2
    
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH1预装载使能	

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能TIM3更新中断（更新周期 比较值）
     N.NVIC_IRQChannel=TIM2_IRQn;
	 N.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级
	 N.NVIC_IRQChannelSubPriority=4;//响应优先级
	 N.NVIC_IRQChannelCmd=ENABLE;//使能中断2分组
	 NVIC_Init(&N);//初始化中断分组
    	
	 TIM_Cmd(TIM2, ENABLE);  //使能TIM2
  
}





extern u32  pulseamount_Left ;
extern u32  pulseamount_Right ;
 // TIM_SetCompare1(TIM4,0); //       左轮
 // TIM_SetCompare2(TIM2,0);  //
////*****************************   (  算距离  ) 周期中断函数 ************************////

extern int pwm_left;
extern int pwm_right;


void TIM4_IRQHandler(void)   //TIM4中断           左轮   测  pwm脉冲数目
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM1  
             if(pwm_left!=0)
                 pulseamount_Left++;              //要做到有脉冲时才开始加
            
              
		}
}
void TIM2_IRQHandler(void)   //TIM2中断            右轮     测  pwm  脉冲数目
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
                 if(pwm_right!=0)
	             pulseamount_Right++;          
		}
}