#include "stm32f10x.h"
#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
int Encoder_Left;             //左右编码器的脉冲计数
int main(void)
  { 
		delay_init();	    	            //=====延时函数初始化	
		uart_init(9600);	            //=====串口初始化
    Encoder_Init_TIM2();            //=====编码器接口
		TIM3_Int_Init(499,7199);
    while(1)
	   {
		   	printf("%d\r\n",Encoder_Left);
			 delay_ms(1000);
	   } 
}

