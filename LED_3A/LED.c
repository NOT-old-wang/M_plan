/*-----------------------------------------------
名称：数码管显示红外遥控器中(1-9)键值

内容：按配套遥控器上的1-9按键会在数码管上对应显示,注意其它按键没有反应的。
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

//uchar code table_du[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};// 显示段码值0~9
uchar irtime;
bit irprosok,irok;
uchar ircode[4];
uchar irdata[33];
uchar startflag;
uchar  bitnum;

void timer0init(void)//定时器0初始化 256*(1/12m)*12=0.256ms
{

  TMOD=0x02;//定时器0工作方式2，TH0是重装值，TL0是初值
  TH0=0x00; //重载值
  TL0=0x00; //初始化值
  ET0=1;    //开中断
  TR0=1;    
}


void tim0_isr (void) interrupt 1 using 1  //定时器0中断服务函数
{
  irtime++;  //用于计数2个下降沿之间的时间
}


void int0init(void)  //外部中断0初始化
{
 IT0 = 1;   //指定外部中断0下降沿触发，INT0 (P3.2)
 EX0 = 1;   //使能外部中断
 EA = 1;    //开总中断
}


void int0 () interrupt 0 //外部中断0服务函数
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


void irpros(void) // 红外码值处理
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


void ir_work(void) //红外键值处理
{
	switch(ircode[2])   //判断第三个数码值
	         {
			 case 0x0c:LED_GPIO = 1; 
//			 P0=table_du[1];
			 break;//1 显示相应的按键值
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
		  irprosok=0;//处理完成标志
  }


void main(void)
{
 int0init(); //初始化外部中断
 timer0init();//初始化定时器
 P3M0 = 0x10;		 //P3.4强推挽输出
 P3M1 = 0x00;		 //P3.4强推挽输出
  LED_GPIO = 0;
//  P0=0x00; //数码管清屏
//  wela=1;      //位锁存
//  wela=0;

 while(1)//主循环
   {
    if(irok)       //如果接收好了进行红外处理
	  {   
	   irpros();
 	   irok=0;
	  }
//	LED_GPIO = 1;
    if(irprosok)  //如果处理好后进行工作处理
	  {
	   ir_work();
  	  }
   }
}
  
  