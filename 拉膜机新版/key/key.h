#ifndef key_h
#define key_h
#include "stm32f10x.h"

#define KEY1 PEin(0)		//��ȡKEY1      ����(ȷ��)
#define KEY2 PEin(1)		//��ȡKEY2      ����  
#define KEY3 PEin(2)		//��ȡKEY3      ����(��һ��    ���ܼ�1
#define KEY4 PEin(3)		//��ȡKEY4      ��С(��һ��)   ���ܼ�2
#define KEY5 PEin(4)		//��ȡKEY5      ���� 
#define KEY6 PEin(5)		//��ȡKEY6      
#define KEY7 PEin(6)		//��ȡKEY7      

#define KEY8 PEin(7)		//��ȡKEY8      Xǰ
#define KEY9 PEin(8)		//��ȡKEY9      X��
#define KEY10 PEin(9)		//��ȡKEY10     Yǰ
#define KEY11 PEin(10)	//��ȡKEY11     Yǰ
#define KEY12 PEin(11)	//��ȡKEY12     Zǰ
#define KEY13 PEin(12)	//��ȡKEY13     Zǰ



#define KEY1_PRES		1		//KEY1����
#define KEY2_PRES		2		//KEY2����
#define KEY3_PRES		3		//KEY3����
#define KEY4_PRES		4		//KEY4����
#define KEY5_PRES		5		//KEY5����
#define KEY6_PRES		6		//KEY6����
#define KEY7_PRES		7		//KEY7����
#define KEY8_PRES		8		//KEY8����
#define KEY9_PRES		9		//KEY9����
#define KEY10_PRES	10	//KEY10����
#define KEY11_PRES	11	//KEY11����
#define KEY12_PRES	12	//KEY12����
#define KEY13_PRES	13	//KEY12����




void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��		





#endif




