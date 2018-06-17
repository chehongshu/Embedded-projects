# ifndef __LED_H
# define __LED_H	 
# include "sys.h"

# define LED0 PCout(8)	// PC8
# define LED1 PCout(9)	// PC9
# define LED2 PCout(10) // PC10


//初始化
void LED_Init(void);

//蜂鸣器初始化
void buzzer_Init(void);

//警告开始(灯亮 蜂鸣器响)
void Warning_Start(void);

//警告停止
void Warning_Stop(void);

#endif
