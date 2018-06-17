#ifndef _HC_SR04_H
#define _HC_SR04_H
#define module_interval 25    //定义超声波模块接收发射端间距(单位：mm)
#define object_distance 100.0   //检测物体的距离

void NVIC_Configuration(void);
void TIM_Configuration(void);
void GPIO_Configuration(void);
void RCC_Configuration(void);
float Sensor_using(void);
void _delay(void);

#endif

