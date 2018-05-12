#include "time.h"
#include "led.h"
#include "delay.h"

unsigned int time_flag=0;
#define time_hour 3600
#define time_min 60

// 基本T6
void time6_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //时钟使能
	
	//定时器TIM6初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); //使能指定的TIM6中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM6, ENABLE);  //使能TIM6					 
}

void TIM6_IRQHandler(void)   //TIM6中断
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //检查TIM6更新中断发生与否
		{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //清除TIMx更新中断标志 
		time_flag++;
		LED=!LED;
		}
	if(time_flag == 5*time_hour)
		relay = off;
}


