#include "function.h"
#include "steppermotor.h"
#include "delay.h"
#include "Photoelectric_door.h"
 #include "led.h"


/***********************************************************************************************************
*函数：
*功能：  左右结构向右转
*参数：无
*返回：无
*************************************************************************************************************/
int count = 0;
void zuoyou_go_R(int delaytime)
{
						count ++;
						zuoyou_ENA_CAN;
						zuoyou_DIR_reverse;//  右转
						
						zuoyou_PWM_H;
						delay_us(delaytime);
						zuoyou_PWM_L;
					
						delay_us(delaytime);
}
/*
**左右结构向左转
*/
void zuoyou_go_L(int delaytime)
{
	
						zuoyou_ENA_CAN;
						zuoyou_DIR_positive;
						
						zuoyou_PWM_H;
						delay_us(delaytime);
						zuoyou_PWM_L;
					
						delay_us(delaytime);
}


/***********************************************************************************************************
*函数：
*功能：  前后结构向前
*参数：无
*返回：无
*************************************************************************************************************/
void qianhou_go_Q(int delaytime)
{
						qianhou_ENA_CAN;
						qianhou_DIR_positive;//  前转
						
						qianhou_PWM_H;
						delay_us(delaytime);
						qianhou_PWM_L;
					
						delay_us(delaytime);
}
/***********************************************************************************************************
*函数：
*功能：  前后结构向后
*参数：无
*返回：无
*************************************************************************************************************/

void qianhou_go_H(int delaytime)
{
						qianhou_ENA_CAN;
						qianhou_DIR_reverse;//  后转
						
						qianhou_PWM_H;
						delay_us(delaytime);
						qianhou_PWM_L;
					
						delay_us(delaytime);
}


/***********************************************************************************************************
*函数：
*功能：  上下结构向下
*参数：无
*返回：无
*************************************************************************************************************/

void shangxia_go_S(int delaytime)
{
	          int go_i;
						shangxia_ENA_CAN;
						shangxia_DIR_reverse;
	
						shangxia_PWM_H;
          	delay_us(delaytime);
						//for(go_i=0;go_i<1000;go_i++)  __NOP;
						shangxia_PWM_L;
					  delay_us(delaytime);
						//for(go_i=0;go_i<1000;go_i++)  __NOP;
}

/***********************************************************************************************************
*函数：
*功能：  上下结构向上
*参数：无
*返回：无
*************************************************************************************************************/

void shangxia_go_X(int delaytime)
{
						int go_i;
						shangxia_ENA_CAN;
					  shangxia_DIR_positive;
						
						shangxia_PWM_H;
						//delay_us(delaytime);
	          for(go_i=0;go_i<1000;go_i++)  __NOP;
						      shangxia_PWM_L;
					
					  for(go_i=0;go_i<1000;go_i++)  __NOP;
}
