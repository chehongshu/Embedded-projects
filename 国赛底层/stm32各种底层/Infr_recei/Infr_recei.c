#include "Infr_recei.h"
#include "sys.h"
#include "delay.h"
#include "blue_tooth.h"

////红外接收器的初始化和  得到的ad值
/************************************************
////  粗调
/ ①左边的io为 PA5			   ADC第5通道   ②右边的PA0   ADC 第0通道
 ③后面的io为    PA4   ADC第4通道
 ④前 左1（偏向外侧 的）   PC2      ADC第12通道 ⑤  前左2  （偏向中心的） PC1     ADC第11通道
 ⑥前 右1（偏向外侧 的）   PB0      ADC第8通道  ⑦   前右2  （偏向中心的）  PC0    ADC第10通道
 ⑧中心与激光重合的io为    PC4      ADC第14通道
 
 /////微调
 ⑨左 PC5 为 ADC第15通道   （10）. 右PC3 为 ADC第13通道
 
/
**********************************************/
int CH_ALLL[]={5,0,4,12,11,8,10,14,15,13};
double  voltage[10];
       u16  adcx;

/*
*********************************************************************************************************
*	函 数 名:       void  Infr_recei_three_Init(void)    
*	功能说明:            对  adc1 的十个通道初始化
*	形    参：    										void
*	返 回 值:                			  void
*********************************************************************************************************
*/

		   
//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3																	   
void  Infr_recei_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_4|GPIO_Pin_5;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 10;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}		
/*
*********************************************************************************************************
*	函 数 名:       u16 Get_Adc(u8 ch,int ch_rank)   
*	功能说明:            获得ADC值
*	形    参：    						   ch   通道   ch_rank   被调用的顺序
*	返 回 值:                   ADC 的数字值
*********************************************************************************************************
*/

u16 Get_Adc(u8 ch,int ch_rank)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, ch_rank, ADC_SampleTime_1Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}
/*
*********************************************************************************************************
*	函 数 名:             u16 Get_Adc_Average(u8 ch,u8 times,int rank)
*	功能说明:                 求出 某个通道的平均值
*	形    参：    						   ch   通道   times   次数  rank   被调用的顺序
*	返 回 值:                   ADC 的平均值  更加准确
*********************************************************************************************************
*/
u16 Get_Adc_Average(u8 ch,u8 times,int rank)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch,rank);
		delay_ms(5);
	}
	return temp_val/times;
} 
/*
*********************************************************************************************************
*	函 数 名:                 void Get_ADC_ALL(void )
*	功能说明:                 求出 十个通道的  ADC的电压转换值
*	形    参：    						  void
*	返 回 值:                   全局变量   voltage[i]各个ADC转换的ADC的值
*********************************************************************************************************
*/
void Get_ADC_ALL(void )
{
	
	int i=0;
	for(i=0;i<10;i++){
				adcx=Get_Adc_Average(CH_ALLL[i],5,1);// 平均值
				voltage[i]=(double)adcx*(3.3/4096);	//  电压
	}
}
void Get_ADCZ(void)
{
				adcx=Get_Adc_Average(CH_ALLL[7],5,1);// 平均值
				voltage[7]=(double)adcx*(3.3/4096);	//  电压
}
///在  定时器不断地扫描
//// 得到这几个AD值


void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

	
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM2, TIM_IT_Update ,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 

	
	TIM_Cmd(TIM2, ENABLE); 	 
}
extern int j;
void TIM2_IRQHandler(void)   
{	
			if ( RESET!=TIM_GetITStatus(TIM2, TIM_IT_Update) )
			{
										Get_ADCZ();
										Blue_tooth_number(USART2,voltage[7]);
										Blue_tooth_number(USART2,j); 
				
								TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  
				
		}
}



