#ifndef __INFR_RECEI_H
#define __INFR_RECEI_H	 
#include "sys.h"


void  Infr_recei_Init(void);
u16 Get_Adc(u8 ch,int ch_rank)   ;
u16 Get_Adc_Average(u8 ch,u8 times,int rank);
void Get_ADC_ALL(void);


void TIM2_Int_Init(u16 arr,u16 psc);
		 				    
#endif
