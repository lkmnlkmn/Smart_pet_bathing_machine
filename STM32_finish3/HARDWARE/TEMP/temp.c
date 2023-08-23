/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx����
  * @UpdateTime   2023/4/3   ljd
  ******************************************************************************
*/ 

#include "temp.h"
#include "stm32f10x.h"

/*PTC����Ƭ��ʼ��*/
void TEMP_Init(void){

GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(T1_GPIO_CLK|T2_GPIO_CLK,ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = PINT1;				 //MOTOR1 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOT1, &GPIO_InitStructure);					 //�����趨������ʼ��
 T1_OFF;					  //�رյ��1

 GPIO_InitStructure.GPIO_Pin = PINT2 ;	    		 //MOTOR2 �˿�����, �������
 GPIO_Init(GPIOT2, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 T2_OFF;						 //�رյ��2
	
}