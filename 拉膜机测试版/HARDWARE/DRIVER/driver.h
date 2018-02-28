#ifndef __DRIVER_H
#define __DRIVER_H
#include "sys.h"
#include "stdlib.h"	


/********** 驱动器 端口定义 **************
Y轴
//DRIVER_DIR_Y   PE14 
//DRIVER_OE_Y    PE15 
//STEP_PULSE_Y   PC7 (TIM8_CH2)
A轴
//DRIVER_DIR_A   PE12
//DRIVER_OE_A    PE13
//STEP_PULSE_A   PA11 (TIM1_CH4)

******************************************/
#define DRIVER_DIR_A   PEout(12) // X轴旋转方向 
#define DRIVER_OE_A    PEout(13) // X轴使能脚 高电平有效
#define DRIVER_DIR_Y   PEout(14)// Y轴旋转方向 
#define DIRVER_OE_Y    PEout(15)// Y轴使能脚 低电平有效
#define RCR_VAL_A    71  //每计数（RCR_VAL_X+1）次，中断一次，这个值（0~255）设置大一些可以降低中断频率
#define RCR_VAL_Y   71   //每计数（RCR_VAL_Y+1）次，中断一次，这个值（0~255）设置大一些可以降低中断频率71

#define One_Circle_Pulse 6400 //转动一圈所需要的脉冲数（32细分）
#define One_Circle_Distance  4  //转动一圈的距离mm
#define One_Pulse_Distance 6.25e-4//一个脉冲的距离
#define one_angle_pluse 17.7777 //一个角度的脉冲   one_pulse/360
//printf("%f",One_Pulse_Distance);

//#define RCR_VAL    255 
typedef enum
{
	CW = 1,//高电平顺时针
	CCW = 0,//低电平逆时针
}DIR_Type;//运行方向

extern long target_pos_A;//有符号方向
extern long current_pos_A;//有符号方向

extern long target_pos_Y;//有符号方向
extern long current_pos_Y;//有符号方向



void Driver_Init_Y(void);//驱动器初始化
void TIM8_OPM_RCR_Init(u16 arr,u16 psc);//TIM8_CH2 单脉冲输出+重复计数功能初始化
void TIM8_Startup(u32 frequency);   //启动定时器8
void Locate_Rle_Y(long num,u32 frequency,DIR_Type dir); //相对定位函数
void Locate_Abs_Y(long num,u32 frequency);//绝对定位函数
void TIM1_OPM_RCR_Init(u16 arr,u16 psc);//TIM1_CH4 单脉冲输出+重复计数功能初始化
void TIM1_Startup(u32 frequency);   //启动定时器1
void Driver_Init_A(void);//驱动器初始化
void Locate_Rle_A(long num,u32 frequency,DIR_Type dir); //相对定位函数
void Locate_Abs_A(long num,u32 frequency);//绝对定位函数

/*相对距离控制*/
void A_rle_distance(long dis,u32 frequency); //A轴方向距离控制.输入长度mm，频率即可
void Y_rle_distance(long dis,u32 frequency); //Y轴方向距离控制.输入角度，频率即可

/*绝对距离控制*/
void A_abs_distance(long dis,u32 frequency); //A轴方向距离控制.输入长度mm，频率即可
void Y_abs_distance(long dis,u32 frequency); //Y轴方向距离控制.输入角度，频率即可

/****绝对坐标系******/
void AY_back_zero(u32 frequency); //回零点
void AY_MOVE(long x_num,long y_num,u32 frequency);//独自坐标定位


#endif


