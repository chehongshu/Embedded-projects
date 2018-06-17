#ifndef __USART_H
#define __USART_H	
#include "sys.h" 
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "stdlib.h"

#define bity0(num) (* ( (char *)(&num)+0 ) )
#define bity1(num) (* ( (char *)(&num)+1 ) )
#define bity2(num) (* ( (char *)(&num)+2 ) )
#define bity3(num) (* ( (char *)(&num)+3 ) )
	
#define USART_REC_LEN  			100  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记
extern u16 length;
extern u8  Start;
extern u8  Usart_State;
/*
Usart_State 自定义8位串口状态寄存器作用
0x01 开始接收有效数据标志位
0x02 有效数据接收完毕
0x04 数据溢出（有效数据的长度超出了存储数据的数组的大小）
0x08 数据是否被读取
0x10 数据存储器书否为空 1 不为空 0 为空
*/

void fanhang(USART_TypeDef* USART_x);
void usart_init(u32 bound);
void usart2_init(u32 bound);

//void USART_Sentstring(char *str);
void USART_SentChar(USART_TypeDef* USART_x,char data);
void USART_Sentstring(USART_TypeDef* USART_x,char *str);
void USART_Sendnumber(USART_TypeDef* USART_x,double m);
void USART_Sentstring_1(USART_TypeDef* USART_x,char *str,int n);
void USART_Send_NUM(USART_TypeDef* USART_x,double m,int wei);
void USART_Send_u32(USART_TypeDef* USART_x,u32 m);
void USART_Sentstring_MPU(USART_TypeDef* USART_x,char *str);
void USART_Sentstring_1_MPU(USART_TypeDef* USART_x,char *str,int n);
void USART_Send_NUM_MPU(USART_TypeDef* USART_x,double m,int wei);
void Clr_Rx(u8 *p);
void Clr_array(u8 *p,u8 Array_Len);

void usart1_niming_report(u8 fun,float num,u8 len);
void UsartChangePID(u8 *p);

#endif
