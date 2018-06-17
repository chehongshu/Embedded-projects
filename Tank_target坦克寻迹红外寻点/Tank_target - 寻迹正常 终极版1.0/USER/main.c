# include "stm32f10x.h"
# include "delay.h"
# include "sys.h"
# include "pwm.h"
//# include "usart.h"
# include "steppermotor.h"
# include "led.h"
# include "timer.h"
# include "ST_drive.h"

 int main(void)
 {	
	 delay_init();	    	         //延时函数初始化	 
	 
	 steppermotor_init();          //步进电机初始化
	 
	 TIM3CH1_PWM_Init(1000, 25);   // 72000/(899+1) = 80KHz;  左轮
	 TIM1CH4_PWM_Init(1000, 25);   //右轮
	 TIM7_Int_Init(10, 7200-1);    //加速
	 TIM5_Int_Init(10, 7200-1);    //寻迹
	 ST_drive_Init();              //st188初始化        
	 
	 start_motor();                //小车开始跑
	 buzzer_Init();                //蜂鸣器初始化
   LED_Init();                   //LED初始化
   TIM6_Int_Init(5000, 7200);
	 LED0 = 0;
	 while(1)
	 {
		 //Warning();
	 }
		
 }
