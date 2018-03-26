#include "step_motor.h"

vu32 x_double_cycle = 0;
vu32 y_double_cycle = 0;
vu32 z_double_cycle = 0;

extern vu32 x_Pluse;
extern vu32 y_Pluse;
extern vu32 z_Pluse;

extern vu32 x_need_Pluse;
extern vu32 y_need_Pluse;
extern vu32 z_need_Pluse;


vu32 frequency = 0;
vs32 x_sum_Pluse = 0;
vs32 y_sum_Pluse = 0;
vs32 z_sum_Pluse = 0;

s16 X_distance=0;
s16 Y_distance=0;
s16 Z_distance=0;

void step_motor_init()  //电机初始化
{
	 
	//电机管脚初始化
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIO时钟
	//初始化GPIO PA6,7
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;  //开漏 !!!!!
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//方向管脚初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能GPIO时钟
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;  //开漏 !!!!!
//  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  //推挽 !!!!!
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
	//电机使能管脚
  
	 TIM6->CR1&=0xfe;    //关闭定时器6	 
	 TIM7->CR1&=0xfe;    //关闭定时器7	
	 TIM5->CR1&=0xfe;    //关闭定时器5	 
}

void x_step_motor_start() //X电机启动
{
//	frequency=step_frv_motor(25600);//测试用--1秒1圈
//	frequency=step_frv_motor(100000);//接近最大测试用
	time6_Init(frequency,71);
//	while(x_need_Pluse!=x_Pluse);
}

void y_step_motor_start() //Y电机启动
{
//	frequency=step_frv_motor(25600);//测试用--1秒1圈
//	frequency=step_frv_motor(100000);//接近最大测试用
	time7_Init(frequency,71);
//	while(y_need_Pluse!=y_Pluse);
}

void z_step_motor_start() //Z电机启动
{
	time5_Init(frequency,71);
}


void x_step_motor_stop() //X电机停止
{
	x_Pluse=0;x_need_Pluse=0;frequency=0;
//  GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	TIM6->CR1&=0xfe;    //关闭定时器6		
}

void y_step_motor_stop() //Y电机停止
{
	y_Pluse=0;y_need_Pluse=0;frequency=0;
//  GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	TIM7->CR1&=0xfe;    //关闭定时器7
}

void z_step_motor_stop() //Y电机停止
{
	z_Pluse=0;z_need_Pluse=0;frequency=0;
//  GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	TIM5->CR1&=0xfe;    //关闭定时器7
}


void step_motor_STOP() //电机急停
{
	x_Pluse=0;y_Pluse=0; x_need_Pluse=0;y_need_Pluse=0; frequency=0;
//  GPIO_ResetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_9);//使能端复位 
	TIM6->CR1&=0xfe;    //关闭定时器6	 
  TIM7->CR1&=0xfe;    //关闭定时器7
	TIM5->CR1&=0xfe;    //关闭定时器5
	
}

void x_step_direction(u8 mode)  //方向控制
{
  if(mode==1)
	{
	 GPIO_SetBits(GPIOC,GPIO_Pin_6);
	}
	else if(mode==0)
	{
	 GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	}

}
void y_step_direction(u8 mode)  //方向控制
{
  if(1==mode)
	{
	 GPIO_SetBits(GPIOC,GPIO_Pin_7);
	}
	else if(0==mode)
	{
	 GPIO_ResetBits(GPIOC,GPIO_Pin_7);
	}

}

void z_step_direction(u8 mode)  //Z方向控制
{
 if(1==mode)
	{
	 GPIO_SetBits(GPIOC,GPIO_Pin_8);
	}
	else if(0==mode)
	{
	 GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	}
}

u32 step_calculate(u16 distance)   //距离转化成脉冲(cm)
{
    return distance/one_pulse_dis;
}

u32 step_circle_pulse(u8 circle)   //圈数转化成脉冲数
{
	return circle*one_pulse;
}

u32 step_frv_motor(float frv) //频率计算   
{
	float f=2e-6;               //不是很准 后期改善算法
	u32 Frv;                    //>10HZ <250KHZ
	Frv=(1/(f*frv))-1;
  return Frv;
}


void step_circle_turn(u8 motor,u8 circle)  //控制电机转几圈
{
	if(motor==1)
	{
   x_need_Pluse=step_circle_pulse(circle);
	}else if(motor==2)
	{
	 y_need_Pluse=step_circle_pulse(circle);
	}
}

u8 x_step_angle(s16 angle,float frv)
{
	if(angle>=0)
	{
	  x_need_Pluse=one_angle_pluse*angle;
		x_step_direction(0);     //赋值方向
		frequency=step_frv_motor(frv);//由频率计算计数值
		x_step_motor_start();//开始驱动电机
	}
	else
	{
		x_need_Pluse=-(one_angle_pluse*angle);
		x_step_direction(1);     //赋值方向
		frequency=step_frv_motor(frv);//由频率计算计数值
		x_step_motor_start();//开始驱动电机
	}
	return 0;
}
u8 y_step_angle(s16 angle,float frv)  //Y轴方向距离控制.输入角度，方向，频率即可
{
	if(angle>=0)
	{
	  y_need_Pluse=one_angle_pluse*angle;
		y_step_direction(0);     //赋值方向
		frequency=step_frv_motor(frv);//由频率计算计数值
		y_step_motor_start();//开始驱动电机
	}
	else
	{
		y_need_Pluse=-(one_angle_pluse*angle);
		y_step_direction(1);     //赋值方向
		frequency=step_frv_motor(frv);//由频率计算计数值
		y_step_motor_start();//开始驱动电机
	}
	return 0;
}
u8 x_y_step_angle(s16 x_angle,s16 y_angle,float frv)
{
   x_step_angle(x_angle,frv);
   y_step_angle(y_angle,frv);
	 return 0;
}


u8 x_step_motor(u16 distance,u8 dir,float frv)  //X轴方向距离速度控制
{
  x_step_direction(dir);     //赋值方向
  x_need_Pluse=step_calculate(distance);//算出脉冲数
	frequency=step_frv_motor(frv);//由频率计算计数值
	x_step_motor_start();//开始驱动电机
	return 0;
}

u8 y_step_motor(u16 distance,u8 dir,float frv)  //Y轴方向距离速度控制
{
  y_step_direction(dir);     //赋值方向
  y_need_Pluse=step_calculate(distance);//算出脉冲数
	frequency=step_frv_motor(frv);//由频率计算计数值
	y_step_motor_start();//开始驱动电机
	return 0;
}

u8 z_step_motor(u16 distance,u8 dir,float frv)  //Y轴方向距离速度控制
{
  z_step_direction(dir);     //赋值方向
  z_need_Pluse=step_calculate(distance);//算出脉冲数
	frequency=step_frv_motor(frv);//由频率计算计数值
	z_step_motor_start();//开始驱动电机
	return 0;
}

///***未写完****/
//u8 back_zero(float frv) //回原点  只适用于相对定位函数之后
//{
//  if(x_sum_Pluse>=0)
//	{
//  	x_step_direction(0);     //赋值方向
//	  x_need_Pluse=x_sum_Pluse;//算出脉冲数
//		frequency=step_frv_motor(frv);//由频率计算计数值
//    x_step_motor_start();//开始驱动电机
//	}
//	else if(x_sum_Pluse<0)
//	{
//	  x_step_direction(1);     //赋值方向
//	  x_need_Pluse=-x_sum_Pluse;//算出脉冲数
//		frequency=step_frv_motor(frv);//由频率计算计数值
//    x_step_motor_start();//开始驱动电机
//	}
//	
////  if(y_sum_Pluse>=0)
////	{
////  	y_step_direction(0);     //赋值方向
////	  y_need_Pluse=y_sum_Pluse;//算出脉冲数
////		frequency=step_frv_motor(frv);//由频率计算计数值
////    y_step_motor_start();//开始驱动电机
////	}
////	else if(y_sum_Pluse<0)
////	{
////	  y_step_direction(1);     //赋值方向
////	  y_need_Pluse=-y_sum_Pluse;//算出脉冲数
////		frequency=step_frv_motor(frv);//由频率计算计数值
////    y_step_motor_start();//开始驱动电机
////	}

//}

void X_Locate_Rle(s16 distance,float frv) //X相对定位函数
{
	X_distance+=distance;
  if(distance>=0)
	{
		 x_step_motor(distance,0,frv);
//		 x_sum_Pluse+=x_need_Pluse;
	}else if(distance<0){ 
	 	 x_step_motor(-distance,1,frv);
//	   x_sum_Pluse-=x_need_Pluse;
	}
}

void Y_Locate_Rle(s16 distance,float frv) //Y相对定位函数
{
	Y_distance+=distance;
  if(distance>=0)
	{
		 y_step_motor(distance,0,frv);
//		 y_sum_Pluse+=y_need_Pluse;
	}else if(distance<0){ 
	 	y_step_motor(-distance,1,frv);
//	   y_sum_Pluse-=y_need_Pluse;
	}
}

void Z_Locate_Rle(s16 distance,float frv) //Z相对定位函数
{
 Z_distance+=distance;
 if(distance>=0)
	{
		 z_step_motor(distance,0,frv);
//		 z_sum_Pluse+=z_need_Pluse;
	}else if(distance<0){ 
	   z_step_motor(-distance,1,frv);
//	   z_sum_Pluse-=z_need_Pluse;
	}
}

void Locate_Rle(s16 distance,float frv,u8 motor_num) //相对定位函数
{
  if(motor_num==X)
	{
		X_Locate_Rle(distance,frv);
	}
	else if(motor_num==Y)
	{
		Y_Locate_Rle(distance,frv);
	}else if(motor_num==Z)
	{
    Z_Locate_Rle(distance,frv);
	}else if(motor_num==ALL)
	{
		X_Locate_Rle(distance,frv);
		Y_Locate_Rle(distance,frv);
    Z_Locate_Rle(distance,frv);
	}
}

void motor_start(s16 X_distance,float X_frequency,
	               s16 Y_distance,float Y_frequency,
								 s16 Z_distance,float Z_frequency)
{
	X_Locate_Rle(X_distance,X_frequency);
	Y_Locate_Rle(Y_distance,Y_frequency);
  Z_Locate_Rle(Z_distance,Z_frequency);
}

void back_zero(float frv)  //回原点
{
	x_step_motor(abs(X_distance),1,frv);
  y_step_motor(abs(Y_distance),1,frv);
	z_step_motor(abs(Z_distance),1,frv);
	X_distance=0;Y_distance=0;Z_distance=0;
}