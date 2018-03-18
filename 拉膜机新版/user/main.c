#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "exti.h"
#include  "time.h"
#include  "usart1.h"
#include  "shell.h"
#include "oled.h"
#include "step_motor.h"
#include "display.h"


extern vu32 x_Pluse;
extern vu32 y_Pluse;
extern vu32 z_Pluse;

extern vu32 x_need_Pluse;
extern vu32 y_need_Pluse;
extern vu32 z_need_Pluse;


/*使用的资源   2相，32细分，1.8度步距角      老王2018/3/1
TIM5 TIM6 TIM7  --的两个定时器来模拟控制步进，
可以修改step_motor.h里的宏定义
TIM4--shell
电机X:脉冲：PA6  方向PC6     注：使能不需要
电机Y:脉冲：PA7  方向PC7 
电机Z:脉冲: PA5  方向PC8  
oled：PG13,14,15 PC0,1
key：PD1 2 3    
LED:PF6 7 8

*/
//用串口发man或help，即可知道程序的使用
//ls 可列出所有可控制的函数

void test_fun(void(*ledset)(u8),u8 sta)  //shell 测试函数
{
	ledset(sta);
}  	


int main()
{
	vu8 key=0;           
	delay_init();	    	 //延时函数初始化	
  KEY_Init();	
	step_motor_init();   //步进电机初始化
  uart1_init(115200);
	usmart_dev.init(SystemCoreClock/1000000);	//初始化USMART	time4
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //设置NVIC中断分组2:2位抢占优先级，2位响应优先();
//	LED_Init();
 while(1)
 {  		
     if(x_Pluse== x_need_Pluse)  x_step_motor_stop();	  //要一直转只需注释掉这句
	   if(y_Pluse== y_need_Pluse)  y_step_motor_stop();	  //要一直转只需注释掉这句
	   if(z_Pluse== z_need_Pluse)  z_step_motor_stop();	  //要一直转只需注释掉这句
    	key=KEY_Scan(0);	//得到键值
	   	if(key)
		{				   
			switch(key)
			{				 
				case KEY1_PRES:	//急停
				 step_motor_STOP(); 
					break; 
				case KEY2_PRES:	//启动	 
					break;
				case KEY3_PRES:	
				Locate_Rle(20,20000,X); //相对定位函数 	20mm  20000HZd的速度  X轴
				Locate_Rle(20,20000,Y); //相对定位函数 
				Locate_Rle(30,30000,Z); //相对定位函数 
					break;
			  case KEY4_PRES:	//测试	 
				Locate_Rle(-20,20000,X); 
				Locate_Rle(-20,20000,Y); 
				Locate_Rle(-30,20000,Z); 
					break;
				case KEY5_PRES:	//自动
					break;
			}
		}
 }
}
