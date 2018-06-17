#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "JLX_12864.h"
#include "pwm.h"
#include "myiic.h" 
#include "LDC1314.h"
#include "steppermotor.h"
#include "function.h"
#include "key.h"
#include "exti.h"

//  1 初始值  之后减去  初始值
//  2  拐歪    歪到     里面去

char a[10]="now time"; 
char b[10]="distance";
char c[10]="speed";

u32 second;   //秒
double distance;  // 走的距离
double speed;    //  走的速度

int zhongduanbiaozhi;

u32  pulseamount_Left ;   //左轮脉冲的数目
u32  pulseamount_Right ;  //右轮脉冲的数目

s32 passageway1;
s32 passageway2;
s32 passageway3;
s32 passageway4;

s32 passageway1_init;
s32 passageway2_init;
s32 passageway3_init;
s32 passageway4_init;

s32 different_value1;//  三通道   和   二通道的  差值

s32 different_value2;  //  四通道  和 一通道的 差值

s32 buzhi1;
s32 buzhi2;

u16 duty_left=2000;

u16 duty_right=2000;

u16 set_duty_left=1000;
u16 set_duty_right=1000;

int pwm_left;
int pwm_right;


extern int i;

int flag=0;


int  moshi=1;


int main(void)
{	
    /***************************初始化部分*****************************************/
    
    
	delay_init();	    	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // 设置中断优先级分组2
	LED_Init();		  	        //初始化与LED连接的硬件接口
    
    
    KEY_Init(); 
                              EXTIX_Init();
    buzzer_Init();             //   蜂鸣器  初始化  
  
     /// pwm初始化
    TIM4_PWM_Init(duty_left,36);    //最终到1k         从 2000到1000   1ms  进一次中断 加50   进20次  停止 
    TIM2_PWM_Init(duty_right,36 );    //最终到1k    duty_right
         
    TIM5_Int_Init(1000,72);    //1ms  扫描一次     加速曲线
     //  12864  
    LCD12864_init();
     //  LDC1314  的
    IIC_Init();
    LDC1314_MultiInit();
    steppermotor_init();
    
     stop_motor();//    先停止  
     
//     TIM_SetCompare1(TIM4,0); //       左轮
//     TIM_SetCompare2(TIM2,0);  //      右轮
    
      delay_ms(1500) ;  //   延时
     
   
           ///定时器中断
           
	TIM3_Int_Init(10000,7200); //1s 进一次中断
    
   
    
   
    
    
         passageway2_init=LDC_Read_Reg(0X02);    // 二通道 读数    
         passageway3_init=LDC_Read_Reg(0X04);    //三通道 读数
         passageway1_init=LDC_Read_Reg(0X00);    // 一通道 读数    
         passageway4_init=LDC_Read_Reg(0X06);    //四通道 读数
         buzhi1 = passageway3_init  - passageway2_init;   //
         buzhi2 =  passageway4_init - passageway1_init;    //
   	while(1)
{  
	
	/*
         J12864_led_double1(1,20,passageway1,1); 
         J12864_led_double1(2,20,passageway2,1); 
         
         J12864_led_double1(1,60,passageway3,1); 
         J12864_led_double1(2,60,passageway4,1); 
        
        
        
        
        
                                    passageway2=LDC_Read_Reg(0X02);    // 二通道 读数    
                                    passageway3=LDC_Read_Reg(0X04);    //三通道 读数
                                    
                                    different_value1= passageway3-passageway2-buzhi1 ;
                                    
                                    passageway1=LDC_Read_Reg(0X00);    // 一通道 读数    
                                    passageway4=LDC_Read_Reg(0X06);    //四通道 读数
                                    
                                    different_value2= passageway4-passageway1-buzhi2;
        
      
        start_motor();          //  开始了    
                  if(flag==0)
                  {
								
                   pwm_left=500;   
                   pwm_right=500;   
                TIM_SetCompare1(TIM4, pwm_left);  //       左轮
                TIM_SetCompare2(TIM2, pwm_right);  //      右轮
                   
                  }
         Display();
        
        
         J12864_led_double1(6,20,different_value1,1);  //   中间的
         J12864_led_double1(7,20,different_value2,1);   //  两边的
                  
                  
              ///////        距离和时间
         distance= Through_distance( pulseamount_Left,pulseamount_Right ); 
      
          speed=gain_speed( second , distance ) ;
                  
           
         GPIO_ResetBits(GPIOC,GPIO_Pin_12);	
            LED1=0;       
           

          if (moshi==1)   
          { 
              
              search_path1( passageway1, passageway2, passageway3, passageway4);
                

              if(second>=33)
              {
                  stop_motor();
                  
                  LED1=1;
                GPIO_SetBits(GPIOC,GPIO_Pin_12);
                    pwm_left=0;   
                   pwm_right=0;  
                TIM_SetCompare1(TIM4,pwm_left);  //       左轮
                TIM_SetCompare2(TIM2,pwm_right);  //      右轮   
                     flag   =  1;                   
              }                  

              
           }                  
          if(moshi==2)
            search_path2( passageway1, passageway2, passageway3, passageway4);    
             */  
	}
}

