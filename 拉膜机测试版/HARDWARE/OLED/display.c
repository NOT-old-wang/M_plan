#include "display.h"

//��������
long A_move_mm=0;
long B_move_mm=0;
long C_move_mm=0;

long A_move_speed=32000;  //Ĭ��20mm/s
long B_move_speed=32000;
long C_move_speed=32000;

char motor_type=0;//A:1  B:2  C:3 
#define A_moto 1
#define B_moto 2
#define C_moto 3


unsigned char  KeyFuncIndex=0;    //��ŵ�ǰ�Ĳ˵�����
unsigned char  KEY_TYPE=0;		  //��ǰ���µļ�ֵ����
void (*KeyFuncPtr)(void);            //���尴������ָ��


void ui_start(void)
{
	 switch(KEY_TYPE)
	{
		case  KEY1_PRES:			  
				All_motor_start();  //����
				break; 
		case  KEY2_PRES:	
        All_motor_stop();		//ֹͣ
				break; 
		case  KEY3_PRES:			 
				motor_distance();   //���λ�����ý���;
				break;
	  case  KEY4_PRES:		      
		    motor_speed();      //����ٶ����ý���
				break;
		case  KEY5_PRES:			 
				All_motor_back();	  //���� 
				break; 
		case  KEY6_PRES:			 
				motor_adjust();     //΢��
				break;
	  case  KEY7_PRES:		      
		    ;
				break; 
		default : 
				break;
				//�˴���Ӱ����������
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
		case  KEY1_PRES:			 //ȷ�� 
			goto out1; 
				break; 
		case  KEY3_PRES:			 	//(��һ��)
/*************************************/	
			while(1)
	    {
	     switch(KEY_TYPE)
	      {
				 case  KEY1_PRES:			 //ȷ�� 
			     goto out2;  
				     break; 
	       case  KEY3_PRES:			 //����
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
	       case  KEY4_PRES:		   //��С   
		     
				     break;
		     default : 
				     break;
	      }
				out2:break;
			}
/*************************************/	
				break;
	  case  KEY4_PRES:		      
		    //��С(��һ��)
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