# include "steppermotor.h"
# include "sys.h"

extern u16 left_speed;   //左轮速度
extern u16 right_speed;  //右轮速度

/*
*********************************************************************************************************
*	函 数 名:     steppermotor_init
*	功能说明:     步进电机初始化
*	形    参：    void
*	返 回 值:     void 
*********************************************************************************************************
*/
void steppermotor_init(void)         //  步进电机    前后方向 和  开关  两个io
{
       GPIO_InitTypeDef  GPIO_InitStructure;
       
			//使能GPIO时钟源
       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PC
        
			//初始化IO口
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_5;				
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_Init(GPIOB, &GPIO_InitStructure);
	
			 GPIO_ResetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_7 );  //左右轮电机使能位拉低
			 GPIO_SetBits(GPIOB, GPIO_Pin_6);  //左右轮电机方向
}

/*
*********************************************************************************************************
*	函 数 名:     stop_motor
*	功能说明:     小车停止前进
*	形    参：    void
*	返 回 值:     void 
*********************************************************************************************************
*/
void stop_motor(void)
{    
   TIM_Cmd(TIM3, DISABLE);
	 TIM_Cmd(TIM1, DISABLE);
}


/*
*********************************************************************************************************
*	函 数 名:     start_motor
*	功能说明:     小车开始前进
*	形    参：    void
*	返 回 值:     void 
*********************************************************************************************************
*/
void start_motor(void)
{
   TIM_Cmd(TIM3, ENABLE);
	 TIM_Cmd(TIM1, ENABLE);
}

/*
*********************************************************************************************************
*	函 数 名:     speed_change
*	功能说明:     改变小车速度
*	形    参：    void
*	返 回 值:     void 
*********************************************************************************************************
*/
void speed_change(void)
{
	 TIM_SetAutoreload(TIM3, left_speed);   //  更改左轮速度 
   TIM_SetAutoreload(TIM1, right_speed);  //  更改右轮速度
}


    
