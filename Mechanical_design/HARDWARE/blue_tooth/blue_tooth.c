#include "delay.h"
#include "sys.h"
#include "usart.h"

//   用于 蓝牙发送接收 的 简单子程序

// sprintf(sendbuf,"n0.val=%d",aaa);

//        
//         /*************************
//                接受阶段
//         *************************/
//        
//                  if(USART_RX_STA&0x8000)  //   判断接收完成了  进if里面去
//		        {					   
//			len=USART_RX_STA&0x3fff;      //得到此次接收到的数据长度    高两位为0其实就是去掉0x0a ， 0x0b  所以就是最终的字符串长度了
//			printf("\r\n您发送的消息为:\r\n");          //  直接发串口的  而sprintf为可以串口也发  液晶屏也直接发  不建议用
//			    for(t=0;t<len;t++)
//			    {
//				USART1->DR=USART_RX_BUF[t];     //  接收到的数据放在
//				while((USART1->SR&0X40)==0);   //等待发送结束
//			     }
//			printf("\r\n\r\n");  //  插入换行
//			USART_RX_STA=0;   /// 标志位清零
 void Blue_tooth_number(USART_TypeDef* USART_x,double angle)
{
        /**************************
                 发送阶段
        **************************/ 
	      USART_Sendnumber(USART_x,angle)	;		
        //接收到的数据必须是0x0d 0x0a结尾  所以每次发送一波都要 加上0x0d 0x0a
        USART_SendData(USART_x,0x0d);                                      //
        while(USART_GetFlagStatus(USART_x,USART_FLAG_TC)==RESET);      //    判断    发送  是否  完成
        USART_SendData(USART_x,0x0a);                                        //
        while(USART_GetFlagStatus(USART_x,USART_FLAG_TC)==RESET);       //    判断    发送  是否  完成
        delay_ms(1000);
}

void Blue_tooth_String(USART_TypeDef* USART_x,char* string)
{
        /**************************
                 发送阶段
        **************************/ 
	      USART_Sentstring(USART_x,string)	;		
        //接收到的数据必须是0x0d 0x0a结尾  所以每次发送一波都要 加上0x0d 0x0a
        USART_SendData(USART_x,0x0d);                                      //
        while(USART_GetFlagStatus(USART_x,USART_FLAG_TC)==RESET);      //    判断    发送  是否  完成
        USART_SendData(USART_x,0x0a);                                        //
        while(USART_GetFlagStatus(USART_x,USART_FLAG_TC)==RESET);       //    判断    发送  是否  完成
        delay_ms(1000);
}
void  PC_senddata_HMI(int number)
{
        sprintf( sendbuf,"n0.val=%d", number); //  将number的值输入到n0上
            i=0;
            while(sendbuf[i]!='\0')
           {
                USART_GetFlagStatus(USART1, USART_FLAG_TC);
                USART_SendData(USART1,sendbuf[i]);                               //发送数据
                while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};   //    判断    发送  是否  完成
             i++;
             }
              //  结束符三个FF FF FF
                    USART_SendData(USART1,0xff);
                    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){}; 
                    USART_SendData(USART1,0xff);
                    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){}; 
                     USART_SendData(USART1,0xff);
                    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){}; 
         
                  
}    
