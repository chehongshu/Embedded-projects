#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/

int Encoder_Left;             //左右编码器的脉冲计数

int main(void)
{ 
	Stm32_Clock_Init(9);            //系统时钟设置
	delay_init(72);                 //延时初始化
	uart_init(72,9600);           //初始化串口1
	Encoder_Init_TIM2();            //初始化编码器1 
	Encoder_Init_TIM4();            //初始化编码器2 
	Timer1_Init(499,7199);           //=====5MS进一次中断服务函数
	while(1)
		{
			printf("%d\r\n",Encoder_Left);
		} 
}
