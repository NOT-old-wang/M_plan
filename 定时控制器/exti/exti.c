#include "exti.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "time.h"

void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

	  key1_Init();
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //下降沿触发
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

  
}

//外部中断0服务程序 
void EXTI1_IRQHandler(void)
{
//  LED1=0;
	EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE0上的中断标志位  
}