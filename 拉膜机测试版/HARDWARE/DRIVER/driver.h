#ifndef __DRIVER_H
#define __DRIVER_H
#include "sys.h"
#include "stdlib.h"	


/********** ������ �˿ڶ��� **************
Y��
//DRIVER_DIR_Y   PE14 
//DRIVER_OE_Y    PE15 
//STEP_PULSE_Y   PC7 (TIM8_CH2)
A��
//DRIVER_DIR_A   PE12
//DRIVER_OE_A    PE13
//STEP_PULSE_A   PA11 (TIM1_CH4)

******************************************/
#define DRIVER_DIR_A   PEout(12) // X����ת���� 
#define DRIVER_OE_A    PEout(13) // X��ʹ�ܽ� �ߵ�ƽ��Ч
#define DRIVER_DIR_Y   PEout(14)// Y����ת���� 
#define DIRVER_OE_Y    PEout(15)// Y��ʹ�ܽ� �͵�ƽ��Ч
#define RCR_VAL_A    71  //ÿ������RCR_VAL_X+1���Σ��ж�һ�Σ����ֵ��0~255�����ô�һЩ���Խ����ж�Ƶ��
#define RCR_VAL_Y   71   //ÿ������RCR_VAL_Y+1���Σ��ж�һ�Σ����ֵ��0~255�����ô�һЩ���Խ����ж�Ƶ��71

#define One_Circle_Pulse 6400 //ת��һȦ����Ҫ����������32ϸ�֣�
#define One_Circle_Distance  4  //ת��һȦ�ľ���mm
#define One_Pulse_Distance 6.25e-4//һ������ľ���
#define one_angle_pluse 17.7777 //һ���Ƕȵ�����   one_pulse/360
//printf("%f",One_Pulse_Distance);

//#define RCR_VAL    255 
typedef enum
{
	CW = 1,//�ߵ�ƽ˳ʱ��
	CCW = 0,//�͵�ƽ��ʱ��
}DIR_Type;//���з���

extern long target_pos_A;//�з��ŷ���
extern long current_pos_A;//�з��ŷ���

extern long target_pos_Y;//�з��ŷ���
extern long current_pos_Y;//�з��ŷ���



void Driver_Init_Y(void);//��������ʼ��
void TIM8_OPM_RCR_Init(u16 arr,u16 psc);//TIM8_CH2 ���������+�ظ��������ܳ�ʼ��
void TIM8_Startup(u32 frequency);   //������ʱ��8
void Locate_Rle_Y(long num,u32 frequency,DIR_Type dir); //��Զ�λ����
void Locate_Abs_Y(long num,u32 frequency);//���Զ�λ����
void TIM1_OPM_RCR_Init(u16 arr,u16 psc);//TIM1_CH4 ���������+�ظ��������ܳ�ʼ��
void TIM1_Startup(u32 frequency);   //������ʱ��1
void Driver_Init_A(void);//��������ʼ��
void Locate_Rle_A(long num,u32 frequency,DIR_Type dir); //��Զ�λ����
void Locate_Abs_A(long num,u32 frequency);//���Զ�λ����

/*��Ծ������*/
void A_rle_distance(long dis,u32 frequency); //A�᷽��������.���볤��mm��Ƶ�ʼ���
void Y_rle_distance(long dis,u32 frequency); //Y�᷽��������.����Ƕȣ�Ƶ�ʼ���

/*���Ծ������*/
void A_abs_distance(long dis,u32 frequency); //A�᷽��������.���볤��mm��Ƶ�ʼ���
void Y_abs_distance(long dis,u32 frequency); //Y�᷽��������.����Ƕȣ�Ƶ�ʼ���

/****��������ϵ******/
void AY_back_zero(u32 frequency); //�����
void AY_MOVE(long x_num,long y_num,u32 frequency);//�������궨λ


#endif


