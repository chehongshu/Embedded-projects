#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"
#include "lcd.h"	  
#include "ov7670.h"
#include "usmart.h"  
   
//Mini STM32开发板扩展实验20
//摄像头 实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com	
//广州市星翼电子科技有限公司	  

extern u8 ov_sta;	//在exit.c里面定义
extern u8 ov_frame;	//在timer.c里面定义		 
//更新LCD显示
void camera_refresh(void)
{
	u32 j;
 	u16 color;	 
	if(ov_sta==2)
	{
		LCD_Scan_Dir(U2D_L2R);		//从上到下,从左到右 
		LCD_SetCursor(0x00,0x0000);	//设置光标位置 
		LCD_WriteRAM_Prepare();     //开始写入GRAM	
 		OV7670_CS=0;	 
 		OV7670_RRST=0;				//开始复位读指针 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
		OV7670_RRST=1;				//复位读指针结束 
		OV7670_RCK=1;  
		for(j=0;j<76800;j++)
		{
			GPIOB->CRL=0X88888888;		   
			OV7670_RCK=0; 
			color=OV7670_DATA;		//读数据
			OV7670_RCK=1; 	
			color<<=8;					  
 			OV7670_RCK=0;
			color|=OV7670_DATA;		//读数据		  
			OV7670_RCK=1; 
			GPIOB->CRL=0X33333333;						 	 
			LCD_WR_DATA(color);	 
		}  
 		OV7670_CS=1; 							 
		OV7670_RCK=0; 
		OV7670_RCK=1; 
		EXTI->PR=1<<15;     		//清除LINE8上的中断标志位
		ov_sta=0;					//开始下一次采集
 		ov_frame++; 
		LCD_Scan_Dir(DFT_SCAN_DIR);	//恢复默认扫描方向 	  				 	 
	} 
}	  
int main(void)
{	
	u8 i;	
   	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
  	OV7670_Init();				  

	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD
	if(lcddev.id==0X6804) 	//强制设置屏幕分辨率为320*240.以支持3.5寸大屏
	{
		lcddev.width=240;
		lcddev.height=320; 
	}
	usmart_dev.init(72);	//初始化USMART		
 			    
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,200,16,"Mini STM32");	
	LCD_ShowString(60,70,200,200,16,"OV7670 TEST");	
	LCD_ShowString(60,90,200,200,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,200,16,"2012/10/31");  	 
	LCD_ShowString(60,130,200,200,16,"Use USMART To Set!");	 
  	LCD_ShowString(60,150,200,200,16,"OV7670 Init...");	  
	while(OV7670_Init())//初始化OV7670
	{
		LCD_ShowString(60,150,200,200,16,"OV7670 Error!!");
		delay_ms(200);
	    LCD_Fill(60,230,239,246,WHITE);
		delay_ms(200);
	}
 	LCD_ShowString(60,150,200,200,16,"OV7670 Init OK");
	delay_ms(1500);	 	   	  
	Timerx_Init(10000,7199);			//TIM3,10Khz计数频率,1秒钟中断									  
	EXTI15_Init();						//使能定时器捕获
	OV7670_Window_Set(10,174,240,320);	//设置窗口	  
  	OV7670_CS=0;						 	 
 	while(1)
	{	
 		camera_refresh();	//更新显示	 
 		if(i!=ov_frame)		//DS0闪烁.
		{
			i=ov_frame;
			LED0=!LED0;
 		}
	}	   
}















