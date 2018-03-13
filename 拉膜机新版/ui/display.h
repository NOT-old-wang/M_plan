#ifndef __DISPLAY_H
#define __DISPLAY_H	
#include "oled.h"
#include "key.h"
#include "delay.h"

#define MENU_SIZE 50          //�˵�����


extern long move_mm;


void ui_start(void);     //OLED���н���
void main_window(void);  //������    ��ѡ������ٶȺ�λ��

void motor_distance(void); //���λ�����ý���
void motor_distance_window(void);

void motor_speed(void);    //����ٶ����ý���
void motor_speed_window(void);
void Start(void);
void motor_adjust(void);   //�������


#endif


