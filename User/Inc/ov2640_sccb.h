#ifndef __OV2640_SCCB_H__
#define __OV2640_SCCB_H__

#include "main.h"
#include "stm32f4xx_hal.h"

#define ATK_MC2640_SCCB_GPIO_PULLUP 1

#define ATK_MC2640_SCCB_SCL_GPIO_PORT SCCB_SCL_GPIO_Port
#define ATK_MC2640_SCCB_SCL_GPIO_PIN SCCB_SCL_Pin
#define ATK_MC2640_SCCB_SCL_GPIO_CLK_ENABLE() \
    do                                        \
    {                                         \
        __HAL_RCC_GPIOB_CLK_ENABLE();         \
    } while (0)
#define ATK_MC2640_SCCB_SDA_GPIO_PORT SCCB_SDA_GPIO_Port
#define ATK_MC2640_SCCB_SDA_GPIO_PIN SCCB_SDA_Pin
#define ATK_MC2640_SCCB_SDA_GPIO_CLK_ENABLE() \
    do                                        \
    {                                         \
        __HAL_RCC_GPIOB_CLK_ENABLE();         \
    } while (0)

#define ATK_MC2640_SCCB_SCL(x)                                                                                                                                                                             \
    do                                                                                                                                                                                                     \
    {                                                                                                                                                                                                      \
        x ? HAL_GPIO_WritePin(ATK_MC2640_SCCB_SCL_GPIO_PORT, ATK_MC2640_SCCB_SCL_GPIO_PIN, GPIO_PIN_SET) : HAL_GPIO_WritePin(ATK_MC2640_SCCB_SCL_GPIO_PORT, ATK_MC2640_SCCB_SCL_GPIO_PIN, GPIO_PIN_RESET); \
    } while (0)
#define ATK_MC2640_SCCB_SDA(x)                                                                                                                                                                             \
    do                                                                                                                                                                                                     \
    {                                                                                                                                                                                                      \
        x ? HAL_GPIO_WritePin(ATK_MC2640_SCCB_SDA_GPIO_PORT, ATK_MC2640_SCCB_SDA_GPIO_PIN, GPIO_PIN_SET) : HAL_GPIO_WritePin(ATK_MC2640_SCCB_SDA_GPIO_PORT, ATK_MC2640_SCCB_SDA_GPIO_PIN, GPIO_PIN_RESET); \
    } while (0)
#define ATK_MC2640_SCCB_READ_SDA() HAL_GPIO_ReadPin(ATK_MC2640_SCCB_SDA_GPIO_PORT, ATK_MC2640_SCCB_SDA_GPIO_PIN)

void atk_mc2640_sccb_init(void);
void atk_mc2640_sccb_3_phase_write(uint8_t id_addr, uint8_t sub_addr, uint8_t dat);
void atk_mc2640_sccb_2_phase_write(uint8_t id_addr, uint8_t sub_addr);
void atk_mc2640_sccb_2_phase_read(uint8_t id_addr, uint8_t *dat);

#endif /* __OV2640_SCCB_H__ */
