#include "key.h"
#include "delay.h"
#include "led.h"


void key1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;//内部上拉
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}


u8 key1(u8 mode)
{
 static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY1==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1==0)return KEY1_PRES;
	}else if(KEY1==1)key_up=1; 	    
 	return 0;// 无按键按下
}
u8 key2(u8 mode)
{

  return 0;
}

