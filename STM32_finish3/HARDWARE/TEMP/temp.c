/**
  ******************************************************************************
  * @file    xxx.h
  * @author  ljd
  * @date    2023/4/3
  * @brief   xxx驱动
  * @UpdateTime   2023/4/3   ljd
  ******************************************************************************
*/ 

#include "temp.h"
#include "stm32f10x.h"

/*PTC加热片初始化*/
void TEMP_Init(void){

GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(T1_GPIO_CLK|T2_GPIO_CLK,ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = PINT1;				 //MOTOR1 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOT1, &GPIO_InitStructure);					 //根据设定参数初始化
 T1_OFF;					  //关闭电机1

 GPIO_InitStructure.GPIO_Pin = PINT2 ;	    		 //MOTOR2 端口配置, 推挽输出
 GPIO_Init(GPIOT2, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 T2_OFF;						 //关闭电机2
	
}