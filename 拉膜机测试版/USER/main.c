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
	Driver_Init_A();			//��������ʼ��
	Driver_Init_Y();			//��������ʼ��
  	
	TIM1_OPM_RCR_Init(999,72-1); //1MHz����Ƶ��  ������+�ظ�����ģʽ
	TIM8_OPM_RCR_Init(999,72-1); //1MHz����Ƶ��  ������+�ظ�����ģʽ
	
	while(1) 
	{	
		LED1=0;
		keyval=KEY_Scan(0);
		if(keyval==KEY1_PRES)
		{
			LED1=1;
			Locate_Abs_A(0,32000);//����WKUP������� 0.8cm/s
		}else if(keyval==KEY2_PRES)
		{
			LED1=1;
      A_abs_distance(30,32000);// 2cm/s ǰ��30mm
		}else if(keyval==KEY3_PRES)
		{
			LED1=1;
			A_rle_distance(5,32000);
		}			
	}			
}

