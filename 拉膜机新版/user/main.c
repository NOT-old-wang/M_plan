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

/***********返回参数在这里修改*************/
#define back_speed	5000
/*****************************************/

/***********3x3参数在这里修改*************/
#define x_y_dis_size3_3     150      //150mm
#define x_y_speed3_3        5000    //10000hz
#define p_size3_3           1.311    //比例
#define z_speed3_3          p_size3_3 * x_y_speed3_3
#define z_dis_size3_3       x_y_dis_size3_3 * p_size3_3
/****************************************/

/***********3x3.5参数在这里修改*************/
#define x_dis_size3_5     150      //150mm
#define y_dis_size3_5     185      //185mm
#define z_dis_size3_5     197      //197mm
#define x_speed3_5        5000     //5000hz
#define y_speed3_5        ((float)y_dis_size3_5/(float)x_dis_size3_5)*x_speed3_5  
#define z_speed3_5        ((float)z_dis_size3_5/(float)x_dis_size3_5)*x_speed3_5 
/****************************************/

vu32 x_Pluse = 0;
vu32 y_Pluse = 0;
vu32 z_Pluse = 0;


vu32 x_need_Pluse = 0;
vu32 y_need_Pluse = 0;
vu32 z_need_Pluse = 0;	

extern s16 X_distance;
extern s16 Y_distance;
extern s16 Z_distance;

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
void control(void);
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
		       Locate_Rle(5,5000,X); 
			     Locate_Rle(5,5000,Y);
			     Locate_Rle(5,5000,Z); 
           delay_ms(500);				
			break; 
			
			case KEY2_PRES:	//返回
	  			 
			     back_zero(back_speed); 
           delay_ms(500);				
			break;
			
			case KEY3_PRES:	//功能1  3x3
		       Locate_Rle(x_y_dis_size3_3,x_y_speed3_3,X); 
			     Locate_Rle(x_y_dis_size3_3,x_y_speed3_3,Y);
			     Locate_Rle(z_dis_size3_3  ,z_speed3_3  ,Z); 
				   delay_ms(500);					
			break;
			  
			case KEY4_PRES:	//功能2  3x3.5
				   Locate_Rle(x_dis_size3_5,x_speed3_5,X); 
				   Locate_Rle(y_dis_size3_5,y_speed3_5,Y); 
				   Locate_Rle(z_dis_size3_5,z_speed3_5,Z); 
           delay_ms(500);	
			break;
			
			case KEY5_PRES:	//功能3
           step_motor_STOP();  
			break;
			
		  case KEY6_PRES:	//急停
				   step_motor_STOP();
			break;
			  
			case KEY8_PRES:	//X轴正转
			     Locate_Rle(200,5000,X); 
				   delay_ms(500);
			break;
			
			case KEY9_PRES:	//X轴反转
				   Locate_Rle(-200,5000,X);
				   delay_ms(500);
			break;
			
			case KEY10_PRES:	//Y轴正转
			     Locate_Rle(200,5000,Y); 
				   delay_ms(500);
			break;
			     
			case KEY11_PRES://Y轴反转	 
				   Locate_Rle(-200,5000,Y);
				   delay_ms(500);
			break;
				
			case KEY12_PRES://Z轴正转
				   Locate_Rle(200,5000,Z);
				   delay_ms(500);
			break;
				
			case KEY13_PRES://Z轴正转
				   Locate_Rle(-200,5000,Z);
				   delay_ms(500);
			break;
	}	
}
