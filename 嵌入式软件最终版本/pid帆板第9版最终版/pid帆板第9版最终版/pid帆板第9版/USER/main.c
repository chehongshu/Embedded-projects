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



int speed=10;
int t_angle=45;
int distance=10;
int page=1;
int arrow=1;
    u8 t=0; 
    u8  key=0;
    u8 lcd_id[12];			//存放LCD ID字符串

	float pitch,roll,yaw; 		//欧拉角
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;     //陀螺仪原始数据 
    short temp;    //温度
     
     
     float setroll;             //设置的角度
     double pwmval=0;                  //每次 pid算出来的角度
     static double  npwmval=0; //累加的角度
         //设置的  roll角度   
      int i;
			double DIP=0.0;
void INIT()
{    	
	
	delay_init();	    //延时函数初始化	 
    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    
    IncPID_Init();  //pid初始化 
    
    usart_init(9600);	 	//串口初始化为9600  
    
	MPU_Init();   //   里面已经有了  mpu的iic操作    
   
  
	 LED_Init();			     //LED端口初始化   里面有pwm复用应放在pwm初始化的前面
	
     LCD_Init();
    

      EXTIX_Init();        //按键中断初始化

   TIM1_PWM_Init(999,72); //1khz       （72M/72）的分之一时间乘以999+1位一周期的时间反过来就是频率
      POINT_COLOR=RED;

		
}

	
 	
 	
	
 int main(void)
 {	 
     

	 INIT();
	
     sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。
   
    while(mpu_dmp_init())
 	{
		LCD_ShowString(30,130,200,16,16,"MPU6050 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}    


  	while(1) 
	{		 
					if(Usart_State&0x02)
		 {   UsartChangePID(USART_RX_BUF);
			 Usart_State|=0x08;
			 Usart_State&=~0x02;
//			 DIP=sptr->Proportion;
			 USART_Sentstring(USART1,"Proportion: ");
			 USART_Send_NUM(USART1,sptr->Proportion,3);
			 USART_Sentstring(USART1,"   ");
             USART_Sentstring(USART1,"Integral : ");
			 USART_Send_NUM(USART1,sptr->Integral,3);
			 USART_Sentstring(USART1,"   ");
             USART_Sentstring(USART1,"Derivative : ");
			 USART_Send_NUM(USART1,sptr->Derivative,3);
			 USART_Sentstring(USART1,"   ");

//			 USART_Sentstring(USART1,"Kp_G : ");
//			 USART_Send_NUM(USART1,Kp_G,3);
//			 USART_Sentstring(USART1,"   ");
//             USART_Sentstring(USART1,"Ki_G : ");
//			 USART_Send_NUM(USART1,Ki_G,3);
//			 USART_Sentstring(USART1,"   ");
//             USART_Sentstring(USART1,"Kd_G : ");
//			 USART_Send_NUM(USART1,Kd_G,3);
//			 fanhang(USART1);
//			 USART_Sentstring(USART1,"Pwm1 : ");
//			 USART_Send_NUM(USART1,Pwm1,3);
//			 USART_Sentstring(USART1,"   ");

//			 USART_Sentstring(USART1,"Pwm2 : ");
//			 USART_Send_NUM(USART1,Pwm2,3);
//			 USART_Sentstring(USART1,"   ");

//			 USART_Sentstring(USART1,"QbT : ");
//			 USART_Send_NUM(USART1,Qibai_T,3);
//			 USART_Sentstring(USART1,"   ");
//			 
//			 USART_Sentstring(USART1,"TDt : ");
//			 USART_Send_NUM(USART1,TDt,3);
//			 USART_Sentstring(USART1,"   ");
//			 fanhang(USART1);

//			 USART_Sentstring(USART1,"SAL : ");
//			 USART_Send_NUM(USART1,SAL,3);
//			 USART_Sentstring(USART1,"   ");
//			 
//			 USART_Sentstring(USART1,"SAR : ");
//			 USART_Send_NUM(USART1,SAR,3);
//			 USART_Sentstring(USART1,"   ");
//			 USART_Sentstring(USART1,"DAR : ");
//			 USART_Send_NUM(USART1,DAR,3);
//			 USART_Sentstring(USART1,"   ");
//			 
//			 USART_Sentstring(USART1,"DAL : ");
//			 USART_Send_NUM(USART1,DAL,3);
//			 USART_Sentstring(USART1,"   ");
			 fanhang(USART1);
			 

			 
		 }

//        xianshi((long int)npwmval);
		 
		 if(page==1)
		 {
			 mpu_dmp_get_data(&pitch,&roll,&yaw);   //或得  角度  
			 xianshi(0);
		 
		 }
		 if(page==3||page==4)
		 {
			
		 
    
             
            mpu_dmp_get_data(&pitch,&roll,&yaw);   //获得的  角度
        setroll=(float)t_angle;                 //显示的  与  算法的  交接   改变的目标角度
//               xianshi((long int)npwmval);
          
       
//         if((setroll-(-roll))>=9)
//         { TIM_SetCompare1(TIM1,700);  //为了起速快一些。  这样可以极快的缩短时间   但这样可能会很不稳定
//           xianshi(700);
//         }
//        else
//           {
            
           pwmval=IncPID_Calc(setroll,(-roll)); //  pid该变量
         
           npwmval=npwmval+pwmval;        //累加      
         if(t_angle<50)
         { 		
                if(npwmval>=800)
                npwmval=800;

            if(npwmval<=0)
                  npwmval=0;
   TIM_SetCompare1(TIM1, (long int)npwmval) ;				//PB5 输出pwm      输出100占空比 大概是60度
		}						
         else
         {
                if(npwmval>=999)
                npwmval=999;

            if(npwmval<=0)
                  npwmval=0;
   TIM_SetCompare1(TIM1, (long int)npwmval) ;
         }
      
                     xianshi((long int)npwmval);                
       
      
      //  }
      }          
		 	 if(page==2)
		 {
			 mpu_dmp_get_data(&pitch,&roll,&yaw);   //或得  角度
			 switch(speed)
			 {
			   case 0:
					 	TIM_SetCompare1(TIM1, 0) ; 
				 xianshi(0); break;
				 case 1 : 
				 	TIM_SetCompare1(TIM1, 100) ; 
				 xianshi(100); break;
				 case 2 : 
				 	TIM_SetCompare1(TIM1, 200) ;
				 xianshi(200);  break;
				 case 3 : 
				 	TIM_SetCompare1(TIM1, 300) ; 
				 xianshi(300); break;
				 case 4 : 
				 	TIM_SetCompare1(TIM1, 400) ; 
				 xianshi(400); break;
				 case 5 : 
				 	TIM_SetCompare1(TIM1, 500) ;
				 xianshi(500);  break;
				 case 6 : 
				 	TIM_SetCompare1(TIM1, 600) ; 
				 xianshi(600); break;
				 case 7 : 
				 	TIM_SetCompare1(TIM1, 700) ;
				xianshi(700); 	 break;
				 case 8 : 
				 	TIM_SetCompare1(TIM1, 800) ; 
				xianshi(800); 	break;
				 case 9 : 
				 	TIM_SetCompare1(TIM1, 900) ; 
				xianshi(900); 	break;
				 case 10 : 
				 	TIM_SetCompare1(TIM1, 999) ; 
				xianshi(1000); break;
		 }

        }  
			   		 
                            

	}

	} 

