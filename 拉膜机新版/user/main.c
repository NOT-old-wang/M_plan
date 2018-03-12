#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "exti.h"
#include  "time.h"
#include  "usart1.h"
#include  "shell.h"
#include "oled.h"
#include "step_motor.h"


extern vu32 frequency;
extern vu32 double_cycle;
extern vu32 double_pluse;

extern vu32 x_Pluse;
extern vu32 y_Pluse;
extern vu32 z_Pluse;

extern vu32 x_need_Pluse;
extern vu32 y_need_Pluse;
extern vu32 z_need_Pluse;


/*ʹ�õ���Դ   2�࣬128ϸ�֣�1.8�Ȳ����      ����2017/7/13
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
	usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART	time4
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ����();
//	LED_Init();
 while(1)
 {  		
     if(x_Pluse== x_need_Pluse)  x_step_motor_stop();	  //Ҫһֱתֻ��ע�͵����
	   if(y_Pluse== y_need_Pluse)  y_step_motor_stop();	  //Ҫһֱתֻ��ע�͵����
	   if(z_Pluse== z_need_Pluse)  z_step_motor_stop();	  //Ҫһֱתֻ��ע�͵����
    	key=KEY_Scan(0);	//�õ���ֵ
	   	if(key)
		{				   
			switch(key)
			{				 
				case KEY1_PRES:	//��ͣ
				 step_motor_STOP(); 
					break; 
				case KEY2_PRES:	//����	 
//				x_y_step_angle(45,-45,30000);
					break;
				case KEY3_PRES:	
				Locate_Rle(10,10000,X); //��Զ�λ���� X��10000HZ���ٶ�ǰ��10mm	
				Locate_Rle(20,20000,Y); //��Զ�λ���� Y��20000HZ���ٶ�ǰ��20mm
				Locate_Rle(30,30000,Z); //��Զ�λ���� Z��30000HZ���ٶ�ǰ��30mm
					break;
			  case KEY4_PRES:	//����	 
				Locate_Rle(-10,10000,X); //��Զ�λ���� X��10000HZ���ٶȺ���10mm	
				Locate_Rle(-20,20000,Y); //��Զ�λ���� Y��20000HZ���ٶȺ���20mm
				Locate_Rle(-30,30000,Z); //��Զ�λ���� Z��30000HZ���ٶȺ���30mm
					break;
				case KEY5_PRES:	   //�Զ�
					break;
			}
		}
 }
}
