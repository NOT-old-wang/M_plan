#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "led.h"	 
#include "usmart.h"	
#include "driver.h"


	
int main(void)
{	 
	u8 keyval;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	usmart_dev.init(72); 	//��ʼ��USMART	
	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();					//��ʼ������
	Driver_Init_X();			//��������ʼ��
	Driver_Init_Y();			//��������ʼ��
  	
	TIM1_OPM_RCR_Init(999,72-1); //1MHz����Ƶ��  ������+�ظ�����ģʽ
	TIM8_OPM_RCR_Init(999,72-1); //1MHz����Ƶ��  ������+�ظ�����ģʽ
	
	while(1) 
	{		 	 	
//		keyval=KEY_Scan(0);
//		if(keyval==KEY1_PRES)
//		{
//			LED1=!LED1;
////			Locate_Rle_Y(25600,50000,CW);
//			Locate_Abs_Y(0,50000);//����WKUP�������
//		}else if(keyval==KEY2_PRES)
//		{
//			LED2=!LED2;
//      Locate_Rle_Y(25600,100000,CW);
//		delay_ms(1000);
//		delay_ms(1000);
//		 Locate_Rle_Y(25600,100000,CCW);
//		 Locate_Rle_X(1,50000,CW);//����KEY0����500Hz��Ƶ�� ˳ʱ�뷢200����
		 Y_angle(360,60000);
		delay_ms(500);
		Y_angle(-360,60000);
//		 Y_angle(-45,50000);
//		}else if(keyval==KEY3_PRES)
//		{
////			LED3=!LED3;
//////			Locate_Rle_Y(1,50000,CCW);//����KEY1����500Hz��Ƶ�� ��ʱ�뷢400����
//////			Locate_Rle_X(1,50000,CCW);//����KEY1����500Hz��Ƶ�� ��ʱ�뷢400����
////     XY_MOVE(25600,-12800,50000);
//		}			
	}			
}

