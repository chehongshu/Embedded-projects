#ifndef  __HALL_ELEMENT_H
#define __HALL_ELEMENT_H
#include "sys.h"   

///  读取io的值
#define  HALL_ELEMMENT_First     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)//读取第一个霍尔元件
#define  HALL_ELEMMENT_Second  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)//读取第二霍尔元件


#endif




