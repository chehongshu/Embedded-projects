#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "exti.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "pwm.h"
#include "PID.h"
#include "xianshi.h"
extern int speed;
extern int t_angle;
extern int distance;
extern int page;
extern int arrow;	
extern    u8 t; 
extern    u8  key;
extern   u8 lcd_id[12];			//存放LCD ID字符串
extern	float pitch,roll,yaw; 		//欧拉角
extern short aacx,aacy,aacz;		//加速度传感器原始数据
extern	short gyrox,gyroy,gyroz;     //陀螺仪原始数据 
extern  short temp;    //转换用变量
extern  double npwmval;
     

 extern     int i;
void xianshi(int PWM)
{
	

   if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)     //算出 xyz方向上的 三个参数	
        {                                          
            MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
            MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);  //得到陀螺仪数据  
		
				}
		
		if ((page==1)&&(arrow==1))
		{
		temp=-roll*10;//为了显示小数部分
		POINT_COLOR=RED;	  
		LCD_ShowString(10,20,210,16,16,"->"); 
			
			LCD_ShowString(40,20,200,16,16,"fan speed:");
		LCD_ShowxNum(160,20,speed,2,16,0);
			
			
							LCD_ShowString(40,50,200,16,16,"target angle:");
		LCD_ShowxNum(160,50,t_angle,2,16,0);
			
				LCD_ShowString(40,80,200,16,16,"distance:");
		LCD_ShowxNum(160,80,distance,2,16,0);
			
			LCD_ShowString(40,150,200,16,16,"current angle:");
				if(temp<0)
				{
					LCD_ShowChar(40+108,150,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(40+108,150,' ',16,0);		//去掉负号 
				LCD_ShowNum(40+108+12,150,temp/10,3,16);		//显示整数部分	     //显示roll
				LCD_ShowChar(40+108+48,150,'.',16,0);		//显示负号
				LCD_ShowNum(40+108+60,150,temp%10,1,16);		//显示小数部分
				LCD_ShowChar(40+108+72,150,'C',16,0);		//显示负号
	

				
					LCD_ShowString(40,180,200,16,16,"DutyRatio");	
				  	LCD_ShowxNum(160,180,PWM,4,16,0);

		}
		

		
		
				if ((page==1)&&(arrow==2))
		{
	temp=-roll*10;//为了显示小数部分
			POINT_COLOR=RED;	  
		
				LCD_ShowString(40,20,200,16,16,"fan speed:");
		LCD_ShowxNum(160,20,speed,2,16,0);
			
			LCD_ShowString(10,50,210,16,16,"->"); 
							LCD_ShowString(40,50,200,16,16,"target angle:");
		LCD_ShowxNum(160,50,t_angle,2,16,0);
			
				LCD_ShowString(40,80,200,16,16,"distance:");
		LCD_ShowxNum(160,80,distance,2,16,0);
			
			LCD_ShowString(40,150,200,16,16,"current angle:");
				if(temp<0)
				{
					LCD_ShowChar(40+108,150,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(40+108,150,' ',16,0);		//去掉负号 
				LCD_ShowNum(40+108+12,150,temp/10,3,16);		//显示整数部分	     //显示roll
				LCD_ShowChar(40+108+48,150,'.',16,0);		//显示负号
				LCD_ShowNum(40+108+60,150,temp%10,1,16);		//显示小数部分
				LCD_ShowChar(40+108+72,150,'C',16,0);		//显示负号
	

				
					LCD_ShowString(40,180,200,16,16,"DutyRatio");	
				  	LCD_ShowxNum(160,180,PWM,4,16,0);
		}
		
				if ((page==1)&&(arrow==3))
		{
		
temp=-roll*10;//为了显示小数部分
			POINT_COLOR=RED;	  
	 
					LCD_ShowString(40,20,200,16,16,"fan speed:");
		LCD_ShowxNum(160,20,speed,2,16,0);
			
			
							LCD_ShowString(40,50,200,16,16,"target angle:");
		LCD_ShowxNum(160,50,t_angle,2,16,0);
			
				LCD_ShowString(10,80,210,16,16,"->");
				LCD_ShowString(40,80,200,16,16,"distance:");
		LCD_ShowxNum(160,80,distance,2,16,0);
			
			LCD_ShowString(40,150,200,16,16,"current angle:");
				if(temp<0)
				{
					LCD_ShowChar(40+108,150,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(40+108,150,' ',16,0);		//去掉负号 
				LCD_ShowNum(40+108+12,150,temp/10,3,16);		//显示整数部分	     //显示roll
				LCD_ShowChar(40+108+48,150,'.',16,0);		//显示负号
				LCD_ShowNum(40+108+60,150,temp%10,1,16);		//显示小数部分
				LCD_ShowChar(40+108+72,150,'C',16,0);		//显示负号
	

				
					LCD_ShowString(40,180,200,16,16,"DutyRatio");	
				  	LCD_ShowxNum(160,180,PWM,4,16,0);
		}
		
				if (page==2)
		{
	temp=-roll*10;//为了显示小数部分
			POINT_COLOR=RED;	  
		LCD_ShowString(200,20,210,16,16,"<-"); 
			LCD_ShowString(40,20,200,16,16,"fan speed:");
		LCD_ShowxNum(160,20,speed,2,16,0);
			
			
							LCD_ShowString(40,50,200,16,16,"target angle:");
		LCD_ShowxNum(160,50,t_angle,2,16,0);
			
				LCD_ShowString(40,80,200,16,16,"distance:");
		LCD_ShowxNum(160,80,distance,2,16,0);
			
			LCD_ShowString(40,150,200,16,16,"current angle:");
				if(temp<0)
				{
					LCD_ShowChar(40+108,150,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(40+108,150,' ',16,0);		//去掉负号 
				LCD_ShowNum(40+108+12,150,temp/10,3,16);		//显示整数部分	     //显示roll
				LCD_ShowChar(40+108+48,150,'.',16,0);		//显示负号
				LCD_ShowNum(40+108+60,150,temp%10,1,16);		//显示小数部分
				LCD_ShowChar(40+108+72,150,'C',16,0);		//显示负号
	

				
					LCD_ShowString(40,180,200,16,16,"DutyRatio");	
				  	LCD_ShowxNum(160,180,PWM,4,16,0);
		}
		
						if (page==3)
		{
temp=-roll*10;//为了显示小数部分
			POINT_COLOR=RED;	  
	
			LCD_ShowString(40,20,200,16,16,"fan speed:");
		LCD_ShowxNum(160,20,speed,2,16,0);
			
				LCD_ShowString(200,50,210,16,16,"<-"); 
							LCD_ShowString(40,50,200,16,16,"target angle:");
		LCD_ShowxNum(160,50,t_angle,2,16,0);
			
				LCD_ShowString(40,80,200,16,16,"distance:");
		LCD_ShowxNum(160,80,distance,2,16,0);
			
			LCD_ShowString(40,150,200,16,16,"current angle:");
				if(temp<0)
				{
					LCD_ShowChar(40+108,150,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(40+108,150,' ',16,0);		//去掉负号 
				LCD_ShowNum(40+108+12,150,temp/10,3,16);		//显示整数部分	     //显示roll
				LCD_ShowChar(40+108+48,150,'.',16,0);		//显示负号
				LCD_ShowNum(40+108+60,150,temp%10,1,16);		//显示小数部分
				LCD_ShowChar(40+108+72,150,'C',16,0);		//显示负号
	

				
					LCD_ShowString(40,180,200,16,16,"DutyRatio");	
				  	LCD_ShowxNum(160,180,PWM,4,16,0);
		}
		
						if (page==4)
		{
        temp=-roll*10;//为了显示小数部分
			POINT_COLOR=RED;	  
	
			LCD_ShowString(40,20,200,16,16,"fan speed:");
		LCD_ShowxNum(160,20,speed,2,16,0);
			
							LCD_ShowString(40,50,200,16,16,"target angle:");
		LCD_ShowxNum(160,50,t_angle,2,16,0);
			
				LCD_ShowString(200,80,210,16,16,"<-"); 
				LCD_ShowString(40,80,200,16,16,"distance:");
		LCD_ShowxNum(160,80,distance,2,16,0);
			
			LCD_ShowString(40,150,200,16,16,"current angle:");
				if(temp<0)
				{
					LCD_ShowChar(40+108,150,'-',16,0);		//显示负号
					temp=-temp;		//转为正数
				}else LCD_ShowChar(40+108,150,' ',16,0);		//去掉负号 
				LCD_ShowNum(40+108+12,150,temp/10,3,16);		//显示整数部分	     //显示roll
				LCD_ShowChar(40+108+48,150,'.',16,0);		//显示负号
				LCD_ShowNum(40+108+60,150,temp%10,1,16);		//显示小数部分
				LCD_ShowChar(40+108+72,150,'C',16,0);		//显示负号
	

				
					LCD_ShowString(40,180,200,16,16,"DutyRatio");	
				  	LCD_ShowxNum(160,180,PWM,4,16,0);
            }
}

