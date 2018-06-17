#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "Encoder.h"

signed int angle = 0;
int k = 0;
int main(void)
{
	 
				delay_init();	    	 //延时函数初始化	  
				NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
				TIM4_Init();
				 while(1){
					 angle  =  update_angle();
					 delay_ms(50);
					 k++;
				}
				 
}
