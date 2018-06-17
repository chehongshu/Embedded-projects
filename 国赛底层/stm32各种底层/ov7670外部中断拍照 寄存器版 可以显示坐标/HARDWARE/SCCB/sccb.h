#ifndef __SCCB_H
#define __SCCB_H
#include "sys.h"

//由7670改7620

#define SCCB_SDA_IN()  {GPIOC->CRL&=0XFF0FFFFF;GPIOC->CRL|=0X00800000;}
#define SCCB_SDA_OUT() {GPIOC->CRL&=0XFF0FFFFF;GPIOC->CRL|=0X00300000;}

//IO操作函数	 
#define SCCB_SCL    		PCout(4)	 	//SCL
#define SCCB_SDA    		PCout(5) 		//SDA	 

#define SCCB_READ_SDA    	PCin(5)  		//输入SDA    
#define SCCB_ID   			0X42  			//OV7670的ID 与7620相同

///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_RD_Byte(void);
u8 SCCB_WR_Reg(u8 reg,u8 data);
u8 SCCB_RD_Reg(u8 reg);
#endif













