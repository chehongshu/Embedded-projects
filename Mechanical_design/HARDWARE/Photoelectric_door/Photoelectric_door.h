#ifndef __PHOTOELECTRIC_DOOR_H
#define __PHOTOELECTRIC_DOOR_H	 
#include "sys.h"
/***************************************
/  光电门  四个
/    a couple of two
/   one  start  // one  finish

//  zuoyou				start:    PF7      finish:  PE6
//  qianhou  		start:		PG10    finish:  PG14  
//   读取电压值为1时有东西靠近
****************************************/

//  左右的
#define zuoyou_PDoor_L        					  	  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)  
#define zuoyou_PDoor_R        				    	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)
//  前后的
#define qianhou_PDoor_Q           			   GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10)
#define qianhou_PDoor_H          			   	 GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_14)


//  上下的
#define shangxia_PDoor            			    GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_3)


//    吹风机的 左右的光电门
#define  HD_zuoyou_PDoor_L              GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)	
#define  HD_zuoyou_PDoor_R             GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)


#define  HD_rotating_PDoor         		    	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)

void  zuoyou_PDoor_Init(void);

void qianhou_PDoor_Init(void);

void shangxia_PDoor_Init(void);

void HD_zuoyou_PDoor_Init(void);

void HD_rotating_PDoor_Init(void);		    

#endif



