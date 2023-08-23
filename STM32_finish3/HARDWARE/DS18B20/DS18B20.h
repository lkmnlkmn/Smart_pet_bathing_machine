/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx驱动
  * @UpdateTime   2023/4/3   ljd
  ******************************************************************************
*/ 

#ifndef _DS18B20_H
#define _DS18B20_H
#include <stm32f10x.h>

/* DQ引脚相关宏定义 */
#define GPIODQ GPIOB
#define PINDQ GPIO_Pin_15
#define DQ_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
/* DQ电平操作宏 */
#define DQ_H GPIO_SetBits(GPIODQ,PINDQ)
#define DQ_L GPIO_ResetBits(GPIODQ,PINDQ)
/* DS18B20的指令宏 */
#define CONVERTT 0x44         //温度转化
#define READSCRATCHPAD 0xbe   //读取暂存器
#define WRITESCRATCHPAD 0x4e  //写暂存器
#define COPYSCRATCHPAD 0x48  	//复制暂存器
#define RECALLEE 0xb8					//重置暂存器
#define READPOWERSUPPLY 0xb4	//读取供电方式

void DS18B20_DQGPIOConfig(void);
void DS18B20_Init(void);
void DS18B20_Rst(void);
uint8_t DS18B20_ReadByte(void);
void DS18B20_WriteBye(uint8_t data);
float DS18B20_GetTemp(void);

#endif
