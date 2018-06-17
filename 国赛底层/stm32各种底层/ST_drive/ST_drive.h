#ifndef __ST_DRIVE_H
#define __ST_DRIVE_H 
#include "sys.h"


#define ST_Left        GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define ST_Right     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)

void ST_drive_Init();//≥ı ºªØ
		 				    
#endif
