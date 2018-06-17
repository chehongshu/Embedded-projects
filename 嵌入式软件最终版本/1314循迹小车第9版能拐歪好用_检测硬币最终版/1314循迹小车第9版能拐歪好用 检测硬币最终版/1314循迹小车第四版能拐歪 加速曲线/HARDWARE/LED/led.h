#ifndef __LED_H
#define __LED_H	 
#include "sys.h"



#define LED0 PCout(8)	// PC8          ºìµÆ
#define LED1 PCout(9)	// PC9	        »ÆµÆ
#define LED2 PCout(10)	// PC10	        ÂÌµÆ

//    Èý¸ö µÆ   
//    PC8  ºìµÆ  
//    PC9  »ÆµÆ
//    PC10 ÂÌµÆ
//


void LED_Init(void);//³õÊ¼»¯

		 				    
#endif
