#include "led.h"

//   三个灯   
//  PC8 红灯  
//  PC9 黄灯
// PC10  绿灯
//
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PC端口时钟
    
    
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PC.8 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC.8
 GPIO_ResetBits(GPIOC,GPIO_Pin_8);						 //PC.8 输出低

    
    
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	    		 //LED1-->PC.9 端口配置, 推挽输出
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_ResetBits(GPIOC,GPIO_Pin_9);                               //PC.9 输出低 
    

    
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //LED2-->PC.10 端口配置, 推挽输出
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_ResetBits(GPIOC,GPIO_Pin_10); 						 //PC.10 输出低 
}
 
