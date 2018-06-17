#include "Hair_dryer.h"
#include "delay.h"

void A_hair_dryer_init(void)
{
				GPIO_InitTypeDef  GPIO_InitStructure;
				//使能GPIO时钟源
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);	 //使能 PC   PD  时钟
			   //初始化IO
				/***************** 第一个电机（大方向的转动 ）    电吹风左右************************/
				/***************** EN->PD10 DIR --> PD12  PWM-->PD14************************/
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_14;				
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_Init(GPIOD, &GPIO_InitStructure);
				/***************** 第二个电机（左右的移动） 电吹风旋转*************************/
				/***************** EN->PB12  DIR --> PB14   PWM-->PD8 *************************/
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_14;			
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_Init(GPIOB, &GPIO_InitStructure);
	
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;		
	     GPIO_Init(GPIOD, &GPIO_InitStructure);
			 
			 HD_zuoyou_ENA_NOT;
			 HD_rotating_ENA_NOT;
			

}

//PC11     继电器
void  relay_Init()
{
	      GPIO_InitTypeDef  GPIO_InitStructure;//  定义结构体
	
				 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //  使能时钟
					
				 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				
				 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	// 拉低输入	 
				 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
				 GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	       relay_L;
	
}

/***********************************************************************************************************
*函数：
*功能：  左右结构向右转
*参数：无
*返回：无
*************************************************************************************************************/

void HD_zuoyou_go_R(int delaytime)
{
	
						HD_zuoyou_ENA_CAN;
	          HD_zuoyou_DIR_positive;
					
						
						HD_zuoyou_PWM_H;
						delay_us(delaytime);
						
	          HD_zuoyou_PWM_L;
					
						delay_us(delaytime);
}
/*
**左右结构向左转
*/
void HD_zuoyou_go_L(int delaytime)
{
	
						HD_zuoyou_ENA_CAN;
						HD_zuoyou_DIR_reverse;
						
						HD_zuoyou_PWM_H;
						delay_us(delaytime);
						
						HD_zuoyou_PWM_L;
						delay_us(delaytime);
}


/***********************************************************************************************************
*函数：
*功能：  吹风机 旋转向左
*参数：无
*返回：无
*************************************************************************************************************/
void   HD_rotating_go_L(int delaytime)
{
						HD_rotating_ENA_CAN;
						HD_rotating_DIR_positive;//  前转
						
						HD_rotating_PWM_H;
						delay_us(delaytime);
						HD_rotating_PWM_L;
					
						delay_us(delaytime);
}
/***********************************************************************************************************
*函数：
*功能：   吹风机 旋转向右
*参数：无
*返回：无
*************************************************************************************************************/
void HD_rotating_go_R(int delaytime)
{
						HD_rotating_ENA_CAN;
						HD_rotating_DIR_reverse;//  后转
						
						HD_rotating_PWM_H;
						delay_us(delaytime);
						HD_rotating_PWM_L;
					
						delay_us(delaytime);
}
/***********************************************************************************************************
*函数：
*功能：   吹风机  不能够 旋转
*参数：无
*返回：无
*************************************************************************************************************/

void stop_rotating()
{
						HD_rotating_ENA_NOT;
						HD_zuoyou_ENA_NOT;
}
