#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "Photoelectric_door.h"
#include "steppermotor.h"
#include "function.h"
#include "timer.h"
#include "sortsOf_ways.h"
#include "Hair_dryer.h"
#include "details_func.h"


extern char reset;     //     改变 当前功能的顺序的作用

u8  HMI_receive; // 接收 信号 0x01
u8 HMI_receive_BUF;
extern u8 Rx; //  接收信号



int i_mian; //  测试
int flagmian;//  测试

int  fflag1=1;


/************************************************
 ALIENTEK战舰STM32   ZET6
***********************************************/
extern int zuozhuan_flag;
extern int youzhuan_flag;

int main(void)
{
			 
							delay_init();	    //延时函数初始化	  
							LED_Init();                              
							KEY_Init();
							steppermotor_init(); 
							LED1_L;
							LED2_L;
	
							//  光电门的初始化 
							zuoyou_PDoor_Init();
							qianhou_PDoor_Init();
							shangxia_PDoor_Init();
	
							HD_zuoyou_PDoor_Init();
              HD_rotating_PDoor_Init();
        
	
								A_hair_dryer_init();
                relay_Init();
								TIM3_Int_Init(9999,71);//1ms     扫描
	
	               TIM4_Int_Init(4999,71);//100ms     scan
							
						  // 初始化 Uart  接收 HMI 发来的数据

							  usart2_init(9600);  //  HMI 的  波特率  为9600  PA2  PA3
	              delay_ms(300);  //  aim to dianya pingwen

	
				while(1)
		  	{

					HMI_receive_BUF = HMI_receive;
								//	0x01  开始  0x02  吹干    0x03 暂停     0x04  停止
					HMI_receive  =  Rx;// 接收HMI 发来的数据

					if(HMI_receive_BUF   !=  HMI_receive )
					{
						   fflag1 = 1;
									 
									qianhou_ENA_NOT;
									zuoyou_ENA_NOT;
									shangxia_ENA_NOT;
								 HD_zuoyou_ENA_NOT;
			           HD_rotating_ENA_NOT; 
						
					}
					/**
					* HMI_receive    
					 0x01   -->  启动  第一种洗头方式
					 0x02   -->  启动 第二种洗头方式
					 0x03   -->    启动第二种洗头方式的 升级版本
					 0x04   -->  急停
  					**/
					switch(HMI_receive)
					{

					
									case 0x01: 
//																				 if(fflag1)
//																					 {
//																																			 clear_flag();    
//																																				fflag1 = 0; 
//																																				reset = 0;
//																																	
//																						 }
																		 switch(reset)
																		 {
																			 
																					 case 0:            Water_spray_func(); break;
																					 case 1:
																																			//  标志位  清零
																																				clear_flag();
																																				 reset = 2;
																																					break;
																					 case 2:       			 Water_spray_func_another();  //  标志位  清零
																																					break;
																					 case 3:        	//  标志位  清零
																																					clear_flag();
																																					 reset = 4;
																																						break;
																					 case 4:      				   ReSet_Location();   break;  
																																											
																					 case 5:         				clear_flag();
																																				reset = 6; 
																																				HD_zuoyou_ENA_NOT;
																																				HD_rotating_ENA_NOT;
																																				 break;
																					 
																					 case 6:      						wish_first_wish_hair();   
																																		 //   wish_another_wish_hair();
																																						break;
																					 
																					 
																					 case 7:       				    clear_flag();
																																					reset = 8; break;
																					 
																					 case 8:        			      function_Hair_Dry();  break;
																			 
																		 }

																		 
																		 
																		 break;
																		 
							case  0x02:   // 吹干
								                           if(fflag1)
																						 {
																														 clear_flag();    
                																						  fflag1 = 0; 
																												      reset = 0;
																						 }
								                           switch(reset)
																	    	 {
																			 
																					 case 0:            Water_spray_func(); break;
																					 case 1:
																																	
																																				clear_flag();
																																				 reset = 2;
																																					break;
																					 case 2:       		//	 Water_spray_func_another();  //  标志位  清零
																						                              reset = 3;
																																					break;
																					 case 3:        	//  标志位  清零
																																					clear_flag();
																																					 reset = 4;
																																						break;
																					 case 4:      				  //           ReSet_Location();
                                       																			reset = 5;			
                                     																					 break;  
																																											
																					 case 5:         			 	clear_flag();
																																				reset = 6; 
																																				HD_zuoyou_ENA_NOT;
																																				HD_rotating_ENA_NOT;
																																				 break;
																					 
																					 case 6:      						//wish_first_wish_hair();   
																																		     // wish_another_wish_hair();
																					                                reset = 7;
																																						break;
																					 
																					 
																					 case 7:       				      clear_flag();
																																					reset = 8; break;
																					 
																					 case 8:        			             relay_L;
																						                                  function_Hair_Dry();  break;
																			 
																		 }
																																	break;
																						 
							case 0x03:                                relay_L;
																																 stop_motor();  //  急停
																																		break;
							
				      case 0x04:         
								                           if(fflag1)
																						 {
																														 clear_flag();   
                                                              relay_L;																							 
                																						  fflag1 = 0; 
																												      reset = 0;
																						 }
								                           switch(reset)
																	    	 {
																			 
																					 case 0:            Water_spray_func(); break;
																					 case 1:
																																	
																																				clear_flag();
																																				 reset = 2;
																																					break;
																					 case 2:       		//	 Water_spray_func_another();  //  标志位  清零
																						                              reset = 3;
																																					break;
																					 case 3:        	//  标志位  清零
																																					clear_flag();
																																					 reset = 4;
																																						break;
																					 case 4:      				reset = 5;
                       																	    //				 ReSet_Location();  
                                 																					 break;  
																																											
																					 case 5:         			 	clear_flag();
																																				reset = 6; 
																																				HD_zuoyou_ENA_NOT;
																																				HD_rotating_ENA_NOT;
																																				 break;
																					 
																					 case 6:      						//wish_first_wish_hair();   
																																		 //   wish_another_wish_hair();
																					                                reset = 7;
																																						break;
																					 
																					 
																					 case 7:       				      clear_flag();
								                                      
																																	             break;
																					 case 8:                   stop_motor();break;
																					 break;

 		                        		}
			}
					
    
////				        wish_another_wish_hair();


//											if(zuozhuan_flag == 1)
//											{
//												zuoyou_go_L(100);
//											}
//											if(youzhuan_flag == 0)
//											{
//												zuoyou_go_R(100);
//											}			
//								
//								
//											// shangxia_closedLoop_scan();
//										 
  							
							
			}
  
				
}
          
