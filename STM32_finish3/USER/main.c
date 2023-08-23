#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "sys.h"
#include "beep.h"
#include "exti.h"
#include "usart.h"
#include "Net_Things.h"
#include "usart.h"
#include "string.h"
#include "DS18B20.h"
#include "pwm.h"
#include "task.h"
#include "temp.h"
#include "motor.h"

//LED    		PB5 PE5
//BEEP   		PB8
//KEY     	PA0 PE2 PE3 PE4
//USART   	PA9 PA10 PB2 PB3
//DS18B20 	PB15
//MOTOR     M1 PB13 M2 PB14
//PTC       T1 PA11  T2 PA12
//PWM       PB5



u8 DS18B20_ROM[8]; //���DS18B20��64ΪROM����

// void Delay(u32 count)
// {
//   u32 i=0;
//   for(;i<count;i++);
// }
 
 int main(void)
 {
	 
//	float temp;
//	u16 i;
	 
	delay_init();	    	 //��ʱ������ʼ��	
	 TIM4_Init();	 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	uart2_init(115200);
UnConnect();
	 
	Net_Things_Init();

 	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	BEEP_Init();         	//��ʼ���������˿�
	KEY_Init();         	//��ʼ���밴�����ӵ�Ӳ���ӿ�
	EXTIX_Init();		 	//�ⲿ�жϳ�ʼ��
	 DS18B20_Init();   //DS18B20��ʼ��
	 FEN_Init();
	 MOTOR_Init();
	 TEMP_Init();
//	LED0=0;					//����LED0

//	PubTopic("you can hear me?");
//	Property_Post(26,31);
	 
	TIM3_PWM_Init(899,0);	 //����Ƶ��PWMƵ��=72000000/900=80Khz,���ڵĵ���
fuc_TASK();
	 
  while(1)
	{
//		i=PWM_Breath(300);
//		printf("%d\r\n",i);
//		USART_SendData(USART2,"AT");
//		Usart_SendString();
//		delay_ms(1000);	
//		temp=DS18B20_GetTemp();
//		printf("temp=%f\r\n",temp);
		
//		delay_ms(1000);
		

	}
 }
 


