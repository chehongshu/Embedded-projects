#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

//////**********************       按键   PB13    PB14   PB15 

/////***********************            蜂鸣器   PC12

void KEY_Init(void) //    按键  的  io     初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//IO口使能

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//   S1   S2   S3  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA0,8


}
void buzzer_Init() //   蜂鸣器       初始化
{    
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //IO口使能

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //PB.12 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC.8
        
    GPIO_ResetBits(GPIOC,GPIO_Pin_12);						 //PB.12 输出低

}

    
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY1按下
//2，KEY2按下
//3，KEY3按下 
//4，KEY4按下 
//注意此函数有响应优先级,KEY1>KEY2>KEY3>KEY4!!
 u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(S13==0||S14==0||S15==0) )
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(S13==0)return KEY13_PRES;
		else if(S14==0)return KEY14_PRES;
		else if(S15==0)return KEY15_PRES;
		
	}else if(S13==1&&S14==1&&S15==1)key_up=1; 	    
 	return 0;// 无按键按下
}


