/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx驱动
  * @UpdateTime   2023/4/3   ljd
  ******************************************************************************
*/ 

#include "pwm.h"
#include "temp.h"
#include "motor.h"
#include "Net_Things.h"
#include "DS18B20.h"
#include "stdio.h"
#include "tim.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "string.h"
#include "led.h"

#ifndef _TASK_H
#define _TASK_H

#define TIME1     5
#define TIME2     2
#define TIME3     10
#define TIME4     20
//#define TIME5     2


#define EX					1 //连接云端

#define TEST_TEMP				2 //测试水温  （时刻执行 需要加计时器）
#define UP_TEMP1						1
#define DOWN_TEMP1					0
#define WAIT_TEMP1          2


#define WASH1						3 //第一次加水冲洗
#define OPEN_M1							1
#define CLOSE_M1     				0

#define WASH2						4	//第二次加沐浴露
#define OPEN_M2      				1
#define CLOSE_M2						0

#define WASH3						5	//第三次加水冲洗

#define HAIR						6 //吹干
#define OPEN_HAIR      				1
#define CLOSE_HAIR     				0
#define UP_TEMP2      				1
#define DOWN_TEMP2    				0


#define SEND_DATA				7 //上传完毕数据

#define OVER						8 //完成步骤


#define NOTHING					0 //不做任何事

#define TEMPLOW     25
#define TEMPMAX     30

#define finish   1
#define keep    0



//函数
void platform_data_handle(char * buff);
void fuc_TEST_TEMP(void);
void fuc_WASH1(int state);
void fuc_WASH2(int state);
void fuc_WASH3(int state);
void fuc_HAIR(int state);
void fuc_SEND_DATA(void);
void fuc_OVER(void);
void fuc_EX(void);
void fuc_DIRECTORY(void);
void fuc_TASK(void);
void fuc_init(void);
void fuc_temp(void);

#endif
