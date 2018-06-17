#include "sortsOf_ways.h"
#include "steppermotor.h"
#include "Photoelectric_door.h"
#include "function.h"
#include "delay.h"
#include "details_func.h"
#include "Hair_dryer.h"

/************标志位 定义区**************************/
 // main function

int     step_number=3000;// 一次 走的 步数     (left or right)                       *需要更改*
int     step_min = 4000;  ///  最小角度步数                             *需要更改*
int     step_max=46000; //  最大角度步数                              *需要更改*

int   	 step_number_sum = 0;// 走的总步数
// main func
char   reset = 0; //  change function


//       FLAG
int  second_qianhou_flag = 0;  //   control behind or  forward dirction
char  second_xiang_flag = 0;  //  control    left or right direction

char  second       =  0;    //
char  reset_flag   =  0;   //
//   dry hair flag
extern int Water_spray_flag ;
extern int quit_flag ;
extern int hair_dry_flag;

//  another     function   Flag
int qianxiang_flag;
int zuozhuan_flag;
int youzhuan_flag;
int change_direction_flag = 0;
 /*******************************************
*   标志位清零   to 0
******************************************/
void  clear_flag()
{
										//main	
									 reset_flag = 0;
	
										//  dry
									 quit_flag  = 0;
									 Water_spray_flag = 0;
									 hair_dry_flag = 0 ;
	
										//Flag  main 
										second_qianhou_flag = 0;
										second_xiang_flag = 0;
										second = 0;
										
										//Flag  another
                  	qianxiang_flag = 0;
										zuozhuan_flag = 0; 
										youzhuan_flag = 0;
	                change_direction_flag = 0;

}
/*******************************************
*
*      恢复到原位      一直  扫描
******************************************/

int reset_i;
void ReSet_Location()
{
	
								//  首先判断是  否在  复位位置  在复位位置则 不动   直接 进入下一个操作
								if(  reset_flag ==1 )
								{
											//  刚好 在原来位置不需要动
											// 向前动一点
														 //  往前走一点
																																for( reset_i=0;reset_i<qianhou_walkMount;reset_i++)
																																	{
																																						qianhou_go_Q(qianhou_delay);		
																																	 }
																																
																																 	 for(reset_i=0;reset_i<10000;reset_i++) 
																																			{
																																									HD_zuoyou_go_R(100);
																																								if(HD_zuoyou_PDoor_R == 1)
																																								{
																																												break;
																																								}
																																			 }
																																	 for(reset_i=0;reset_i<200;reset_i++) 
																																			{
																																									HD_zuoyou_go_L(100);
																																						
																																			 }
																															for(reset_i = 0;reset_i<30000;reset_i++)
																																	{
																																			 
																																				HD_rotating_go_L(100);
																																			 
																																				 if(HD_rotating_PDoor == 1){
																																					 
																																						 break;
																																			 }
																																	}
																																for(reset_i = 0;reset_i<3000;reset_i++)
																																	{
																																			 
																																				HD_rotating_go_R(100);
																																			 
																																	
																																	}
																																reset = 5;
																					   qianhou_ENA_NOT;	zuoyou_ENA_NOT;shangxia_ENA_NOT;
																																		
																																		 
													}else{
																																				//  不在   一个位置
																																				qianhou_go_H(qianhou_delay);
																																				//   一直到等于1时结束
													
																	}
				
			

}
/*******************************************
*
*    记步旋转
******************************************/
int step_rotating_number = 12000; //  步骤 旋转的步数               *需要更改*  

//  for
int step_rotating_j1;
int step_rotating_j2;
int k2;
int i3;
int i4;

void step_rotating(void)
{
	
												for( step_rotating_j1= 0; step_rotating_j1<step_rotating_number;step_rotating_j1++)
												{
																 //  向前
																 qianhou_go_Q(qianhou_delay);
													       relay_H;
												}		
												delay_ms(1000);
												delay_ms(500);
												for(step_rotating_j2= 0; step_rotating_j2<step_rotating_number;step_rotating_j2++)
												{
																	 // 向 后
																	 qianhou_go_H(qianhou_delay);
													          relay_H;
												}		
								
}	
/*******************************************
*  闭环来回旋转
******************************************/
void closedLoop_rotation(void)
{
	                       relay_H;
												if( second_qianhou_flag  ==  0) 
												{
																		// 向  前
																	qianhou_go_Q(qianhou_delay);
												}else if(second_qianhou_flag == 1)
												{	
																		// 向  后
																	qianhou_go_H(qianhou_delay);
												}else if(second_qianhou_flag == 2)
												{
																	for(k2=0;k2<500;k2++)
																	{						
																			// 向  前
																				qianhou_go_Q(qianhou_delay);
																	}
																	
																	second = 1;//  回到  turn left or right 
																	second_qianhou_flag = 0;//  clear flag
					
												}
}

int flag_1 = 1; //  一个开环控制
int flag_2 = 1; //  一个开环控制
/*******************************************
*   main function
******************************************/
//  main洗头方式
void wish_first_wish_hair()
{
	                relay_H;
		 /*
	    *       1.   分两层
			*       2.   先转到 最左面 把最左面当做原点   
			*			  3.    往右转一点（有个范围是以平角转的）
			*				4.    在中间为 全部转  闭环
		  */
	                                
											 // 一直向  左转  碰到光电门之后  当做原点 
											if( second ==  0 )  
											{
																zuoyou_go_R(50);		
												
											}else if( second == 1 )
											{
														 
																	if(flag_1 ==1){
																																	// run  left
																																	for( i3=0;i3<step_number;i3++)
																																	{
																																				zuoyou_go_L(zuoyou_delay); 
																																	}
																																	flag_1=0;
																												}
																	
																													if(second_xiang_flag == 2)
																													{
																																// run  left
																																	for( i3=0;i3<step_number;i3++)
																																	{
																																			zuoyou_go_L(zuoyou_delay); 
																																	}
																																	step_number_sum  +=  step_number;
																																	
																													}else if(second_xiang_flag  == 1)
																													{
																																		// run  right
																																			for(i4=0;i4<step_number;i4++)
																																		{
																																				zuoyou_go_R(zuoyou_delay); 
																																		}
																																			step_number_sum  -=  step_number;
																																		
																																		 if(step_number_sum  <  2000 )  //   少于多少之后  返回之后  停止
																																		 {
																																					flag_2 = 0;
																																		 }
																														 
																									}
																									 if(flag_2 == 1)
																									 {
																													 second = 2;
																									 }else if(flag_2 ==0)
																									 {
																													 second  = 3;
																									 }
											}else if(second  == 2)
											{
																					if( step_number_sum  <  step_min )
																					{
																								step_rotating();			//  记步 旋转
																								second = 1;
																					}else if(step_number_sum >step_max)
																					{
																								step_rotating();			//    记步旋转
																								second = 1;
																					}else if((step_number_sum >= step_min)&&(step_number_sum <= step_max))
																					{
																								closedLoop_rotation();			//  闭环旋转
																					}		
																		
												}else if(second == 3)
												{
																		stop_motor();
																		reset = 7;    // Go   Hair_Dry  
												}

}
/*******************************************
*   another function
******************************************/
int wish_another_i;//for
// second _flag  Flag


int qianhou_flag;

int qianhou_walkMount_step_sum;
int qianhou_walkMount_step_sum_max;
void wish_another_wish_hair()
{
				
			if(  change_direction_flag  ==  0  ) 
			{
								
													 if(  qianxiang_flag == 0  ){
													
																															
																														 for( wish_another_i=0;wish_another_i<qianhou_walkMount;wish_another_i++)
																															{
																																			qianhou_go_Q(qianhou_delay);		
																															}												
																															
																																				qianxiang_flag=1;  
																												 
																 }else if(qianxiang_flag == 1)
																	{
												
																															 if(zuozhuan_flag==1){
																																						
																																							zuoyou_go_L(zuoyou_delay);
																																}	 
																															 if(zuozhuan_flag==2)
																															 {
																																				for(wish_another_i=0;wish_another_i<zuozhuan_walkMount ;wish_another_i++)
																																					{
																																								zuoyou_go_L(zuoyou_delay);
																																					}
																																					
																																					delay_ms(1000) ;
																																					qianxiang_flag = 0;
																																					zuozhuan_flag = 0; 
																																					youzhuan_flag = 0;
																																				
																															 }
																															 if(youzhuan_flag==0)
																															 {
																																	    zuoyou_go_R(zuoyou_delay);
																																}
																				
																				}
																	
																				
															    		qianhou_walkMount_step_sum += qianhou_walkMount;
																				if(qianhou_walkMount_step_sum>qianhou_walkMount_step_sum_max)
																				{
																					   change_direction_flag =1;
																				}
																				
									}else if(change_direction_flag==1)
					      {
																			 if(qianxiang_flag == 0){
																				 
																													for(wish_another_i=0;wish_another_i< qianhou_walkMount ;wish_another_i++)
																													{
																																		qianhou_go_H(qianhou_delay);		
																													}							
																																	  qianxiang_flag = 1;
																															 
																				 }else if(qianxiang_flag == 1)
																				 {
																													 if(zuozhuan_flag==1)
																														 {
																															    		zuoyou_go_L(zuoyou_delay);
																														}	 
																													 if(zuozhuan_flag==2)
																													 {
																																	for(wish_another_i=0;wish_another_i<zuozhuan_walkMount;wish_another_i++)
																																	{
																																	 					zuoyou_go_L(zuoyou_delay);
																															  		}
																																			
																																					delay_ms(100);						
																																			    qianxiang_flag = 0;
																																					youzhuan_flag = 0;  
																																					zuozhuan_flag = 0;
																																			   
																														}
																													  
																													 if(youzhuan_flag==0)
																													 {
																																	zuoyou_go_R(zuoyou_delay);
																													 }
										}
									
									}	else if(change_direction_flag==2)
								 {      
																		 stop_motor();
																				reset = 7;
									}
	
}