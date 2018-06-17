# ifndef __SCREEN_H
# define __SCREEN_H
# include "sys.h"

//得到当前红点的坐标
void getCurrentPoint(void);

//提高题3达到任意环数
void improve3Fun(u8 target);

//提高题2回到10环
void improve2Fun(void);

//提高题1显示功能
void improve1Fun(void);

//提高题1闪烁hongdian
void slightPoint(u8 dat);

//基础题3获得数功能
void base3Fun(void);

//中点坐标校准按钮功能
void centerAdjustFun(void);

//边缘坐标校准按钮功能
void borderAdjustFun(void);

//发送串口指令停止位
void stop(void);

# endif
