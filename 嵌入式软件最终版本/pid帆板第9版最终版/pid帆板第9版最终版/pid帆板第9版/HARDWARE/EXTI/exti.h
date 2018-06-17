#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"

void EXTIX_Init(void);//外部中断初始化	
//void EXTI2_IRQHandler(void);
//void EXTI3_IRQHandler(void);
//void EXTI4_IRQHandler(void);

void EXTI0_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
 void EXTI9_5_IRQHandler(void);
#endif

