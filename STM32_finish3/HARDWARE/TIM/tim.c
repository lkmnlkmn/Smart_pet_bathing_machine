/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx����
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
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 			//ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = 1000;		 				//�Զ���װ�ؼĴ������ڵ�ֵ1/CK_CNT=1us,1000x1us=1ms	
	TIM_TimeBaseStructure.TIM_Prescaler =71; 						//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��ƵֵCK_CNT=CK_INT/(71+1)=1MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		//TIM_CKD_DIV1��.h�ļ����Ѿ�����õģ�TIM_CKD_DIV1=0��Ҳ����ʱ�ӷ�Ƶ����Ϊ0
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 				//����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//�жϳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 				//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�	
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  				//TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  		//��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  			//�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  								//��ʼ��NVIC�Ĵ���
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE );						 //ʹ��ָ����TIM4�ж�,��������ж�
	
	TIM_Cmd(TIM4,DISABLE);
//	TIM_Cmd(TIM4, ENABLE);  										//ʹ��TIMx					 
}


void TIM4_IRQHandler(void)   										//TIM4�ж�
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  			//���TIM3�����жϷ������
		{
			
			time++;	
			if(time/1000)     //����
			{
					time=0;
					sec++;
				if(sec==86400){sec=0;}
//				printf("first %d-%d-%d\r\n",sec/1440,sec/60-sec/1440,sec%60);
				fuc_DIRECTORY(); //ÿ���ж�һ��״̬
			}

			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  ); 				//���TIMx�����жϱ�־ 
			}
}
