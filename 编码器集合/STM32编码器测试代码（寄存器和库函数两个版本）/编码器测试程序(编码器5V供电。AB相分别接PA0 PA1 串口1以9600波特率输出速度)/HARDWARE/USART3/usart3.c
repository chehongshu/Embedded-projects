
#include "usart3.h"
u8 Usart3_Receive;
 u8 mode_data[8];
 u8 six_data_1[4]={6,5,4,0};
 u8 six_data_2[4]={4,5,6,0};

/**************************************************************************
函数功能：串口3初始化
入口参数：pclk2:PCLK2 时钟频率(Mhz)    bound:波特率
返回  值：无
**************************************************************************/
void uart3_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
  mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<3;   //使能PORTB口时钟  
	RCC->APB1ENR|=1<<18;  //使能串口时钟 
	GPIOB->CRH&=0XFFFF00FF; 
	GPIOB->CRH|=0X00008B00;//IO状态设置
	GPIOB->ODR|=1<<10;	  
	RCC->APB1RSTR|=1<<18;   //复位串口1
	RCC->APB1RSTR&=~(1<<18);//停止复位	   	   
	//波特率设置
 	USART3->BRR=mantissa; // 波特率设置	 
	USART3->CR1|=0X200C;  //1位停止,无校验位.
	//使能接收中断
	USART3->CR1|=1<<8;    //PE中断使能
	USART3->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	MY_NVIC_Init(3,3,USART3_IRQn,2);//组2，最低优先级 
}

/**************************************************************************
函数功能：串口3接收中断
入口参数：无
返回  值：无
**************************************************************************/
void USART3_IRQHandler(void)
{	
	if(USART3->SR&(1<<5))//接收到数据
	{	  
	  static	int uart_receive=0;//蓝牙接收相关变量
		uart_receive=USART3->DR; 
		if(uart_receive<10)    mode_data[0]=uart_receive;

			if((mode_data[0]==six_data_2[0]////手势滑动识别
			&&mode_data[1]==six_data_2[1]
			&&mode_data[2]==six_data_2[2]
			&&mode_data[3]==six_data_2[3])
			||(mode_data[0]==six_data_1[0]
			&&mode_data[1]==six_data_1[1]
			&&mode_data[2]==six_data_1[2]
			&&mode_data[3]==six_data_1[3]))
		{	
			Flag_Stop=!Flag_Stop;
			mode_data[0]=0;	mode_data[1]=0;	mode_data[2]=0;	mode_data[3]=0;
		}
		if(uart_receive==0x00)	Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////刹车
		if(uart_receive==0x05)	Flag_Qian=1,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////后
		if(uart_receive==0x01)	Flag_Qian=0,Flag_Hou=1,Flag_Left=0,Flag_Right=0;//////////////前
		else if(uart_receive==0x06||uart_receive==0x07||uart_receive==0x08)	
													Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=1;
		else if(uart_receive==0x02||uart_receive==0x03||uart_receive==0x04)	
													Flag_Qian=0,Flag_Hou=0,Flag_Left=1,Flag_Right=0;
		
    //以下是保持历史数据
		mode_data[7]=mode_data[6];
		mode_data[6]=mode_data[5];
		mode_data[5]=mode_data[4];
		mode_data[4]=mode_data[3];
		mode_data[3]=mode_data[2];
		mode_data[2]=mode_data[1];
		mode_data[1]=mode_data[0];
	}  											 
} 


