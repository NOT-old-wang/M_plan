#ifndef  _led_h
#define _led_h
#include "sys.h"
void LED_Init(void);
int led_flicker(u8 number,u16 time_ms);
void led_set(u8 sta);
	
#define LED1 PFout(6)
#define LED2 PFout(7)
#define LED3 PFout(8)	
#define LED4 PFout(9)




#endif
