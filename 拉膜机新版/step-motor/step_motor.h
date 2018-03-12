#ifndef step_motor_h
#define step_motor_h
#include "stm32f10x.h"
#include "time.h"
#include "key.h"
#include "led.h"

/***********old_wang 7/16***********/

#define one_pulse  6400 //一圈脉冲数
#define one_dis  4      //一圈距离mm
#define one_pulse_dis  6.25e-4  //一个脉冲的距离  one_dis/one_pulse (mm)
#define one_angle_pluse 17.7777 //一个角度的脉冲   one_pulse/360

typedef enum
{
	X  = 0,//X轴电机
	Y  = 1,//Y轴电机
	Z  = 2,//Z轴电机
	
}motor_Type;//选取哪个电机

//步进x轴y轴
void step_motor_init(void);//电机初始化
void x_step_motor_start(void);//X电机启动
void y_step_motor_start(void);//Y电机启动
void Z_step_motor_start(void);//Z电机启动

void x_step_motor_stop(void); //X电机停止
void y_step_motor_stop(void); //Y电机停止
void z_step_motor_stop(void); //Z电机停止

void step_motor_STOP(void); //电机急停

void x_step_direction(u8 mode);  //x方向控制
void y_step_direction(u8 mode);  //y方向控制
void z_step_direction(u8 mode);  //Z方向控制

u32 step_calculate(u16 distance); //距离转化成脉冲
u32 step_circle_pulse(u8 circle);//圈数转化成脉冲数

u8 x_step_motor(u16 distance,u8 dir,float frv);  //X轴方向距离控制.输入距离，方向，频率即可
u8 y_step_motor(u16 distance,u8 dir,float frv);  //Y轴方向距离控制
u8 z_step_motor(u16 distance,u8 dir,float frv);  //Y轴方向距离控制

u32 step_frv_motor(float frv); //频率计算  输入HZ
u16 step_angle_motor(u16 Angle);//角度计算出X轴y轴脉冲
void step_circle_turn(u8 motor,u8 circle);  //控制电机转几圈

u8 x_step_angle(s16 angle,float frv);  //X轴方向距离控制.输入角度，频率即可
u8 y_step_angle(s16 angle,float frv);  //Y轴方向距离控制.输入角度，频率即可
u8 x_y_step_angle(s16 x_angle,s16 y_angle,float frv);

/***输入距离(带正负)，频率，哪个电机***/
void X_Locate_Rle(s16 distance,float frv,motor_Type motor_num); //相对定位函数
void Y_Locate_Rle(s16 distance,float frv,motor_Type motor_num); //相对定位函数
void Z_Locate_Rle(s16 distance,float frv,motor_Type motor_num); //相对定位函数
u8 Locate_Rle(s16 distance,float frv,motor_Type motor_num); //相对定位函数
/***************************/

/**输入距离(带正负)，频率，哪个电机***/
//u8 Locate_Abs(s16 distance,float frv,motor_Type motor_num);//绝对定位函数
/******/

//u8 back_zero(float frv);  //回原点
///**输入坐标(带正负)  频率***/
//u8 x_y_Location(s16 x_distance,s16 y_distance,float frv);//坐标定位函数 --单动
///******/

///**输入坐标(带正负)  频率***/
//u8 XY_Location(s16 x_distance,s16 y_distance,float frv);//坐标定位函数 --双动
///******/

#endif
