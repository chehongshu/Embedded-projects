#ifndef __MALLOC_H
#define __MALLOC_H
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌĞòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßĞí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEK MiniSTM32¿ª·¢°å
//ÄÚ´æ¹ÜÀí Çı¶¯´úÂë	   
//ÕıµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//ĞŞ¸ÄÈÕÆÚ:2014/3/12
//°æ±¾£ºV1.0
//°æÈ¨ËùÓĞ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖİÊĞĞÇÒíµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////


 
#ifndef NULL
#define NULL 0
#endif

//ÄÚ´æ²ÎÊıÉè¶¨.
#define MEM_BLOCK_SIZE			2  	  						//ÄÚ´æ¿é´óĞ¡Î2×Ö½Ú
#define MEM_MAX_SIZE			2*1024  						//×î´ó¹ÜÀíÄÚ´æ 2K
#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE 	//ÄÚ´æ±í´óĞ¡
 
		 
//ÄÚ´æ¹ÜÀí¿ØÖÆÆ÷
struct _m_mallco_dev
{
	void (*init)(void);				//³õÊ¼»¯
	u8 (*perused)(void);		  	//ÄÚ´æÊ¹ÓÃÂÊ
	u8 	*membase;					//ÄÚ´æ³Ø 
	u16 *memmap; 					//ÄÚ´æ¹ÜÀí×´Ì¬±í
	u8  memrdy; 					//ÄÚ´æ¹ÜÀíÊÇ·ñ¾ÍĞ÷
};
extern struct _m_mallco_dev mallco_dev;	//ÔÚmallco.cÀïÃæ¶¨Òå

void mymemset(void *s,u8 c,u32 count);	//ÉèÖÃÄÚ´æ
void mymemcpy(void *des,void *src,u32 n);//¸´ÖÆÄÚ´æ     
void mem_init(void);					 //ÄÚ´æ¹ÜÀí³õÊ¼»¯º¯Êı(Íâ/ÄÚ²¿µ÷ÓÃ)
u32 mem_malloc(u32 size);		 		//ÄÚ´æ·ÖÅä(ÄÚ²¿µ÷ÓÃ)
u8 mem_free(u32 offset);		 		//ÄÚ´æÊÍ·Å(ÄÚ²¿µ÷ÓÃ)
u8 mem_perused(void);					//µÃÄÚ´æÊ¹ÓÃÂÊ(Íâ/ÄÚ²¿µ÷ÓÃ) 
////////////////////////////////////////////////////////////////////////////////
//ÓÃ»§µ÷ÓÃº¯Êı
void myfree(void *ptr);  				//ÄÚ´æÊÍ·Å(Íâ²¿µ÷ÓÃ)
void *mymalloc(u32 size);				//ÄÚ´æ·ÖÅä(Íâ²¿µ÷ÓÃ)
void *myrealloc(void *ptr,u32 size);	//ÖØĞÂ·ÖÅäÄÚ´æ(Íâ²¿µ÷ÓÃ)
#endif













