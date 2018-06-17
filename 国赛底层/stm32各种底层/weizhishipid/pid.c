#include "pid.h"   
 //  位置式pid
  
void PIDInit1(PID *sptr,int setpoint) 
{  
	sptr->SumError = 0; 
	sptr->LastError = 0; //Error[-1]  
	sptr->PrevError = 0; //Error[-2]
	
	 
	sptr->Proportion = P_DATA; //比例常数 Proportional Const  
	sptr->Integral = I_DATA ;//积分常数Integral Const  
	sptr->Derivative = D_DATA; //微分常数 Derivative Const  

	sptr->SetPoint = setpoint;
}

int LocPIDCalc(PID *sptr,int NextPoint)
{   
	int iError,dError;
	iError = sptr->SetPoint - NextPoint; //偏差
	sptr->SumError += iError;   //积分
	/*if(sptr->Integral * sptr->SumError>300)
	{
		sptr->SumError=(int)(300.0/sptr->Integral);
	}
	if(sptr->Integral * sptr->SumError<-300)
	{
		sptr->SumError=(int)(-300.0/sptr->Integral);
	}*/

	dError = iError - sptr->LastError; //微分
	sptr->LastError = iError;
	return((int)(sptr->Proportion * iError) //比例项		
		+ (int)(sptr->Integral * sptr->SumError) //积分项 
		+ (int)(sptr->Derivative * dError)); //微分项 
} 
