#include "gp2y10.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include "adc.h"
#include "delay.h"
#include "utilities.h"

#include <stdint.h>

uint32_t get_adc1(void)
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 10);
    return HAL_ADC_GetValue(&hadc1);
}

void get_gp2y10_value(uint16_t *AQI, uint16_t *PM25)
{
    uint32_t tmp[10] = {0};
    uint32_t value = 0;
    uint8_t i;

    for (i = 0; i < 10; i++)
    {
        GP2Y10_CONTROL_L;
        delay_us(280);
        tmp[i] = get_adc1();
        delay_us(40);
        GP2Y10_CONTROL_H;
        delay_us(9680);
    }

    bubble_sort(tmp, 10);

    for (i = 1; i < 9; i++)
    {
        value += tmp[i];
    }

    value /= 8;
    *PM25 = (uint16_t)(((float)(((float)value) / (float)4096.0 * (float)3.3) * (float)0.17 - (float)0.1) * (float)1000.0);

    if (*PM25 > 0 && *PM25 <= 35)
    {
        *AQI = (uint16_t)(50.0 / 35.0 * (float)(*PM25 - 0) + 0);
    }
    else if (*PM25 > 35 && *PM25 <= 75)
    {
        *AQI = (uint16_t)(50.0 / 40.0 * (float)(*PM25 - 35) + 35.0);
    }
    else if (*PM25 > 75 && *PM25 <= 115)
    {
        *AQI = (uint16_t)(50.0 / 40.0 * (float)(*PM25 - 75) + 75.0);
    }
    else if (*PM25 > 115 && *PM25 <= 150)
    {
        *AQI = (uint16_t)(50.0 / 35.0 * (float)(*PM25 - 115) + 115.0);
    }
    else if (*PM25 > 150 && *PM25 <= 250)
    {
        *AQI = (uint16_t)(100.0 / 100.0 * (float)(*PM25 - 150) + 150.0);
    }
    else if (*PM25 > 250 && *PM25 <= 350)
    {
        *AQI = (uint16_t)(100.0 / 100.0 * (float)(*PM25 - 250) + 250.0);
    }
    else if (*PM25 > 350 && *PM25 <= 500)
    {
        *AQI = (uint16_t)(100.0 / 150.0 * (float)(*PM25 - 350) + 350.0);
    }
    else
    {
        *AQI = 0;
    }
}
