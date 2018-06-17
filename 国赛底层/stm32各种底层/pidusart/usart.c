#include "usart.h"
#include "PID.h"
u8 USART_RX_BUF[USART_REC_LEN]={'\0'};//接收缓冲
u16 USART_RX_STA=0;            //接收状态标记
/***************************
函数名：usart_init(u32 bound)
功能：初始化UART1
返回值：无
****************************/
void usart2_init(u32 bound)
{
	  GPIO_InitTypeDef GPIO;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	  
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟  zhuying 
 	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	  USART_DeInit(USART2);  //复位串口1
	  
	  GPIO.GPIO_Pin=GPIO_Pin_2;
	  GPIO.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出 参考 《中文参考手册 V10》 P110 的表格“ 8.1.11 外设的 GPIO 配置”，
      GPIO.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO);
	
	  GPIO.GPIO_Pin=GPIO_Pin_3;
	  GPIO.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入 参考 《中文参考手册 V10》 P110 的表格“ 8.1.11 外设的 GPIO 配置”，
      GPIO.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO);
	
	   //Usart1 NVIC 配置 中断优先级 
      NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//通道
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	  NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	  //NVIC_Configuration();
	  
	  //配置参数
	  USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	  USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

      USART_Init(USART2, &USART_InitStructure); //初始化串口//初始化UART1
	  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//使能中断 接收中断 接收标志RXNE
	  USART_Cmd(USART2, ENABLE);                    //使能串口 
}
void usart_init(u32 bound)
{
	  GPIO_InitTypeDef GPIO;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	  
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟  zhuying 
 	  USART_DeInit(USART1);  //复位串口1
	  
	  GPIO.GPIO_Pin=GPIO_Pin_9;
	  GPIO.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出 参考 《中文参考手册 V10》 P110 的表格“ 8.1.11 外设的 GPIO 配置”，
      GPIO.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO);
	
	  GPIO.GPIO_Pin=GPIO_Pin_10;
	  GPIO.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入 参考 《中文参考手册 V10》 P110 的表格“ 8.1.11 外设的 GPIO 配置”，
      GPIO.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO);
	
	   //Usart1 NVIC 配置 中断优先级 
      NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//通道
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	  NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	  //NVIC_Configuration();
	  
	  //配置参数
	  USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	  USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

      USART_Init(USART1, &USART_InitStructure); //初始化串口//初始化UART1
	  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能中断 接收中断 接收标志RXNE
	  USART_Cmd(USART1, ENABLE);                    //使能串口 
}
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数
void _ttywrch(int ch)  
 { 
     while((USART1->SR&0X40)==0);//循环发送,直到发送完毕    
     USART1->DR = (u8) ch;  
 }
 
struct __FILE 
{ 
	int handle; 

};

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
/************************
发送给上位机的串口工具
多字节接收 不需要 开头和结尾标记
********************/

/*********************************
函数名：fanhang()
功能： 实现换行
返回值：无
**********************************/
void fanhang(USART_TypeDef* USART_x)
{
	char *m="\r\n";
	while(*m!='\0')
 {
  USART_SendData(USART_x, *m);
  while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE) == RESET){}////等待发送结
  m++;
 } 
}
/****************************
函数名：
功能：
返回值：
*****************************/
/****************************
函数名：void USART_SentChar(USART_TypeDef* USART_x,char data)
功能：发送字符
返回值：无
*****************************/
void USART_SentChar(USART_TypeDef* USART_x,char data)
{
  USART_SendData(USART_x, data);
  while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE) == RESET){}////等待发送结
}
/****************************
函数名：USART_Sentstring(char *str)
功能：发送一个字符串
返回值：无
******************************/

void USART_Sentstring(USART_TypeDef* USART_x,char *str)
{
 while(*str!='\0')
 {
  USART_SendData(USART_x, *str);
  while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE) == RESET){}////等待发送结
  str++;
 }
 //fanhang();//根据实际情况再合适的地方加上换行
 
}
/****************************
函数名：void USART_Sentstring_1(char *str,int n)
功能：发送一个字符串
用于 发送数字  专用
返回值：无
******************************/

void USART_Sentstring_1(USART_TypeDef* USART_x,char *str,int n)
{
	int flag=0;
 while(*str!='\0')
 {
	 if(*str=='.')
	 { flag=1;
	   n+=1;
	 }
    if(flag)
    { if(n==0)
	 break;
	 n--;
     }	  
  USART_SendData(USART_x, *str);
  while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE) == RESET){}////等待发送结
  str++;
  
 }
 //fanhang(USART_x);//根据实际情况再合适的地方加上换行
 
}
	
/*******************************
函数名:USART_Sendnumber(double m)
功能：发送一个double型数字
返回值：无
********************************/
void USART_Sendnumber(USART_TypeDef* USART_x,double m)
{  char p[100]={'\0'};
   sprintf(p, "%f", m);
   USART_Sentstring(USART_x,p);
}
/*******************************
函数名:void USART_Send_NUM(double m,int wei)
功能：发送一个double型数字
返回值：无
wei 要保留的小数位数
********************************/
void USART_Send_NUM(USART_TypeDef* USART_x,double m,int wei)
{  
   char p[100]={'\0'};
   sprintf(p, "%f", m);
   USART_Sentstring_1(USART_x,p,wei);
}
/*******************************
函数名:USART_Send_u32(u32 m)
功能：发送一个u32型数字
返回值：无
********************************/
void USART_Send_u32(USART_TypeDef* USART_x,u32 m)
{  char p[100]={'\0'};
   sprintf(p, "%d", m);
   USART_Sentstring(USART_x,p);
}

/********************************8
发送给 单片机
单字节接收 在发送数据串是 需要自定义开头结尾识别符
***********************************/


/****************************
函数名：void USART_Sentstring_MPU(char *str)
功能：发送一个字符串
返回值：无
******************************/
void USART_Sentstring_MPU(USART_TypeDef* USART_x,char *str)
{
 
 USART_SendData(USART_x,'F');//数据开始标志 F（first）
 while(*str!='\0')
 {
  USART_SendData(USART_x, *str);
  while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE) == RESET);////等待发送结
  str++;
 }
 USART_SendData(USART_x,'\r');//数据结束标志 E（end）
}
/****************************
函数名：void USART_Sentstring_1(char *str,int n)
功能：发送一个字符串
用于 发送数字  专用
返回值：无
******************************/

void USART_Sentstring_1_MPU(USART_TypeDef* USART_x,char *str,int n)
{
	int flag=0;
	USART_SendData(USART_x,'F');//数据开始标志 F（first）
    while(*str!='\0')
    {
	 if(*str=='.')
	 { flag=1;
	   n+=1;
	 }
    if(flag)
    { if(n==0)
	 break;
	 n--;
     }	  
    USART_SendData(USART_x, *str);
    while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE) == RESET){}////等待发送结
    str++;
  
   }
 USART_SendData(USART_x,'\r');//数据结束标志 E（end）
}
	
/*******************************
函数名:void USART_Send_NUM(double m,int wei)
功能：发送一个double型数字
返回值：无
wei 要保留的小数位数
********************************/
void USART_Send_NUM_MPU(USART_TypeDef* USART_x,double m,int wei)
{  
   char p[100]={'\0'};
   sprintf(p, "%f", m);
   USART_Sentstring_1_MPU(USART_x,p,wei);
}







  /***********************************8
用于pid的调试模块功能函数      start
  *********************************888*/

//单字节接收 
u16 length=0;
u8  Start=0;
u8  Usart_State=0x00;
            /*
            Usart_State  作用
            0x01 开始接收有效数据标志位
            0x02 有效数据接收完毕
            0x04 数据溢出（有效数据的长度超出了存储数据的数组的大小）
            0x08 数据是否被读取
            0x10 数据存储器书否为空 1 不为空 0 为空
            0x20 接收到有效数据
            */

void Clr_Rx(u8 *p)       //清空  数组
	{
		int i=0;
		for(i=0;i<=(USART_REC_LEN-1);i++)
		{
			p[i]='\0';
		}
		length=0;	
	}
void Clr_array(u8 *p,u8 Array_Len)  //清空数组   输入  字符串长度和 指针
	{
		int i=0;
		for(i=0;i<=(Array_Len-1);i++)
		{
			p[i]='\0';
		}
	}
    
    
    
    /////*       UART使用        *//////
//1.在接收中断一个字符发送不要添加发送等待，以保证数据正常接受。2，在非接收中断函数连续发送字符必须添加发送等待，以确保不丢数据。
void USART1_IRQHandler(void)    //UART  中断函数
	{    
		u8 Rx;
		if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{    
			Rx=USART_ReceiveData(USART1);
            if(Usart_State&0X01)
			{
				if(Rx=='E')
				{
					length=0;
					Usart_State&=~0x01;
					Usart_State|=0x02;
					Usart_State|=0X10;
					
					
				}
				else
				{
					if(length<=(USART_REC_LEN-1))
					{
						USART_RX_BUF[length]=Rx;
						length++;
					}
					else
					{  
						Usart_State|=0x04;
						return ;
					}					
				}					
			}
             else
			 {
				 if(Rx =='S')
			     {
				   if(Usart_State&0X10)//数据的存储器是否为空 不为空 则清空数据存储器
			        {
				        Clr_Rx(USART_RX_BUF);
					       Usart_State&=~0X10;//清零数据存储器
			         }
				   Usart_State|=0x01;
				   Usart_State&=~0x02;
				   
			     }
             }				 
	    }
 }
/*************ESP8266 数据接收***************/
 void USART2_IRQHandler(void)
	{    
		u8 Rx;
		if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{  
				Rx=USART_ReceiveData(USART2);
			    // Recieve_data(Rx);//dui
//					if(length<=(USART_REC_LEN-1))
//					{
//						USART_RX_BUF[length]=Rx;
//						length++;
//					}
//					else
//					{
//						length=0;
//						USART_RX_BUF[length]=Rx;
//						
//					}
			
		}
 }
/*
void USART1_IRQHandler(void)
	{
	   u8 Res;
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
		
		if((USART_RX_STA&0x8000)==0)//接收未完成
			{
			if(USART_RX_STA&0x4000)//接收到了0x0d
			  {
				if(Res!=0x0a)
					USART_RX_STA=0;//接收错误,重新开始
				else 
					USART_RX_STA|=0x8000;	//接收完成了 
			  }
			else
			   {	
				if(Res==0x0d)
					USART_RX_STA|=0x4000;
				else
				  {
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))
					  USART_RX_STA=0;//接收数据错误,重新开始接收	  
				  }		 
			   }
			 }   		 
     } 
 }

*/
         //  u8: unsigned char    u16:unsigned short int     u32:unsigned int
          /*  #include "stdlib.h"  //  atof atoi的头文件
              #include "string.h"  //这个是   strcmp函数的  头文件    */
void UsartChangePID(u8 *p)      
{   
	char FloatOrInt=0;
	char pid[10];       //   字符的字符串                         
	char num[10];        //   对应的数字给的字符串
    int  i=0,j=0;
	char *s1,*s2;                            
	double Vatual=0;
	
	while((j<10)&&(p[i]!='='))        //  字符数组的指针        前部分   
	{
		pid[j]=p[i];
		i++;
		j++;	
	}
	pid[j]='\0';
	s1=pid;
	j=0;
	if(p[i]=='=')
	{ 
		i++;                                 
	  while((j<10)&&(p[i]!='\0'))      //   数字转为字符的指针        后部分
	  { 
		  if(p[i]=='.')
		  FloatOrInt=1;
			
		   num[j]=p[i];
		i++;
		j++;	
	  }	
	}
	num[j]='\0';
	s2=num;
	if(FloatOrInt)                                     
		Vatual=atof(s2);            //atof    将字符串转化为    double   后面输入的数 转化为double
	else
	  Vatual=atoi(s2);                      //atoi           将字符串转化为    int
	
	if(strcmp(s1, "Proportion")==0)         //比较两个字符串是否一样的  来判断是哪个  字符也就是哪个变量
	{
		sptr->Proportion=(double)Vatual;
	}
	if(strcmp(s1, "Integral")==0)
	{
		sptr->Integral=(double)Vatual;
	}
	if(strcmp(s1, "Derivative")==0)
	{
	sptr->Derivative=(double)Vatual;
	}
    
//	if(strcmp(s1, "Kp_G")==0)
//	{
//		Kp_G=Vatual;
//	}
//	if(strcmp(s1, "Ki_G")==0)
//	{
//		Ki_G=Vatual;                                  
//	}
//	if(strcmp(s1, "Kd_G")==0)
//	{
//		Kd_G=Vatual;
//	}
//	if(strcmp(s1, "Pwm1")==0)
//	{
//		Pwm1=(u8)Vatual;
//	}
//	if(strcmp(s1, "Pwm2")==0)
//	{
//		Pwm2=(u8)Vatual;
//	}
//	if(strcmp(s1, "QbT")==0)
//	{
//		Qibai_T=(u8)Vatual;    
//	}
//	if(strcmp(s1, "TDt")==0)
//	{
//		TDt=(u8)Vatual;
//	}
//	if(strcmp(s1, "SAL")==0)
//	{
//		SAL=(int)Vatual;
//	}
//	if(strcmp(s1, "SAR")==0)
//	{
//		SAR=(int)Vatual;
//	}
//	if(strcmp(s1, "DAR")==0)
//	{
//		DAR=(int)Vatual;
//	}
//	if(strcmp(s1, "DAL")==0)
//	{
//		DAL=(int)Vatual;
//	}
}
/****************************************
main函数 中的  用法就是给串口助手发数据  显示目前的数据是什么
 	while(1) 
	{		
if(Usart_State&0x02)
		 {   UsartChangePID(USART_RX_BUF);
			 Usart_State|=0x08;
			 Usart_State&=~0x02;
//			 DIP=sptr->Proportion;
			 USART_Sentstring(USART1,"Proportion: ");
			 USART_Send_NUM(USART1,sptr->Proportion,3);
			 USART_Sentstring(USART1,"   ");
             USART_Sentstring(USART1,"Integral : ");
			 USART_Send_NUM(USART1,sptr->Integral,3);
			 USART_Sentstring(USART1,"   ");
             USART_Sentstring(USART1,"Derivative : ");
			 USART_Send_NUM(USART1,sptr->Derivative,3);
			 USART_Sentstring(USART1,"   ");

//			 USART_Sentstring(USART1,"Kp_G : ");
//			 USART_Send_NUM(USART1,Kp_G,3);
//			 USART_Sentstring(USART1,"   ");
//             USART_Sentstring(USART1,"Ki_G : ");
//			 USART_Send_NUM(USART1,Ki_G,3);
//			 USART_Sentstring(USART1,"   ");
//             USART_Sentstring(USART1,"Kd_G : ");
//			 USART_Send_NUM(USART1,Kd_G,3);
//			 fanhang(USART1);
//			 USART_Sentstring(USART1,"Pwm1 : ");
//			 USART_Send_NUM(USART1,Pwm1,3);
//			 USART_Sentstring(USART1,"   ");

//			 USART_Sentstring(USART1,"Pwm2 : ");
//			 USART_Send_NUM(USART1,Pwm2,3);
//			 USART_Sentstring(USART1,"   ");

//			 USART_Sentstring(USART1,"QbT : ");
//			 USART_Send_NUM(USART1,Qibai_T,3);
//			 USART_Sentstring(USART1,"   ");
//			 
//			 USART_Sentstring(USART1,"TDt : ");
//			 USART_Send_NUM(USART1,TDt,3);
//			 USART_Sentstring(USART1,"   ");
//			 fanhang(USART1);

//			 USART_Sentstring(USART1,"SAL : ");
//			 USART_Send_NUM(USART1,SAL,3);
//			 USART_Sentstring(USART1,"   ");
//			 
//			 USART_Sentstring(USART1,"SAR : ");
//			 USART_Send_NUM(USART1,SAR,3);
//			 USART_Sentstring(USART1,"   ");
//			 USART_Sentstring(USART1,"DAR : ");
//			 USART_Send_NUM(USART1,DAR,3);
//			 USART_Sentstring(USART1,"   ");
//			 
//			 USART_Sentstring(USART1,"DAL : ");
//			 USART_Send_NUM(USART1,DAL,3);
//			 USART_Sentstring(USART1,"   ");
			 fanhang(USART1);
			 

			 
		 }
     }

  /***********************************8
用于pid的调试模块功能函数      finish
  *********************************888*/






/***************************
函数名：
功能：把4字节的float性的数字转化为4个char性的字符
从高位往地位排列
返回值：
****************************/
char * FloatChangeChar(float num,char *p)
{   u8 i=0;
	char buf[4];
	for( i=0;i<4;i++)
	{
		buf[i]=(* ( (char *)(&num)+(3-i) ) );
		p[i]=  (* ( (char *)(&num)+(3-i) ) );
	}
	return buf;
}
/***************************
函数名：
功能：把4字节的float性的数字转化为4个char性的字符
从高位往地位排列
返回值：
****************************/
char * IntChangeChar(int num,char *p)
{   u8 i=0;
	char buf[4];
	for( i=0;i<4;i++)
	{
		buf[i]=(* ( (char *)(&num)+(4-i) ) );
		p[i]=  (* ( (char *)(&num)+(4-i) ) );
	}
	return buf;
	
}

/***************************
函数名：
功能：把4字节的float性的数字转化为4个char性的字符
从高位往地位排列
返回值：
****************************/
char * U16ChangeChar(u16 num,char *p)
{   u8 i=0;
	char buf[2];
	for(i=0;i<2;i++)
	{
		buf[i]=(* ( (char *)(&num)+(2-i) ) );
		p[i]=  (* ( (char *)(&num)+(2-i) ) );
	}
	return buf;
	
}
/***************************
函数名：
功能：把4字节的float性的数字转化为4个char性的字符
从高位往地位排列
返回值：
****************************/
char * U32ChangeChar(u32 num,char *p)
{   u8 i=0;
	char buf[4];
	for( i=0;i<4;i++)
	{
		buf[i]=(* ( (char *)(&num)+(4-i) ) );
		p[i]=  (* ( (char *)(&num)+(4-i) ) );
	}
	return buf;
	
}

void usart1_niming_report(u8 fun,float num,u8 len)

{
   static u8 d=0;
	
    u8 send_buf[32];

    u8 i;
	d++;
    if(len>28)return;    //最多28字节数据 

    send_buf[len+3]=0;  //校验数置零

    send_buf[0]=0X88;   //帧头

    send_buf[1]=fun;    //功能字

    send_buf[2]=len;    //数据长度
    send_buf[3]=bity3(num);
    send_buf[4]=bity2(num);
    send_buf[5]=bity1(num);
    send_buf[6]=bity0(num);
    send_buf[7]=d;
    //for(i=0;i<len;i++)send_buf[3+i]=data[i];     //复制数据
    for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];    //计算校验和 

    for(i=0;i<len+4;i++)USART_SentChar(USART1,send_buf[i]);   //发送数据到串口1 

}
/*
//通过串口1上报结算后的姿态数据给电脑

//aacx,aacy,aacz:x,y,z三个方向上面的加速度值

//gyrox,gyroy,gyroz:x,y,z三个方向上面的陀螺仪值

//roll:横滚角.单位0.01度。 -18000 -> 18000 对应 -180.00  ->  180.00度

//pitch:俯仰角.单位 0.01度。-9000 - 9000 对应 -90.00 -> 90.00 度

//yaw:航向角.单位为0.1度 0 -> 3600  对应 0 -> 360.0度

void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw)

{

    u8 tbuf[28]; 

    u8 i;

    for(i=0;i<28;i++)tbuf[i]=0;//清0

    tbuf[0]=(aacx>>8)&0XFF;

    tbuf[1]=aacx&0XFF;

    tbuf[2]=(aacy>>8)&0XFF;

    tbuf[3]=aacy&0XFF;

    tbuf[4]=(aacz>>8)&0XFF;

    tbuf[5]=aacz&0XFF; 

    tbuf[6]=(gyrox>>8)&0XFF;

    tbuf[7]=gyrox&0XFF;

    tbuf[8]=(gyroy>>8)&0XFF;

    tbuf[9]=gyroy&0XFF;

    tbuf[10]=(gyroz>>8)&0XFF;

    tbuf[11]=gyroz&0XFF;    

    tbuf[18]=(roll>>8)&0XFF;

    tbuf[19]=roll&0XFF;

    tbuf[20]=(pitch>>8)&0XFF;

    tbuf[21]=pitch&0XFF;

    tbuf[22]=(yaw>>8)&0XFF;

    tbuf[23]=yaw&0XFF;

    usart1_niming_report(0XAF,tbuf,28);//飞控显示帧,0XAF

}
//发送加速度传感器数据和陀螺仪数据

//aacx,aacy,aacz:x,y,z三个方向上面的加速度值

//gyrox,gyroy,gyroz:x,y,z三个方向上面的陀螺仪值

void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz)

{

    u8 tbuf[12]; 

    tbuf[0]=(aacx>>8)&0XFF;       //16位数据拆分为两部分传输

    tbuf[1]=aacx&0XFF;

    tbuf[2]=(aacy>>8)&0XFF;

    tbuf[3]=aacy&0XFF;

    tbuf[4]=(aacz>>8)&0XFF;

    tbuf[5]=aacz&0XFF; 

    tbuf[6]=(gyrox>>8)&0XFF;

    tbuf[7]=gyrox&0XFF;

    tbuf[8]=(gyroy>>8)&0XFF;

    tbuf[9]=gyroy&0XFF;

    tbuf[10]=(gyroz>>8)&0XFF;

    tbuf[11]=gyroz&0XFF;

    usart1_niming_report(0XA1,tbuf,12);//自定义帧,0XA1

}
*/