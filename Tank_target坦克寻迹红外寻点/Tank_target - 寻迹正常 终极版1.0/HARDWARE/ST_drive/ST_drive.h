#ifndef __ST_DRIVE_H
#define __ST_DRIVE_H 
#include "sys.h"


#define ST_Left_First    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define ST_Left_Second   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)
#define ST_Right_First   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)
#define ST_Right_Second  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)

//ST188≥ı ºªØ
void ST_drive_Init(void);
		 				    
#endif
