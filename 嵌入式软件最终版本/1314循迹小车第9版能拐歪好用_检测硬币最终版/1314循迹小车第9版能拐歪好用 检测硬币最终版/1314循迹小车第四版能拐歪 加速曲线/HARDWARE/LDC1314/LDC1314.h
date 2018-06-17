#ifndef __LDC1314_H
#define __LDC1314_H
#include  "myiic.h"
#define LDC1314_CMD_DATA_MSB_CH0	0x00
#define LDC1314_CMD_DATA_LSB_CH0	0x01
#define LDC1314_CMD_DATA_MSB_CH1	0x02
#define LDC1314_CMD_DATA_LSB_CH1	0x03
#define LDC1314_CMD_DATA_MSB_CH2	0x04
#define LDC1314_CMD_DATA_LSB_CH2	0x05
#define LDC1314_CMD_DATA_MSB_CH3	0x06
#define LDC1314_CMD_DATA_LSB_CH3	0x07
#define LDC1314_CMD_REF_COUNT_CH0	0x08
#define LDC1314_CMD_REF_COUNT_CH1	0x09
#define LDC1314_CMD_REF_COUNT_CH2	0x0A
#define LDC1314_CMD_REF_COUNT_CH3	0x0B
#define LDC1314_CMD_OFFSET_CH0	0x0C
#define LDC1314_CMD_OFFSET_CH1	0x0D
#define LDC1314_CMD_OFFSET_CH2	0x0E
#define LDC1314_CMD_OFFSET_CH3	0x0F
#define LDC1314_CMD_SETTLE_COUNT_CH0	0x10
#define LDC1314_CMD_SETTLE_COUNT_CH1	0x11
#define LDC1314_CMD_SETTLE_COUNT_CH2	0x12
#define LDC1314_CMD_SETTLE_COUNT_CH3	0x13
#define LDC1314_CMD_CLOCK_DIVIDERS_CH0 	0x14
#define LDC1314_CMD_CLOCK_DIVIDERS_CH1 	0x15
#define LDC1314_CMD_CLOCK_DIVIDERS_CH2 	0x16
#define LDC13v_CMD_CLOCK_DIVIDERS_CH3 	0x17
#define LDC1314_CMD_STATUS 	0x18
#define LDC1314_CMD_ERROR_CONFIG 	0x19
#define LDC1314_CMD_CONFIG 	0x1A
#define LDC1314_CMD_MUX_CONFIG 	0x1B
#define LDC1314_CMD_RESET_DEVICE 	0x1C
#define LDC1314_CMD_SYSTEM_CLOCK_CONFIG	0x1D
#define LDC1314_CMD_DRIVE_CURRENT_CH0	0x1E
#define LDC1314_CMD_DRIVE_CURRENT_CH1 	0x1F
#define LDC1314_CMD_DRIVE_CURRENT_CH2 	0x20
#define LDC1314_CMD_DRIVE_CURRENT_CH3	0x21
#define LDC1314_CMD_MANUFACTID	0x7E
#define LDC1314_CMD_DEVID	0x7F

void LDC1314Single_init(void);
void LDC1314_MultiInit(void);
void LDC_Write_ZI(u8 add,u16 value);
u16 LDC_Read_ZI(u8 add);
//void LDC_Write_Reg(u8 add,u8 value);
//u8 LDC_Read_Reg(u8 add);
u16 LDC_Read_Reg(u8 add);
void LDC_Write_Reg(u8 add,u16 value);
void IO_Init(void);
#endif
