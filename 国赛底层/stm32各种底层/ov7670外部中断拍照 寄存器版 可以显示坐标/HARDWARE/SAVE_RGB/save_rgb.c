#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "lcd.h" 
#include "sccb.h" 
#include "ov7670.h"
#include "exti.h"
#include "flash.h"
#include "spi.h"
#include "save_rgb.h"
#include "malloc.h"  
#include "MMC_SD.h" 
#include "ff.h"  
#include "fattester.h"  
#include "exfuns.h"
#include "delay.h"	

//extern u16 RGB_565[19200];
static u8 path_name[20] = "0:/DATA/bmp_";
u8 num_1 = '0', num_2  = '0' , num_3 = '0';
extern u8 ov_sta;
static u32 RGB_k = 1;

void change_path()
{
	u8 t = 0;
	num_1 ++;
	if(num_1 > '9')
	{
		num_1 ='0';
		num_2 ++;
	}
	if(num_2 > '9')
	{
		num_2 ='0';
		num_3 ++;
	}
	if(num_3 > '9')
	{
		num_3 ='0';
		num_2 ='0';
		num_1 ='0';
	}
	path_name[12] = num_3;
	path_name[13] = num_2;
	path_name[14] = num_1;
	path_name[15] = '.';
	path_name[16] = 'b';
	path_name[17] = 'm';	
	path_name[18] = 'p';
	path_name[19] = '\0';
	
	printf("check path:");
	for(t = 0 ; t < 20 ; t ++)
	{
		printf("%c" , path_name[t]);
	}
	printf("\n");
}

void u32_to_4u8(u32 the_32 , u8 the_4u8[4])
{
	u8 t = 0;
	
	lcddev.width=240;
	lcddev.height=320; 
	lcddev.dir = 1;
	LCD_Scan_Dir(R2L_U2D);			//从上到下,从左到右 
	LCD_SetCursor(0x00,0x0000);	//设置光标位置 
	LCD_WriteRAM_Prepare();     //开始写入GRAM	
	
	for(t = 0 ; t < 4 ; t ++)
	{
		the_4u8[t] = 0;
	}
	
	if(the_32 & 0xFF000000)
	{ 
		//printf("3\n");
		delay_ms(100);
		the_4u8[3] = (u8)((the_32 & 0xFF000000) >> 24);
	} 
	if(the_32 & 0x00FF0000)
	{
		//printf("2\n");
		delay_ms(100);
		the_4u8[2] = (u8)((the_32 & 0x00FF0000) >> 16);
	}
	if(the_32 & 0x0000FF00)
	{
		//printf("1\n");
		delay_ms(100);
		the_4u8[1] = (u8)((the_32 & 0x0000FF00) >> 8);
	}
	if(the_32 & 0x000000FF)
	{
		//printf("0\n");
		delay_ms(100);
		the_4u8[0] = (u8)(the_32 & 0x000000FF) ;
	}
	//printf("inter = %d ,%x , %x  , %x  , %x\n" , the_32 , the_4u8[0] , the_4u8[1] , the_4u8[2] , the_4u8[3]);
	delay_ms(200);
	
}

u8 save_to_sdcard()
{
	u8 i = 0 , red , green , blue;
	u32 bp = 0 , j = 0 , k = 0;
	u8 bmp_head[54] , tempflag = 0;
	u8 bsize[4] , wide[4] , high[4] , csize[4];
	u8 flag_save = 1;
	u16 color = 0;
	FIL  newfile;	
	u8 t=0 , res = 0;		
	
	u8 buffer[10];
	for(t = 0 ; t < 10 ; t ++)
	{
		buffer[t] = '1' + t;
	}
	
	if(tempflag == 0)
	{
		bmp_head[0] = 'B';
		bmp_head[1] = 'M';
		
		u32_to_4u8(RGB_SIZE , bsize);
		for(i = 0 ; i < 4 ; i ++)
		{
			bmp_head[i + 2] = bsize[i];
		}		
		for(i = 0 ; i < 4 ; i ++)
		{
			bmp_head[i + 6] = 0;
		}		
		bmp_head[0x0A] = 0x36;
		for(i = 1 ; i < 4 ; i ++)
		{
			bmp_head[i + 0x0A] = 0;
		}	
		
		bmp_head[0x0E] = 0x28;
		for(i = 1 ; i < 4 ; i ++)
		{
			bmp_head[i + 0x0E] = 0;
		}	
		
		u32_to_4u8(RGB_WIDTH , wide);
		for(i = 0 ; i < 4 ; i ++)
		{
			bmp_head[i + 0x12] = wide[i];
		}		
		u32_to_4u8(RGB_HIGH , high);
		for(i = 0 ; i < 4 ; i ++)
		{
			bmp_head[i + 0x16] = high[i];
		}		
		
		bmp_head[0x1A] = 1;
		bmp_head[0x1B] = 0;
		bmp_head[0x1C] = 24;
		bmp_head[0x1D] = 0;
		bmp_head[0x1E] = 0;
		for(i = 1 ; i < 4 ; i ++)
		{
			bmp_head[i + 0x1E] = 0;
		}
		
		u32_to_4u8(RGB_SIZE - 54 , csize);
		for(i = 0 ; i < 4 ; i ++)
		{
			bmp_head[i + 0x22] = csize[i];
		}	
		for(i = 0 ; i < 16 ; i ++)
		{
			bmp_head[i + 0x26] = 0;
		}
	}
	/*
	for(t = 0 ; t < 4 ; t ++)
	{
		printf("%x , %x  , %x  , %x\n" , bsize[t] , wide[t] , high[t] , csize[t]);
		delay_ms(200);
	}
	
	*/
	//for(i = 0 ; i < 54 ; i ++)printf("i = %d , %d \n", i , bmp_head[i]);
	
	
	LCD_Scan_Dir(DFT_SCAN_DIR);	//恢复默认扫描方向 	
	
	while(SD_Initialize())
	{
		LCD_ShowString(60,150,200,16,16,"SD Card Error!");
		delay_ms(200);
		LCD_Fill(60,150,240,150+16,WHITE);//清除显示			  
		delay_ms(200);
	}
	if(SD_Initialize() == 0)
	{
		LCD_ShowString(60,150,200,16,16,"SD Card OK!");
	}
	
	exfuns_init();		//为fatfs相关变量申请内存		
	mem_init();			//初始化内存池	
	f_mount(fs[0],"0:",1); 					//挂载SD卡  	
	
	while(flag_save)
	{
		if(ov_sta == 2)
		{
			flag_save = 0;
			
			f_mkdir("0:DATA");
			change_path();
			while(!(res = f_open(&newfile,path_name,FA_READ)))
			{
				//printf("FA_READ res is %d \n" , res );
				delay_ms(50);
				change_path();
				f_close(&newfile);
			}
			res = f_open(&newfile,path_name,FA_OPEN_ALWAYS | FA_WRITE);
			//printf("res = %d \n" , res);
			f_lseek(&newfile,0);
			f_write(&newfile,bmp_head,sizeof(bmp_head) , & bp);	
			
			OV7670_CS=0;	 
			OV7670_RRST=0;				//开始复位读指针 
			OV7670_RCK=0;
			OV7670_RCK=1;
			OV7670_RCK=0;		
			OV7670_RRST=1;				//复位读指针结束 
			OV7670_RCK=1; 
					
			//delay_ms(3);	
			//pixels();
			
			f_lseek(&newfile,54);
			
			for(k = 0 ; k < 4 ; k ++)
			{
				GPIOB->CRL&=0X00000000;//IO状态设置
				GPIOB->CRL|=0X88888888;//IO状态设置
				GPIOB->ODR|=0X00FF;//IO状态设置
				
			
				for(i = 0 ; i < 120 ; i ++)
				{
					for(j = 0 ; j < 160 ; j ++)
					{
						color = 0;
						OV7670_RCK=0;           
						color= OV7670_DATA;   
						OV7670_RCK=1; 		
						color<<=8;
						OV7670_RCK=0;        
						color|= (OV7670_DATA);        
						OV7670_RCK=1;
						red = (u8)((color & 0xF800) >> 8);
						green = (u8)((color & 0x07E0) >> 3);
						blue = (u8)((color & 0x001F) << 3);
						
						f_write(&newfile,&blue,1 , & bp);
						f_write(&newfile,&green,1 , & bp);
						f_write(&newfile,&red,1 , & bp);
						
					}
				}
			}
		f_close(&newfile);
		printf("saved\n");
		LCD_ShowString(30,150,200,16,16,"SAVE OK!");
			delay_ms(1000);
		GPIOB->CRL=0X33333333; //PB0-7  上拉输出
		GPIOB->CRH=0X33333333; //PB8-15 上拉输出
		GPIOB->ODR=0XFFFF;    //全部输出高
		}
	}
	
	
	
	return 0;
}


