#include "steper.h"
#include "movexy.h"
#include "math.h"
#include "usart.h"

void moveTo(double xT,double yT)
{
	double a2=(xT+8.0)*(xT+8.0)+(79.2-yT)*(79.2-yT);
	double b2=(80.3-xT)*(80.3-xT)+(79.2-yT)*(79.2-yT);
	double a=sqrt(a2);
	double b=sqrt(b2);
	//printf("%lf,%lf\r\n",a,b);
	aT=(int)(a*stepnum);
	bT=(int)(b*stepnum);
	//printf("%d,%d\r\n",aT,bT);
	aE=aT-aC;
	bE=bT-bC;
	//printf("%d,%d\r\n",aE,bE);
	while((aE!=0)||(bE!=0))
	{
		if(aE>0)
		{
			aZheng();
		}
		else if(aE<0)
		{
			aFu();
		}
		if(bE>0)
		{
			bZheng();
		}
		else if(bE<0)
		{
			bFu();
		}
		aE=aT-aC;
		bE=bT-bC;		
	}
}

double upRand(double xT, double x0, double y0, double RandR)
{
	double tmpY,yT;
	tmpY = RandR*RandR - (xT-x0)*(xT-x0);
	yT = sqrt(tmpY) + y0;
	return yT;
}

double downRand(double xT, double x0, double y0, double RandR)
{
	double tmpY,yT;
	tmpY = RandR*RandR - (xT-x0)*(xT-x0);
	yT = -sqrt(tmpY) + y0;
	return yT;
}

void DrawRand(double x0, double y0, double RandR)
{
	double xT,yT;
	for(xT = x0 - RandR; xT <= x0 + RandR; xT += 0.05)	//ÉÏ°ëÔ°
	{
		yT = upRand(xT,x0,y0,RandR);
		moveTo(xT,yT);
	}
	for(xT = x0 + RandR; xT >= x0 - RandR; xT -= 0.05)	//ÏÂ°ëÔ²
	{
		yT = downRand(xT,x0,y0,RandR);
		moveTo(xT,yT);
	}
}
