#include "timer.h"
#include "led.h"
#include "Photoelectric_door.h"
#include "details_func.h"
#include "steppermotor.h"

extern int zuozhuan_flag;
extern int youzhuan_flag;
extern int change_direction_flag;


extern char  second_qianhou_flag;
extern char  second_xiang_flag;


extern char second;

extern char reset_flag ;

extern int hair_dry_flag;

extern int Water_spray_flag;


//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
			if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
				{
						TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
								
							
														if(zuoyou_PDoor_L==1)//  碰到左边的光电门
														{
		
																		second_xiang_flag = 1; 
															
															
															
															      zuozhuan_flag  = 0;
														       	youzhuan_flag = 0;
															   
														}
														
														 if(zuoyou_PDoor_R==1)// 碰到右边的光电门
														{							
																			second_xiang_flag = 2;
																			second = 1;
																			Water_spray_flag = 1;
															
                                      zuozhuan_flag  = 1;
															        youzhuan_flag  = 1;
														}
														
														if(qianhou_PDoor_Q == 1)// 碰到前面的
														{
						
																  	second_qianhou_flag  = 1;
														}
														
														if(qianhou_PDoor_H == 1)  //  碰到后面的光电门
														{
						
																	 second_qianhou_flag  = 2;
															
																   reset_flag = 1;  
															
															
															
															     change_direction_flag  = 2;
																	
														}
													
														
													//	 hair dry 的光电门													
													if( HD_zuoyou_PDoor_L == 1)
													 {
															   hair_dry_flag = 3 ;
													 }	
													
													if(HD_zuoyou_PDoor_R == 1)
													 {
															   hair_dry_flag = 1 ;
														}											
						
					
				}
}


//这里使用的是定时器4
void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM4, ENABLE);  //使能TIMx					 
}
//定时器3中断服务程序
extern int reset;

void TIM4_IRQHandler(void)   //TIM3中断
{
						if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
							{
								
											TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx更新中断标志 
										
																					if((reset>=3)&&(reset<7))
																					{
																			
																									shangxia_closedLoop_scan();
																	}
																				
					    }
				
}











