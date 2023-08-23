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



u8 DS18B20_ROM[8]; //存放DS18B20的64为ROM编码

// void Delay(u32 count)
// {
//   u32 i=0;
//   for(;i<count;i++);
// }
 
 int main(void)
 {
	 
//	float temp;
//	u16 i;
	 
	delay_init();	    	 //延时函数初始化	
	 TIM4_Init();	 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	uart2_init(115200);
UnConnect();
	 
	Net_Things_Init();

 	LED_Init();		  		//初始化与LED连接的硬件接口
	BEEP_Init();         	//初始化蜂鸣器端口
	KEY_Init();         	//初始化与按键连接的硬件接口
	EXTIX_Init();		 	//外部中断初始化
	 DS18B20_Init();   //DS18B20初始化
	 FEN_Init();
	 MOTOR_Init();
	 TEMP_Init();
//	LED0=0;					//点亮LED0

//	PubTopic("you can hear me?");
//	Property_Post(26,31);
	 
	TIM3_PWM_Init(899,0);	 //不分频。PWM频率=72000000/900=80Khz,周期的倒数
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
 


