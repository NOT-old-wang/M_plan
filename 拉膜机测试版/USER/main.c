#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "led.h"	 
#include "usmart.h"	
#include "driver.h"


	
int main(void)
{	 
	u8 keyval;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	usmart_dev.init(72); 	//初始化USMART	
	LED_Init();			     //LED端口初始化
	KEY_Init();					//初始化按键
	Driver_Init_X();			//驱动器初始化
	Driver_Init_Y();			//驱动器初始化
  	
	TIM1_OPM_RCR_Init(999,72-1); //1MHz计数频率  单脉冲+重复计数模式
	TIM8_OPM_RCR_Init(999,72-1); //1MHz计数频率  单脉冲+重复计数模式
	
	while(1) 
	{		 	 	
//		keyval=KEY_Scan(0);
//		if(keyval==KEY1_PRES)
//		{
//			LED1=!LED1;
////			Locate_Rle_Y(25600,50000,CW);
//			Locate_Abs_Y(0,50000);//按下WKUP，回零点
//		}else if(keyval==KEY2_PRES)
//		{
//			LED2=!LED2;
//      Locate_Rle_Y(25600,100000,CW);
//		delay_ms(1000);
//		delay_ms(1000);
//		 Locate_Rle_Y(25600,100000,CCW);
//		 Locate_Rle_X(1,50000,CW);//按下KEY0，以500Hz的频率 顺时针发200脉冲
		 Y_angle(360,60000);
		delay_ms(500);
		Y_angle(-360,60000);
//		 Y_angle(-45,50000);
//		}else if(keyval==KEY3_PRES)
//		{
////			LED3=!LED3;
//////			Locate_Rle_Y(1,50000,CCW);//按下KEY1，以500Hz的频率 逆时针发400脉冲
//////			Locate_Rle_X(1,50000,CCW);//按下KEY1，以500Hz的频率 逆时针发400脉冲
////     XY_MOVE(25600,-12800,50000);
//		}			
	}			
}

