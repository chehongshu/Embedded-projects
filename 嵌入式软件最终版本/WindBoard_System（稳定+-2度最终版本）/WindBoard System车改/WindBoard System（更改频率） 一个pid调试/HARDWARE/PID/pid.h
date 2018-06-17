#ifndef	__PID_H__
#define __PID_H__
# include "sys.h"
 
 typedef struct PID 
{ 
	long SumError;      //误差累计
	double Proportion;  //比例常数 
	double Integral;    //积分常数 
	double Derivative;  //微分常数 
	double LastError;      //Error[-1] 
	double PrevError;      //Error[-2] 
} PID;

extern  PID sPID; 
extern  PID *sptr;

void leftPid_Init(void); 
double IncPID_Calc(double SetPoint, double actualPoint);
double IncPID_Calc(double SetPoint, double actualPoint) ;
void pidsetKpid(int dat1, int dat2, int dat3);
void baseRun(void);
void promoteRun(void);
//右边电机pid计算
double rightMontorCal(double target, double actual);

#endif
