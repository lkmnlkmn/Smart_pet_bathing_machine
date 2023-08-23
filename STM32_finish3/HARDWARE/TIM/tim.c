/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx驱动
  * @UpdateTime   2023/4/3   ljd
  ******************************************************************************
*/ 

#include "delay.h"
#include "tim.h"
#include "usart.h"
#include "led.h"
#include "task.h"

int sec=0;
int time=0;

void TIM4_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 			//时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = 1000;		 				//自动重装载寄存器周期的值1/CK_CNT=1us,1000x1us=1ms	
	TIM_TimeBaseStructure.TIM_Prescaler =71; 						//设置用来作为TIMx时钟频率除数的预分频值CK_CNT=CK_INT/(71+1)=1MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		//TIM_CKD_DIV1是.h文件中已经定义好的，TIM_CKD_DIV1=0，也就是时钟分频因子为0
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 				//根据指定的参数初始化TIMx的时间基数单位
	
	//中断初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 				//设置NVIC中断分组2:2位抢占优先级，2位响应优先级	
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  				//TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  		//先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  			//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  								//初始化NVIC寄存器
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE );						 //使能指定的TIM4中断,允许更新中断
	
	TIM_Cmd(TIM4,DISABLE);
//	TIM_Cmd(TIM4, ENABLE);  										//使能TIMx					 
}


void TIM4_IRQHandler(void)   										//TIM4中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  			//检查TIM3更新中断发生与否
		{
			
			time++;	
			if(time/1000)     //计秒
			{
					time=0;
					sec++;
				if(sec==86400){sec=0;}
//				printf("first %d-%d-%d\r\n",sec/1440,sec/60-sec/1440,sec%60);
				fuc_DIRECTORY(); //每秒判断一次状态
			}

			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  ); 				//清除TIMx更新中断标志 
			}
}
