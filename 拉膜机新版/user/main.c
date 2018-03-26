#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "exti.h"
#include "time.h"
#include "usart1.h"
#include "shell.h"
#include "oled.h"
#include "step_motor.h"
#include "display.h"


vu32 x_Pluse = 0;
vu32 y_Pluse = 0;
vu32 z_Pluse = 0;

vu32 x_need_Pluse = 0;
vu32 y_need_Pluse = 0;
vu32 z_need_Pluse = 0;	


/*ʹ�õ���Դ   2�࣬32ϸ�֣�1.8�Ȳ����      ����2018/3/1
1Ȧ4mm
TIM5 TIM6 TIM7  --��������ʱ����ģ����Ʋ�����
�����޸�step_motor.h��ĺ궨��
TIM4--shell
���X:���壺PA6  ����pPC6     ע��ʹ�ܲ���Ҫ
���Y:���壺PA7  ����pPC7 
���Z:����: PA5  ����pPC8  
oled��PG13,14,15 PC0,1
key��PD1 2 3    
LED:PF6 7 8

*/
//�ô��ڷ�man��help������֪�������ʹ��
//ls ���г����пɿ��Ƶĺ���

void test_fun(void(*ledset)(u8),u8 sta)  //shell ���Ժ���
{
	ledset(sta);
}  	


int main()
{
	vu8 key=0;           
	delay_init();	    	 //��ʱ������ʼ��	
  KEY_Init();	
	step_motor_init();   //���������ʼ��
  uart1_init(115200);
//	usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART	time4
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ����();
 while(1)
 {  		
     if(x_Pluse== x_need_Pluse)  x_step_motor_stop();	  //Ҫһֱתֻ��ע�͵����
	   if(y_Pluse== y_need_Pluse)  y_step_motor_stop();	  //Ҫһֱתֻ��ע�͵����
	   if(z_Pluse== z_need_Pluse)  z_step_motor_stop();	  //Ҫһֱתֻ��ע�͵����
    	key=KEY_Scan(0);	//�õ���ֵ			   
			switch(key)
			{				 
				case KEY1_PRES:	//����	 
				Locate_Rle(20,20000,X); //��Զ�λ���� 	50mm  20000HZ���ٶ�  X��
				Locate_Rle(20,20000,Y);
				Locate_Rle(20,20000,Z);  
					break; 
				case KEY2_PRES:	//����
//				back_zero(10000);
				Locate_Rle(-20,20000,X); 
				Locate_Rle(-20,20000,Y); 
				Locate_Rle(-20,20000,Z); 	
					break;
				case KEY3_PRES:	//����1
				Locate_Rle(10,10000,X); 
				Locate_Rle(10,10000,Y); 
				Locate_Rle(10,10000,Z); 
					break;
			  case KEY4_PRES:	//����2 
				Locate_Rle(30,30000,X); 
				Locate_Rle(30,30000,Y); 
				Locate_Rle(30,30000,Z); 
					break;
				case KEY5_PRES:	//����3
//				Locate_Rle(30,30000,X); 
//				Locate_Rle(30,30000,Y); 
//				Locate_Rle(30,30000,Z); 
					break;
				case KEY6_PRES:	//��ͣ
				step_motor_STOP();
					break;
//			  case KEY8_PRES:	//X����ת
//				x_step_motor(8,0,4500);
//				case KEY9_PRES:	//X�ᷴת
//				x_step_motor(8,1,4500);	
//					break;
//				case KEY10_PRES:	//Y����ת
//			  y_step_motor(8,0,4500);
//					break;
//			  case KEY11_PRES://Y�ᷴת	 
//				y_step_motor(8,1,4500);
//					break;
//				case KEY12_PRES://Z����ת
//				z_step_motor(8,0,4500);
//					break;
//				case KEY13_PRES://Z����ת
//				z_step_motor(8,1,4500);
//					break;
			}
		
 }
}
