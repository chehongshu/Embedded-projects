#ifndef _JINBUDIANJI_H_
#define _JINBUDIANJI_H_

#define ENA_Left_H     GPIO_SetBits(GPIOA,GPIO_Pin_4)       //使能    左 
#define ENA_Left_L     GPIO_ResetBits(GPIOA,GPIO_Pin_4)     //不使能  左

#define ENA_Right_H    GPIO_SetBits(GPIOA,GPIO_Pin_6)       //使能    右
#define ENA_Right_L    GPIO_ResetBits(GPIOA,GPIO_Pin_6)     //不使能  右

#define DIR_Left_H     GPIO_SetBits(GPIOA,GPIO_Pin_5);      //   轮子正向  左  
#define DIR_Left_L     GPIO_ResetBits(GPIOA,GPIO_Pin_5);    //   轮子反向  左

#define DIR_Right_H    GPIO_SetBits(GPIOA,GPIO_Pin_7);      //   轮子正向   右
#define DIR_Right_L    GPIO_ResetBits(GPIOA,GPIO_Pin_7);    //   轮子反向   右



void steppermotor_init();

void go_straight();

void stop_motor();

void start_motor();

void  turn_left();

void  turn_right();


#endif