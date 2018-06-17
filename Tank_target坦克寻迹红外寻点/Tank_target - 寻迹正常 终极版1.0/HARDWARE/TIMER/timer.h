# ifndef __TIMER_H
# define __TIMER_H
# include "sys.h"

# define SPEED_VALUE 1000  //车轮速度值

//定时器5中断初始化
void TIM5_Int_Init(u16 arr,u16 psc); 

//定时器6中断初始化
void TIM6_Int_Init(u16 arr,u16 psc);

//定时器7中断初始化
void TIM7_Int_Init(u16 arr,u16 psc);
 
#endif
