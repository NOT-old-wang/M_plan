#ifndef key_h
#define key_h
#include "stm32f10x.h"

#define KEY1 PEin(0)		//��ȡKEY1      ����(ȷ��)
#define KEY2 PEin(1)		//��ȡKEY2      ֹͣ  
#define KEY3 PEin(2)		//��ȡKEY3      ����(��һ��)
#define KEY4 PEin(3)		//��ȡKEY4      ��С(��һ��)
#define KEY5 PEin(4)		//��ȡKEY5      ���� 
#define KEY6 PEin(7)		//��ȡKEY6      ΢��(��)
#define KEY7 PEin(8)		//��ȡKEY7      ΢��(��)

#define KEY1_PRES		1		//KEY1����
#define KEY2_PRES		2		//KEY2����
#define KEY3_PRES		3		//KEY3����
#define KEY4_PRES		4		//KEY4����
#define KEY5_PRES		5		//KEY5����
#define KEY6_PRES		6		//KEY6����
#define KEY7_PRES		7		//KEY7����



void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��		





#endif




