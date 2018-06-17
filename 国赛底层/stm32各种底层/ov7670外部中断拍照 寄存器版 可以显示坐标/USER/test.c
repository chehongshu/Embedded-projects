#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "lcd.h" 
#include "sccb.h" 
#include "ov7670.h"
#include "exti.h"
#include "flash.h"
#include "spi.h"
#include "save_rgb.h"
#include "ff.h"  
#include "exfuns.h"

#define mean(x,y) (((x)+(y))>>1)
//ALIENTEK Mini STM32开发板接ov7670 摄像头 
//作者：龚冰剑

//模版来源：
//ALIENTEK Mini STM32开发板范例代码1
//跑马灯实验		   


extern u8 ov_sta ,ultra_red;
typedef struct
{
	u32 X;  //实际坐标X
	u32 Y;  //实际坐标Y
	u32 XY; //实际值
	u32 x_min;
	u32 x_max;
	u32 y_min;
	u32 y_max;
	u32 rgb;
	u32 r;
	u32 g;
	u32 b;
	u16 tp_x;
	u16 tp_y;
}R_XY;
R_XY R;
//u16 buffer[50];
u16 RGB_565[19200];
void start_delay()
{
		POINT_COLOR=RED;//设置字体为红色 		
		delay_ms(1000);
		printf("3\n");	
		LCD_ShowString(30,40,200,24,24,"3");	
		delay_ms(1000);
		printf("2\n");
		LCD_ShowString(30,40,200,24,24,"2");	
		delay_ms(1000);
		printf("1\n");
		LCD_ShowString(30,40,200,24,24,"1");	
		delay_ms(1000);
		printf("Start!\n");
		LCD_ShowString(30,40,200,24,24,"Start!");	
		delay_ms(1000);
}


u8 refresh_TFT_160()
{
	u16 i = 0 , j = 0;
	u16 color = 0;
	u8 temp = 1;

	if(ov_sta == 2)
	{
		lcddev.width=120;
		lcddev.height=160; 
		lcddev.dir = 0;
		LCD_Scan_Dir(D2U_R2L);			//从上到下,从左到右 
		LCD_SetCursor(0x00,0x0000);	//设置光标位置 
		LCD_WriteRAM_Prepare();     //开始写入GRAM	
		
		GPIOB->CRL&=0X00000000;//IO状态设置
		GPIOB->CRL|=0X88888888;//IO状态设置
		GPIOB->ODR|=0X00FF;//IO状态设置
		
		
		temp = 0;
		OV7670_CS=0;	 
 		OV7670_RRST=0;				//开始复位读指针 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
	
		OV7670_RRST=1;				//复位读指针结束 
		OV7670_RCK=1; 
    		
		//delay_ms(3);	
		//pixels();
		//delay_ms(3);	
		for(i = 0 ; i < 120 ; i ++)
		{
			for(j = 0 ; j < 80 ; j ++)
			{
				//color = 0;   
				OV7670_RCK=0;    	
				//color= OV7670_DATA;   
				OV7670_RCK=1; 	
				//color<<=8;
				OV7670_RCK=0; 
				//color|= (OV7670_DATA);        
				OV7670_RCK=1;
			}
			
			for(j = 0 ; j < 160 ; j ++)
			{
				color = 0;
				OV7670_RCK=0;           
				color= OV7670_DATA;   
				OV7670_RCK=1; 		
				color<<=8;
				OV7670_RCK=0;        
				color|= (OV7670_DATA);        
				OV7670_RCK=1;
				RGB_565[j + i * 160] = color;
			}
			
			for(j = 0 ; j < 80 ; j ++)
			{
				//color = 0;   
				OV7670_RCK=0;    	
				//color= OV7670_DATA;   
				OV7670_RCK=1; 	
				//color<<=8;
				OV7670_RCK=0; 
				//color|= (OV7670_DATA);        
				OV7670_RCK=1;
			}
		}
		
 		OV7670_CS=1; 							 
		OV7670_RCK=0; 
		OV7670_RCK=1; 
		ov_sta=0;					//开始下一次采集
		
		
		GPIOB->CRL=0X33333333; //PB0-7  上拉输出
		GPIOB->CRH=0X33333333; //PB8-15 上拉输出
		GPIOB->ODR=0XFFFF;    //全部输出高
		
		for(i = 0 ; i < 19200 ; i ++)
		{
			LCD_WR_DATA(RGB_565[i]); 
			//delay_ms(1);
		}
		LCD_Scan_Dir(DFT_SCAN_DIR);	//恢复默认扫描方向 	  
	}
	
	
	//EXTI->PR=1<<15;     		//清除LINE8上的中断标志位
	//delay_ms(5);
	
	return temp;
}


u8 refresh_TFT_320()
{
	u16 i = 0 , j = 0 , k = 0;
	u16 color = 0;
	u32 t=0;
	u8 temp = 1;
	
	if(ov_sta == 2)
	{
		lcddev.width=240;
		lcddev.height=320; 
		lcddev.dir = 1;
		LCD_Scan_Dir(L2R_D2U);			//从上到下,从左到右 
		LCD_SetCursor(0x00,0x0000);	//设置光标位置 
		LCD_WriteRAM_Prepare();     //开始写入GRAM	
		
		temp = 0;
		OV7670_CS=0;	 
 		OV7670_RRST=0;				//开始复位读指针 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
	
		OV7670_RRST=1;				//复位读指针结束 
		OV7670_RCK=1; 
    		
		//delay_ms(3);	
		//pixels();
		for(k = 0 ; k < 4 ; k ++)
		{
			
			GPIOB->CRL&=0X00000000;//IO状态设置
			GPIOB->CRL|=0X88888888;//IO状态设置
			GPIOB->ODR|=0X00FF;//IO状态设置
				
			//delay_ms(3);	
			for(i = 0 ; i < 320 ; i ++)
			{
				for(j = 0 ; j < 60 ; j ++)
				{
					color = 0;
					OV7670_RCK=0;           
					color= OV7670_DATA;   
					OV7670_RCK=1; 		
					color<<=8;
					OV7670_RCK=0;        
					color|= (OV7670_DATA);        
					OV7670_RCK=1;
					if((j+k*60)>=2&&(j+k*60)<=237&&i>=41&&i<=274)
					{
						if(color>=54000)	
						{	
							R.r=color;		
							if(t<=3)
							{
									R.x_min=j;
									R.y_min=i;
							}
								
							if(R.x_max<=j) R.x_max=j;
						
							if(R.y_max<=i) R.y_max=i;	
						//求出中点
							R.X=mean(R.x_min,R.x_max);
							R.Y=mean(R.y_min,R.y_max);	
							
							t++;
						}	
					}	
					RGB_565[j + i * 60] = color;
				}
			}
		
			
			GPIOB->CRL=0X33333333; //PB0-7  上拉输出
			GPIOB->CRH=0X33333333; //PB8-15 上拉输出
			GPIOB->ODR=0XFFFF;    //全部输出高
			//delay_ms(3);		
			for(i = 0 ; i < 19200 ; i ++)
			{
				LCD_WR_DATA(RGB_565[i]); 
			}
		}
		
		
 		OV7670_CS=1; 							 
		OV7670_RCK=0; 
		OV7670_RCK=1; 
		ov_sta=0;					//开始下一次采集
		
	}
	
	
	
	//EXTI->PR=1<<15;     		//清除LINE8上的中断标志位
	//delay_ms(5);
	return temp;
}



int main(void)
{		 		
	u32 num_i ;
	u8 choice = 0;
	
	Stm32_Clock_Init(9); 	//系统时钟设置
	delay_init(72);	     	//延时初始化
	uart_init(72,9600);	 	//串口初始化为9600
	EXTI15_Init();
	SCCB_Init();
	OV7670_Init();
	/*
	if(lcddev.id==0X6804||lcddev.id==0X5310||lcddev.id==0X5510) //强制设置屏幕分辨率为320*240.以支持3.5寸大屏 无必要
	{
	
		LCD_Clear(BLUE);
		delay_ms(500);
		lcddev.width=120;
		lcddev.height=160; 
		lcddev.dir = 1;
	}
	*/
		//MYDMA_Config(DMA1_Channel1 , (u32)&GPIOB->IDR , (u32)RGB_565[0] , 160);
		//TIM2_Cap_Init(0XFFFF,2-1);		//以72Mhz的频率计数 
	
		LCD_Init();

		//start_delay();
		LCD_Clear(WHITE);
		POINT_COLOR=RED;//设置字体为红色 			
		LCD_ShowString(30,240,200,24,24,"LCDTFT   OK");
		delay_ms(500);
		
		for(num_i = 0 ; num_i < 19200 ; num_i ++)
		{
			RGB_565[num_i] = 200;
		}
		
	
  //GPIOB->CRL=0X88888888;//IO状态设置
	//GPIOB->CRH=0X88888888;//IO状态设置
	//GPIOB->ODR&=0XFFFF;//IO状态设置
	LCD_ShowString(30,70,200,24,24,"1/4");
		
		 
  	OV7670_CS=0;	
	while(1)
	{
		if(ultra_red == 1)
		{
			choice = 1;
		}
		switch(choice)
		{
			case 0:
				while(refresh_TFT_320())
				{
					choice = 0;
					printf("x:%d,y:%d\r\n",R.X,R.Y);
				}				
				//LCD_Clear(BLACK);
				break;
			case 1:
				ultra_red = 0;
				save_to_sdcard();
				delay_ms(3000);
				choice = 0;
				break;
			case 2:
					for(num_i = 0 ; num_i < 20 ; num_i ++)
				{
					while(refresh_TFT_160())
				{choice = 0;}
				}				
				break;
			default:
				choice = 1;
		}
		
		
		//delay_ms(20);
	}	 
	
}








/*



	
	for(j = 0 ; j< 50 ; j ++)
				{
					buffer[j] = 0;
				}



for(j = 0 ; j< 50 ; j ++)
				{
					buffer[j] = (GPIOB->IDR);
				}
				for(j = 0 ; j< 50 ; j ++)
				{
					printf("%x%x%x%x%x%x%x%x " , (buffer[j]&0x80) >> 7 ,  (buffer[j]&0x40) >>6,  (buffer[j]&0x20) >>5 ,( buffer[j]&0x10) >>4, (buffer[j]&0x08) >>3,  (buffer[j]&0x04) >>2,  (buffer[j]&0x02 )>>1  , buffer[j]&0x01);
				}






void refresh_TFT()
{
	u16 i = 0 , j = 0;
	u16 color = 0;
	
	lcddev.width=120;
	lcddev.height=160; 
	lcddev.dir = 1;
	LCD_Scan_Dir(L2R_U2D);			//从上到下,从左到右 
	LCD_SetCursor(0x00,0x0000);	//设置光标位置 
	LCD_WriteRAM_Prepare();     //开始写入GRAM	
	
	GPIOB->CRL&=0X00000000;//IO状态设置
	GPIOB->CRL|=0X88888888;//IO状态设置
	GPIOB->ODR|=0X00FF;//IO状态设置
	
	
		OV7670_CS=0;	 
 		OV7670_RRST=0;				//开始复位读指针 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
	
		OV7670_RRST=1;				//复位读指针结束 
		OV7670_RCK=1; 
    		
		delay_ms(3);	
		//pixels();
		//delay_ms(3);	
		for(i = 0 ; i < 120 ; i ++)
		{
		
		  
			for(j = 0 ; j < 480 ; j ++)
			{
				color = 0;   
				OV7670_RCK=0;    	
				color= OV7670_DATA;   
				OV7670_RCK=1; 	
				color<<=8;
				OV7670_RCK=0; 
				color|= (OV7670_DATA);        
				OV7670_RCK=1;
			}
			for(j = 0 ; j < 160 ; j ++)
			{
				color = 0;
				OV7670_RCK=0;           
				color= OV7670_DATA;   
				OV7670_RCK=1; 		
				color<<=8;
				OV7670_RCK=0;        
				color|= (OV7670_DATA);        
				OV7670_RCK=1;
				RGB_565[j + i * 160] = color;
			}
		}
		
 		OV7670_CS=1; 							 
		OV7670_RCK=0; 
		OV7670_RCK=1; 
		ov_sta=0;					//开始下一次采集
	
	
	GPIOB->CRL=0X33333333; //PB0-7  上拉输出
	GPIOB->CRH=0X33333333; //PB8-15 上拉输出
	GPIOB->ODR=0XFFFF;    //全部输出高
	
	delay_ms(50);
	for(i = 0 ; i < 19200 ; i ++)
	{
		LCD_WR_DATA(RGB_565[i]); 
	}
	LCD_Scan_Dir(DFT_SCAN_DIR);	//恢复默认扫描方向 	  
	EXTI->PR=1<<15;     		//清除LINE8上的中断标志位
}

*/














