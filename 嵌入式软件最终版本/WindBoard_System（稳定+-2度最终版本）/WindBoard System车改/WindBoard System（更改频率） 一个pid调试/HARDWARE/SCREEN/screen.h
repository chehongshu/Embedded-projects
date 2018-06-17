# ifndef __SCREEN_H
# define __SCREEN_H
# include "sys.h"

//显示菜单界面
void showMenu(u8 selectNum);

//显示基础题1和提高题1的角度设置界面
void allQuestion1Set(u8 num);

//显示基础题1和提高题1的开始界面
void allQuestion1Start(u8 queNum);

//基础2/提高2角度设置界面
void allQuestion2Set(u8 numLocate, u8 num);

//基础2/提高2角度开始界面
void allQuestion2Start(u8 num);

//基础2/提高2运行界面
void allQuestion2Running(u8 num);

//基础提高1运行界面
void allQuestion1Runing(u8 num);

//实时显示的数据刷新
void freshData(void);

# endif



