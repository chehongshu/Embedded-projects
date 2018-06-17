# include "PID.h"
# include "pwm.h"
# include "math.h"
# include "usart.h"
# include "12864.h"
# include "led.h"
# include <math.h>

 PID pid1;// 
 PID pid2;// 
 
  //==== 基础部分的
 int err1 = 837; //TIMER3   前面的
 int err2 = 800;	//TIMER4   后面的
 
 //=== 提高部分的
 int err1_promote = 820;
 int err2_promote = 800;
void setErr(int i, int j)
{
	err1_promote = i;
	err2_promote = j;
}
 
extern double targetData;
 
extern double tempData;
double currentPwmData = 0;
double currentPwmData2 = 0;
extern float pitch;
extern 
//左边电机pid初始化
void leftPid_Init(void) 
{ 
	pid1.SumError = 0; 
	pid1.LastError = 0;    
	pid1.PrevError = 0;    
	pid1.Proportion = 0 ; 
	pid1.Integral = 0;
	pid1.Derivative = 0;
	
	pidsetKpid(990,23,7500);      // 990 23 7500 //  基础部分的pid的值
	
}

//pid1参数整定
void pidsetKpid(int dat1, int dat2, int dat3)
{
	pid1.Proportion = ((double)dat1)/100;
	pid1.Integral = ((double)dat2)/10000;
	pid1.Derivative = ((double)dat3)/10;
}


void baseRun(void)
{
//			TIM_SetCompare1(TIM3, err1);
//			TIM_SetCompare1(TIM4, err2);
	
			currentPwmData = IncPID_Calc(targetData, 90-pitch);
			if ( currentPwmData<=0 )
			{
				TIM_SetCompare1(TIM4, err2+(fabs)(currentPwmData));
				TIM_SetCompare1(TIM3, err1);
			}
			else if ( currentPwmData>0 )
			{
				TIM_SetCompare1(TIM3, err1+currentPwmData);
				TIM_SetCompare1(TIM4, err2);
			}
}

//double IncPID_Calc2(double SetPoint, double actualPoint)                                                       
//{ 
//			double Error;
//			double iIncpid;
//			Error = SetPoint - actualPoint;
//			pid2.SumError += Error;
////			   if(pid2.SumError> 40000){
////								pid2.SumError = 40000;
////				}else if(pid2.SumError < -40000)
////				{
////						    pid2.SumError = -40000;
////				}
//			iIncpid = pid2.Proportion*Error + 
//								pid2.Integral*(pid2.SumError) + 
//								pid2.Derivative*(Error-pid2.LastError);
//			pid2.LastError =  Error;
//			return iIncpid; 												
//}


//void promoteRun(void)
//{
////							TIM_SetCompare1(TIM3, err1_promote);
////							TIM_SetCompare1(TIM4, err2_promote);
//	
//	   			currentPwmData  =  IncPID_Calc2(targetData, 90-pitch);
//          
//        	if ( currentPwmData<=0 )
//					{
//						TIM_SetCompare1(TIM4, err2_promote+(fabs)(currentPwmData));
//						TIM_SetCompare1(TIM3, err1_promote);
//					}
//					else if ( currentPwmData>0 )
//					{
//						TIM_SetCompare1(TIM3, err1_promote+currentPwmData);
//						TIM_SetCompare1(TIM4, err2_promote);
//					}
//					
//}

//=== 基础部分的

double IncPID_Calc(double SetPoint, double actualPoint)                                                       
{ 
			double Error;
			double iIncpid;
			Error = SetPoint - actualPoint;
			pid1.SumError += Error;
			   if(pid1.SumError> 40000){
								pid1.SumError = 40000;
				}else if(pid1.SumError < -40000)
				{
						    pid1.SumError = -40000;
				}
			iIncpid = pid1.Proportion*Error + 
								pid1.Integral*(pid1.SumError) + 
								pid1.Derivative*(Error-pid1.LastError);
			pid1.LastError =  Error;
			return iIncpid; 												
}






