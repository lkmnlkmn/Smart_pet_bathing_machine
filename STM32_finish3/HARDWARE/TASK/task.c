/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx����
  * @UpdateTime   2023/4/3   ljd
  ******************************************************************************
*/ 


#include "stm32f10x.h"
#include "task.h"
#include "pwm.h"
#include "temp.h"
#include "motor.h"
#include "Net_Things.h"
#include "DS18B20.h"
#include "stdio.h"
#include "tim.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "string.h"
#include "led.h"
#include "sys.h"
#include "beep.h"
#include "string.h"


//#define TIME_WASH1 300 //5*60
//#define TIME_WASH2 120 //2*60
//#define TIME_WASH3 600 //10*60
//#define TIME_HAIR  1200 //20*60
#define TIME_WASH1 39 //5*60
#define TIME_WASH2 39 //2*60
#define TIME_WASH3 39 //10*60
#define TIME_HAIR  39 //20*60


int TASK=0;
int T1,T2,M1,M2,FEN;


int sec1,min1,hour1;
extern int sec;

int temp_low = TEMPLOW;
int temp_max = TEMPMAX;

int mode;

int LightSwitch;
float temp;

int ex1;

int post1=0;
int post2=0;
int post3=0;
	
int sta1,sta2;

extern int get_data;
extern u8 RX_Data[400];
extern int TASK1;
void platform_data_handle(char * buff){  //���ܼ��
	
	char * p;
	
			if((p=strstr(buff,"\"tempmin\":")))
			{temp_low=(*(p+10)-48)*10+*(p+11)-48;
			printf("  %d\r\n",temp_low);}
			
			if((p=strstr(buff,"\"tempmax\":")))
			{temp_max=(*(p+10)-48)*10+*(p+11)-48;
			printf("  %d\r\n",temp_max);}
			
			if((p=strstr(buff,"\"tempopen\":1")))
			{TASK=TEST_TEMP;sta1=0;LED0=1;printf("��ˮ");PubTopicinfo2(temp,TASK,sta1,sta2);}
			
			if((p=strstr(buff,"\"workopen\":1")))
			{TASK=WASH1;sta2=0;LED1=1;printf("����");LED1=!LED1;PubTopicinfo2(temp,TASK,sta1,sta2);}
			
		}
void fuc_temp(void){

	 temp=DS18B20_GetTemp();
	 printf("temp=%f\r\n",temp);
}

void fuc_TEST_TEMP(void) //����ˮ�º��ʶ� 35���¼��� 37����ֹͣ���� �м�ʱ�̵ȴ���һ��
{

	if(TASK==TEST_TEMP)         //��һ��ˮ�¼����� �����ˮ�׶�
	{
		if(temp<temp_low){
			T1_ON;  //����
			T1=UP_TEMP1;
		}else if(temp>temp_max){
			T1_OFF;
			T1=DOWN_TEMP1;
		}else{
			T1=WAIT_TEMP1; 

		}
	}else{										//֮�����ˮ�¼����� �����ʺ�ˮ�µ�������֮�����
		if(temp<temp_low+0.5){
		T1_ON;  //����
		T1=UP_TEMP1;
	}else if(temp>temp_max-0.5){
		T1_OFF;
		T1=DOWN_TEMP1;
	}else{
		T1=WAIT_TEMP1;   
		}
	}
}

void fuc_WASH1(int state)  //��һ�γ�ˮ
{
	if(M1!=OPEN_M1&&!state){  //�����û������δ���
		M1_ON;
		M1=OPEN_M1;
	}else if(state){
		M1_OFF;
		M1=CLOSE_M1;
		TASK=WASH2;   
	}
}

void fuc_WASH2(int state)  //����ԡ¶
{
	if(M2!=OPEN_M2&&!state){
		M2_ON;
		M2=OPEN_M2;
	}else if(state){
		M2_OFF;
		M2=CLOSE_M2;
		TASK=WASH3;  //����ȥ2���Ӻ� �����ϴ�׶�
	}
}

void fuc_WASH3(int state)  //�ڶ��γ�ˮ
{
	if(M1!=OPEN_M1&&!state){
		M1_ON;
		M1=OPEN_M1;
		
	}else if(state){
		M1_OFF;
		M1=CLOSE_M1;
		
		TASK=HAIR;  //����ȥ10���Ӻ� ���봵�ɽ׶�
	}
}

void fuc_HAIR(int state)
{
	if((T2!=UP_TEMP2||FEN!=OPEN_HAIR) && !state){
		T2_ON;
		FEN_ON;
		T2=UP_TEMP2;
		FEN=OPEN_HAIR;
	}else if(state){
		FEN_OFF;
		T2_OFF;
		T2=DOWN_TEMP2;
		FEN=CLOSE_HAIR;
	
		TASK=SEND_DATA;  //����ȥ30���Ӻ� ��������׶�
	}
}

void fuc_SEND_DATA(void) //��������
{
	delay_ms(1);
	post3=1;
	TASK=OVER;
}

void fuc_OVER(void)  //����
{
//	TIM_Cmd(TIM4, DISABLE);	//�ر��ж�
	int i;
	for(i=0;i<5;i++){BEEP=!BEEP;delay_ms(1000);BEEP=!BEEP;delay_ms(100);}

	fuc_init();

	LED1=0;
	

}

void fuc_EX(void)
{
if(ex1){
	M1_OFF;
	M1=CLOSE_M1;
	M2_OFF;
	M2=CLOSE_M2;
	FEN_OFF;
	FEN=CLOSE_HAIR;
	T2_OFF;
	T2=DOWN_TEMP2;
}else{
TASK=TASK1;
TASK1=0;
switch(TASK)
		{
			case WASH1:	 	 M1_ON;M1=OPEN_M1;break;
			case WASH2:		 M2_ON;M2=OPEN_M2;break;
			case WASH3:		 M1_ON;M1=OPEN_M1;break;
			case HAIR: 		 T2_ON;FEN_ON;T2=UP_TEMP2;FEN=OPEN_HAIR;break;  
			default: break;
}

}
}

void fuc_DIRECTORY(void) //��task������� ȷ��������һ��
{

	fuc_temp();

	if(TASK==NOTHING){sta1=1;LED0=0;}
	if(TASK==TEST_TEMP&&T1==WAIT_TEMP1){sta2=1;LED1=0;}
	
	if(sec%20==0){post1=1;}
	if(sec%20==1){post2=1;}
	if(sec%20==2){post3=1;}
	if(TASK!=NOTHING){
	fuc_TEST_TEMP(); //�����Ƿ����
	LightSwitch=1;		
//	
//	if(TASK==NOTHING){sec1=0;}
	sec1++;
//	printf("second %d-%d-%d\r\n",sec1/1440,sec1/60-sec1/1440,sec1%60);
	}

	
	switch(TASK)
		{
			case WASH1:		 printf("WASH1��%d\r\n",sec1); if(sec1<TIME_WASH1){fuc_WASH1(keep);}else if(sec1==TIME_WASH1){fuc_WASH1(finish);sec1=0;}break; //��ˮ1
			case WASH2:		 printf("WASH2��%d\r\n",sec1); if(sec1<TIME_WASH2){fuc_WASH2(keep);}else if(sec1==TIME_WASH2){fuc_WASH2(finish);sec1=0;}break;
			case WASH3:		 printf("WASH3��%d\r\n",sec1); if(sec1<TIME_WASH3){fuc_WASH3(keep);}else if(sec1==TIME_WASH3){fuc_WASH3(finish);sec1=0;}break;
			case HAIR: 		 printf(" HAIR��%d\r\n",sec1); if(sec1<TIME_HAIR) {fuc_HAIR(keep);} else if(sec1==TIME_HAIR) {fuc_HAIR(finish); sec1=0;}break;
			case SEND_DATA:printf("SENDDATA\r\n");fuc_SEND_DATA();break; 
			case OVER:		 printf("OVER\r\n");fuc_OVER();break; 
			case EX:       printf("EXIT\r\n");fuc_EX();sec1--;break;
			default: sec1=0;break;
		}
	
}

void fuc_init(void)
{
	//��ʼ��
	//����ˮ�·�Χ
	FEN_Init();
	MOTOR_Init();
	TEMP_Init();
	
	temp_low=TEMPLOW;
	temp_max=TEMPMAX;
	//��ʼ����������ʱ��
	sec1=0;
	min1=0;
	hour1=0;
	
	sec=0;  //��ʱ�� ����
	T1=DOWN_TEMP1;
	T2=DOWN_TEMP2;
	M1=CLOSE_M1;
	M2=CLOSE_M2;
	FEN=CLOSE_HAIR;
	LightSwitch=0;
	
	TASK=NOTHING;
	
	sta1=0;
	sta2=0;
	LED0=!sta1;
	LED1=!sta2;

}
void fuc_TASK(void)
{
	fuc_init();
	delay_ms(1000);//����	
	TIM_Cmd(TIM4, ENABLE);  										//ʹ��TIMx	
	while(1)
	{
		if(post1){Property_Post(LightSwitch,temp,M1);post1=0;}
		if(post2){Property_Post2(M2,T1,FEN);post2=0;}
		
		
		if(post3){PubTopicinfo2(temp,TASK,sta1,sta2);post3=0;}
		if(get_data!=0){
		printf("\r\n");
		platform_data_handle((char *)RX_Data);
		get_data=0;
		}
			
//		if(sec%10==0){
//		printf("111\r\n");
//		printf("222\r\n");
//		printf("333\r\n");
//		Property_Post(LightSwitch,temp,M1);
//		delay_ms(500);//����		
//		Property_Post2(M2,T1,FEN);
//		delay_ms(500);//����		
//	}
		delay_us(1);//����
	}
}

	

	
	
//#define finish   1
//#define keep    0

//LED    		PB5 PE5
//BEEP   		PB8
//KEY     	PA0 PE2 PE3 PE4
//USART   	PA9 PA10 PB2 PB3
//DS18B20 	PB15
//MOTOR     M1 PB13 M2 PB14
//PTC       T1 PB8  T2 PB9
//PWM       PB5

//#define CONECT					1 //�����ƶ�
//#define TEST_TEMP				2 //����ˮ��  ��ʱ��ִ�� ��Ҫ�Ӽ�ʱ����
////#define UP_TEMP1						3
////#define DOWN_TEMP1					4
//
//#define WASH1						3 //��һ�μ�ˮ��ϴ
////#define OPEN_M1							5
////#define CLOSE_M1     				6
//#define WASH2						4	//�ڶ��μ���ԡ¶
////#define OPEN_M2      				7
///#define CLOSE_M2						8
//#define WASH3						5	//�����μ�ˮ��ϴ
//#define HAIR						6 //����
////#define OPEN_HAIR      				9
////#define CLOSE_HAIR     				10
////#define UP_TEMP2      				11
////#define DOWN_TEMP2    				12
//#define OVER						7 //��ɲ���
//#define SEND_DATA				8 //�ϴ��������
//#define NOTHING					0 //�����κ���
