#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "led.h"	 
#include "usmart.h"	
#include "driver.h"
#include "oled.h"
#include "display.h"

/*使用的资源 
按键：
 KEY1 PEin(0)		//读取KEY1      启动
 KEY2 PEin(1)		//读取KEY2      停止  
 KEY3 PEin(2)		//读取KEY3      增大(下一个)
 KEY4 PEin(3)		//读取KEY4      减小(上一个)
 KEY5 PEin(4)		//读取KEY5      归零 
 KEY6 PEin(7)		//读取KEY6      微调(进)
 KEY7 PEin(8)		//读取KEY7      微调(退)

OLED: 3.3v  
D0(SCLK)--PC0 | D1(SDIN)--PC1 | DC-- PD3| CS--PD6 | RST--PG15

A轴
//DRIVER_DIR_A   PE12
//DRIVER_OE_A    PE13
//STEP_PULSE_A   PA11 (TIM1_CH4)

量程:0-18mm
*/	
int main(void)
{	 
	u8 keyval;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	usmart_dev.init(72); 	//初始化USMART	
	LED_Init();			     //LED端口初始化
	OLED_Init();
	KEY_Init();					//初始化按键
	Driver_Init_A();			//驱动器初始化
	Driver_Init_Y();			//驱动器初始化
	main_window();
//	motor_speed_window();
	TIM1_OPM_RCR_Init(999,72-1); //1MHz计数频率  单脉冲+重复计数模式
	TIM8_OPM_RCR_Init(999,72-1); //1MHz计数频率  单脉冲+重复计数模式
	while(1) 
	{	
		ui_start();
//		LED1=0;
//		keyval=KEY_Scan(0);
//		if(keyval==KEY1_PRES)
//		{
//			LED1=1;
//			Locate_Abs_A(0,32000);//按下WKUP，回零点 0.8cm/s
//		}else if(keyval==KEY2_PRES)
//		{
//			LED1=1;
//      A_abs_distance(30,32000);// 2cm/s 前进30mm
//		}else if(keyval==KEY3_PRES)
//		{
//			LED1=1;
//			A_rle_distance(5,32000);
//		}			
	}			
}

