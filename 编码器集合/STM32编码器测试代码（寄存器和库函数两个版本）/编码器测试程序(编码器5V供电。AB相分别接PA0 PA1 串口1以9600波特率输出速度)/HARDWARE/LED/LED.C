#include "led.h"
//初始化 PB8 为输出口.并使能PORTB口的时钟
void LED_Init(void)
{
RCC->APB2ENR|=1<<3; //使能 PORTB 时钟  
GPIOB->CRH&=0XFFFFFFF0;
GPIOB->CRH|=0X00000003;//PB8 推挽输出
GPIOB->ODR|=1<<8; //PB8 输出高
}

/**************************************************************************
函数功能：LED闪烁
入口参数：闪烁频率 
返回  值：无
**************************************************************************/
void Led_Flash(u16 time)
{
	  static int temp;
		if(++temp==time)	LED=~LED,temp=0;
}
