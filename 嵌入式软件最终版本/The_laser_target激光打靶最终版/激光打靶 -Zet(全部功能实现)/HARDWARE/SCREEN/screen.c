# include "screen.h"
# include "sysvalue.h"
# include "usart.h"
# include "led.h"
# include "math.h"
# include "moveMotor.h"
# include "delay.h"

//串口返回的数据
extern int uartReceiveData;
//得到激光点的XY坐标
extern void getXY(int * x, int * y);
//用于校准的中心点和边缘点
extern int adjustPoint[2][2];
//当前红点的坐标
int currentPoint[2] = {0}; 
//临时存放闪烁红点的坐标
int tempSlightPoint[2] = {0};
 //中心的和边缘点的距离
double adjustPointDis = 0;
//当前点和中点的距离
double currentDisToPoint = 0;
//激光源发光时间计时标志位
int cntFlag = 0;

//提高题3达到任意环数
void improve3Fun(u8 target)
{
	int i=0;
	int currentDisX = 0;
	int currentDisY = 0;
	
	//计算摄像头捕获到的中心点和边缘点在屏幕上的距离
	adjustPointDis = sqrt( (double)adjustPoint[1][0]*(double)adjustPoint[1][0] + (double)adjustPoint[1][1]*(double)adjustPoint[1][1]);
	
	//计算当前点和所需到达目标环数的x，y方向距离
	switch ( target)
	{
		case 4: currentDisX = currentPoint[0]; currentDisY = (int)(currentPoint[1]- ( (adjustPointDis/7.0)*7- (adjustPointDis/16.0))); break;
		case 5: currentDisX = currentPoint[0]; currentDisY = (int)(currentPoint[1]- ( (adjustPointDis/7.0)*6- (adjustPointDis/16.0))); break;
		case 6: currentDisX = currentPoint[0]; currentDisY = (int)(currentPoint[1]- ( (adjustPointDis/7.0)*5- (adjustPointDis/16.0))); break;
		case 7: currentDisX = currentPoint[0]; currentDisY = (int)(currentPoint[1]- ( (adjustPointDis/7.0)*4- (adjustPointDis/16.0))); break;
		case 8: currentDisX = currentPoint[0]; currentDisY = (int)(currentPoint[1]- ( (adjustPointDis/7.0)*3- (adjustPointDis/16.0))); break;
		case 9: currentDisX = currentPoint[0]; currentDisY = (int)(currentPoint[1]- ( (adjustPointDis/7.0)*2- (adjustPointDis/16.0))); break;
		default: break;
	}
	
	//x坐标复位
	if (currentDisX<0)
	{
		for (i=0; i<(int)(1.75*(double)(fabs)(currentDisX)); i++)
		{
			moveX(0);
		}
	}
	else if ( currentDisX>0 )
	{
		for (i=0; i<(int)(1.75*(double)(currentDisX)); i++)
		{
			moveX(1);
		}
	} 
	
	//y坐标复位
	if ( currentDisY<0 )
	{
		for (i=0; i<(int)(0.85*(double)(fabs)(currentDisY)); i++)
		{
			moveY(1);
		}
	}
	else if ( currentDisY>0 )
	{
		for (i=0; i<(int)(0.85*(double)(currentDisY)); i++)
		{
			moveY(0);
		}
	}
	
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	cntFlag = 1;
	uartReceiveData = 0;
}
	
//提高题2回到10环
void improve2Fun(void)
{
	int i=0;
	
	//x坐标复位
	if (currentPoint[0]<0)
	{
		for (i=0; i<(int)(1.75*(double)(fabs)(currentPoint[0])); i++)
		{
			moveX(0);
			//delay_ms(10);
		}
	}
	else if ( currentPoint[0]>0 )
	{
		for (i=0; i<(int)(1.75*(double)(currentPoint[0])); i++)
		{
			moveX(1);
		}
	} 
	
	//y坐标复位
	if (currentPoint[1]<0)
	{
		for (i=0; i<(int)(0.85*(double)(fabs)(currentPoint[1])); i++)
		{
			moveY(1);
		}
	}
	else if ( currentPoint[1]>0 )
	{
		for (i=0; i<(int)(0.85*(double)(currentPoint[1])); i++)
		{
			moveY(0);
		}
	}
	
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	cntFlag = 1;
	uartReceiveData = 0;
}

//得到当前红点的坐标
void getCurrentPoint(void)
{
	//得到坐标
	getXY(&currentPoint[0], &currentPoint[1]);
	
	//将屏幕坐标转换为以中心为原点的坐标值
	currentPoint[0] = currentPoint[0] - adjustPoint[0][0];
	currentPoint[1] = adjustPoint[0][1] - currentPoint[1];
	
	printf("t2.txt=\"%d,%d\"", currentPoint[0], currentPoint[1]); stop(); 
	printf("t2.txt=\"%d,%d\"", currentPoint[0], currentPoint[1]); stop(); 
	printf("t2.txt=\"%d,%d\"", currentPoint[0], currentPoint[1]); stop(); 
	
	uartReceiveData=0;
}

//提高题1显示功能
void improve1Fun(void)
{
	
	//获取当前红点的坐标
	getXY(&currentPoint[0], &currentPoint[1]); 
	
	//将屏幕坐标转换为以中心为原点的坐标值
	currentPoint[0] = currentPoint[0] - adjustPoint[0][0];
	currentPoint[1] = adjustPoint[0][1] - currentPoint[1];
	
	//计算显示在串口屏幕上的坐标
	currentPoint[0] = (int)(169+( (double)94*(double)currentPoint[0] ) / (double)adjustPointDis);
	currentPoint[1] = (int)(102-( (double)94*(double)currentPoint[1] ) / (double)adjustPointDis);
	
	tempSlightPoint[0] = currentPoint[0];
	tempSlightPoint[1] = currentPoint[1];
	
	//清屏
		printf("page improve1");
		stop();
		printf("page improve1");
		stop();
	
	//在串口屏上显示红点
	printf("pic %d,%d,9", tempSlightPoint[0], tempSlightPoint[1]); stop();
	printf("pic %d,%d,9", tempSlightPoint[0], tempSlightPoint[1]); stop();
	printf("pic %d,%d,9", tempSlightPoint[0], tempSlightPoint[1]); stop();
	
	uartReceiveData = 0;
}

//提高题1闪烁hongdian
void slightPoint(u8 dat)
{
	if (dat==1)
	{
		printf("page improve1");
		stop();
		printf("page improve1");
		stop();
		printf("page improve1");
		stop();
	}
	else if (dat==2)
	{
		//在串口屏上显示红点
		printf("pic %d,%d,9", currentPoint[0], currentPoint[1]); stop();
		printf("pic %d,%d,9", currentPoint[0], currentPoint[1]); stop();
		printf("pic %d,%d,9", currentPoint[0], currentPoint[1]); stop();
	}
	
	uartReceiveData = 0;
}

//基础题3获得数功能
void base3Fun(void)
{
	double currentPointDis = 0;  //当前点和中心点的距离
	double ratioOfCurrAdj = 0;   //中心点和当前点的距离 ：中心点和边缘的的距离
	int currentRing = 0;         //当前的环数
	char direction[10][8] = {"中心", "正上", "正下", "正左", "正右", "左上", "左下", "右上", "右下", "脱靶"};
	u8 dirDat = 0;  //9个方向的数据
	
	//获取当前红点的坐标
	getXY(&currentPoint[0], &currentPoint[1]); 
	
	//将屏幕坐标转换为以中心为原点的坐标值
	currentPoint[0] = currentPoint[0] - adjustPoint[0][0];
	currentPoint[1] = adjustPoint[0][1] - currentPoint[1];
	
	//计算摄像头捕获到的中心点和边缘点在屏幕上的距离
	adjustPointDis = sqrt( (double)adjustPoint[1][0]*(double)adjustPoint[1][0] + (double)adjustPoint[1][1]*(double)adjustPoint[1][1]);
	
	//计算中心点和当前点的距离
	currentPointDis = sqrt( (double)currentPoint[0]*(double)currentPoint[0] + (double)currentPoint[1]*(double)currentPoint[1]);
	
	//计算当前点的环数
	ratioOfCurrAdj = currentPointDis/adjustPointDis;
	
	if ( ratioOfCurrAdj<=0.143 )
	{
		currentRing = 10;
	}
	else if ( ratioOfCurrAdj>0.143 && ratioOfCurrAdj<=0.286 )
	{
		currentRing = 9;
	}
	else if ( ratioOfCurrAdj>0.286 && ratioOfCurrAdj<=0.429 )
	{
		currentRing = 8;
	}
	else if ( ratioOfCurrAdj>0.429 && ratioOfCurrAdj<=0.572 )
	{
		currentRing = 7;
	}
	else if ( ratioOfCurrAdj>0.572 && ratioOfCurrAdj<=0.715 )
	{
		currentRing = 6;
	}
	else if ( ratioOfCurrAdj>0.715 && ratioOfCurrAdj<=0.857 )
	{
		currentRing = 5;
	}
	else if ( ratioOfCurrAdj>0.857 && ratioOfCurrAdj<=1 )
	{
		currentRing = 4;
	}
	else   //脱靶
	{
		currentRing = 0;
		dirDat = 9;
	}
	
	//如果没有脱靶，判断方位
	if ( currentRing!=0 )
	{
			if ( fabs(currentPoint[0])<5 && fabs(currentPoint[1])<5 )
			{
				dirDat = 0;  //中心点
			}
			else if ( fabs(currentPoint[0])<5 && currentPoint[1]>0 )
			{
				dirDat = 1;  //正上
			}
			else if ( fabs(currentPoint[0])<5 && currentPoint[1]<0 )
			{
				dirDat = 2;  //正下
			}
			else if ( fabs(currentPoint[1])<7 && currentPoint[0]>0 )
			{
				dirDat = 4;  //正右
			}
			else if ( fabs(currentPoint[1])<7 && currentPoint[0]<0 )
			{
				dirDat = 3;  //正左
			}
			else if ( currentPoint[0]>0 && currentPoint[1]>0 )
			{
				dirDat = 7;  //右上
			}
			else if ( currentPoint[0]<0 && currentPoint[1]>0 )
			{
				dirDat = 5;  //左上
			}
			else if ( currentPoint[0]<0 && currentPoint[1]<0 )
			{
				dirDat = 6;  //左下
			}
			else if ( currentPoint[0]>0 && currentPoint[1]<0 )
			{
				dirDat = 8;  //右下
			}
	}
	printf("t2.txt=\"%d\"", currentRing); stop();
	printf("t2.txt=\"%d\"", currentRing); stop();
	printf("t2.txt=\"%d\"", currentRing); stop();
	printf("t4.txt=\"%s\"", direction[dirDat]); stop();
	printf("t4.txt=\"%s\"", direction[dirDat]); stop();
	printf("t4.txt=\"%s\"", direction[dirDat]); stop();
	
	uartReceiveData = 0; 
}

//中点坐标校准按钮功能
void centerAdjustFun(void)
{
		getXY(&adjustPoint[0][0], &adjustPoint[0][1]); 
		LED1 = !LED1; 
		printf("t3.txt=\"%d,%d\"",adjustPoint[0][0], adjustPoint[0][1]); stop(); 
		getXY(&adjustPoint[0][0], &adjustPoint[0][1]); 
		printf("t3.txt=\"%d,%d\"",adjustPoint[0][0], adjustPoint[0][1]); stop(); 
		getXY(&adjustPoint[0][0], &adjustPoint[0][1]); 
		printf("t3.txt=\"%d,%d\"",adjustPoint[0][0], adjustPoint[0][1]); stop(); 
		getXY(&adjustPoint[0][0], &adjustPoint[0][1]); 
		printf("t3.txt=\"%d,%d\"",adjustPoint[0][0], adjustPoint[0][1]); stop();
		uartReceiveData = 0; 
}

//边缘坐标校准按钮功能
void borderAdjustFun(void)
{
		//得到红点在屏幕上的坐标
		getXY(&adjustPoint[1][0], &adjustPoint[1][1]); 
	
		//将屏幕坐标转换为以中心为原点的坐标值
		adjustPoint[1][0] = adjustPoint[1][0] - adjustPoint[0][0];
	  adjustPoint[1][1] = adjustPoint[0][1] - adjustPoint[1][1];
		
		printf("t4.txt=\"%d,%d\"",adjustPoint[1][0], adjustPoint[1][1]); stop(); 
		printf("t4.txt=\"%d,%d\"",adjustPoint[1][0], adjustPoint[1][1]); stop(); 
		printf("t4.txt=\"%d,%d\"",adjustPoint[1][0], adjustPoint[1][1]); stop(); 
		printf("t4.txt=\"%d,%d\"",adjustPoint[1][0], adjustPoint[1][1]); stop(); 
		uartReceiveData = 0;
	
}

//发送串口指令停止位
void stop(void)		       
{		 
	 u8 i;
	 printf("9");
	 for(i=0;i<3;i++)
	 {
			USART_SendData(USART1,0xff);  //发送一个字节
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//等待发送结束
	 } 
} 
