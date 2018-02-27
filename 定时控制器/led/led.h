#ifndef  _led_h
#define _led_h
#include "sys.h"
void LED_Init(void);

#define on 1
#define off 0

#define relay PFout(6)
#define LED PFout(7)





#endif
