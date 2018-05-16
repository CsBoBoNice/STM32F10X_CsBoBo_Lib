#ifndef _CSBOBO_STM32F10X_IWDG_H_
#define _CSBOBO_STM32F10X_IWDG_H_
#include "stm32f10x.h"

void IWDG_Init(u8 prer,u16 rlr);
void IWDG_Feed(void);

#endif
