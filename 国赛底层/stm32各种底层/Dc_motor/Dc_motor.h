#ifndef __Dc_motor_H
#define __Dc_motor_H	 
#include "sys.h"

 
//  L298N    EN  Ω« 
#define L_EN    PBout(0)    // PB0
#define R_EN   PBout(1)     // PB1

//  Left     IN1   IN2
#define  L_IN_1     PAout(0)
#define  L_IN_2     PAout(1)

//  Right     IN1   IN2
#define  R_IN_1     PAout(2)
#define  R_IN_2     PAout(3)


void motor_Init(void);//IO≥ı ºªØ
void motor_forward(void);
void motor_backward(void);			   		    
#endif
