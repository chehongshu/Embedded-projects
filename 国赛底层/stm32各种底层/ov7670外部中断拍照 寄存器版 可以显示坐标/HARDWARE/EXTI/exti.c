#include "exti.h"
#include "delay.h"
#include "usart.h"
#include "ov7670.h"

//中断服务函数
u8 ov_sta;
u8 ultra_red = 0;

void EXTI15_10_IRQHandler(void)
{			
	if(EXTI->PR&(1<<15))//是15线的中断
	{     
		if(ov_sta<2)
		{
			if(ov_sta==0)
			{
				OV7670_WRST=0;	 	//复位写指针		  
				OV7670_WRST=1;	
				OV7670_WREN=1;		//允许写入FIFO
			}else OV7670_WREN=0;	//禁止写入FIFO 	 
			
			ov_sta++;
		}
		EXTI->PR=1<<15;     //清除LINE15上的中断标志位	
	}
	
	
	if(EXTI->PR&(1<<13))//是13线的中断
	{     
		printf("PC13 is come 1-0\n");
		ultra_red = 1;
		EXTI->PR=1<<13;     //清除LINE13上的中断标志位	
	}
}



//外部中断初始化程序
//初始化PA15为中断输入.
void EXTI15_Init(void)
{
	RCC->APB2ENR|=1<<2;     //使能PORTA时钟
	RCC->APB2ENR|=1<<4;     //使能PORTC时钟
	JTAG_Set(SWD_ENABLE);	//关闭JTAG  	 
	GPIOA->CRH&=0X0FFFFFFF;	//PA15设置成输入	  
	GPIOA->CRH|=0X80000000; 				   
 	GPIOA->ODR|=1<<15;	   	//PA15上拉	
	
	GPIOC->CRH&=0XFF0FFFFF;	//PC13设置成输入	  
	GPIOC->CRH|=0X00800000; 				   
 	GPIOC->ODR|=1<<13;	   	//PC13上拉	
	
	Ex_NVIC_Config(GPIO_A,15,FTIR);//下降沿触发
	MY_NVIC_Init(2,1,EXTI15_10_IRQn,2);//抢占2，子优先级1，组2	

	Ex_NVIC_Config(GPIO_C,13,FTIR);//下降沿触发
	MY_NVIC_Init(2,1,EXTI15_10_IRQn,2);//抢占2，子优先级1，组2		
}














