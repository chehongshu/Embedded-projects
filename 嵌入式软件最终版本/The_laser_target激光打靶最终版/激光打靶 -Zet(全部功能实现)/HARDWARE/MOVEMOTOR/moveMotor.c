# include "moveMotor.h"
# include "delay.h"

//电机初始化
void motorInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_3|GPIO_Pin_6);
	
}

//沿x轴移动
void moveX(u8 dir)
{
	int i = 0;
	
	if ( dir )
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	}
	else 
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
	}
	
	for (i=0; i<5; i++)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		delay_us(500);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		delay_us(500);
	}
	
	//GPIO_SetBits(GPIOA, GPIO_Pin_6);
}

//沿y轴转动
void moveY(u8 dir)
{
	int i = 0;
	if ( dir )
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}
	else 
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	}
	
	for (i=0; i<10; i++)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		delay_us(50);
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		delay_us(50);
	}
	
	//GPIO_SetBits(GPIOA, GPIO_Pin_3);
}
	



