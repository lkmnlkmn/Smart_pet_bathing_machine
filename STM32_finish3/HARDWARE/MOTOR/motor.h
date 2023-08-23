/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx驱动
  * @UpdateTime   2023/4/3   ljd
  ******************************************************************************
*/ 

#ifndef _MOTOR_H
#define _MOTOR_H

#include <stm32f10x.h>
/*对引脚宏定义*/
#define GPIOM1 GPIOB
#define GPIOM2 GPIOB
#define PINM1 GPIO_Pin_13
#define PINM2 GPIO_Pin_14
#define M1_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define M2_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
/*对引脚的控制*/

#define M1_ON  GPIO_ResetBits(GPIOM1,PINM1)   //低电平触发
#define M1_OFF GPIO_SetBits(GPIOM1,PINM1) 
#define M2_ON  GPIO_ResetBits(GPIOM2,PINM2)		//低电平触发
#define M2_OFF GPIO_SetBits(GPIOM2,PINM2)

void MOTOR_Init(void);//初始化
#endif
