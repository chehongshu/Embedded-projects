#include "LDC1314.h"
#include "delay.h"

  ////  从左到右  0 1 2 3  通道



 /* LDC_Read_Reg(0X00);
 LDC_Read_Reg(0X02);       LDC1314   4个通道
 LDC_Read_Reg(0X04);
 LDC_Read_Reg(0X06); */
 
 
 
 
 
 
//void LDC_Write_Reg(u8 add,u8 value)
//{

//	 IIC_Start(); 
//	IIC_Send_Byte(0X54);	   //发送写命令ADDR=0
//	IIC_Wait_Ack();
//	IIC_Send_Byte(add);
//	IIC_Wait_Ack();
//	IIC_Send_Byte(value);
//	IIC_Wait_Ack();
//  IIC_Stop();//产生一个停止条件 
//	delay_ms(10);	 
//}

//u8 LDC_Read_Reg(u8 add)
//{
//		u16 status;
//	 IIC_Start(); 
//	 IIC_Send_Byte(0X54);	   //发送写命令ADDR=0
//	 IIC_Wait_Ack();
//	 IIC_Send_Byte(add);
//	 IIC_Wait_Ack();
//	 IIC_Start(); 
//	 IIC_Send_Byte(0X55);	   //发送写命令ADDR=0
//	 IIC_Wait_Ack(); 
//	 status=IIC_Read_Byte(0);
//	 IIC_Stop();
//	return (status);
//}

void LDC_Write_Reg(u8 add,u16 value)
{

	 IIC_Start(); 
	IIC_Send_Byte(0X54);	   //发送写命令ADDR=0
	IIC_Wait_Ack();
	IIC_Send_Byte(add);
	IIC_Wait_Ack();
	IIC_Send_Byte(value>>8);
	IIC_Wait_Ack();
	IIC_Send_Byte(value&0xff);
	IIC_Wait_Ack();
   IIC_Stop();//产生一个停止条件 
	delay_ms(10);	 
}

u16 LDC_Read_Reg(u8 add)
{
		u16 status;
	  u16 a,b;
	 IIC_Start(); 
	 IIC_Send_Byte(0X54);	   //发送写命令ADDR=0
	 IIC_Wait_Ack();
	 IIC_Send_Byte(add);
	 IIC_Wait_Ack();
	 IIC_Start(); 
	 IIC_Send_Byte(0X55);	   //发送写命令ADDR=0
	 IIC_Wait_Ack(); 
	 a=IIC_Read_Byte(1); 
	 b=IIC_Read_Byte(0);		
	 status=(a<<8)+b;
	 IIC_Stop();
	return (status);
}
//void LDC_Write_ZI(u8 add,u16 value)
//{

//			LDC_Write_Reg(add,value/256);
//	    LDC_Write_Reg(add+1,value%256);
////	    LDC_Write_Reg(add,value>>8);
////	    LDC_Write_Reg(add+1,value&0XFF);

//}

//u16 LDC_Read_ZI(u8 add)
//{
//		u16 status,a,b;
//	  a=LDC_Read_Reg(add);
//	  b=LDC_Read_Reg(add+1);	
//		status=a*256+b;

//	return (status);
//}

void LDC1314Single_init(void)
{u16 tenp=0;
	LDC_Write_Reg(0x08,0x04D6);//单通道初始化
	LDC_Write_Reg(0x08,0x04D6);
	LDC_Write_Reg(0x08,0x04D6);
	LDC_Write_Reg(0x08,0x04D6);
	
  // LDC_Read_Reg(u8 add)
	LDC_Write_Reg(0x10,0x000A);
  LDC_Write_Reg(0x10,0x000A);
	LDC_Write_Reg(0x10,0x000A);
	LDC_Write_Reg(0x10,0x000A);
	
	LDC_Write_Reg(0x14,0x1002);
	LDC_Write_Reg(0x14,0x1002);
	LDC_Write_Reg(0x14,0x1002);
	LDC_Write_Reg(0x14,0x1002);

	LDC_Write_Reg(0x19,0x0000);
	LDC_Write_Reg(0x19,0x0000);
	LDC_Write_Reg(0x19,0x0000);
	LDC_Write_Reg(0x19,0x0000);
	
	LDC_Write_Reg(0x1B,0x020C);
	LDC_Write_Reg(0x1B,0x020C);
	LDC_Write_Reg(0x1B,0x020C);
	LDC_Write_Reg(0x1B,0x020C);
	
	LDC_Write_Reg(0x1E,0x9000);
	LDC_Write_Reg(0x1E,0x9000);
	LDC_Write_Reg(0x1E,0x9000);
	LDC_Write_Reg(0x1E,0x9000);
	
   tenp=LDC_Read_Reg(0X08);
	LDC_Write_Reg(0x1A,0x1401);
//	LDC_Write_ZI(0x01,0x0001);
}
void LDC1314_MultiInit(void)
   {

   
   LDC_Write_Reg(0x08,0x04D6);
   LDC_Write_Reg(0x09,0x04d6);
	 LDC_Write_Reg(0x0A,0x04d6);
	 LDC_Write_Reg(0x0B,0x04d6);
   LDC_Write_Reg(0x10,0x000A);
   LDC_Write_Reg(0x11,0x000A);
	 LDC_Write_Reg(0x12,0x000A);
	 LDC_Write_Reg(0x13,0x000A);
   LDC_Write_Reg(0x14,0x1002);
   LDC_Write_Reg(0x15,0x1002);
	 LDC_Write_Reg(0x16,0x1002);
	 LDC_Write_Reg(0x17,0x1002);
   LDC_Write_Reg(0x19,0x0000);
   LDC_Write_Reg(0x1B,0xC20C);
       
       
     LDC_Write_Reg(0x1E,0x7000);
     LDC_Write_Reg(0x1F,0x7000);
	 LDC_Write_Reg(0x20,0x7000);
	 LDC_Write_Reg(0x21,0x7000);
     
     
   LDC_Write_Reg(0x1A,0x1401);
}
//输出用的读取code_data的值
//void IO_Init(void){

//   GPIO_InitTypeDef GPIO_InitStructure;
//	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);//使能时钟
//	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6 ;
//	 GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
//	 GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化io口，推挽输出
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//作为片选端口
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //PG8复用推挽输出 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化GPIOG
////	GPIO_SetBits(GPIOG,GPIO_Pin_5);
//	GPIO_ResetBits(GPIOG,GPIO_Pin_6);//PG5，6上拉	
//	GPIO_ResetBits(GPIOG,GPIO_Pin_5);
//	
//}

