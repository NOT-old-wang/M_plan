#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "exti.h"
#include "time.h"
#include "usart1.h"
#include "shell.h"
#include "oled.h"
#include "step_motor.h"
#include "display.h"

/***********参数在这里修改*************/
#define x_y_dis_size     150      //150mm
#define x_y_speed        20000    //20000hz
#define p_size           1.311    //比例
#define z_speed          p_size*x_y_speed
#define z_dis_size       x_y_dis_size*p_size
/**************************************/

vu32 x_Pluse = 0;
vu32 y_Pluse = 0;
vu32 z_Pluse = 0;

vu32 x_need_Pluse = 0;
vu32 y_need_Pluse = 0;
vu32 z_need_Pluse = 0;	

vu8 key=0;

/*使用的资源   2相，32细分，1.8度步距角      老王2018/3/1
1圈4mm
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
void control();
void test_fun(void(*ledset)(u8),u8 sta)  //shell 测试函数
{
	ledset(sta);
}  	

int main()
{           
	delay_init();	    	 //延时函数初始化	
  KEY_Init();	
	step_motor_init();   //步进电机初始化
  uart1_init(115200);
//	usmart_dev.init(SystemCoreClock/1000000);	//初始化USMART	time4
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //设置NVIC中断分组2:2位抢占优先级，2位响应优先();
 while(1)
 {  		
   control();
 }
}



void control()
{
	key=KEY_Scan(0);	//得到键值			   
	switch(key)
	{				 
			case KEY1_PRES:	//启动	 
		       Locate_Rle(x_y_dis_size,x_y_speed,X); 
			     Locate_Rle(x_y_dis_size,x_y_speed,Y);
			     Locate_Rle(z_dis_size  ,z_speed  ,Z); 
           delay_ms(500);				
			break; 
			
			case KEY2_PRES:	//返回
				   back_zero(20000);
           delay_ms(500);				
			break;
			
			case KEY3_PRES:	//功能1
				   Locate_Rle(30,25000,X); 
				   Locate_Rle(30,25000,Y); 
				   Locate_Rle(30,25000,Z);
				   delay_ms(500);					
			break;
			  
			case KEY4_PRES:	//功能2 
				   Locate_Rle(50,25000,X); 
				   Locate_Rle(50,25000,Y); 
				   Locate_Rle(50,25000,Z); 
           delay_ms(500);					
			break;
			
			case KEY5_PRES:	//功能3
           step_motor_STOP(); 
			break;
			
		  case KEY6_PRES:	//急停
				   step_motor_STOP();
			break;
			  
			case KEY8_PRES:	//X轴正转
			     x_step_motor(8,0,10000);
				   delay_ms(500);
			case KEY9_PRES:	//X轴反转
				   x_step_motor(8,1,10000);	
				   delay_ms(500);
			break;
				
			case KEY10_PRES:	//Y轴正转
			     y_step_motor(8,0,10000);
				   delay_ms(500);
			break;
			     
			case KEY11_PRES://Y轴反转	 
				   y_step_motor(8,1,10000);
				   delay_ms(500);
			break;
				
			case KEY12_PRES://Z轴正转
				   z_step_motor(8,0,10000);
				   delay_ms(500);
			break;
				
			case KEY13_PRES://Z轴正转
				   z_step_motor(8,1,10000);
				   delay_ms(500);
			break;
	}	
}
