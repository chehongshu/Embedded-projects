#ifndef __SORTSOF_WAYS_H
#define __SORTSOF_WAYS_H	 
#include "sys.h"
/**
*   各种总体的功能
*   功能的汇总
*   anchor ： chehongshu
*   date ： 2017/5/13
**/


/**
*     上下    左右    前后的    io翻转的 延时   ， 
*      影响自定义   io   翻转的占空比
*/
#define     shangxia_dalay    100

#define     qianhou_delay       200

#define     zuoyou_delay        200

/*
*     定义步数
*     需要调试
*/

#define   qianhou_walkMount      3000     //  向后向前一小步的部步数
#define   zuozhuan_walkMount      55000   //   向左 回到中间的步数
#define   shangxia_walkMount     70000    //  向上向下的步骤



 /*******************************************
*   标志位清零
******************************************/
void  clear_flag(void);


/*******************************************
*
*      恢复到原位
******************************************/
void ReSet_Location(void);
 /*******************************************
*      吹干头发
*       用两个电机  配合 相应的 运动  吹风
******************************************/
void Dry_Hair(void);



void wish_first_wish_hair(void);

void wish_another_wish_hair(void);


#endif
