# include "motor_control.h"
# include "screen.h"
# include "led.h"
# include "sysvalue.h"
# include "beep.h"

extern float pitch;
extern u8 targetData1;
extern u8 sysCurrentStyle;
//调试目标角度
extern double targetData;

//基础题目1模式
void base1Mode(void)
{
					static int cnt = 0;  //计时5s
					static int flag = 0; //是否到达目标值标志位
					static int flag2 = 0;  //结束是否到达终点标志位
					baseRun();//=== 基础算法
	      //  promoteRun();//=== 提高算法
					freshData();//=== 刷12864
					
//					if ( 0==flag )
//					{
//						flag = isTarget(targetData1);
//					}
//					else if ( 1==flag )  //到达目标点发出声光报警
//					{
//								cnt++;
//								LED1 = !LED1;
//								LED2 = !LED2;
//								LED3 = !LED2;
//								BEEP = 1;
//									if ( cnt>=1300 )  //大致计时一段时间
//									{
//												//targetData1 = 150;  //目标值设为150使风板停在终点
//												TIM_SetCompare1(TIM4, 0);
//												cnt = 0;
//												flag2 = 1;  
//									}
//					}
//					
//					if ( 1==flag2 )
//					{
//						if ( (90-pitch)>120 )
//						{
//							//停止风机转动
//							TIM_SetCompare1(TIM3, 0);
//							TIM_SetCompare1(TIM4, 0);
//							sysCurrentStyle = SYS_MENU;  //结束返回菜单界面
//							flag = 0;
//							flag2 = 0;
//							BEEP = 0;
//						}
//					}
}

//基础题目2
void base2Mode(void)
{
	baseRun();
	freshData();
	
	//if ( (90-pitch)>)
}

//判断是否达到目标值
u8 isTarget(int dat)
{
	static int cnt = 1;
	int sum = 0;
	static float data[5] = {0};
  u8 i = 0;
	cnt ++;
	if ( 0==cnt%200 )
	{
		sum = 0;
		cnt = 0;
		
		//获取最近5次的数据
		for (i=0; i<4; i++)
		{
			data[i] = data[i+1];
		}
		data[i] = 90-pitch;
		
		//求和
		for (i=0; i<5; i++)
		{
			sum += data[i];
		}
		
		//如果数据平均值在上下5度范围内则表示到达目标点
		if ( (sum/5)>=dat-5 && (sum/5)<dat+5)
		{
			return 1;
		}
	}
	return 0;
}

//硬件误差校准
int changeData(u8 dat)
{
	if ( dat<=60 && dat>45 )   //输入的目标数据在40-60之间
	{
		return dat-5;
	}
	else if ( dat>60 && dat<=80 )
	{
		return dat;
	}
	else if ( dat>=100 && dat<105 )
	{
		return dat;
	}
	
	return 0;  //数据错误返回0
}


