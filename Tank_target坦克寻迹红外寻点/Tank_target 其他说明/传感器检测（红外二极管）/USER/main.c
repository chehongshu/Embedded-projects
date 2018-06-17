#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "blue_tooth.h"
#include "adc.h"
#include "Under_SMotor.h"
//   用于 蓝牙发送接收 的 简单子程序
	 double  zuo2,you2,zhong;
int main(void)
 {	
		u8 t;
		u8 len;	
		u16 times=0;        
    int i=0;

 
		delay_init();	    	 //延时函数初始化	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
		usart2_init(9600);	 //串口初始化为9600
     Adc_Init();
     Under_SMotor_init();
	   TIM4_Init(999,35);//2k
	   delay_ms(1000);
  	    delay_ms(1000);
	    delay_ms(1000);
	while(1)
	{
		
		 Under_ENA_NOT;
			zuo2=(double)Get_Adc_Average(10,10)*(3.3/4096);
			you2=(double)Get_Adc_Average(11,10)*(3.3/4096);
			zhong=(double)Get_Adc_Average(14,10)*(3.3/4096);
		   if(zuo2>you2)
			 {
			//	 Under_DIR_Left;
			Under_DIR_Right;
				 Under_ENA;
			 }else if(zuo2<you2)
			 {
	//			 Under_DIR_Right;
				 Under_DIR_Left;
				 Under_ENA;
			 }
			 if(zhong>2.45)
			 {
				 Under_ENA_NOT;
			 }
		
		
		    Blue_tooth_String(USART2,"左面的传感器 ");
	    	Blue_tooth_number(USART2,zuo2);
				Blue_tooth_String(USART2,"右边的传感器 ");
		    Blue_tooth_number(USART2,you2);
      	Blue_tooth_String(USART2,"中间的传感器 ");
				Blue_tooth_number(USART2,		zhong);
		
		
		
    }
}
