#include "key.h"
#include "delay.h"
#include "led.h"
#include "step_motor.h"

void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0
	                              |GPIO_Pin_1
	                              |GPIO_Pin_2
	                              |GPIO_Pin_3
	                              |GPIO_Pin_4
	                              |GPIO_Pin_7
	                              |GPIO_Pin_8
	                              |GPIO_Pin_9
	                              |GPIO_Pin_10
	                              |GPIO_Pin_11
	                              |GPIO_Pin_12;//KEY
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE


}
//按键处理函数
//返回按键值
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按	
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0||KEY6==0||KEY7==0
		||KEY8==0||KEY9==0||KEY10==0||KEY11==0||KEY12==0||KEY13==0))
	{
		delay_ms(10);//去抖动 
		if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(KEY3==0)return KEY3_PRES;
		else if(KEY4==0)return KEY4_PRES;
		else if(KEY5==0)return KEY5_PRES;
		else if(KEY6==0)return KEY6_PRES;
		else if(KEY7==0)return KEY7_PRES;
		else if(KEY8==0)return KEY8_PRES;
		else if(KEY9==0)return KEY9_PRES;
		else if(KEY10==0)return KEY10_PRES;
		else if(KEY11==0)return KEY11_PRES;
		else if(KEY12==0)return KEY12_PRES;
		else if(KEY13==0)return KEY13_PRES;
		
	}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1&&KEY6==1&&KEY7==1
					 &&KEY8==1&&KEY9==1&&KEY10==1&&KEY11==1&&KEY12==1&&KEY13==1) key_up=1; 
 	return 0;// 无按键按下
}


