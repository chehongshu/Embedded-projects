#ifndef __HAIR_DRYER_H
#define __HAIR_DRYER_H	 
#include "sys.h"
/**
*   吹风机功能
*   anchor ： chehongshu
*   date ： 2017/5/13
**/


		/***************** 第一个电机（大方向的转动 ）    电吹风左右************************/
		/***************** EN->PD10     DIR --> PD12     PWM-->PD14************************/
		
#define HD_zuoyou_ENA_CAN    			GPIO_ResetBits(GPIOD,GPIO_Pin_10)       //使能   
#define HD_zuoyou_ENA_NOT     			GPIO_SetBits(GPIOD,GPIO_Pin_10)     //不使能  

#define HD_zuoyou_DIR_positive     GPIO_SetBits(GPIOD,GPIO_Pin_12);      //   轮子正向    
#define HD_zuoyou_DIR_reverse     GPIO_ResetBits(GPIOD,GPIO_Pin_12);    //   轮子反向 

#define HD_zuoyou_PWM_H    			 GPIO_SetBits(GPIOD,GPIO_Pin_14);      //      
#define HD_zuoyou_PWM_L    			 GPIO_ResetBits(GPIOD,GPIO_Pin_14);    //   


		/***************** 第二个电机（左右的移动） 电吹风旋转*************************/
		/***************** EN->PB12  DIR --> PB14   PWM-->PD8 *************************/
		
#define HD_rotating_ENA_CAN    GPIO_ResetBits(GPIOB,GPIO_Pin_12)       //使能   
#define HD_rotating_ENA_NOT     GPIO_SetBits(GPIOB,GPIO_Pin_12)     //不使能  

#define HD_rotating_DIR_positive     GPIO_SetBits(GPIOB,GPIO_Pin_14);      //   轮子正向    
#define HD_rotating_DIR_reverse     GPIO_ResetBits(GPIOB,GPIO_Pin_14);    //   轮子反向 

#define HD_rotating_PWM_H     GPIO_SetBits(GPIOD,GPIO_Pin_8);      
#define HD_rotating_PWM_L     GPIO_ResetBits(GPIOD,GPIO_Pin_8);    

#define   relay_H      GPIO_SetBits(GPIOC,GPIO_Pin_11);          //  继电器 拉高
#define   relay_L      GPIO_ResetBits(GPIOC,GPIO_Pin_11);        // 继电器拉低


void   A_hair_dryer_init(void);

void  relay_Init(void);

void   HD_zuoyou_go_R(int delaytime);

void   HD_zuoyou_go_L(int delaytime);

void   HD_rotating_go_L(int delaytime);

void   HD_rotating_go_R(int delaytime);

void   stop_rotating(void);


#endif
