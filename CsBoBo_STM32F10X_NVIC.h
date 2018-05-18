#ifndef _CSBOBO_STM32F10X_NVIC_H
#define _CSBOBO_STM32F10X_NVIC_H 			   
#include "stm32f10x.h"

void NVIC_Configuration(uint32_t NVIC_PriorityGroup);
void NVIC_Init_IRQChannel(	uint8_t NVIC_IRQChannel,\
							uint8_t NVIC_IRQChannelPreemptionPriority,\
							uint8_t NVIC_IRQChannelSubPriority,\
							FunctionalState NVIC_IRQChannelCmd\
							);//初始化中断线


#endif

