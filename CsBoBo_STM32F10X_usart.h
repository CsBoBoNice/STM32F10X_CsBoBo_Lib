#ifndef _CSBOBO_STM32F10X_USART_H
#define _CSBOBO_STM32F10X_USART_H

#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>

		
#define USART_PERIOD_MS	1	//串口使用的定时器进入中断的时间单位MS

#define USING_USART1	//不适用可注释,节省RAM
//#define USING_USART2
//#define USING_USART3
//#define USING_UART4
//#define USING_UART5
/********************串口驱动程序配置选项***********************/
/***********************************USART1***************************************/
#ifdef USING_USART1
#define USART1_BUF_SIZE 			256		//接收一、二级缓冲区大小
#define USART1_RECEIVE_OVERTIME		20			//字节超时时间, 单位为ms

extern uint8_t USART1_ready_buf[];
extern __IO uint8_t USART1_ready_buf_ok;
extern __IO uint16_t USART1_ready_buf_len;
void USART1_ISR(void);
#endif
/*************************************USART2**************************************/

#ifdef USING_USART2
#define USART2_BUF_SIZE				256	//接收一、二级缓冲区大小	
#define USART2_RECEIVE_OVERTIME		200		//字节超时时间, 单位为ms

extern uint8_t USART2_ready_buf[];
extern __IO uint8_t USART2_ready_buf_ok;
extern __IO uint16_t USART2_ready_buf_len;
void USART2_ISR(void);
#endif
/*************************************USART3**************************************/

#ifdef USING_USART3
#define USART3_BUF_SIZE				128	//接收一、二级缓冲区大小
#define USART3_RECEIVE_OVERTIME		10		//字节超时时间, 单位为ms

extern uint8_t USART3_ready_buf[];
extern __IO uint8_t USART3_ready_buf_ok;
extern __IO uint16_t USART3_ready_buf_len;
void USART3_Init(void);
#endif
/*************************************USART4**************************************/

#ifdef USING_UART4
#define UART4_BUF_SIZE				128	//接收一、二级缓冲区大小
#define UART4_RECEIVE_OVERTIME		10		//字节超时时间, 单位为ms	

extern uint8_t UART4_ready_buf[];
extern __IO uint8_t UART4_ready_buf_ok;
extern __IO uint16_t UART4_ready_buf_len;
void UART4_Init(void);
#endif
/*************************************USART5**************************************/

#ifdef USING_UART5
#define UART5_BUF_SIZE				128	//接收一、二级缓冲区大小
#define UART5_RECEIVE_OVERTIME		10		//字节超时时间, 单位为ms	

extern uint8_t UART5_ready_buf[];
extern __IO uint8_t UART5_ready_buf_ok;
extern __IO uint16_t UART5_ready_buf_len;
void UART5_ISR(void);
#endif

#define UART_OK 1
#define UART_ERROR 0

/******************************API************************************************/

//串口初始化函数
void USART_init	(	USART_TypeDef * USARTx,			
					GPIO_TypeDef* USART_TX_GPIOx,	
					u16 USART_TX_PIN,
					GPIO_TypeDef* USART_RX_GPIOx,
					u16 USART_RX_PIN,
					uint32_t USART_BaudRate,			//波特率设置
					uint16_t USART_WordLength,			//字长(数据位+校验位)
					uint16_t USART_StopBits,			//停止位		
					uint16_t USART_Parity,				//校验位选择
					uint16_t USART_Mode,				//USART模式控制
					uint16_t USART_HardwareFlowControl,	//硬件流控制
					uint8_t PreemptionPriority,			//抢占优先级
					uint8_t SubPriority					//子优先级
				);//串口初始化

void Change_printf(USART_TypeDef* USART_prt);//重定向串口选择
void USART_SendByte(USART_TypeDef* USARTx,uint8_t SendByte);	//发送一个字节
void USART_SendChars(USART_TypeDef* USARTx,const uint8_t* SendChars,uint16_t len);	//发送一串数据
void UART_SendString(USART_TypeDef* USARTx,char* s);	//USART发送字符串

void USART_ReceiveOvertimeProcess(void);	//在滴答中断 SysTick_Handler中执行的代码

int Get_USART_ready_buf_ok(USART_TypeDef * usart);	//判断串口是否接收完毕
void Clean_USART_ready_buf_OK(USART_TypeDef * usart);	//清除串口是否接收完毕标志
void Clean_USART_ready_buf(USART_TypeDef * usart); //清除串口缓存数据

#endif

