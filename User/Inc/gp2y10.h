#ifndef __GP2Y10_H__
#define __GP2Y10_H__

#include "stm32f4xx_hal.h"

#define GP2Y10_CONTROL_H HAL_GPIO_WritePin(GP2Y10_LED_GPIO_Port, GP2Y10_LED_Pin, GPIO_PIN_SET)
#define GP2Y10_CONTROL_L HAL_GPIO_WritePin(GP2Y10_LED_GPIO_Port, GP2Y10_LED_Pin, GPIO_PIN_RESET)

void get_gp2y10_value(uint16_t *AQI, uint16_t *PM25);

#endif /* __GP2Y10_H__ */
