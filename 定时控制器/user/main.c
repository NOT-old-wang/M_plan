#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "exti.h"
#include "time.h"


int main()
{
	vu8 key=0;           
	delay_init();	    	 //��ʱ������ʼ��	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ����();
	LED_Init();
	relay = on;
	time6_Init(9999,7199);
	while(1)
	{  

	}
}
