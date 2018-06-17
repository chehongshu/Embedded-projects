#ifndef __LED_H
#define __LED_H	 
#include "sys.h"


#define LED1_H  GPIO_SetBits(GPIOB,GPIO_Pin_5)	
#define LED2_H  GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define LED1_L  GPIO_ResetBits(GPIOB,GPIO_Pin_5)	
#define LED2_L  GPIO_ResetBits(GPIOB,GPIO_Pin_6)

void LED_Init(void);//≥ı ºªØ

		 				    
#endif
