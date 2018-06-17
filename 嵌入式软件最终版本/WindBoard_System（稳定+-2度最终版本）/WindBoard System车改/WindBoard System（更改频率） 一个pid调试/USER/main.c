# include "sys.h"
# include "delay.h"
# include "usart.h"
# include "key.h"
# include "led.h"
# include "pwm.h"
# include "timer.h"
# include "beep.h"
# include "sysvalue.h"
# include "screen.h"
# include "12864.h"
# include "pid.h"
# include "mpu6050.h"
# include "mpuiic.h"
# include "usmart.h"
# include "motor_control.h"

//初始化系统状态为菜单选择状态
u8 sysCurrentStyle = SYS_MENU;
//菜单项选中的案例
u8 selectBtn = BASE1;
//设置的目标角度值
u8 targetData1 = 70;
u8 targetData2[2] = {0};
//设定数值时的个十百位选择
u8 numLocate = 1;
//欧拉角
float pitch = 0, roll = 0, yaw = 0; 	

//调试目标角度
double targetData = 60;
extern double currentPwmData;
double kp_temp;
extern u8 USART_RX_BUF[USART_REC_LEN];
int receive; 

void angle_set(u8 sta)
{
	targetData = sta;
}

//完成系统整体的初始化
void InitAll()
{

	//延时函数初始化	 	 
	delay_init();	    
	
  //设置NVIC中断分组2:2位抢占优先级，2位响应优先级	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	
	uart_init(9600);//===    UART 
	
		//====  1. USMART 移植   2.USMART 初始化    3. 改TIMER定时器(USMART中的)  4.注瞮smart_config 
		//====   5. 初始化uart 7. 写函数    8.串口助手直接调用 
	
	usmart_dev.init(72);//===    单片机   的主频  72M  
	
	//按键扫描初始化
	KEY_Init();  
	//LED初始化
	LED_Init();
	//蜂鸣器初始化
	BEEP_Init();
	//定时器中断初始化
	//TIM2_INT_Init(500, 7200);
	//初始化12864
	LCD_Init();
	//mpu6050初始化
	MPU_Init();

	//左右电机pid初始化
	leftPid_Init();
}

 int main(void)
 {
					  //外设初始化
					  InitAll();
					  //角度获取初始化
						while( mpu_dmp_init() )
						{
							delay_ms(200);
							LED1 = !LED1;
							LED2 = !LED2;
							LED3 = !LED3;
							delay_ms(200);
						} 
						
						//pwm输出初始化
						TIM3_PWM_Init(3000 ,0);	//=== 				 3000         0
						TIM4_PWM_Init(3000 ,0);	//=== 				 3000         0
					
						//显示菜单界面，默认选中基础题1
						//showMenu(selectBtn);
			
						delay_ms(1000);
						delay_ms(1000);
						delay_ms(1000);
				while(1)
				{

											mpu_dmp_get_data(&pitch,&roll,&yaw);   //或得角度 	
											kp_temp = 90-pitch;
											//targetData1 = changeData(targetData1);
//											if ( targetData1>=110 && targetData1<=140 )
//											{
//												pidsetKpid(3010, 8, 3900);
//											}
//											else if ( targetData1<110 && targetData1>=45 )
//											{
//												pidsetKpid(700, 8, 4000);
//											}
																base1Mode();
									
											 /*switch ( sysCurrentStyle )
												{
													case SYS_BASE1_RUNING: 
																//targetData1 = changeData(targetData1);
																base1Mode(); break;
													case SYS_BASE2_RUNING:
																base2Mode(); break;
													default: break;
												}*/
					}
 }
 
 
 
 
