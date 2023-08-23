/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx����
  * @UpdateTime   2023/4/3   ljd
  ******************************************************************************
*/ 

#ifndef _TEMP_H
#define _TEMP_H

#include <stm32f10x.h>
/*�����ź궨��*/
#define GPIOT1 GPIOA
#define GPIOT2 GPIOA
#define PINT1 GPIO_Pin_11
#define PINT2 GPIO_Pin_12
#define T1_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define T2_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
/*�����ŵĿ���*/

#define T1_ON  GPIO_ResetBits(GPIOT1,PINT1)   //�͵�ƽ����
#define T1_OFF GPIO_SetBits(GPIOT1,PINT1) 
#define T2_ON  GPIO_ResetBits(GPIOT2,PINT2)		//�͵�ƽ����
#define T2_OFF GPIO_SetBits(GPIOT2,PINT2)

void TEMP_Init(void);//��ʼ��
#endif
