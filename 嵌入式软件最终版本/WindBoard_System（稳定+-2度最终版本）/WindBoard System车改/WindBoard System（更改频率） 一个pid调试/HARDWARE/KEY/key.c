# include "key.h"
# include "delay.h"
# include "sysvalue.h"
# include "screen.h"
# include "led.h"

extern u8 sysCurrentStyle;
extern u8 selectBtn;
extern u8 numLocate;
extern u8 targetData1;
extern u8 targetData2[2];
 	    
//按键初始化函数 
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	
} 

//按键扫描
u8 KEY_Scan(void)
{	 
	static u8 key_up = 1;  		  
	if(key_up&&(KEY1==1 || KEY2==1 || KEY3==1 || KEY4==1 || KEY5==1 || KEY6==1))
	{
		delay_ms(10);
		key_up=0;
		if(KEY1==0)
		{
			return KEY1_PRES;
		}
		else if( KEY2==0 )
		{
			return KEY2_PRES;
		}	
		else if( KEY3==0 )
		{
			return KEY3_PRES; 
		}
		else if ( KEY4==0 )
		{
			return 	KEY4_PRES;
		}
		else if ( KEY5==0 )
		{
			return KEY5_PRES;
		}
		else if ( KEY6==0 )
		{
			return KEY6_PRES;
		}
	}else if( KEY1==1 && KEY2==1 && KEY3==1 && KEY4==1 && KEY5==1 && KEY6==1 )
	{
		key_up=1;
	} 	     
	return 0;
}

/************************************
按键1功能实现（-）
************************************/
void KEY1_Fun(void)
{
	LED1 = !LED1;
	LED2 = !LED2;
	LED3 = !LED3;
	//功能代码
	switch ( sysCurrentStyle )
	{
		case SYS_MENU: selectBtn = selectBtn%2+1; showMenu(selectBtn); break;   //在菜单界面按下按键1切换基础题
		case SYS_BASE1_SET: changeTargetDataDown(&targetData1); allQuestion1Set(numLocate); break;	//基础题1设置界面下设置数据减
		case SYS_IMPROVE1_SET: changeTargetDataDown(&targetData1); allQuestion1Set(numLocate); break;	//提高题1设置界面下设置数据减
		case SYS_BASE2_SET1: changeTargetDataDown(&targetData2[0]); allQuestion2Set(numLocate, 0); break;	 //基础题2设置界面下设置数据1减
		case SYS_BASE2_SET2: changeTargetDataDown(&targetData2[1]); allQuestion2Set(numLocate, 1); break;	 //基础题2设置界面下设置数据2减
		case SYS_IMPROVE2_SET1: changeTargetDataDown(&targetData2[0]); allQuestion2Set(numLocate, 0); break;	 //基础题2设置界面下设置数据1减
		case SYS_IMPROVE2_SET2: changeTargetDataDown(&targetData2[1]); allQuestion2Set(numLocate, 1); break;	 //基础题2设置界面下设置数据2减
		default: break;
	}
}

/************************************
按键2功能实现（+）
************************************/
void KEY2_Fun(void)
{
	LED1 = !LED1;
	LED2 = !LED2;
	LED3 = !LED3;
	//功能代码
	switch( sysCurrentStyle )
	{
		case SYS_MENU: selectBtn = selectBtn%2+3; showMenu(selectBtn); break;   //在菜单界面按下按键2切换提高题
		case SYS_BASE1_SET: changeTargetDataUp(&targetData1); allQuestion1Set(numLocate); break;	 //基础题1设置界面下设置数据加
		case SYS_IMPROVE1_SET: changeTargetDataUp(&targetData1); allQuestion1Set(numLocate); break;	 //提高题1设置界面下设置数据加
		case SYS_BASE2_SET1: changeTargetDataUp(&targetData2[0]); allQuestion2Set(numLocate, 0); break;	 //基础题2设置界面下设置数据1加
		case SYS_BASE2_SET2: changeTargetDataUp(&targetData2[1]); allQuestion2Set(numLocate, 1); break;	 //基础题2设置界面下设置数据2加
		case SYS_IMPROVE2_SET1: changeTargetDataUp(&targetData2[0]); allQuestion2Set(numLocate, 0); break;	 //提高题2设置界面下设置数据1加
		case SYS_IMPROVE2_SET2: changeTargetDataUp(&targetData2[1]); allQuestion2Set(numLocate, 1); break;	 //提高题2设置界面下设置数据2加
		default: break;
	}
}

/************************************
按键3功能实现（确认）
*************************************/
void KEY3_Fun(void)
{
	LED1 = !LED1;
	LED2 = !LED2;
	LED3 = !LED3;
	//功能代码
	switch ( sysCurrentStyle )
	{
		case SYS_MENU: MenuSureKey_Fun(); break;  //选着小题号
		case SYS_BASE1_SET:sysCurrentStyle = SYS_BASE1_START; allQuestion1Start(1); break;//基础题1设置完成开始运行
		case SYS_IMPROVE1_SET:sysCurrentStyle = SYS_IMPROVE1_START; allQuestion1Start(2); break;//提高题1设置完成开始运行
		case SYS_BASE2_SET1:sysCurrentStyle = SYS_BASE2_SET2; numLocate=1; allQuestion2Set(numLocate, 1); break;//基础题2参数1设置完成开始设置参数2
		case SYS_BASE2_SET2:sysCurrentStyle = SYS_BASE2_START; allQuestion2Start(1); break; //基础题2参数设置完毕开始运行
		case SYS_IMPROVE2_SET1:sysCurrentStyle =SYS_IMPROVE2_SET2; numLocate=1; allQuestion2Set(numLocate, 1); break;//基础题2参数1设置完成开始设置参数2
		case SYS_IMPROVE2_SET2:sysCurrentStyle = SYS_IMPROVE2_START;allQuestion2Start(2); break; //提高题2参数设置完毕开始运行
		default: break;
	}
}

/************************************
按键4功能实现（设置位选择）
************************************/
void KEY4_Fun(void)
{
	LED1 = !LED1;
	LED2 = !LED2;
	LED3 = !LED3;
	//功能代码
	switch ( sysCurrentStyle )
	{
		case SYS_BASE1_SET: 
		case SYS_IMPROVE1_SET: numLocate = numLocate%3; numLocate++; allQuestion1Set(numLocate); break;
		case SYS_BASE2_SET1: numLocate = numLocate%3; numLocate++; allQuestion2Set(numLocate, 0); break;
		case SYS_BASE2_SET2: numLocate = numLocate%3; numLocate++; allQuestion2Set(numLocate, 1); break;
		case SYS_IMPROVE2_SET1: numLocate = numLocate%3; numLocate++; allQuestion2Set(numLocate, 0); break;
		
		default: break;
	}
}

/************************************
按键5功能实现 （运行）
************************************/
void KEY5_Fun(void)
{
	LED1 = !LED1;
	LED2 = !LED2;
	LED3 = !LED3;
	//功能代码
	switch ( sysCurrentStyle )
	{
		case SYS_BASE1_START: sysCurrentStyle = SYS_BASE1_RUNING; allQuestion1Runing(1); break;
		case SYS_BASE2_START: sysCurrentStyle = SYS_BASE2_RUNING; allQuestion2Running(1); break;
		case SYS_IMPROVE1_START: sysCurrentStyle = SYS_IMPROVE1_RUNING; allQuestion1Runing(2); break;
		case SYS_IMPROVE2_START: sysCurrentStyle = SYS_IMPROVE2_RUNING; allQuestion2Running(2); break;
		default: break;
	}
}

/************************************
按键6功能实现 （结束）（返回主菜单）
*************************************/
void KEY6_Fun(void)
{
	LED1 = !LED1;
	LED2 = !LED2;
	LED3 = !LED3;
	//功能代码
	switch ( sysCurrentStyle )
	{
		case SYS_BASE1_START: 
		case SYS_IMPROVE1_START: 
		case SYS_BASE2_START: 
		case SYS_IMPROVE2_START: 
		case SYS_BASE1_RUNING:
		case SYS_BASE2_RUNING:
		case SYS_IMPROVE1_RUNING:
		case SYS_IMPROVE2_RUNING:
		sysCurrentStyle = SYS_MENU; selectBtn=1; numLocate = 1; showMenu(selectBtn); targetData1=0; targetData2[0] = 0; targetData2[1]=0; TIM_SetCompare1(TIM3,0); TIM_SetCompare1(TIM4,0);break; //各小题运行结束回到菜单界面
		default: break;
	}
}

/**********************************
菜单确认键功能实现
**********************************/
void MenuSureKey_Fun(void)
{
	switch ( selectBtn ) //判断选中的目标
	{
		case BASE1: sysCurrentStyle = SYS_BASE1_SET; allQuestion1Set(numLocate); numLocate = 1; break;
		case BASE2: sysCurrentStyle = SYS_BASE2_SET1; allQuestion2Set(numLocate, 0); break;
		case IMPROVE1: sysCurrentStyle = SYS_IMPROVE1_SET; allQuestion1Set(numLocate); break;
		case IMPROVE2: sysCurrentStyle = SYS_IMPROVE2_SET1; allQuestion2Set(numLocate, 0); break;
		default: break;
	}
}

/************************************
改变目标值函数（加）
*************************************/
void changeTargetDataUp(u8 * data)
{
		if ( 1==numLocate ) //设置百位
		{
			 if ((*data)<80) (*data)+=100;
		}
		else if ( 2==numLocate ) //设置十位
		{
			if ( (1==(*data)/100 && (*data)%100<70 && (*data)%100/10<9) || (0==(*data)/100 && (*data)%100/10<9) )
			{
				*data += 10;
			}
		}
		else if ( 3==numLocate ) //设置各位
		{
			if ( (*data)<180 && ((*data)%10)<9)
			{
				(*data)++;
			}
		}
}

/************************************
改变目标值函数（减）
*************************************/
void changeTargetDataDown(u8 * data)
{
		if ( 1==numLocate ) //设置百位
		{
			 if ((*data)>100) (*data)-=100;
		}
		else if ( 2==numLocate ) //设置十位
		{
			if ( (*data)%100/10>0 )
			{
				*data -= 10;
			}
		}
		else if ( 3==numLocate ) //设置个位
		{
			if ( (*data)%10>0 )
			{
				(*data)--;
			}
		}
}






