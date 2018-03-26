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

void step_motor_init()  //�����ʼ��
{
	 
	//����ܽų�ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOʱ��
	//��ʼ��GPIO PA6,7
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;  //��© !!!!!
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//����ܽų�ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��GPIOʱ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;  //��© !!!!!
//  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  //���� !!!!!
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
	//���ʹ�ܹܽ�
  
	 TIM6->CR1&=0xfe;    //�رն�ʱ��6	 
	 TIM7->CR1&=0xfe;    //�رն�ʱ��7	
	 TIM5->CR1&=0xfe;    //�رն�ʱ��5	 
}

void x_step_motor_start() //X�������
{
//	frequency=step_frv_motor(25600);//������--1��1Ȧ
//	frequency=step_frv_motor(100000);//�ӽ���������
	time6_Init(frequency,71);
//	while(x_need_Pluse!=x_Pluse);
}

void y_step_motor_start() //Y�������
{
//	frequency=step_frv_motor(25600);//������--1��1Ȧ
//	frequency=step_frv_motor(100000);//�ӽ���������
	time7_Init(frequency,71);
//	while(y_need_Pluse!=y_Pluse);
}

void z_step_motor_start() //Z�������
{
	time5_Init(frequency,71);
}


void x_step_motor_stop() //X���ֹͣ
{
	x_Pluse=0;x_need_Pluse=0;frequency=0;
//  GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	TIM6->CR1&=0xfe;    //�رն�ʱ��6		
}

void y_step_motor_stop() //Y���ֹͣ
{
	y_Pluse=0;y_need_Pluse=0;frequency=0;
//  GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	TIM7->CR1&=0xfe;    //�رն�ʱ��7
}

void z_step_motor_stop() //Y���ֹͣ
{
	z_Pluse=0;z_need_Pluse=0;frequency=0;
//  GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	TIM5->CR1&=0xfe;    //�رն�ʱ��7
}


void step_motor_STOP() //�����ͣ
{
	x_Pluse=0;y_Pluse=0; x_need_Pluse=0;y_need_Pluse=0; frequency=0;
//  GPIO_ResetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_9);//ʹ�ܶ˸�λ 
	TIM6->CR1&=0xfe;    //�رն�ʱ��6	 
  TIM7->CR1&=0xfe;    //�رն�ʱ��7
	TIM5->CR1&=0xfe;    //�رն�ʱ��5
	
}

void x_step_direction(u8 mode)  //�������
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
void y_step_direction(u8 mode)  //�������
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

void z_step_direction(u8 mode)  //Z�������
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

u32 step_calculate(u16 distance)   //����ת��������(cm)
{
    return distance/one_pulse_dis;
}

u32 step_circle_pulse(u8 circle)   //Ȧ��ת����������
{
	return circle*one_pulse;
}

u32 step_frv_motor(float frv) //Ƶ�ʼ���   
{
	float f=2e-6;               //���Ǻ�׼ ���ڸ����㷨
	u32 Frv;                    //>10HZ <250KHZ
	Frv=(1/(f*frv))-1;
  return Frv;
}


void step_circle_turn(u8 motor,u8 circle)  //���Ƶ��ת��Ȧ
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
		x_step_direction(0);     //��ֵ����
		frequency=step_frv_motor(frv);//��Ƶ�ʼ������ֵ
		x_step_motor_start();//��ʼ�������
	}
	else
	{
		x_need_Pluse=-(one_angle_pluse*angle);
		x_step_direction(1);     //��ֵ����
		frequency=step_frv_motor(frv);//��Ƶ�ʼ������ֵ
		x_step_motor_start();//��ʼ�������
	}
	return 0;
}
u8 y_step_angle(s16 angle,float frv)  //Y�᷽��������.����Ƕȣ�����Ƶ�ʼ���
{
	if(angle>=0)
	{
	  y_need_Pluse=one_angle_pluse*angle;
		y_step_direction(0);     //��ֵ����
		frequency=step_frv_motor(frv);//��Ƶ�ʼ������ֵ
		y_step_motor_start();//��ʼ�������
	}
	else
	{
		y_need_Pluse=-(one_angle_pluse*angle);
		y_step_direction(1);     //��ֵ����
		frequency=step_frv_motor(frv);//��Ƶ�ʼ������ֵ
		y_step_motor_start();//��ʼ�������
	}
	return 0;
}
u8 x_y_step_angle(s16 x_angle,s16 y_angle,float frv)
{
   x_step_angle(x_angle,frv);
   y_step_angle(y_angle,frv);
	 return 0;
}


u8 x_step_motor(u16 distance,u8 dir,float frv)  //X�᷽������ٶȿ���
{
  x_step_direction(dir);     //��ֵ����
  x_need_Pluse=step_calculate(distance);//���������
	frequency=step_frv_motor(frv);//��Ƶ�ʼ������ֵ
	x_step_motor_start();//��ʼ�������
	return 0;
}

u8 y_step_motor(u16 distance,u8 dir,float frv)  //Y�᷽������ٶȿ���
{
  y_step_direction(dir);     //��ֵ����
  y_need_Pluse=step_calculate(distance);//���������
	frequency=step_frv_motor(frv);//��Ƶ�ʼ������ֵ
	y_step_motor_start();//��ʼ�������
	return 0;
}

u8 z_step_motor(u16 distance,u8 dir,float frv)  //Y�᷽������ٶȿ���
{
  z_step_direction(dir);     //��ֵ����
  z_need_Pluse=step_calculate(distance);//���������
	frequency=step_frv_motor(frv);//��Ƶ�ʼ������ֵ
	z_step_motor_start();//��ʼ�������
	return 0;
}

///***δд��****/
//u8 back_zero(float frv) //��ԭ��  ֻ��������Զ�λ����֮��
//{
//  if(x_sum_Pluse>=0)
//	{
//  	x_step_direction(0);     //��ֵ����
//	  x_need_Pluse=x_sum_Pluse;//���������
//		frequency=step_frv_motor(frv);//��Ƶ�ʼ������ֵ
//    x_step_motor_start();//��ʼ�������
//	}
//	else if(x_sum_Pluse<0)
//	{
//	  x_step_direction(1);     //��ֵ����
//	  x_need_Pluse=-x_sum_Pluse;//���������
//		frequency=step_frv_motor(frv);//��Ƶ�ʼ������ֵ
//    x_step_motor_start();//��ʼ�������
//	}
//	
////  if(y_sum_Pluse>=0)
////	{
////  	y_step_direction(0);     //��ֵ����
////	  y_need_Pluse=y_sum_Pluse;//���������
////		frequency=step_frv_motor(frv);//��Ƶ�ʼ������ֵ
////    y_step_motor_start();//��ʼ�������
////	}
////	else if(y_sum_Pluse<0)
////	{
////	  y_step_direction(1);     //��ֵ����
////	  y_need_Pluse=-y_sum_Pluse;//���������
////		frequency=step_frv_motor(frv);//��Ƶ�ʼ������ֵ
////    y_step_motor_start();//��ʼ�������
////	}

//}

void X_Locate_Rle(s16 distance,float frv) //X��Զ�λ����
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

void Y_Locate_Rle(s16 distance,float frv) //Y��Զ�λ����
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

void Z_Locate_Rle(s16 distance,float frv) //Z��Զ�λ����
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

void Locate_Rle(s16 distance,float frv,u8 motor_num) //��Զ�λ����
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

void back_zero(float frv)  //��ԭ��
{
	x_step_motor(abs(X_distance),1,frv);
  y_step_motor(abs(Y_distance),1,frv);
	z_step_motor(abs(Z_distance),1,frv);
	X_distance=0;Y_distance=0;Z_distance=0;
}