#ifndef  _CSBOBO_STM32F10X_DAC_H_
#define  _CSBOBO_STM32F10X_DAC_H_

#include "stm32f10x.h"

void PWM_DAC_Init(u8 TIMx,u16 TIM_channel,u8 remap_pwm);
void PWM_DAC_Set(TIM_TypeDef* TIMx,u16 TIM_channel,u16 vol);
#endif
