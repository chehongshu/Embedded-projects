# include "timer.h"
# include "ST_drive.h"
# include "steppermotor.h"
# include "led.h"

u8 second = 0;   //计算从小车开始到结束的时间
u8 counter = 0;  //经过黑线条的个数

/*
*********************************************************************************************************
*	函 数 名:     TIM5_Int_Init
*	功能说明:     定时器5中断初始化 
*	形    参：    arr 装载值  psc 预分频 (1ms进一次中断)
*	返 回 值:     void 
*********************************************************************************************************
*/
void TIM5_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//定时器时钟源使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 

	//定时器初始化
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 
 
	//中断使能
	TIM_ITConfig(TIM5, TIM_IT_Update ,ENABLE);
	
	//设置中断向量分组
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 

	//开启定时器
	TIM_Cmd(TIM5, ENABLE); 	 
}

/*
*********************************************************************************************************
*	函 数 名:     TIM6_Int_Init
*	功能说明:     定时器6中断初始化
*	形    参：    arr 装载值  psc 预分频 (1s进一次中断)
*	返 回 值:     void 
*********************************************************************************************************
*/
void TIM6_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//定时器时钟源使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); 

	//定时器初始化
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 
 
	//中断使能
	TIM_ITConfig(TIM6, TIM_IT_Update ,ENABLE);
	
	//设置中断向量分组
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 

	//开启定时器
	TIM_Cmd(TIM6, ENABLE); 	 
}

/*
*********************************************************************************************************
*	函 数 名:     TIM7_Int_Init
*	功能说明:     定时器7中断初始化
*	形    参：    arr 装载值  psc 预分频 (1s进一次中断)
*	返 回 值:     void 
*********************************************************************************************************
*/
void TIM7_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//定时器时钟源使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); 

	//定时器初始化
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 
 
	//中断使能
	TIM_ITConfig(TIM7, TIM_IT_Update ,ENABLE);
	
	//设置中断向量分组
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 

	//开启定时器
	TIM_Cmd(TIM7, ENABLE); 	 
}

u16 left_speed = SPEED_VALUE;     //左车轮装载值
u16 right_speed = SPEED_VALUE;    //右车轮装载值
u8 RightDir_Flag = 0;             //右车轮方向标志位
u8 Stop_Flag = 0;                 //到达射击位置停止标志位
u8 time = 0;                      //出轨计时
u8 time_flag = 0;                 //出轨计时中断标志位

/*
*********************************************************************************************************
*	函 数 名:     TIM5_IRQHandler
*	功能说明:     定时器5中断服务函数 （小车寻迹实现）
*	形    参：    void
*	返 回 值:     void 
*********************************************************************************************************
*/
void TIM5_IRQHandler(void)   
{
	static u16 i = 0;
	//发生定时器溢出中断
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) 
		{
			//左轮靠近黑线
			 if ( 0==ST_Left_First && 1==ST_Left_Second )     
				{
					 left_speed = 2000;                           //左车轮减速    
					 right_speed = SPEED_VALUE;                   //右车轮车速不变
					 speed_change();                              //向左拐弯 //  改变相应的 频率
					
												 if ( 1==time_flag )
												 {
													 time_flag = 0;                               //出轨标志位清零
													 time = 0;                                    //出轨计时清零
													 Warning_Stop();
												 }
				}
				//右车轮靠近黑线
				if ( 1==ST_Right_First && 0==ST_Right_Second )  
				{
					 right_speed = 2000;                           //右车轮减速    
					 left_speed = SPEED_VALUE ;                   //左车轮车速不变
					 speed_change();                              //向右拐弯
					
													 if ( 1==time_flag )
													 {
														 time_flag = 0;                               //出轨标志位清零
														 time = 0;                                    //出轨计时清零
														 Warning_Stop();
													 }
				}
				
													//出轨判断
													if ( 1==ST_Right_First && 1==ST_Right_Second && 0==time_flag)
													{
														time_flag = 1;																//出轨标志位置位
														time = 0;																			//出轨计时清零
														
													}
				
				//大转弯的特殊情况
				if ( 0==RightDir_Flag && second>12 )
				{
					if ( 0==ST_Right_First && 1==ST_Right_Second && 1==ST_Left_First && 1==ST_Left_Second)//0111
					{
						LED0 = 1;//   亮灯
						right_speed = SPEED_VALUE;
						GPIO_ResetBits(GPIOB, GPIO_Pin_6);  //车轮反转
						RightDir_Flag = 1;                  //标志大弯  的 标志位 之后不进入此if  之后  标志位为2  进行延时和继续进行
					}
			  }
				
			//到达射击点
			if ( ((0==ST_Right_First && ( 0==ST_Right_Second || 0==ST_Left_First)) || (0==ST_Left_Second && (0==ST_Right_Second || 0==ST_Left_First) ) )&& 0==Stop_Flag ) 
			{
				 Stop_Flag = 1;                                //到达射击位置停止标志位置位
				 counter ++;
			}
			//  进行停止
			if ( Stop_Flag  )
			{
				if ( 1==counter ) //起点时不停止，小车开始前进// 第一次
				{ 
					Stop_Flag = 0;
				}
				else if ( counter>1 && counter<=6 )// 除了第一次和最后一次
				{
					i++;
					if ( 900==i )   //扫描到炮击点延时900个中断周期停止小车
					{
					 stop_motor();                                 //小车停止行走
					 Warning_Start();                              //警告开始
					}
					if ( 3000==i && counter!=6 )           //暂停3000-900个中断周期后小车开始运行  遇到黑线第6次后小车停止
					{
						start_motor();
						Warning_Stop();
						i = 0;
						Stop_Flag = 0;
					}
				}
				
			}
		
		}
    //清除中断标志位
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  
}

/*
*********************************************************************************************************
*	函 数 名:     TIM6_IRQHandler
*	功能说明:     定时器6中断服务函数 （ 0.5s进中断 实现计时）
*	形    参：    void
*	返 回 值:     void 
*********************************************************************************************************
*/
void TIM6_IRQHandler(void)   
{	
	if ( RESET!=TIM_GetITStatus(TIM6, TIM_IT_Update) )
	{
		second ++;  //秒值加0.5
		
		if ( 1==time_flag )  //偏离轨道判断
		{
			time++;
			
			if ( time>=3 )     //偏离1.5s开始报警
			{
				Warning_Start();
			}
		}
	}
	
	if ( second>240 )      //全程超过两秒钟 开始报警
	{
		Warning_Start();                                  //错误警告 
		stop_motor();                                     //停止运行
	}
	
	//清除中断标志位
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  
}

/*
*********************************************************************************************************
*	函 数 名:     TIM7_IRQHandler
*	功能说明:     定时器7中断服务函数(加速 减速 函数)
*	形    参：    void
*	返 回 值:     void 
*********************************************************************************************************
*/
void TIM7_IRQHandler(void)   
{	
	static u16 i = 0;
	
	if ( RESET != TIM_GetITStatus(TIM7, TIM_IT_Update) )
	{
		if ( 0==Stop_Flag ) //加速曲线实现
		{
			if ( right_speed>SPEED_VALUE )
			{
				right_speed -= 100;//  减相当于加，因为 arr越小 频率越大  速度越快
				speed_change();  //
			}
			else 
			{
				right_speed = SPEED_VALUE;
				speed_change();  //
			}
			
			if ( left_speed>SPEED_VALUE )
			{
				left_speed -= 100;
				speed_change();//
			}
			else 
			{
				left_speed = SPEED_VALUE;
				speed_change(); //
			}
	  }
		else if ( 1==Stop_Flag ) //减速曲线实现
		{
			right_speed += 30;
			left_speed += 30;
			speed_change(); //
		}
		
		//急转弯特殊情况  的延时和 继续run的函数
		if ( 1==RightDir_Flag && (++i)==220 )   //   220为大拐弯的时间  
		{ 
			LED0 = 0;
			GPIO_SetBits(GPIOB, GPIO_Pin_6);//  正转  不进行   反转。
			RightDir_Flag++;//  从此不进入这个程序函数
		}
	}
	
	//清除中断标志位
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);  
}






