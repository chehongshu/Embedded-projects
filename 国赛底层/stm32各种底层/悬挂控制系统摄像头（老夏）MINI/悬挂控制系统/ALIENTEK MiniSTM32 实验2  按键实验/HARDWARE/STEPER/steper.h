#ifndef __STEPER_H
#define __STEPER_H
#include "sys.h" 

//¶Ë¿Ú¶¨Òå
#define DIR0 	PAout(5)
#define DIR1 	PAout(6)
#define STEP0 	PAout(7)
#define STEP1 	PAout(8)

extern s32 aC,bC;

void steperInit(void);
void aZheng(void);
void aFu(void);
void bZheng(void);
void bFu(void);

#endif
