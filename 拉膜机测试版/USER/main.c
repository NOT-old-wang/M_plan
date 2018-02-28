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
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	usmart_dev.init(72); 	//初始化USMART	
	LED_Init();			     //LED端口初始化
	KEY_Init();					//初始化按键
	Driver_Init_A();			//驱动器初始化
	Driver_Init_Y();			//驱动器初始化
  	
	TIM1_OPM_RCR_Init(999,72-1); //1MHz计数频率  单脉冲+重复计数模式
	TIM8_OPM_RCR_Init(999,72-1); //1MHz计数频率  单脉冲+重复计数模式
	
	while(1) 
	{	
		LED1=0;
		keyval=KEY_Scan(0);
		if(keyval==KEY1_PRES)
		{
			LED1=1;
			Locate_Abs_A(0,32000);//按下WKUP，回零点 0.8cm/s
		}else if(keyval==KEY2_PRES)
		{
			LED1=1;
      A_abs_distance(30,32000);// 2cm/s 前进30mm
		}else if(keyval==KEY3_PRES)
		{
			LED1=1;
			A_rle_distance(5,32000);
		}			
	}			
}

