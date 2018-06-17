#ifndef  _STEPPERMOTOR_H_
#define _STEPPERMOTOR_H_
				/***************** 第一个电机（大方向的转动）57电机*************************/
				/***************** EN->PG8 DIR --> PC6   PWM-->PC9*************************/
#define qianhou_ENA_CAN    GPIO_ResetBits(GPIOG,GPIO_Pin_8)       //使能   
#define qianhou_ENA_NOT     GPIO_SetBits(GPIOG,GPIO_Pin_8)     //不使能  

#define qianhou_DIR_positive     GPIO_SetBits(GPIOC,GPIO_Pin_7);      //   轮子正向    
#define qianhou_DIR_reverse     GPIO_ResetBits(GPIOC,GPIO_Pin_7);    //   轮子反向 

#define qianhou_PWM_H     GPIO_SetBits(GPIOC,GPIO_Pin_9);      //      
#define qianhou_PWM_L     GPIO_ResetBits(GPIOC,GPIO_Pin_9);    //   
			/***************** 第二个电机（左右的移动） 洗头架42*************************/
				/***************** EN->PG2  DIR --> PG4   PWM-->PG6 *************************/
#define zuoyou_ENA_CAN    GPIO_ResetBits(GPIOG,GPIO_Pin_2)       //使能    
#define zuoyou_ENA_NOT    GPIO_SetBits(GPIOG,GPIO_Pin_2)     //不使能  

#define zuoyou_DIR_positive    GPIO_SetBits(GPIOG,GPIO_Pin_4);      //   轮子正向   
#define zuoyou_DIR_reverse    GPIO_ResetBits(GPIOG,GPIO_Pin_4);    //   轮子反向 

#define zuoyou_PWM_H     GPIO_SetBits(GPIOG,GPIO_Pin_6);      //      
#define zuoyou_PWM_L     GPIO_ResetBits(GPIOG,GPIO_Pin_6);    //  
				/***************** 第三个电机（上下的移动） 丝杆滑台*************************/
				/***************** EN->PD4  DIR --> PD2   PWM-->PD0 *************************/
#define shangxia_ENA_CAN    GPIO_ResetBits(GPIOD,GPIO_Pin_4)       //使能    
#define shangxia_ENA_NOT    GPIO_SetBits(GPIOD,GPIO_Pin_4)     //不使能  

#define shangxia_DIR_positive    GPIO_SetBits(GPIOD,GPIO_Pin_2);      //   轮子正向   
#define shangxia_DIR_reverse    GPIO_ResetBits(GPIOD,GPIO_Pin_2);    //   轮子反向 

#define shangxia_PWM_H     GPIO_SetBits(GPIOD,GPIO_Pin_0);      //      
#define shangxia_PWM_L     GPIO_ResetBits(GPIOD,GPIO_Pin_0)    //  



//步进电机初始化
void steppermotor_init(void);

//停止前进
void stop_motor(void);

//开始前进
void start_motor(void);

//改变小车速度
void speed_change(void);

void little_speed(void);

////小车直走
//void go_straight(void);

////左拐弯
//void turn_left(void);

////右拐弯
//void  turn_right(void);


#endif

