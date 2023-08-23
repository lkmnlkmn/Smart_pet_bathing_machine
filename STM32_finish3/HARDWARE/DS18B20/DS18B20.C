/**
  ******************************************************************************
  * @file    DS180b20.c
  * @author  hhy/wattercutter
  * @date    2020/1/20
  * @brief   DS180B20驱动
	
	* @UpdateTime 
			2021/1/20 hhy/wattercutter
  ******************************************************************************
*/ 
#include "DS18B20.h"
#include "delay.h"
#include  "usart.h"

/**
  * @brief  设置DQ对应的引脚位推挽输出模式
  * @param   无 
  * @retval  无
  */
static void DS18B20_SetDQMode_OUT()
{
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = PINDQ;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(GPIODQ, &GPIO_InitStructure);	
}
/**
  * @brief  设置DQ对应的引脚为输入模式
  * @param   无  
  * @retval  无
  */
static void DS18B20_SetDQMode_IPU()
{
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = PINDQ;	

		/*设置引脚模式为通用上拉输入*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   

		/*调用库函数，初始化GPIO*/
		GPIO_Init(GPIODQ, &GPIO_InitStructure);	
}
/**
  * @brief  配置DQ对应的GPIO引脚
  * @param   无
  * @retval  无
  */
void DS18B20_DQGPIOConfig(void)
{
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd(DQ_GPIO_CLK, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = PINDQ;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(GPIODQ, &GPIO_InitStructure);	
}
/**
  * @brief  配置DQ并复位DS18B20
  * @param   
  *		@arg  
  *		@arg  
  * @retval  无
  */
void DS18B20_Init(void)
{
	/* 初始化GPIO */
	DS18B20_DQGPIOConfig();
	/* 复位 */
	DS18B20_Rst();
}
/**
  * @brief  复位DS18B20
  * @param   无
  * @retval  无
  */
void DS18B20_Rst(void)
{	
	/* 初始化GPIO */
	DS18B20_DQGPIOConfig();
	DS18B20_SetDQMode_OUT();
	/* 先将数据线置高电平“1” */
	DQ_H;
	/* 延时（该时间要求的不是很严格，但是尽可能的短一点） */
	delay_us(1);
	/* 数据线拉到低电平“0”。 */
	DQ_L;
	/* 延时750微秒（该时间的时间范围可以从480到960微秒） */
	delay_us(750);
	/* 数据线拉到高电平“1” */
	DQ_H;
	/* 延时等待（如果初始化成功则在15到60微秒时间之内产生一个由
	DS18B20所返回的低电平“0”。据该状态可以来确定它的存在，
	但是应注意不能无限的进行等待，不然会使程序进入死循环，
	所以要进行超时控制）。 */
	/* 超时时间不要设置得太短 至少70us，否则初始化失败，将获取不到环境温度 */
	delay_us(500);
	uint8_t dqStatus = GPIO_ReadInputDataBit(GPIODQ,PINDQ);

	/*  将数据线再次拉高到高电平“1”后结束。 */
	DQ_H;
}
/**
  * @brief  通过DQ从DS18B20读取一个字节（Byte）
  * @param   无
  * @retval  无
  */
uint8_t DS18B20_ReadByte(void)
{
	uint8_t data = 0x00;
	for(int i=0;i<8;i++)
	{
		DS18B20_SetDQMode_OUT();
		/* 将数据线拉高“1” */
		DQ_H;
		/* 延时2微秒 */
		delay_us(2);
		/* 将数据线拉低“0” */
		DQ_L;
		/* 延时3微秒 */
		delay_us(3); 
		data>>=1;
		/* 将数据线拉高“1” */
		DQ_H;
		DS18B20_SetDQMode_IPU();
		/* 延时5微秒 */
		delay_us(5);
		/* 读数据线的状态得到1个状态位，并进行数据处理 */
		if(GPIO_ReadInputDataBit(GPIODQ,PINDQ))
			data|=0x80;
		/* 延时60微秒 */
		delay_us(60);
	}
	return data;
}
/**
* @brief  通过DQ向DS18B20发送一个字节（Byte）
  * @param   无
  * @retval  无
  */
void DS18B20_WriteByte(uint8_t data)
{
	for(int i=0;i<8;i++){
		/* 数据线先置低电平“0” */
		DQ_L;
		/* 延时确定的时间为15微秒 */
		delay_us(15);
		/* 按从低位到高位的顺序发送字节（一次只发送一位） */
		if(data&0x01){
			GPIO_WriteBit(GPIODQ,PINDQ,Bit_SET);		
		}else{
			GPIO_WriteBit(GPIODQ,PINDQ,Bit_RESET);
		}
		/* 延时时间为45微秒 */
		delay_us(45);
		/* 将数据线拉到高电平 */
		DQ_H;
		data>>=1;
	}
}
/**
  * @brief  获取温度寄存器的值并转换为温度值返回
  * @param   无
  * @retval  无
  */
float DS18B20_GetTemp(void)
{
	DS18B20_Rst();
	DS18B20_WriteByte(0xcc);
	DS18B20_WriteByte(CONVERTT);
	DS18B20_Rst();
	DS18B20_WriteByte(0xcc);
	DS18B20_WriteByte(READSCRATCHPAD);
	uint8_t tempL = DS18B20_ReadByte();
	uint8_t tempH = DS18B20_ReadByte();
	/* 反码 */
//	printf("%d\r\n",tempL);
//	printf("%d\r\n",tempH);
	if(tempH>0x7f)
	{
		tempL = ~tempL;
		tempH = ~tempH+1;
	}
	/* 计算温度值 */
	float temp = ((tempH<<4)|(tempL>>4))+  //整数
	(float)(tempL&0x0f)*0.0625; 					//小数

	return temp;
}
