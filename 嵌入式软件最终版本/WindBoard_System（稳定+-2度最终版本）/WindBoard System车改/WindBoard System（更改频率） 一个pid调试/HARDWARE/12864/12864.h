/*
    PC3----->LCD_CS
		PC4----->LCD_RST
		PC5----->LCD_RS
		PC6----->LCD_SDA
		PC7----->LCD_SCK
		3V3----->LCD_VDD
		GND----->LCD_VSS
		3V3----->LCD_LEDA
*/

# ifndef __12864_H
# define __12864_H
# include "sys.h"

//片选
# define LCD_CS_0()   GPIO_ResetBits(GPIOC, GPIO_Pin_3)
# define LCD_CS_1()   GPIO_SetBits(GPIOC, GPIO_Pin_3)

//复位口
# define LCD_RST_0()  GPIO_ResetBits(GPIOC, GPIO_Pin_4)
# define LCD_RST_1()  GPIO_SetBits(GPIOC, GPIO_Pin_4)

//命令/数据寄存器选择
# define LCD_RS_0()   GPIO_ResetBits(GPIOC, GPIO_Pin_5)
# define LCD_RS_1()   GPIO_SetBits(GPIOC, GPIO_Pin_5)

//数据口
# define LCD_DAT_0()  GPIO_ResetBits(GPIOC, GPIO_Pin_6)
# define LCD_DAT_1()  GPIO_SetBits(GPIOC, GPIO_Pin_6)

//时钟口
# define LCD_SCLK_0() GPIO_ResetBits(GPIOC, GPIO_Pin_7)
# define LCD_SCLK_1() GPIO_SetBits(GPIOC, GPIO_Pin_7)

//IO口初始化
void MYGPIO_Init(void);

//初始化LCD
void LCD_Init(void);

//清屏
void LCD_Clear_Screen(void);

//清除行
void LCD_Clear_Line(u8 _X);

//向LCD发送8字节数据
void LCD_Send_8Bits(u8 dat);

//向LCD写指令
void LCD_Send_Order(u8 cmd);

//向LCD写数据
void LCD_Send_Data(u8 dat);

//显示汉字
void LCD_HZ(u8 x, u8 y, u8 dat);

//选中汉字
void LCD_HZ_OP(u8 x, u8 y,  u8 dat);

//显示字符串
void LCD_HZS(u8 x,u8 y,u8 *string);

//选中字符串
void LCD_HZS_OP(u8 x,u8 y,u8 *string);

//设置坐标
void LCD_Add_XY(u8 x, u8 y);

//显示ASCALL字符
void LCD_ASCALL(u8 c);

//选中ASCALL
void LCD_ASCALL_OP(u8 c);

//显示字符串
void LCD_ASCALLS(u8 *string);

//选中字符串
void LCD_ASCALLS_OP(u8 *string);

//显示整数
void LCD_int(int dat);
	
# endif


