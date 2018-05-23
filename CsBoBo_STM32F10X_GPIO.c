#include "CsBoBo_STM32F10X_GPIO.h"

/*******使用方法***********************************************************/
/*

@例:	GPIO_Common_Init(GPIOA,GPIO_Pin_2|GPIO_Pin_3,GPIO_Mode_Out_PP);	//GPIO初始化
		初始化GPIOA	;PA2，PA3;推挽输出
	
*/
/*************************************************************************/
/*
@例:	GPIO_ResetBits(GPIOD,GPIO_Pin_2);	//引脚拉低

@例:	GPIO_SetBits(GPIOD,GPIO_Pin_2);		//引脚置高

@例:	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)//读取指定端口管脚的输入	

@例:	GPIO_ReadInputData(GPIOD)	//读取指定的 GPIO 端口输入

@例:	GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_2)//读取指定端口管脚的输出

@例:	GPIO_Write(GPIOD, 0x55)//向指定 GPIO 数据端口写入数据
*/
/*************************************************************************/
/*
//参数1：GPIO_TypeDef
					GPIOA
					GPIOB
					GPIOC
					GPIOD
					GPIOF
					GPIOG
					GPIOH
					GPIOI
					GPIOJ
					GPIOK
//参数2：对应引脚	
					GPIO_Pin_0
					GPIO_Pin_1
					GPIO_Pin_2
					GPIO_Pin_3
					GPIO_Pin_4
					GPIO_Pin_5
					GPIO_Pin_6
					GPIO_Pin_7
					GPIO_Pin_8
					GPIO_Pin_9
					GPIO_Pin_10
					GPIO_Pin_11
					GPIO_Pin_12
					GPIO_Pin_13
					GPIO_Pin_14
					GPIO_Pin_15

//参数3：对应模式	 GPIO_Mode				描述			例子
					GPIO_Mode_AIN 			模拟输入		ADC引脚
					GPIO_Mode_IN_FLOATING 	浮空输入		按键
					GPIO_Mode_IPD 			下拉输入
					GPIO_Mode_IPU 			上拉输入		输入捕获
					GPIO_Mode_Out_OD 		开漏输出		I2C、 SMBUS 通讯
					GPIO_Mode_Out_PP 		推挽输出		驱动小灯
					GPIO_Mode_AF_OD 		复用开漏输出
					GPIO_Mode_AF_PP 		复用推挽输出	PWM
//参数3：GPIO速度
					GPIO_Speed_10MHz
					GPIO_Speed_2MHz
					GPIO_Speed_50MHz
*/
/********************************************************************/

/*
─ PA15： JTDI置于上拉模式
─ PA14： JTCK置于下拉模式
─ PA13： JTMS置于上拉模式
─ PB4： JNTRST置于上拉模式

JTMS/SWDIO 		输入 JTAG模式选择 输入/输出 串行数据输入/输出 		PA13
JTCK/SWCLK 		输入 JTAG时钟 		输入 	串行时钟 				PA14
JTDI 			输入 JTAG数据输入  ——  	——					PA15
JTDO/TRACESWO 	输出 JTAG数据输出  —— 	跟踪时为TRACESWO信号 	PB3
JNTRST 			输入 JTAG模块复位  ——  	——					PB4
若使用以上引脚：
//关闭jtag 改变指定管脚的映射	JTAG-DP 失能 + SW-DP 使能
GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	
*/


uint32_t Get_GPIO_PeriphClockCmd(GPIO_TypeDef* GPIOx)
{
	if		(GPIOx==GPIOA){return RCC_APB2Periph_GPIOA;}
	else if	(GPIOx==GPIOB){return RCC_APB2Periph_GPIOB;}
	else if	(GPIOx==GPIOC){return RCC_APB2Periph_GPIOC;}
	else if	(GPIOx==GPIOD){return RCC_APB2Periph_GPIOD;}
	else if	(GPIOx==GPIOE){return RCC_APB2Periph_GPIOE;}
	else if	(GPIOx==GPIOF){return RCC_APB2Periph_GPIOF;}
	else if	(GPIOx==GPIOG){return RCC_APB2Periph_GPIOG;}
	return 0;
}

void GPIO_Common_Init(GPIO_TypeDef* GPIOx,u16 GPIO_PIN,GPIOMode_TypeDef GPIO_Mode,GPIOSpeed_TypeDef GPIO_Speed)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;	//定义一个GPIO_InitTypeDef类型的结构体
	
	uint32_t GPIO_PeriphClockCmd;
	GPIO_PeriphClockCmd=Get_GPIO_PeriphClockCmd(GPIOx);
	
	RCC_APB2PeriphClockCmd( GPIO_PeriphClockCmd, ENABLE);	//开启相关的GPIO外设时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN;	//选择要控制的GPIO引脚	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode; //设置引脚模式

 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed;	//设置引脚速率

	GPIO_Init(GPIOx, &GPIO_InitStructure);	//调用库函数，初始化GPIO
}

/*
  * log:

  *	2018年4月6日
	修改初始化参数类型
	Programmer:陈述

  *	2016年7月8日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/
