#include "display.h"

//变量定义
long A_move_mm=0;
long B_move_mm=0;
long C_move_mm=0;

long A_move_speed=32000;  //默认20mm/s
long B_move_speed=32000;
long C_move_speed=32000;

char motor_type=0;//A:1  B:2  C:3 
#define A_moto 1
#define B_moto 2
#define C_moto 3


unsigned char  KeyFuncIndex=0;    //存放当前的菜单索引
unsigned char  KEY_TYPE=0;		  //当前按下的键值类型
void (*KeyFuncPtr)(void);            //定义按键功能指针


void ui_start(void)
{
	 switch(KEY_TYPE)
	{
		case  KEY1_PRES:			  
				All_motor_start();  //启动
				break; 
		case  KEY2_PRES:	
        All_motor_stop();		//停止
				break; 
		case  KEY3_PRES:			 
				motor_distance();   //电机位移设置界面;
				break;
	  case  KEY4_PRES:		      
		    motor_speed();      //电机速度设置界面
				break;
		case  KEY5_PRES:			 
				All_motor_back();	  //归零 
				break; 
		case  KEY6_PRES:			 
				motor_adjust();     //微调
				break;
	  case  KEY7_PRES:		      
		    ;
				break; 
		default : 
				break;
				//此处添加按键错误代码
	}
	
}

void main_window()
{
	
}

void motor_distance()
{
	motor_distance_window();
	while(1)
	{
	  switch(KEY_TYPE)
	 {
		case  KEY1_PRES:			 //确认 
			goto out1; 
				break; 
		case  KEY3_PRES:			 	//(下一个)
/*************************************/	
			while(1)
	    {
	     switch(KEY_TYPE)
	      {
				 case  KEY1_PRES:			 //确认 
			     goto out2;  
				     break; 
	       case  KEY3_PRES:			 //增大
			   	   switch(motor_type)
						 {
							 case A_moto: A_move_mm++;
								 break;
							 case B_moto: B_move_mm++;
								 break;
							 case C_moto: C_move_mm++;
								 break;
						 }
						 motor_distance_window();
			       break;
	       case  KEY4_PRES:		   //减小   
		     
				     break;
		     default : 
				     break;
	      }
				out2:break;
			}
/*************************************/	
				break;
	  case  KEY4_PRES:		      
		    //减小(上一个)
				break;
		default : 
				break;
			
	 }
	}
	out1:;
}

void motor_distance_window()
{

}

void motor_speed()
{

}