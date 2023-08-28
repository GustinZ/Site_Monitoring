#ifndef __DHT11_H__
#define __DHT11_H__

#include "stm32f4xx_hal.h"
#include "main.h"

#define DHT11_DQ_OUT(x)                                                                                                                              \
    do                                                                                                                                               \
    {                                                                                                                                                \
        x ? HAL_GPIO_WritePin(DHT11_DQ_GPIO_Port, DHT11_DQ_Pin, GPIO_PIN_SET) : HAL_GPIO_WritePin(DHT11_DQ_GPIO_Port, DHT11_DQ_Pin, GPIO_PIN_RESET); \
    } while (0)
#define DHT11_DQ_IN HAL_GPIO_ReadPin(DHT11_DQ_GPIO_Port, DHT11_DQ_Pin)

uint8_t dht11_init(void);
uint8_t dht11_check(void);
uint8_t dht11_read_data(uint8_t *temp, uint8_t *humi);

#endif /* __DHT11_H__ */
