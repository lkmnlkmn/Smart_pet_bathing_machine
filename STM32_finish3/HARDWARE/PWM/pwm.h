/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx����
  * @UpdateTime   2023/4/3   ljd
  ******************************************************************************
*/ 

#ifndef _PWM_H
#define _PWM_H

#include "stm32f10x.h"

#define GPIOPWM GPIOB

#define PINPWM  GPIO_Pin_6

#define PWM_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */

#define GPIOFEN GPIOB

#define PINFEN GPIO_Pin_7

#define FEN_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */

/*�����ŵĿ���*/

#define FEN_ON  GPIO_ResetBits(GPIOFEN,PINFEN)   //�͵�ƽ����
#define FEN_OFF GPIO_SetBits(GPIOFEN,PINFEN) 

void FEN_Init(void);
void TIM3_PWM_Init(u16 arr,u16 psc);
u16 PWM_Breath(u16 pwmvalmax);
#endif

