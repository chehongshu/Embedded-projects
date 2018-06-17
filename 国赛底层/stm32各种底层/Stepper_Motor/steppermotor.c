#include "steppermotor.h"
#include "sys.h"

/*
*********************************************************************************************************
*	函 数 名:     steppermotor_init()     三个电机
*	功能说明:     步进电机初始化
*	形    参：    void
*	返 回 值:     void 
*********************************************************************************************************
*/
void steppermotor_init(void)         //  步进电机    前后方向 和  开关  两个io
{
        GPIO_InitTypeDef  GPIO_InitStructure;
				//使能GPIO时钟源
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA
								|RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOD, ENABLE);	 //使能PA  PC  PG  PD  时钟
	

					 //初始化IO
					/***************** 第一个电机（大方向的转动）57电机*************************/
					/***************** EN->PG8 DIR --> PC7   PWM-->PC9*************************/
				 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_9;				
				 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
				 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				 GPIO_Init(GPIOC, &GPIO_InitStructure);
				 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
				 GPIO_Init(GPIOG, &GPIO_InitStructure);
					/***************** 第二个电机（左右的移动） 洗头架42*************************/
					/***************** EN->PG2  DIR --> PG4   PWM-->PG6 *************************/
				 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6;				
				 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
				 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				 GPIO_Init(GPIOG, &GPIO_InitStructure);

					/***************** 第三个电机（上下的移动） 丝杆滑台*************************/
					/***************** EN->PD4  DIR --> PD2   PWM-->PD0 *************************/
				 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_2|GPIO_Pin_0;				
				 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
				 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				 GPIO_Init(GPIOD, &GPIO_InitStructure);
				 
				 
				 qianhou_ENA_NOT;
				  zuoyou_ENA_NOT;
					shangxia_ENA_NOT;
}

/*
*********************************************************************************************************
*	函 数 名:     stop_motor
*	功能说明:   停止  电机转动
*	形    参：    void
*	返 回 值:     void 
*********************************************************************************************************
*/
void stop_motor(void)
{    
    GPIO_ResetBits(GPIOD,GPIO_Pin_8);
	  GPIO_ResetBits(GPIOD,GPIO_Pin_14);
}



    
