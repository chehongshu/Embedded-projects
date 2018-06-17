#ifndef __MOVEXY_H
#define __MOVEXY_H
#include "sys.h" 

extern s32 aC,bC;
extern s32 aT,bT; //目标AB坐标
extern double stepnum;  // 脉冲数
extern s32 aE,bE; //AB坐标位移矢量

void moveTo(double xT,double yT);
double upRand(double xT, double x0, double y0, double RandR);
double downRand(double xT, double x0, double y0, double RandR);
void DrawRand(double x0, double y0, double RandR);
#endif
