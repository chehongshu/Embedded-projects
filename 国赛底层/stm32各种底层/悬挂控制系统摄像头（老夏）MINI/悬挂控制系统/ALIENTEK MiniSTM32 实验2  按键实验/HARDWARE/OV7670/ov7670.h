#ifndef _OV7670_H
#define _OV7670_H
#include "sys.h"
#include "sccb.h"


#define OV7670_WRST		PAout(0)		//写指针复位
#define OV7670_RCK		PAout(1)		//读数据时钟
#define OV7670_RRST		PAout(4)  		//读指针复位
#define OV7670_CS		PAout(11)  		//片选信号(OE)
#define OV7670_WREN		PAout(12)		//写入FIFO使能
#define OV7670_VSYNC  	PAin(15)		//同步信号检测IO
															  					 
#define OV7670_DATA   GPIOB->IDR&0x00FF  					//数据输入端口
	    				 
u8   OV7670_Init(void);		  	   		 
void OV7670_Light_Mode(u8 mode);
void OV7670_Color_Saturation(u8 sat);
void OV7670_Brightness(u8 bright);
void OV7670_Contrast(u8 contrast);
void OV7670_Special_Effects(u8 eft);
void OV7670_Window_Set(u16 sx,u16 sy,u16 width,u16 height);


#endif





















