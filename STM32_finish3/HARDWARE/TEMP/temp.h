/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx驱动
  * @UpdateTime   2023/4/3   ljd
  ******************************************************************************
*/ 

#ifndef _TEMP_H
#define _TEMP_H

#include <stm32f10x.h>
/*对引脚宏定义*/
#define GPIOT1 GPIOA
#define GPIOT2 GPIOA
#define PINT1 GPIO_Pin_11
#define PINT2 GPIO_Pin_12
#define T1_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define T2_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
/*对引脚的控制*/

#define T1_ON  GPIO_ResetBits(GPIOT1,PINT1)   //低电平触发
#define T1_OFF GPIO_SetBits(GPIOT1,PINT1) 
#define T2_ON  GPIO_ResetBits(GPIOT2,PINT2)		//低电平触发
#define T2_OFF GPIO_SetBits(GPIOT2,PINT2)

void TEMP_Init(void);//初始化
#endif
