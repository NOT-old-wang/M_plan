/*-----------------------------------------------
���ƣ��������ʾ����ң������(1-9)��ֵ

���ݣ�������ң�����ϵ�1-9��������������϶�Ӧ��ʾ,ע����������û�з�Ӧ�ġ�
------------------------------------------------*/
#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char   

sbit ir=P3^2;
  
sbit LED_GPIO=P3^4;  
sfr P3M0 = 0xB2;
sfr P3M1 = 0xB1;



//sbit dula=P2^6;
//sbit wela=P2^7;
uchar irtime;
bit irprosok,irok;
uchar irtime;

//uchar code table_du[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};// ��ʾ����ֵ0~9
uchar irtime;
bit irprosok,irok;
uchar ircode[4];
uchar irdata[33];
uchar startflag;
uchar  bitnum;

void timer0init(void)//��ʱ��0��ʼ�� 256*(1/12m)*12=0.256ms
{

  TMOD=0x02;//��ʱ��0������ʽ2��TH0����װֵ��TL0�ǳ�ֵ
  TH0=0x00; //����ֵ
  TL0=0x00; //��ʼ��ֵ
  ET0=1;    //���ж�
  TR0=1;    
}


void tim0_isr (void) interrupt 1 using 1  //��ʱ��0�жϷ�����
{
  irtime++;  //���ڼ���2���½���֮���ʱ��
}


void int0init(void)  //�ⲿ�ж�0��ʼ��
{
 IT0 = 1;   //ָ���ⲿ�ж�0�½��ش�����INT0 (P3.2)
 EX0 = 1;   //ʹ���ⲿ�ж�
 EA = 1;    //�����ж�
}


void int0 () interrupt 0 //�ⲿ�ж�0������
{
if(startflag)
 {
  if(irtime>32&&irtime<63)  //8-16ms
	{
	   bitnum=0;
	}
	irdata[bitnum]=irtime;
	irtime=0;
	bitnum++;
	if(bitnum==33)
	  {
	   bitnum=0;
	   irok=1;
	  }
 }
else
 {
 irtime=0;
 startflag=1;
 }
}


void irpros(void) // ������ֵ����
{
	uchar mun,k,i,j;
	k=1;
	for(j=0;j<4;j++)
	{
		for(i=0;i<8;i++)
		{
			mun=mun>>1;
			if(irdata[k]>6)
			{
				mun=mun | 0x80;
			}
				k++;
		}
		ircode[j]=mun;
	}
	irprosok=1;
}


void ir_work(void) //�����ֵ����
{
	switch(ircode[2])   //�жϵ���������ֵ
	         {
			 case 0x0c:LED_GPIO = 1; 
//			 P0=table_du[1];
			 break;//1 ��ʾ��Ӧ�İ���ֵ
			 case 0x18:LED_GPIO = 0; 
//			 P0=table_du[2];
			 break;//2
//			 case 0x5e:P0=table_du[3];break;//3
//			 case 0x08:P0=table_du[4];break;//4
//			 case 0x1c:P0=table_du[5];break;//5
//			 case 0x5a:P0=table_du[6];break;//6
//			 case 0x42:P0=table_du[7];break;//7
//			 case 0x52:P0=table_du[8];break;//8
//			 case 0x4a:P0=table_du[9];break;//9
             default:break;
			 }
		  irprosok=0;//������ɱ�־
  }


void main(void)
{
 int0init(); //��ʼ���ⲿ�ж�
 timer0init();//��ʼ����ʱ��
 P3M0 = 0x10;		 //P3.4ǿ�������
 P3M1 = 0x00;		 //P3.4ǿ�������
  LED_GPIO = 0;
//  P0=0x00; //���������
//  wela=1;      //λ����
//  wela=0;

 while(1)//��ѭ��
   {
    if(irok)       //������պ��˽��к��⴦��
	  {   
	   irpros();
 	   irok=0;
	  }
//	LED_GPIO = 1;
    if(irprosok)  //�������ú���й�������
	  {
	   ir_work();
  	  }
   }
}
  
  