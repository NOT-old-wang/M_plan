#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "led.h"	 
#include "usmart.h"	
#include "driver.h"
#include "oled.h"

/*ʹ�õ���Դ 
������
 KEY1 PEin(0)		//��ȡKEY1      ����
 KEY2 PEin(1)		//��ȡKEY2      ֹͣ  
 KEY3 PEin(2)		//��ȡKEY3      ����(��һ��)
 KEY4 PEin(3)		//��ȡKEY4      ��С(��һ��)
 KEY5 PEin(4)		//��ȡKEY5      ���� 
 KEY6 PEin(7)		//��ȡKEY6      ΢��(��)
 KEY7 PEin(8)		//��ȡKEY7      ΢��(��)

OLED: 3.3v  
D0(SCLK)--PC0 | D1(SDIN)--PC1 | RST--PG15 | DS-- PD3| CS--PD6 | RST--PG15

A��
//DRIVER_DIR_A   PE12
//DRIVER_OE_A    PE13
//STEP_PULSE_A   PA11 (TIM1_CH4)
*/
	
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

