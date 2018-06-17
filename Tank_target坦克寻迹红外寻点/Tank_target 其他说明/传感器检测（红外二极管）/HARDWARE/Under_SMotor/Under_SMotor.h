#ifndef _UNDER_SMOTOR_H_
#define _UNDER_SMOTOR_H_
#include "sys.h"
/**********************************

***********************************/
#define  Under_ENA   			 GPIO_ResetBits(GPIOB,GPIO_Pin_9);						 //PB.9 输出高     使能
#define  Under_ENA_NOT     GPIO_SetBits(GPIOB,GPIO_Pin_9);						 //PB.9 输出低   not
#define  Under_DIR_Right	 GPIO_ResetBits(GPIOB,GPIO_Pin_10);						 //PB.10 输出高  
#define  Under_DIR_Left 	 GPIO_SetBits(GPIOB,GPIO_Pin_10);						 //PB.10输出低

# define Voltage PAout(1) 

void  Under_SMotor_PWM_Config(void);

void  Under_SMotor_ENA_DIR_Config(void);

void  The_laser_Config(void);

void  Under_SMotor_init(void);

void Change_speed_Undermotor(TIM_TypeDef * TIM ,int value);

void TIM4_Init(u16 arr,u16 psc);

void TIM2_Int_Init(u16 arr,u16 psc);

#endif
