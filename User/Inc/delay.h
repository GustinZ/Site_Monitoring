#ifndef __DELAY_H__
#define __DELAY_H__

#include "stm32f4xx_hal.h"

void delay_init(uint16_t sysclk);
void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);

#endif /* __DELAY_H__ */
