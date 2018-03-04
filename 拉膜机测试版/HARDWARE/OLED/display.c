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


u8  KEY_TYPE=0;		  //当前按下的键值类型


void ui_start(void)
{
  KEY_TYPE=KEY_Scan(0);
	 switch(KEY_TYPE)
	{
		case  KEY1_PRES:			  
				All_motor_start(A_move_mm,B_move_mm,C_move_mm);  //启动
		    Welcome();
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
	OLED_Clear();
	OLED_ShowString(20,20,"M-project",24);
	OLED_Refresh_Gram();		//更新显示到OLED 
  delay_ms(1800);
}

void motor_distance()
{
	motor_distance_window();
	while(1)
	{
		KEY_TYPE=KEY_Scan(0);
	  switch(KEY_TYPE)
	 {
		case  KEY1_PRES:			 //确认 
			goto out1; 
				break; 
		case  KEY3_PRES:			 	//增大
			 switch(motor_type)
			 {
				 case A_moto: A_move_mm++; if(A_move_mm>=180) A_move_mm=180;
					 break;
				 case B_moto: B_move_mm++; if(B_move_mm>=180) B_move_mm=180;
					 break;
				 case C_moto: C_move_mm++; if(C_move_mm>=180) C_move_mm=180;
					 break;
			 }
			 motor_distance_window();
			 break;
		case  KEY4_PRES:		   //减小  
			 switch(motor_type)
			 {
				 case A_moto: A_move_mm--; if(A_move_mm<=0) A_move_mm=0;
					 break;
				 case B_moto: B_move_mm--; if(B_move_mm<=0) B_move_mm=0;
					 break;
				 case C_moto: C_move_mm--; if(C_move_mm<=0) C_move_mm=0;
					 break;
			 }
			 motor_distance_window();
			 break;
   case  KEY7_PRES:		   //选择电机 
			 	 if(motor_type<4) motor_type+=1;
	       if(motor_type==4) motor_type=1;
	       delay_ms(400);
	   	 break;
				
	 default : 
				 break;
	 }
	delay_ms(100);
	}
	out1:;
}

void motor_distance_window()
{
	OLED_Clear();
	OLED_ShowString(3,5,"motor_distance",12);
	
	OLED_ShowString(3,20,"motor A:",12); 
	OLED_ShowNum(55,20,A_move_mm,3,12);
	OLED_ShowString(80,20,"mm",12);

	OLED_ShowString(3,35,"motor B:",12); 
	OLED_ShowNum(55,35,B_move_mm,3,12);
	OLED_ShowString(80,35,"mm",12);
	
	OLED_ShowString(3,50,"motor C:",12); 
	OLED_ShowNum(55,50,C_move_mm,3,12);
	OLED_ShowString(80,50,"mm",12);
	
	OLED_Refresh_Gram();		//更新显示到OLED 
}

void motor_speed()
{
	
}

void motor_speed_window()
{
	u16 a=20;
	OLED_Clear();
	OLED_ShowString(3,5,"motor_speed",12);
	
	OLED_ShowString(3,20,"motor A:",12); 
	OLED_ShowNum(55,20,a,3,12);
	OLED_ShowString(80,20,"mm/s",12);

	OLED_ShowString(3,35,"motor B:",12); 
	OLED_ShowNum(55,35,a,3,12);
	OLED_ShowString(80,35,"mm/s",12);
	
	OLED_ShowString(3,50,"motor C:",12); 
	OLED_ShowNum(55,50,a,3,12);
	OLED_ShowString(80,50,"mm/s",12);
	
	OLED_Refresh_Gram();		//更新显示到OLED 

}

void motor_adjust()     //微调
{

}

void Welcome(void)
{
	 OLED_Clear();
	 OLED_ShowString(20,20,"Welcome",24);
	 OLED_Refresh_Gram();		//更新显示到OLED 
   delay_ms(1800);
}