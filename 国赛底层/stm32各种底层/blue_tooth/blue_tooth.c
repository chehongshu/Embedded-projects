#include "blue_tooth.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"

void ceshi(){
	
	GPIO_InitTypeDef  GPIO_InitStructure;
		
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure); 			
}
 void Blue_tooth_number(USART_TypeDef* USART_x,double angle)
{
        /**************************
                 发送阶段
        **************************/ 
	      USART_Sendnumber(USART_x,angle)	;		
        //接收到的数据必须是0x0d 0x0a结尾  所以每次发送一波都要 加上0x0d 0x0a
        USART_SendData(USART_x,0x0d);                                      //
        while(USART_GetFlagStatus(USART_x,USART_FLAG_TC)==RESET);      //    判断    发送  是否  完成
        USART_SendData(USART_x,0x0a);                                        //
        while(USART_GetFlagStatus(USART_x,USART_FLAG_TC)==RESET);       //    判断    发送  是否  完成
        delay_ms(1000);
}

void Blue_tooth_String(USART_TypeDef* USART_x,char* string)
{
        /**************************
                 发送阶段
        **************************/ 
	      USART_Sentstring(USART_x,string)	;		
        //接收到的数据必须是0x0d 0x0a结尾  所以每次发送一波都要 加上0x0d 0x0a
        USART_SendData(USART_x,0x0d);                                      //
        while(USART_GetFlagStatus(USART_x,USART_FLAG_TC)==RESET);      //    判断    发送  是否  完成
        USART_SendData(USART_x,0x0a);                                        //
        while(USART_GetFlagStatus(USART_x,USART_FLAG_TC)==RESET);       //    判断    发送  是否  完成
        delay_ms(1000);
}
