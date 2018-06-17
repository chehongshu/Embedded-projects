#ifndef _STEPPERMOTOR_H_
#define _STEPPERMOTOR_H_

#define L_ENA_CAN     GPIO_SetBits(GPIOA,GPIO_Pin_4)       //使能    左 
#define L_ENA_NOT     GPIO_ResetBits(GPIOA,GPIO_Pin_4)     //不使能  左

#define R_ENA_CAN    GPIO_SetBits(GPIOA,GPIO_Pin_6)       //使能    右
#define R_ENA_NOT    GPIO_ResetBits(GPIOA,GPIO_Pin_6)     //不使能  右

#define L_DIR_positive     GPIO_SetBits(GPIOA,GPIO_Pin_5);      //   轮子正向  左  
#define L_DIR_reverse     GPIO_ResetBits(GPIOA,GPIO_Pin_5);    //   轮子反向  左

#define R_DIR_positive    GPIO_SetBits(GPIOA,GPIO_Pin_7);      //   轮子正向   右
#define R_DIR_reverse    GPIO_ResetBits(GPIOA,GPIO_Pin_7);    //   轮子反向   右

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

