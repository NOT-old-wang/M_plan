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

/***********���ز����������޸�*************/
#define back_speed	5000
/*****************************************/

/***********3x3�����������޸�*************/
#define x_y_dis_size3_3     150      //150mm
#define x_y_speed3_3        5000    //10000hz
#define p_size3_3           1.311    //����
#define z_speed3_3          p_size3_3 * x_y_speed3_3
#define z_dis_size3_3       x_y_dis_size3_3 * p_size3_3
/****************************************/

/***********3x3.5�����������޸�*************/
#define x_dis_size3_5     150      //150mm
#define y_dis_size3_5     185      //185mm
#define z_dis_size3_5     197      //197mm
#define x_speed3_5        5000     //5000hz
#define y_speed3_5        ((float)y_dis_size3_5/(float)x_dis_size3_5)*x_speed3_5  
#define z_speed3_5        ((float)z_dis_size3_5/(float)x_dis_size3_5)*x_speed3_5 
/****************************************/

vu32 x_Pluse = 0;
vu32 y_Pluse = 0;
vu32 z_Pluse = 0;


vu32 x_need_Pluse = 0;
vu32 y_need_Pluse = 0;
vu32 z_need_Pluse = 0;	

extern s16 X_distance;
extern s16 Y_distance;
extern s16 Z_distance;

vu8 key=0;

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
void control(void);
void test_fun(void(*ledset)(u8),u8 sta)  //shell ���Ժ���
{
	ledset(sta);
}  	

int main()
{           
	delay_init();	    	 //��ʱ������ʼ��	
  KEY_Init();	
	step_motor_init();   //���������ʼ��
  uart1_init(115200);
//	usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART	time4
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ����();
 while(1)
 {  		
   control();
 }
}



void control()
{
	key=KEY_Scan(0);	//�õ���ֵ			   
	switch(key)
	{				 
			case KEY1_PRES:	//����	 
		       Locate_Rle(5,5000,X); 
			     Locate_Rle(5,5000,Y);
			     Locate_Rle(5,5000,Z); 
           delay_ms(500);				
			break; 
			
			case KEY2_PRES:	//����
	  			 
			     back_zero(back_speed); 
           delay_ms(500);				
			break;
			
			case KEY3_PRES:	//����1  3x3
		       Locate_Rle(x_y_dis_size3_3,x_y_speed3_3,X); 
			     Locate_Rle(x_y_dis_size3_3,x_y_speed3_3,Y);
			     Locate_Rle(z_dis_size3_3  ,z_speed3_3  ,Z); 
				   delay_ms(500);					
			break;
			  
			case KEY4_PRES:	//����2  3x3.5
				   Locate_Rle(x_dis_size3_5,x_speed3_5,X); 
				   Locate_Rle(y_dis_size3_5,y_speed3_5,Y); 
				   Locate_Rle(z_dis_size3_5,z_speed3_5,Z); 
           delay_ms(500);	
			break;
			
			case KEY5_PRES:	//����3
           step_motor_STOP();  
			break;
			
		  case KEY6_PRES:	//��ͣ
				   step_motor_STOP();
			break;
			  
			case KEY8_PRES:	//X����ת
			     Locate_Rle(200,5000,X); 
				   delay_ms(500);
			break;
			
			case KEY9_PRES:	//X�ᷴת
				   Locate_Rle(-200,5000,X);
				   delay_ms(500);
			break;
			
			case KEY10_PRES:	//Y����ת
			     Locate_Rle(200,5000,Y); 
				   delay_ms(500);
			break;
			     
			case KEY11_PRES://Y�ᷴת	 
				   Locate_Rle(-200,5000,Y);
				   delay_ms(500);
			break;
				
			case KEY12_PRES://Z����ת
				   Locate_Rle(200,5000,Z);
				   delay_ms(500);
			break;
				
			case KEY13_PRES://Z����ת
				   Locate_Rle(-200,5000,Z);
				   delay_ms(500);
			break;
	}	
}
