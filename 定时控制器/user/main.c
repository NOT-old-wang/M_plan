#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "exti.h"
#include  "time.h"
//static uint32_t t;
//void dawang_ms();
//void delay();
int main()
{
	vu8 key=0;           
	delay_init();	    	 //延时函数初始化	 
//	key1_Init
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //设置NVIC中断分组2:2位抢占优先级，2位响应优先();
	LED_Init();
// 	time3_PWM_Init(899,0);	 //不分频。PWM频率=72000000/900=80Khz
	time4_PWM_Init(100,72);	 //不分频。PWM频率=72000000/900=80Khz
//	time3_Init(10000,7200); 
//	  time4_Init(10000,7200);
//	time5_Init(5000,7200); 
//	time6_Init(10000,7200);
	EXTIX_Init();         	//初始化外部中断输入 
	while(1)
	{  
//    TIM_SetCompare1(TIM4,10);
//		TIM_SetCompare2(TIM4,30);
//		TIM_SetCompare3(TIM4,50);
//		TIM_SetCompare4(TIM4,90);
//		LED1=0; 
//		delay_ms(500);
//    LED1=1;	
//		delay_ms(500);
	}
}
