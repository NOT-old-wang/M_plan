#ifndef key_h
#define key_h
#include "stm32f10x.h"

#define KEY1 PEin(0)		//读取KEY1      启动(确认)
#define KEY2 PEin(1)		//读取KEY2      返回  
#define KEY3 PEin(2)		//读取KEY3      增大(下一个    功能键1
#define KEY4 PEin(3)		//读取KEY4      减小(上一个)   功能键2
#define KEY5 PEin(4)		//读取KEY5      归零 
#define KEY6 PEin(5)		//读取KEY6      
#define KEY7 PEin(6)		//读取KEY7      

#define KEY8 PEin(7)		//读取KEY8      X前
#define KEY9 PEin(8)		//读取KEY9      X后
#define KEY10 PEin(9)		//读取KEY10     Y前
#define KEY11 PEin(10)	//读取KEY11     Y前
#define KEY12 PEin(11)	//读取KEY12     Z前
#define KEY13 PEin(12)	//读取KEY13     Z前



#define KEY1_PRES		1		//KEY1按下
#define KEY2_PRES		2		//KEY2按下
#define KEY3_PRES		3		//KEY3按下
#define KEY4_PRES		4		//KEY4按下
#define KEY5_PRES		5		//KEY5按下
#define KEY6_PRES		6		//KEY6按下
#define KEY7_PRES		7		//KEY7按下
#define KEY8_PRES		8		//KEY8按下
#define KEY9_PRES		9		//KEY9按下
#define KEY10_PRES	10	//KEY10按下
#define KEY11_PRES	11	//KEY11按下
#define KEY12_PRES	12	//KEY12按下
#define KEY13_PRES	13	//KEY12按下




void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数		





#endif




