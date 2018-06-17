/***********************************************************
*                                                          *
* Copyright: (C), 2014, HDU-LISIA STA  rights reserved.    *
*                                                          *                                                          
* File name: PID.h                                         *
*                                                          *
* Author: GJane                                            *
*                                                          *
* Version: 1.0                                             *
*                                                          *
* Creation date: 2014/4/5                               	 *
*                                                          *
* Description:                                             *
*                                                          *
*                                                          *
*                                                          *
* Modification History:                                    *
*                                                          *
* <Modifier>      <Date>     <version>     <Modifications> *
*                                                          *
*                                                          *
*                                                          *
*                                                          *
***********************************************************/   

/**
 *  \file  PID.h
 *
 *  \brief
 */

#ifndef	__PID_H__
#define __PID_H__
 
 /*----------------------------------------------------------------------------
 *        结构体定义区
 *----------------------------------------------------------------------------*/
 typedef struct PID 
{ 
	long SumError;      //误差累计
	double Proportion;  //比例常数 
	double Integral;    //积分常数 
	double Derivative;  //微分常数 
	double LastError;      //Error[-1] 
	double PrevError;      //Error[-2] 
} PID;

 /*----------------------------------------------------------------------------
 *        变量声明区
 *----------------------------------------------------------------------------*/
extern  PID sPID; 
extern  PID *sptr;

 /*----------------------------------------------------------------------------
 *        函数声明区
 *----------------------------------------------------------------------------*/
void IncPID_Init(void); 
double IncPID_Calc(double SetPoint, double NextPoint);

#endif
