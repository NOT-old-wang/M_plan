#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "exti.h"
#include "time.h"


int main()
{
	vu8 key=0;           
	delay_init();	    	 //延时函数初始化	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //设置NVIC中断分组2:2位抢占优先级，2位响应优先();
	LED_Init();
	relay = on;
	time6_Init(9999,7199);
	while(1)
	{  

	}
}
