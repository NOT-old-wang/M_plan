#ifndef __DISPLAY_H
#define __DISPLAY_H	
#include "oled.h"
#include "key.h"
#include "driver.h"

#define MENU_SIZE 50          //�˵�����


extern long move_mm;


void ui_start(void);     //OLED���н���
void main_window(void);  //������    ��ѡ������ٶȺ�λ��

void motor_distance(); //���λ�����ý���
void motor_distance_window();

void motor_speed();    //����ٶ����ý���
void motor_speed_window();

void motor_adjust(void);   //�������


#endif


