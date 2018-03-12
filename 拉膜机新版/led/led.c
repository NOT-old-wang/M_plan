#include "led.h"
#include "delay.h"


void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);//使能GPIO时钟
	
	//初始化GPIO PF6,7,8
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	GPIO_SetBits(GPIOF,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9); //上电0输出
	   
}

int led_flicker(u8 number,u16 time_ms)  //闪灯，也可模拟PWM
{
	u8 t;
	for(t=0;t<number;t++)
	{
		LED1=0; 
		delay_ms(time_ms);
    LED1=1;	
		delay_ms(time_ms);
	}
	return 0;
}

void led_set(u8 sta)
{
	LED1=sta;
	LED2=sta;
} 

