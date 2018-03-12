#ifndef key_h
#define key_h
#include "stm32f10x.h"

#define KEY1 PEin(0)		//读取KEY1      启动(确认)
#define KEY2 PEin(1)		//读取KEY2      停止  
#define KEY3 PEin(2)		//读取KEY3      增大(下一个)
#define KEY4 PEin(3)		//读取KEY4      减小(上一个)
#define KEY5 PEin(4)		//读取KEY5      归零 
#define KEY6 PEin(7)		//读取KEY6      微调(进)
#define KEY7 PEin(8)		//读取KEY7      微调(退)

#define KEY1_PRES		1		//KEY1按下
#define KEY2_PRES		2		//KEY2按下
#define KEY3_PRES		3		//KEY3按下
#define KEY4_PRES		4		//KEY4按下
#define KEY5_PRES		5		//KEY5按下
#define KEY6_PRES		6		//KEY6按下
#define KEY7_PRES		7		//KEY7按下



void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数		





#endif




