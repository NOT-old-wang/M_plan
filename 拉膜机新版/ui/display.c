#include "display.h"
#include "step_motor.h"

//变量定义
extern vu32 x_Pluse;
extern vu32 y_Pluse;
extern vu32 z_Pluse;

extern vu32 x_need_Pluse;
extern vu32 y_need_Pluse;
extern vu32 z_need_Pluse;


s16 X_move_mm=0;
s16 Y_move_mm=0;
s16 Z_move_mm=0;

float X_move_speed=32000;  //默认20mm/s
float Y_move_speed=32000;
float Z_move_speed=32000;

char motor_type=0;//A:1  B:2  C:3 
#define A_moto 1
#define B_moto 2
#define C_moto 3


u8  KEY_TYPE=0;		  //当前按下的键值类型


void ui_start(void)
{
	if(x_Pluse== x_need_Pluse)  x_step_motor_stop();	  //要一直转只需注释掉这句
	if(y_Pluse== y_need_Pluse)  y_step_motor_stop();	  //要一直转只需注释掉这句
	if(z_Pluse== z_need_Pluse)  z_step_motor_stop();	  //要一直转只需注释掉这句
  
	KEY_TYPE=KEY_Scan(0);
	 switch(KEY_TYPE)
	{
		case  KEY1_PRES:
       motor_start(X_move_mm,X_move_speed,
	                 Y_move_mm,Y_move_speed,
								   Z_move_mm,Z_move_speed);  //启动
		    main_window();
				break; 
		case  KEY2_PRES:	
//        step_motor_STOP(); //电机急停
		   motor_start(-X_move_mm,X_move_speed,
	                 -Y_move_mm,Y_move_speed,
								   -Z_move_mm,Z_move_speed); //返回
		    main_window();
				break; 
		case  KEY3_PRES:			 
				motor_distance();   //电机位移设置界面;
				break;
	  case  KEY4_PRES:		      
		    motor_speed();      //电机速度设置界面
				break;
		case  KEY5_PRES:			 
//				All_motor_back();	  //归零 
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
	OLED_ShowString(12,20,"project-M",24);
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
				 case A_moto: X_move_mm++; if(X_move_mm>=180) X_move_mm=180;
					 break;
				 case B_moto: Y_move_mm++; if(Y_move_mm>=180) Y_move_mm=180;
					 break;
				 case C_moto: Z_move_mm++; if(Z_move_mm>=180) Z_move_mm=180;
					 break;
			 }
			 motor_distance_window();
			 break;
		case  KEY4_PRES:		   //减小  
			 switch(motor_type)
			 {
				 case A_moto: X_move_mm--; if(X_move_mm<=0) X_move_mm=0;
					 break;
				 case B_moto: Y_move_mm--; if(Y_move_mm<=0) Y_move_mm=0;
					 break;
				 case C_moto: Z_move_mm--; if(Z_move_mm<=0) Z_move_mm=0;
					 break;
			 }
			 motor_distance_window();
			 break;
   case  KEY2_PRES:		   //选择电机 
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
	
	OLED_ShowString(3,20,"motor X:",12); 
	OLED_ShowNum(55,20,X_move_mm,3,12);
	OLED_ShowString(80,20,"mm",12);

	OLED_ShowString(3,35,"motor Y:",12); 
	OLED_ShowNum(55,35,Y_move_mm,3,12);
	OLED_ShowString(80,35,"mm",12);
	
	OLED_ShowString(3,50,"motor Z:",12); 
	OLED_ShowNum(55,50,Z_move_mm,3,12);
	OLED_ShowString(80,50,"mm",12);
	
	OLED_Refresh_Gram();		//更新显示到OLED 
}

void motor_speed()
{
	motor_speed_window();
	while(1)
	{
		KEY_TYPE=KEY_Scan(0);
	  switch(KEY_TYPE)
	 {
		case  KEY1_PRES:			 //确认 
			goto out2; 
				break; 
		case  KEY3_PRES:			 	//增大
			 switch(motor_type)
			 {
				 case A_moto: X_move_speed+=100; 
					 break;
				 case B_moto: Y_move_speed+=100;
					 break;
				 case C_moto: Z_move_speed+=100; 
					 break;
			 }
			 motor_speed_window();
			 break;
		case  KEY4_PRES:		   //减小  
			 switch(motor_type)
			 {
				 case A_moto: X_move_speed-=100; 
					 break;
				 case B_moto: Y_move_speed-=100;
					 break;
				 case C_moto: Z_move_speed-=100; 
			 }
			 motor_speed_window();
			 break;
   case  KEY2_PRES:		   //选择电机 
			 	 if(motor_type<4) motor_type+=1;
	       if(motor_type==4) motor_type=1;
	       delay_ms(400);
	   	 break;
				
	 default : 
				 break;
	 }
//	delay_ms(100);
	}
	out2:;
	
}

void motor_speed_window()
{
//	u16 a=20;
	OLED_Clear();
	OLED_ShowString(3,5,"motor_speed",12);
	
	OLED_ShowString(3,20,"motor X:",12); 
	OLED_ShowNum(55,20,X_move_speed,5,12);
	OLED_ShowString(80,20,"mm/s",12);

	OLED_ShowString(3,35,"motor Y:",12); 
	OLED_ShowNum(55,35,Y_move_speed,5,12);
	OLED_ShowString(80,35,"mm/s",12);
	
	OLED_ShowString(3,50,"motor Z:",12); 
	OLED_ShowNum(55,50,Z_move_speed,5,12);
	OLED_ShowString(80,50,"mm/s",12);
	
	OLED_Refresh_Gram();		//更新显示到OLED 

}

void motor_adjust()     //微调
{

}

void Start(void)
{
	 OLED_Clear();
	 OLED_ShowString(20,20,"start",24);
	 OLED_Refresh_Gram();		//更新显示到OLED 
   delay_ms(1800);
}

