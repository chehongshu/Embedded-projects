#include "steper.h" 
#include "delay.h"

void steperInit(void)
{
	RCC->APB2ENR|=1<<2;
	GPIOA->CRL&=0X000FFFFF;
	GPIOA->CRL|=0X33300000;
	GPIOA->CRH&=0XFFFFFFF0;
	GPIOA->CRH|=0X00000003;
	STEP0 = 0;
	STEP1 = 0;	
}

void aZheng(void)
{
	DIR0=0;
	STEP0=0;
	delay_ms(1);
	STEP0=1;
	delay_ms(1);
	aC++;
}

void aFu(void)
{
	DIR0=1;
	STEP0=0;
	delay_ms(1);
	STEP0=1;
	delay_ms(1);
	aC--;
}

void bZheng(void)
{
	DIR1=1;
	STEP1=0;
	delay_ms(1);
	STEP1=1;
	delay_ms(1);
	bC++;
}
void bFu(void)
{
	DIR1=0;
	STEP1=0;
	delay_ms(1);
	STEP1=1;
	delay_ms(1);
	bC--;
}

