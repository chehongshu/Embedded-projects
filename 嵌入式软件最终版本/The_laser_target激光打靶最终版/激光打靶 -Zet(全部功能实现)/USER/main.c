#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "string.h"
#include "ov7670.h"
#include "timer.h"
#include "exti.h"
#include "usmart.h"
#include "sysvalue.h"
#include "screen.h"
#include "moveMotor.h"


/***********************************************
*摄像头使用的变量
************************************************/
extern u8 ov_sta;	//在exit.c里 面定义
extern u8 ov_frame;	//在timer.c里面定义		 

/**********************************************
*main中定义的函数
***********************************************/
void getXY(int * x, int * y);            //得到激光点的XY坐标

/**************************************************
*自己定义的变量
**************************************************/
//串口返回的数据
int uartReceiveData = 0;
//用于校准的中心点和边缘点
int adjustPoint[2][2];

int temp[2];


//主程序
 int main(void)
 {
	/*
	 摄像头使用以及系统初始化
	 */
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为 115200
 	usmart_dev.init(72);		//初始化USMART		
 	LED_Init();		  			//初始化与LED连接的硬件接口
	KEY_Init();					//初始化按键
	LCD_Init();			   		//初始化LCD   
	motorInit();         //电机初始化
	TIM2_Int_Init(150, 7200);      //接收串口屏返回的数据
	TIM3_Int_Init(150, 7200);
 	POINT_COLOR=RED;			//设置字体为红色 
	while(OV7670_Init())//初始化OV7670
	{
		LCD_ShowString(30,230,200,16,16,"OV7670 Error!!");
		delay_ms(200);
	  LCD_Fill(30,230,239,246,WHITE);
		delay_ms(200);
	}
 	LCD_ShowString(30,230,200,16,16,"OV7670 Init OK");
	delay_ms(1500);	 	   
	TIM6_Int_Init(10000,7199);			//10Khz计数频率,1秒钟中断									  
	EXTI8_Init();						//使能定时器捕获
	OV7670_Window_Set(12,176,240,320);	//设置窗口	  
  OV7670_CS=0;					
	LCD_Clear(BLACK);
	
	//开启激光源
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	
	/*
		这边有bug  待解决
	*/
	printf("page main");
	stop();
	printf("page main");
	stop();
	printf("page main");
	stop();

	
	/*
		主函数模块
	*/
 	while(1)
	{	
		
		switch (uartReceiveData)
		{
			case REC_ADJUST1: centerAdjustFun(); break;
			case REC_ADJUST2: borderAdjustFun(); break;
			case REC_RECDATA: base3Fun(); break;
			case REC_SHOW: improve1Fun(); break;
			case REC_SLIGHT1:break;
			case REC_SLIGHT2:break;
			case REC_OPENLIGHT: GPIO_SetBits(GPIOA, GPIO_Pin_7); break;
			case REC_CLOSELIGHT: GPIO_ResetBits(GPIOA, GPIO_Pin_7); break;
			case REC_GETTENRING: improve2Fun(); break;
			case REC_GETPOINT: getCurrentPoint(); break;
			case REC_GETFOURRING: improve3Fun(4); break;
			case REC_GETFIVERING: improve3Fun(5); break;
			case REC_GETSIXRING: improve3Fun(6); break;
			case REC_GETSEVENRING: improve3Fun(7); break;
			case REC_GETEIGHTRING: improve3Fun(8); break;
			case REC_GETNINERING: improve3Fun(9); break;
			case REC_GETTENRING2: improve2Fun(); break;
			default: break;
		}
	}	   
}


//得到激光点的XY坐标
void getXY(int * x, int * y)
{
	u16 tempXY[2][2] = {0};   //用于临时存放捕获到的红点的x y坐标 tempXY[0][0] tempXY[1][0]红点xy坐标的最小值 tempXY[0][1] tempXY[1][1]红点xy坐标的最大值
	u8 flag = 1;        //用于标记每次调用改函数时是否是第一次位tempXY赋值
	u32 j, i;
 	u16 color;	 
	if(ov_sta)//有帧中断更新？
	{
		LCD_Scan_Dir(U2D_L2R);		//从上到下,从左到右  
		if(lcddev.id==0X1963)LCD_Set_Window((lcddev.width-240)/2,(lcddev.height-320)/2,240,320);//将显示区域设置到屏幕中央
		else if(lcddev.id==0X5510||lcddev.id==0X5310)LCD_Set_Window((lcddev.width-320)/2,(lcddev.height-240)/2,320,240);//将显示区域设置到屏幕中央
		LCD_WriteRAM_Prepare();     //开始写入GRAM	
		OV7670_RRST=0;				//开始复位读指针 
		OV7670_RCK_L;
		OV7670_RCK_H;
		OV7670_RCK_L;
		OV7670_RRST=1;				//复位读指针结束 
		OV7670_RCK_H;
		for(i=0;i<240;i++)
		{
			for (j=0; j<320; j++)
			{
				OV7670_RCK_L;
				color=GPIOC->IDR&0XFF;	//读数据
				OV7670_RCK_H; 
				color<<=8;  
				OV7670_RCK_L;
				color|=GPIOC->IDR&0XFF;	//读数据
				OV7670_RCK_H;
				
				//检测是否是红点
				if ( color>RED-2500 && color<RED+2500 )
				{
					color = WHITE; //是红点就显示白色
					
					//获取点坐标四个方向的最值
					if ( flag )  //第一次检测到白点
					{
						tempXY[0][0] = i;       
						tempXY[0][1] = i;
						tempXY[1][0] = j;
						tempXY[1][1] = j;
						flag = 0;
					}
					else 
					{
						//获取x坐标的最值
						if ( i>tempXY[0][1] )
						{
							tempXY[0][1] = i;
						}
						
						//获取y坐标的最值
						if ( j<tempXY[1][0])
						{
							tempXY[1][0] = j;
						}
						else if ( j>tempXY[1][1] )
						{
							tempXY[1][1] = j;
						}
					}
				}
				else 
				{
					color = BLACK; //不是红点就显示黑色
				}
					
				LCD->LCD_RAM=color;    
			}
		}   							  
 		ov_sta=0;					//清零帧中断标记
		ov_frame++; 
		LCD_Scan_Dir(U2D_L2R);	//恢复默认扫描方向 L2R_U2 DDFT_SCAN_DIR
	} 
	
	//计算红点在屏幕上的中心坐标
	(*x) = (tempXY[0][0] + tempXY[0][1])/2;
	(*y) = (tempXY[1][0] + tempXY[1][1])/2;
}	   











