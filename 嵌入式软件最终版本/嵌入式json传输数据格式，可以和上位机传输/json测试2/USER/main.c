# include "sys.h"
# include "delay.h"
# include "malloc.h"
# include "cJSON.h"
# include "usart.h"

int code;

struct result_data
{
    u32 cID;
    char *pName;
    char *datetime;
    u8 cStatus;
};

struct result_data resultData;

/* Parse text to JSON, then render back to text, and print! */
void doit(char * jsonText)
{
	cJSON * root;
	cJSON * result;
	
	//将json数据转化为json结构体
  root = cJSON_Parse(jsonText);
	
	if ( root )   //json数据装换成结构体成功
	{
		 code = cJSON_GetObjectItem(root, "code")->valueint;
		
		 if ( 200==code )   //数据接受正确
		 {
			 result = cJSON_GetObjectItem(root, "result");
			 
			 if ( result )  //获取所需数据成功
			 {
				 resultData.cID = cJSON_GetObjectItem(result, "id")->valueint;
				 resultData.pName = cJSON_GetObjectItem(result, "name")->valuestring;
				 resultData.cStatus = cJSON_GetObjectItem(result, "status")->valueint;
				 resultData.datetime = cJSON_GetObjectItem(result, "datetime")->valuestring;
				 cJSON_Delete(result);
			 }
		 }
	}
	else   //json数据转换失败
	{
		
	}
	 cJSON_Delete(root);
}


 int main(void)
 {
	char receiveData[1000];
	u8 jsonFlag = 0;   //json解析标志位 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);
	 
	mem_init();
	 
	while(1)
	{
		  int16_t len = 0;
		  int i = 0;
		
			//接收到发送过来的数据
			if(USART_RX_STA&0x8000 && 0==jsonFlag )
			{
				len=USART_RX_STA&0x3fff; //得到数据接收的长度
				
				//清空json数据解析缓存
				for (i=0; i<1000; i++)
				{
					receiveData[i] = 0;
				}
				
				//更新接受缓存数据
				for (i=0; i<len; i++)
				{
					receiveData[i] = USART_RX_BUF[i];
				}
				jsonFlag = 1;
				USART_RX_STA = 0;
			}
			
			//解析接收到的json数据
			if ( jsonFlag )
			{
				doit(receiveData);
				jsonFlag = 0;
			}
	}
 }
