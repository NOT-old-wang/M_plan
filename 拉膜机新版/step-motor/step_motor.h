#ifndef step_motor_h
#define step_motor_h
#include "stm32f10x.h"
#include "time.h"
#include "key.h"
#include "led.h"

/***********old_wang 7/16***********/

#define one_pulse  6400 //һȦ������
#define one_dis  4      //һȦ����mm
#define one_pulse_dis  6.25e-4  //һ������ľ���  one_dis/one_pulse (mm)
#define one_angle_pluse 17.7777 //һ���Ƕȵ�����   one_pulse/360

typedef enum
{
	X  = 0,//X����
	Y  = 1,//Y����
	Z  = 2,//Z����
	
}motor_Type;//ѡȡ�ĸ����

//����x��y��
void step_motor_init(void);//�����ʼ��
void x_step_motor_start(void);//X�������
void y_step_motor_start(void);//Y�������
void Z_step_motor_start(void);//Z�������

void x_step_motor_stop(void); //X���ֹͣ
void y_step_motor_stop(void); //Y���ֹͣ
void z_step_motor_stop(void); //Z���ֹͣ

void step_motor_STOP(void); //�����ͣ

void x_step_direction(u8 mode);  //x�������
void y_step_direction(u8 mode);  //y�������
void z_step_direction(u8 mode);  //Z�������

u32 step_calculate(u16 distance); //����ת��������
u32 step_circle_pulse(u8 circle);//Ȧ��ת����������

u8 x_step_motor(u16 distance,u8 dir,float frv);  //X�᷽��������.������룬����Ƶ�ʼ���
u8 y_step_motor(u16 distance,u8 dir,float frv);  //Y�᷽��������
u8 z_step_motor(u16 distance,u8 dir,float frv);  //Y�᷽��������

u32 step_frv_motor(float frv); //Ƶ�ʼ���  ����HZ
u16 step_angle_motor(u16 Angle);//�Ƕȼ����X��y������
void step_circle_turn(u8 motor,u8 circle);  //���Ƶ��ת��Ȧ

u8 x_step_angle(s16 angle,float frv);  //X�᷽��������.����Ƕȣ�Ƶ�ʼ���
u8 y_step_angle(s16 angle,float frv);  //Y�᷽��������.����Ƕȣ�Ƶ�ʼ���
u8 x_y_step_angle(s16 x_angle,s16 y_angle,float frv);

/***�������(������)��Ƶ�ʣ��ĸ����***/
void X_Locate_Rle(s16 distance,float frv,motor_Type motor_num); //��Զ�λ����
void Y_Locate_Rle(s16 distance,float frv,motor_Type motor_num); //��Զ�λ����
void Z_Locate_Rle(s16 distance,float frv,motor_Type motor_num); //��Զ�λ����
u8 Locate_Rle(s16 distance,float frv,motor_Type motor_num); //��Զ�λ����
/***************************/

/**�������(������)��Ƶ�ʣ��ĸ����***/
//u8 Locate_Abs(s16 distance,float frv,motor_Type motor_num);//���Զ�λ����
/******/

//u8 back_zero(float frv);  //��ԭ��
///**��������(������)  Ƶ��***/
//u8 x_y_Location(s16 x_distance,s16 y_distance,float frv);//���궨λ���� --����
///******/

///**��������(������)  Ƶ��***/
//u8 XY_Location(s16 x_distance,s16 y_distance,float frv);//���궨λ���� --˫��
///******/

#endif
