# include "beep.h"

//蜂鸣器初始化
void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//使能系统时钟源
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	//初始化IO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
}

