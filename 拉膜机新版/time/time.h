#ifndef time_h
#define time_h
#include "stm32f10x.h"

//TIM3->CR1&=0xfe;    //关闭定时器3
//TIM3->CR1|=0x01;    //开启定时器3    TIMx->CNT=你要的值，装初值

void time5_Init(u16 arr,u16 psc);
void time6_Init(u16 arr,u16 psc);
void time7_Init(u16 arr,u16 psc);



#endif
