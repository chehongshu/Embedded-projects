# ifndef __MOTOR_CONTROL_
# define __MOTOR_CONTROL_
# include "sys.h"
# include "pid.h"

//基础题目1模式
void base1Mode(void);

//基础题目2模式
void base2Mode(void);

//硬件误差校准
int changeData(u8 dat);

//判断是否达到目标值
u8 isTarget(int dat);


# endif

