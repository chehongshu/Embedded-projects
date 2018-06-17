# include "ST_drive.h"

/*
*********************************************************************************************************
*	函 数 名:     ST_drive_Init
*	功能说明:     st188初始化
*	形    参：    void
*	返 回 值:     void 
*********************************************************************************************************
*/
void ST_drive_Init(void)
{
	
			 GPIO_InitTypeDef  GPIO_InitStructure;
			
			 //使能PB PA端口时钟
			 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);	 
       
			 //PC6 PC7初始化
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;				
     	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 	
			 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
			 GPIO_Init(GPIOC, &GPIO_InitStructure);						

			 //PA7 PA12初始化
			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_12;
			 GPIO_Init(GPIOA, &GPIO_InitStructure);
}


