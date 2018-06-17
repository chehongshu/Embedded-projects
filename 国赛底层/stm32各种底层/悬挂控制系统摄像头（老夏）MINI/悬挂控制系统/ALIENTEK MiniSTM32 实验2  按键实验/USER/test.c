#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "steper.h" 
#include "key.h" 
#include "movexy.h"
#include "ov7670.h"
#include "exti.h"
#include "lcd.h" 
//ALIENTEK Mini STM32开发板范例代码2
//按键输入实验		   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
#define linecount 240
#define mean(x,y) (((x)+(y))>>1)
u32 y[linecount];
s32 aC,bC;
s32 aT,bT; //目标AB坐标
s32 aE,bE; //AB坐标位移矢量
u32 x_min=240;
u32 x_max=0;
u32 y_min=320;
u32 y_max=0;
u32 x_start=0;
u32 y_start=0;
double stepnum = 392.16;  // 脉冲数
double xprepx;
double yprepx;
double xoffset;
double yoffset;
extern u8 ov_sta;
u16 RGB_565[19200];
u32 t=0;
u8 refresh_TFT_320()
{
	u16 i = 0 , j = 0 , k = 0;
	u16 color = 0;
	u8 temp = 1;
	t=0;
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
		x_min=240;
		x_max=0;
		//delay_ms(3);	
		//pixels();
		for(k = 0 ; k < 4 ; k ++)
		{
			
			GPIOB->CRL&=0X00000000;//IO状态设置
			GPIOB->CRL|=0X88888888;//IO状态设置
			GPIOB->ODR|=0X00FF;//IO状态设置
				
			//delay_ms(3);	
			for(i = 0 ; i < 60 ; i ++)
			{
				y_min=320;
				y_max=0;
				for(j = 0 ; j < 320 ; j ++)
				{
					color = 0;
					OV7670_RCK=0;           
					color= OV7670_DATA;   
					OV7670_RCK=1; 		
					color<<=8;
					OV7670_RCK=0;        
					color|= (OV7670_DATA);        
					OV7670_RCK=1;
					color>>=11;
					if((j>120&&j<270)&&((i+k*60)>10&&(i+k*60)<220))
					{
						if(color<17)
						{
							color=0;
							/*
							if(t==0)
							{
								printf("i:%d,j:%d,k:%d\r\n",i,j,k);
								x_min=i+k*60;													
								y_min=j;
							}*/
							if(x_min>=(i+k*60)) x_min=i+k*60;
							
							if(x_max<=(i+k*60)) x_max=i+k*60;	
							
							if(y_min>=j) y_min=j;
									
							if(y_max<=j) y_max=j;
							
							y[i+k*60]=320-mean(y_min,y_max);
											
							t=1;
						}	
						else	
						{
							color=0xffff;//white
						}	
					}
					else
					{
						color=0xf800; // red
					}
					if(j==y_min)
					{
						color=0x03e0;//
					}
					if((i+k*60)==x_min)
					{
						color=0x03e0;
					}
					
					RGB_565[j + i * 320] = color;
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
	
		LCD_Scan_Dir(DFT_SCAN_DIR);	//恢复默认扫描方向 	  
	}
	
	else
	{
	}
	
	//EXTI->PR=1<<15;     		//清除LINE8上的中断标志位
	//delay_ms(5);
	return temp;
}
int main(void)
{	
	double xl,yl;
	int	i;
	Stm32_Clock_Init(9); 	//系统时钟设置
	delay_init(72);	     	//延时初始化 
	uart_init(72,9600);		//串口初始化为9600
	LCD_Init();			   		//初始化LCD  
	EXTI15_Init();
	steperInit();
	while(OV7670_Init())
 	{
		POINT_COLOR=RED;			//设置字体为红色 
		LCD_ShowString(30,130,200,16,16,"ov7670 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}  
//	OV7670_Brightness(3);
	aC=31059;
	bC=44229;
//	for(i=0;i<linecount;i++)
//	{
//		moveTo(x[i],y[i]);
//	}
//	moveTo(0.0,0.0);
	POINT_COLOR=GREEN;
	refresh_TFT_320();
	refresh_TFT_320();
	refresh_TFT_320();
	xprepx=47.5/(x_max-x_min);
	xoffset=60.0-x_max*xprepx;
	yprepx=38.0/(y[x_max]-y[x_min]);
	yoffset=61-y[x_max]*yprepx;
	
	for(i=x_min;i<(x_max+1);i++)
	{
		xl=xprepx*i+xoffset;
		yl=yprepx*y[i]+yoffset;
		printf("moveto:x:%lf,y:%lf\r\n",xl,yl);
		printf("moveto:x:%d,y:%d\r\n",i,y[i]);
		moveTo(xl,yl);
//		LCD_DrawLine(0,y[i],320,y[i]);
//		LCD_DrawLine(i,0,i,240);

	}
	moveTo(0.0,0.0);
	while(1)
	{
//		printf("x_min:%d,y_min:%d,x_max:%d,y_max:%d\r\n",x_min,y[x_min],x_max,y[x_max]);
	}		 
}

























