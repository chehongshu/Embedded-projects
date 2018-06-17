#ifndef __PID_H
#define __PID_H	 

#define P_DATA 2
#define I_DATA 0
#define D_DATA 0

typedef struct PID
{
	int SetPoint;	//设定目标 Desired Value
	long SumError;  //误差累计
	double Proportion; //比例常数 Proportional Const
	double Integral; //积分常数 Integral Const
	double Derivative; //微分常数 Derivative Const
	int LastError; //Error[-1]     
	int PrevError; //Error[-2]
}PID;
PID x；
PID* spt=&x； 

void PIDInit1(PID *sptr,int setpoint);
int LocPIDCalc(PID *sptr,int NextPoint);

#endif
