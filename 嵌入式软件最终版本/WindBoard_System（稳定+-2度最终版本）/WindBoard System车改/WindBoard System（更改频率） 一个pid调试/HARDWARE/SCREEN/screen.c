# include "screen.h"
# include "12864.h"
# include "sysvalue.h"

extern u8 targetData1;
extern u8 targetData2[2];
extern u8 numLocate;

extern float pitch;
extern double currentPwmData;
extern double currentPwmData2;

//显示菜单选择界面
void showMenu(u8 selectNum)
{
	LCD_Clear_Screen();          //清屏
	LCD_HZS(1, 25, (u8*)"012345");  //风板控制系统
	LCD_HZS(4, 20, (u8*)"67");        
	LCD_ASCALL('1'); 									//基础1
	LCD_HZS(4, 80, (u8*)"67");        
	LCD_ASCALL('2');									//基础2
	LCD_HZS(7, 20, (u8*)"89");        
	LCD_ASCALL('1');  								//提高1
	LCD_HZS(7, 80, (u8*)"89");        
	LCD_ASCALL('2'); 									//提高2
	
	switch ( selectNum )
	{
		case BASE1: LCD_HZS_OP(4, 20, (u8*)"67"); LCD_ASCALL_OP('1'); break;
		case BASE2: LCD_HZS_OP(4, 80, (u8*)"67"); LCD_ASCALL_OP('2'); break;
		case IMPROVE1: LCD_HZS_OP(7, 20, (u8*)"89"); LCD_ASCALL_OP('1'); break;
		case IMPROVE2: LCD_HZS_OP(7, 80, (u8*)"89"); LCD_ASCALL_OP('2'); break;
		default: break;
	}
}

//显示基础题1和提高题1的角度设置界面
void allQuestion1Set(u8 numLocate)
{
	LCD_Clear_Screen();          //清屏
	LCD_HZS(1, 35, (u8*)":;<=");  //角度设置
	LCD_Add_XY(5, 50);
	LCD_int(targetData1/100);
	LCD_int(targetData1%100/10);
	LCD_int(targetData1%10);
	switch (numLocate)
	{
		case 1:	LCD_Clear_Line(4); LCD_Add_XY(4, 50); LCD_ASCALL('!');break;
		case 2:	LCD_Clear_Line(4); LCD_Add_XY(4, 55); LCD_ASCALL('!');break;
		case 3: LCD_Clear_Line(4); LCD_Add_XY(4, 60); LCD_ASCALL('!');break;
		default: break;
	}
}

//显示基础题1和提高题1的开始界面
void allQuestion1Start(u8 queNum)
{
	LCD_Clear_Screen();          //清屏
	if ( 1==queNum )
	{
		LCD_HZS(2, 35, (u8*)"67");  //基础
	}
	else if (2==queNum )
	{
		LCD_HZS(2, 35, (u8*)"89");  //提高
	}
	LCD_Add_XY(2, 62);
	LCD_int(1);
	LCD_HZS(2, 70, (u8*)">?");  //开始
	LCD_Add_XY(5, 35);
	LCD_ASCALLS((u8 *)"TARGET DATA");
	LCD_Add_XY(7, 50);
	LCD_int(targetData1);
}

//基础2/提高2角度设置界面
void allQuestion2Set(u8 numLocate, u8 num)
{
	LCD_Clear_Screen();          //清屏
	LCD_HZS(1, 35, (u8*)":;<=");  //角度设置
	LCD_Add_XY(1, 100);
	LCD_int(num+1);
	LCD_Add_XY(5, 50);
	LCD_int(targetData2[num]/100);
	LCD_int(targetData2[num]%100/10);
	LCD_int(targetData2[num]%10);
	switch (numLocate)
	{
		case 1:	LCD_Clear_Line(4); LCD_Add_XY(4, 50); LCD_ASCALL('!');break;
		case 2:	LCD_Clear_Line(4); LCD_Add_XY(4, 55); LCD_ASCALL('!');break;
		case 3: LCD_Clear_Line(4); LCD_Add_XY(4, 60); LCD_ASCALL('!');break;
		default: break;
	}
}

//基础2/提高2角度开始界面
void allQuestion2Start(u8 num)
{
	LCD_Clear_Screen();          //清屏
	if ( 1==num )
	{
		LCD_HZS(2, 35, (u8*)"67");  //基础
	}
	else if ( 2==num )
	{
		LCD_HZS(2, 35, (u8*)"89");  //提高
	}
	LCD_Add_XY(2, 62);
	LCD_int(2);
	LCD_HZS(2, 70, (u8*)">?");  //开始
	LCD_Add_XY(5, 15);
	LCD_ASCALLS((u8 *)"  DATA1     DATA2");
	LCD_Add_XY(7, 35);
	LCD_int(targetData2[0]);
	LCD_Add_XY(7, 90);
	LCD_int(targetData2[1]);
}

//基础提高1运行界面
void allQuestion1Runing(u8 num)
{
	LCD_Clear_Screen();          //清屏
	if ( 1==num )
	{
		LCD_HZS(2, 35, (u8*)"67");  //基础
	}
	else if (2==num )
	{
		LCD_HZS(2, 35, (u8*)"89");  //提高
	}
	LCD_Add_XY(2, 62);
	LCD_int(1);
	LCD_Add_XY(2, 70);
	LCD_ASCALLS((u8 *)"RUNNING");

	LCD_Add_XY(5, 35);
	LCD_ASCALLS((u8 *)"TARGET DATA");
	LCD_Add_XY(7, 50);
	LCD_int(targetData1);
}

//基础2/提高2运行界面
void allQuestion2Running(u8 num)
{
	LCD_Clear_Screen();          //清屏
	if ( 1==num )
	{
		LCD_HZS(1, 35, (u8*)"67");  //基础
	}
	else if ( 2==num )
	{
		LCD_HZS(1, 35, (u8*)"89");  //提高
	}
	LCD_Add_XY(1, 70);
	LCD_ASCALLS((u8 *)"RUNNING");
	LCD_Add_XY(1, 62);
	LCD_int(2);
	LCD_Add_XY(5, 15);
	LCD_ASCALLS((u8 *)"  DATA1     DATA2");
	LCD_Add_XY(7, 35);
	LCD_int(targetData2[0]);
	LCD_Add_XY(7, 90);
	LCD_int(targetData2[1]);
}

//实时显示数据刷新
void freshData(void)
{
	//显示实时角度
	LCD_Clear_Line(3);
	LCD_Add_XY(3, 50);
	LCD_int(90-pitch);
	
	//显示实时占空比 左边电机
		LCD_Clear_Line(4);
		LCD_Add_XY(4, 25);
		LCD_int(currentPwmData);
	
  //显示实时占空比 右边电机
		LCD_Add_XY(4, 65);
		LCD_int(currentPwmData2);
		
}


