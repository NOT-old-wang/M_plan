#ifndef time_h
#define time_h
#include "stm32f10x.h"

//TIM3->CR1&=0xfe;    //�رն�ʱ��3
//TIM3->CR1|=0x01;    //������ʱ��3    TIMx->CNT=��Ҫ��ֵ��װ��ֵ
void time3_Init(u16 arr,u16 psc);
void time4_Init(u16 arr,u16 psc);
void time5_Init(u16 arr,u16 psc);
void time6_Init(u16 arr,u16 psc);

void time3_PWM_Init(u16 arr,u16 psc);
void time4_PWM_Init(u16 arr,u16 psc);

#endif
