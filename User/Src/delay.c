#include "stm32f4xx_hal.h"

static uint32_t g_fac_us = 0;

void delay_init(uint16_t sysclk)
{
#if SYS_SUPPORT_OS
    uint32_t reload;
#endif
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    g_fac_us = sysclk;
#if SYS_SUPPORT_OS
    reload = sysclk;
    reload *= 1000000 / delay_ostickspersec;

    g_fac_ms = 1000 / delay_ostickspersec;
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    SysTick->LOAD = reload;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
#endif
}

void delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD;
    ticks = nus * g_fac_us;
    told = SysTick->VAL;
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}

void delay_ms(uint16_t nms)
{
    uint32_t repeat = nms / 540;
    uint32_t remain = nms % 540;

    while (repeat)
    {
        delay_us(540 * 1000);
        repeat--;
    }

    if (remain)
    {
        delay_us(remain * 1000);
    }
}
