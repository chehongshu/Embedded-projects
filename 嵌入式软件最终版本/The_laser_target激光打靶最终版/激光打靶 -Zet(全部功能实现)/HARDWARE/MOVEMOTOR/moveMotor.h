# ifndef __MOVE_MOTOR
# define __MOVE_MOTOR
# include "sys.h"

//移动初始化
void moveInit(void);

//沿x轴移动
void moveX(u8 dir);

//沿y轴转动
void moveY(u8 dir);


# endif

