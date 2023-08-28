#include "light_check.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "utilities.h"

#include <stdint.h>
#include <stdio.h>

uint32_t get_adc2(void)
{
    HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, 10);
    return HAL_ADC_GetValue(&hadc2);
}

void get_light_value(uint16_t *percent)
{
    uint32_t tmp[10] = {0};
    uint32_t value = 0;
    uint8_t i;

    for (i = 0; i < 10; i++)
    {
        tmp[i] = get_adc2();
    }

    bubble_sort(tmp, 10);

    for (i = 1; i < 9; i++)
    {
        value += tmp[i];
    }

    value /= 8;
    *percent = 100 - (uint16_t)((float)value / (float)4096.0 * (float)100.0);
}
