#include "timer.h"
#include "led.h"


void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
							 
}
void TIM5_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef    T;
	NVIC_InitTypeDef           N;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//普通定时器挂在APB1
	T.TIM_Period=arr;//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	T.TIM_Prescaler=psc;//预分频值
	T.TIM_ClockDivision=TIM_CKD_DIV1;//设置时钟源分频
	T.TIM_CounterMode=TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM5,&T);//初始化TIm3
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);//使能TIM3更新中断（更新周期 比较值）
   N.NVIC_IRQChannel=TIM5_IRQn;
	N.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级
	N.NVIC_IRQChannelSubPriority=2;//响应优先级
	N.NVIC_IRQChannelCmd=ENABLE;//使能中断2分组
	NVIC_Init(&N);//初始化中断分组
    TIM_Cmd(TIM5,ENABLE);//使能外设
}



/*********************         中断部分                  **********************/

extern u32 second; 

extern u16 duty_left;
extern u16 duty_right;
extern u16 set_duty_left;
extern u16 set_duty_right; 



void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
	         second++;
		}
}
void TIM5_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 

        if(duty_left>set_duty_left)
              duty_left  -=  10;
        if(duty_left<set_duty_left)
                duty_left  += 10;
        
        if(duty_left==set_duty_left)
            duty_left=set_duty_left;
        
        if(duty_right>set_duty_right)
                duty_right -= 10;
        if(duty_right<set_duty_right)
                duty_right += 10 ;
         
        if(duty_right==set_duty_right)
           duty_right=set_duty_right;
       
		}
}











