#include "timer.h"


/////        扫描使用。

//通用定时器中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器5!
void Timer5_Init(u16 arr,u16 psc)
{
				TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
				NVIC_InitTypeDef NVIC_InitStructure;

				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //时钟使能

				TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
				TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
				TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
				TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
				TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
		 
			  	TIM_ITConfig(  //使能或者失能指定的TIM中断
					TIM5, //TIM5
					TIM_IT_Update ,
					ENABLE  //使能
					);
					NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5中断
					NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
					NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
					NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
					NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

					TIM_Cmd(TIM5, ENABLE);  //使能TIMx外设
									 
}

extern int Change_Speed;

extern int 	First_Servo_Target ;
extern int 	Second_Servo_Target ;
extern int  Third_Servo_Target ;
extern int  Forth_Servo_Target ;
extern int  Fifth_Servo_Target ;
extern int  Sixth_Servo_Target ;

extern int  First_ServoPWM  ;
extern int  Second_ServoPWM ;
extern int  Third_ServoPWM  ;
extern int  Forth_ServoPWM  ;
extern int  Fifth_ServoPWM  ;
extern int  Sixth_ServoPWM  ;	

/******************** TIM5  中断    函数*************************/
void TIM5_IRQHandler(void)   
{
					if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
						{
							  
										TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
						          	//===  舵机调速度
							//====FIRST 
													if(First_ServoPWM >First_Servo_Target)
													{
																 First_ServoPWM  -= Change_Speed;
													}
													if(First_ServoPWM <First_Servo_Target)
													{
																 First_ServoPWM  += Change_Speed;
													}
													if(First_ServoPWM  ==  First_Servo_Target)
													{
																 First_ServoPWM  = First_Servo_Target;
													}
													
								//====SECOND
													if(Second_ServoPWM >Second_Servo_Target)
													{
																 Second_ServoPWM  -= Change_Speed;
													}else if(Second_ServoPWM <Second_Servo_Target)
													{
																 Second_ServoPWM  += Change_Speed;
													}else if(Second_ServoPWM  ==  Second_Servo_Target)
													{
																 Second_ServoPWM  = Second_Servo_Target;
													}					
							       
								//====THIRD
													if(Third_ServoPWM >Third_Servo_Target)
													{
																 Third_ServoPWM  -= Change_Speed;
													}else if(Third_ServoPWM <Third_Servo_Target)
													{
																 Third_ServoPWM  += Change_Speed;
													}else if(Third_ServoPWM  ==  Third_Servo_Target)
													{
																 Third_ServoPWM  = Third_Servo_Target;
													}					
									//====FORTH
													if(Forth_ServoPWM >Forth_Servo_Target)
													{
																 Forth_ServoPWM  -= Change_Speed;
													}else if(Forth_ServoPWM <Forth_Servo_Target)
													{
																 Forth_ServoPWM  += Change_Speed;
													}else if(Forth_ServoPWM  ==  Forth_Servo_Target)
													{
																 Forth_ServoPWM  = Forth_Servo_Target;
													}						
									//====Fifth
													if(Fifth_ServoPWM >Fifth_Servo_Target)
													{
																 Fifth_ServoPWM  -= Change_Speed;
													}else if(Fifth_ServoPWM <Fifth_Servo_Target)	
													{
																 Fifth_ServoPWM  += Change_Speed;
													}else if(Fifth_ServoPWM  ==  Fifth_Servo_Target)
													{	 
																 Fifth_ServoPWM  = Fifth_Servo_Target;
													}																				
											
											//====Sixth
													if(Sixth_ServoPWM >Sixth_Servo_Target)
													{
																 Sixth_ServoPWM  -= Change_Speed;
													}else if(Sixth_ServoPWM <Sixth_Servo_Target)	
													{
																 Sixth_ServoPWM  += Change_Speed;
													}else if(Sixth_ServoPWM  ==  Sixth_Servo_Target)
													{	 
																 Sixth_ServoPWM  = Sixth_Servo_Target;
													}									
						}
}



//==== USMART   调整程序
void set_First(int value)
{
	First_Servo_Target = value;
}
void  set_Second(int value)
{
	Second_Servo_Target  = value;
}
void   set_T(int value)
{
	Third_Servo_Target = value;
}
void  set_Forth(int value)
{
	Forth_Servo_Target = value;
}
void  set_Fifth(int value)
{
	Fifth_Servo_Target = value;
}
void  set_six(int value)
{
	Sixth_Servo_Target = value;
}


void set_Change_Speed(int speed)
{
	Change_Speed = speed;
}

