#ifndef _CSBOBO_STM32F10X_BASIC_TIM_H_
#define _CSBOBO_STM32F10X_BASIC_TIM_H_
#include "stm32f10x.h"


void Basic_TIM_Init(TIM_TypeDef* TIMx,uint16_t TIM_Period,uint16_t TIM_Prescaler,uint8_t PreemptionPriority,uint8_t SubPriority);


#endif
