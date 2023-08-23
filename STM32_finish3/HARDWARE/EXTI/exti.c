#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "beep.h"
#include "Net_Things.h"
#include "task.h"

/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx驱动
  * @UpdateTime   2023/4/3   ljd
  ******************************************************************************
*/  

//外部中断0服务程序


extern int T1,TASK,sta1,sta2,temp,con,ex1;
int TASK1=0;
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	按键端口初始化

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

    //GPIOE.2 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOE.3	  中断线以及中断初始化配置 下降沿触发 //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOE.4	  中断线以及中断初始化配置  下降沿触发	//KEY0
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


   //GPIO	E.1	  中断线以及中断初始化配置 上升沿触发 PE3  KEY3
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource1); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
}

//外部中断1服务程序 
void EXTI1_IRQHandler(void)  //S4
{
	delay_ms(10);//消抖
	if(KEY3==0)	 	 //按键KEY3
	{		
		if(con){BEEP=!BEEP;delay_ms(10);BEEP=!BEEP;UnConnect();printf("断开\r\n");   //连接网络
			}else{
		BEEP=!BEEP;delay_ms(10);BEEP=!BEEP;Net_Things_Init();printf("连接\r\n");}


		
		
	}
	EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE0上的中断标志位  
}
 
//外部中断2服务程序
void EXTI2_IRQHandler(void)  //S3
{
	delay_ms(10);//消抖
	if(KEY2==0)	  //按键KEY2
	{
		if(TASK!=EX){BEEP=!BEEP;delay_ms(10);BEEP=!BEEP;TASK1=TASK;TASK=EX;ex1=1;}
		else{BEEP=!BEEP;delay_ms(10);BEEP=!BEEP;ex1=0;}



	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE2上的中断标志位  
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)   //S2
{
	delay_ms(10);//消抖
	if(KEY1==0)	 //按键KEY1
	{		
		if(T1==WAIT_TEMP1){TASK=WASH1;sta2=0;printf("工作\r\n");PubTopicinfo2(temp,TASK,sta1,sta2);LED1=1;}
	BEEP=!BEEP;delay_ms(10);BEEP=!BEEP;


	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}

void EXTI4_IRQHandler(void)  //S1
{
	delay_ms(10);//消抖
	if(KEY0==0)	 //按键KEY0
	{
		TASK=TEST_TEMP;sta1=0;printf("加热\r\n");PubTopicinfo2(temp,TASK,sta1,sta2);LED0=1;BEEP=!BEEP;delay_ms(10);BEEP=!BEEP;

		
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE4上的中断标志位  
}
 
