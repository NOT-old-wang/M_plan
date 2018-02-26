#ifndef __DRIVER_H
#define __DRIVER_H
#include "sys.h"
#include "stdlib.h"	


/********** ������ �˿ڶ��� **************
Y��
//DRIVER_DIR_Y   PE14 
//DRIVER_OE_Y    PE15 
//STEP_PULSE_Y   PC7 (TIM8_CH2)
X��
//DRIVER_DIR_Y   PE12
//DRIVER_OE_Y    PE13
//STEP_PULSE_Y   PA11 (TIM1_CH4)

******************************************/
#define DRIVER_DIR_X   PEout(12) // X����ת���� 
#define DRIVER_OE_X    PEout(13) // X��ʹ�ܽ� �ߵ�ƽ��Ч
#define DRIVER_DIR_Y   PEout(14)// Y����ת���� 
#define DIRVER_OE_Y    PEout(15)// Y��ʹ�ܽ� �͵�ƽ��Ч
#define RCR_VAL_X    71  //ÿ������RCR_VAL_X+1���Σ��ж�һ�Σ����ֵ��0~255�����ô�һЩ���Խ����ж�Ƶ��
#define RCR_VAL_Y   71   //ÿ������RCR_VAL_Y+1���Σ��ж�һ�Σ����ֵ��0~255�����ô�һЩ���Խ����ж�Ƶ��71

#define One_Circle_Pulse 25600 //ת��һȦ����Ҫ����������128ϸ�֣�
#define One_Circle_Distance  3.141592654     //ת��һȦ�ľ���
#define One_Pulse_Distance One_Circle_Distance/One_Circle_Pulse //һ������ľ���
#define one_angle_pluse 71.1111 //һ���Ƕȵ�����   one_pulse/360
//printf("%f",One_Pulse_Distance);

//#define RCR_VAL    255 
typedef enum
{
	CW = 1,//�ߵ�ƽ˳ʱ��
	CCW = 0,//�͵�ƽ��ʱ��
}DIR_Type;//���з���

extern long target_pos_X;//�з��ŷ���
extern long current_pos_X;//�з��ŷ���

extern long target_pos_Y;//�з��ŷ���
extern long current_pos_Y;//�з��ŷ���



void Driver_Init_Y(void);//��������ʼ��
void TIM8_OPM_RCR_Init(u16 arr,u16 psc);//TIM8_CH2 ���������+�ظ��������ܳ�ʼ��
void TIM8_Startup(u32 frequency);   //������ʱ��8
void Locate_Rle_Y(long num,u32 frequency,DIR_Type dir); //��Զ�λ����
void Locate_Abs_Y(long num,u32 frequency);//���Զ�λ����
void TIM1_OPM_RCR_Init(u16 arr,u16 psc);//TIM1_CH4 ���������+�ظ��������ܳ�ʼ��
void TIM1_Startup(u32 frequency);   //������ʱ��1
void Driver_Init_X(void);//��������ʼ��
void Locate_Rle_X(long num,u32 frequency,DIR_Type dir); //��Զ�λ����
void Locate_Abs_X(long num,u32 frequency);//���Զ�λ����

/*���ԽǶ�*/
void X_angle(s16 angle,u32 frequency); //X�᷽��������.����Ƕȣ�Ƶ�ʼ���
void Y_angle(s16 angle,u32 frequency); //Y�᷽��������.����Ƕȣ�Ƶ�ʼ���

/****��������ϵ******/
void XY_back_zero(u32 frequency); //�����
void XY_MOVE(long x_num,long y_num,u32 frequency);//�������궨λ


#endif


