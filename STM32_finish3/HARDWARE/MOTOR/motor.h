/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx����
  * @UpdateTime   2023/4/3   ljd
  ******************************************************************************
*/ 

#ifndef _MOTOR_H
#define _MOTOR_H

#include <stm32f10x.h>
/*�����ź궨��*/
#define GPIOM1 GPIOB
#define GPIOM2 GPIOB
#define PINM1 GPIO_Pin_13
#define PINM2 GPIO_Pin_14
#define M1_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define M2_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
/*�����ŵĿ���*/

#define M1_ON  GPIO_ResetBits(GPIOM1,PINM1)   //�͵�ƽ����
#define M1_OFF GPIO_SetBits(GPIOM1,PINM1) 
#define M2_ON  GPIO_ResetBits(GPIOM2,PINM2)		//�͵�ƽ����
#define M2_OFF GPIO_SetBits(GPIOM2,PINM2)

void MOTOR_Init(void);//��ʼ��
#endif
