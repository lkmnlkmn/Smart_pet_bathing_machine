/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx����
  * @UpdateTime   2023/4/3   ljd
  ******************************************************************************
*/ 

#ifndef _DS18B20_H
#define _DS18B20_H
#include <stm32f10x.h>

/* DQ������غ궨�� */
#define GPIODQ GPIOB
#define PINDQ GPIO_Pin_15
#define DQ_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
/* DQ��ƽ������ */
#define DQ_H GPIO_SetBits(GPIODQ,PINDQ)
#define DQ_L GPIO_ResetBits(GPIODQ,PINDQ)
/* DS18B20��ָ��� */
#define CONVERTT 0x44         //�¶�ת��
#define READSCRATCHPAD 0xbe   //��ȡ�ݴ���
#define WRITESCRATCHPAD 0x4e  //д�ݴ���
#define COPYSCRATCHPAD 0x48  	//�����ݴ���
#define RECALLEE 0xb8					//�����ݴ���
#define READPOWERSUPPLY 0xb4	//��ȡ���緽ʽ

void DS18B20_DQGPIOConfig(void);
void DS18B20_Init(void);
void DS18B20_Rst(void);
uint8_t DS18B20_ReadByte(void);
void DS18B20_WriteBye(uint8_t data);
float DS18B20_GetTemp(void);

#endif
