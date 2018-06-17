#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "encoder.h"

volatile s16 encoder_num;

 int main(void)
 { 

			delay_init();	    	 //延时函数初始化	  
			//uart_init(9600);	 	//串口初始化为9600
			//LED_Init();		  		//初始化与LED连接的硬件接口
			//LCD_Init();
			//	POINT_COLOR=RED; 
			 Encoder_Init();
	 
			while(1) 
			{		 
				
			      encoder_num = update_angle();
			     	//	LCD_ShowNum(20,100,encoder_num,3,16);						//显示一个数字
			} 
			
}
