#ifndef key_h
#define key_h
#include "stm32f10x.h"

//#define KEY1 PAin(1)
//#define KEY2 PAin(2)

#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//��ȡ����1
//#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����2

#define KEY1_PRES 	1	//KEY0����
void key1_Init(void);
void key2_Init(void);

u8 key1(u8);
u8 key2(u8);





#endif




