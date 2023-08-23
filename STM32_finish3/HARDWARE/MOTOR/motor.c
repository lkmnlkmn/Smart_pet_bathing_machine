/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx����
  * @UpdateTime   2023/4/3   ljd
  ******************************************************************************
*/ 
#include "motor.h"
#include "stm32f10x.h"

/*�����ʼ��*/
void MOTOR_Init(void){

GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(M1_GPIO_CLK|M2_GPIO_CLK,ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = PINM1;				 //MOTOR1 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOM1, &GPIO_InitStructure);					 //�����趨������ʼ��
 M1_OFF;					  //�رյ��1

 GPIO_InitStructure.GPIO_Pin = PINM2 ;	    		 //MOTOR2 �˿�����, �������
 GPIO_Init(GPIOM2, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 M2_OFF;						 //�رյ��2
	
}