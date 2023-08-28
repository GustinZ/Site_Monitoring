#ifndef __OV2640_H__
#define __OV2640_H__

#include "stm32f4xx_hal.h"

#define ATK_MC2640_USING_DCMI 1

#if (ATK_MC2640_USING_DCMI == 0)
#define ATK_MC2640_DATA_PIN_IN_SAME_GPIO_PORT 0
#endif

#define ATK_MC2640_LED_CTL_BY_OV2640 1

#if (ATK_MC2640_USING_DCMI == 0)
#if (ATK_MC2640_DATA_PIN_IN_SAME_GPIO_PORT != 0)
#define ATK_MC2640_DATE_GPIO_PORT GPIOC
#define ATK_MC2640_DATA_READ_MASK 0x00FF
#endif
#endif

#if (ATK_MC2640_USING_DCMI == 0)
#define ATK_MC2640_DMA_INTERFACE DMA2_Stream0
#define ATK_MC2640_DMA_CLK_ENABLE()  \
    do                               \
    {                                \
        __HAL_RCC_DMA2_CLK_ENABLE(); \
    } while (0)
#endif

#if (ATK_MC2640_USING_DCMI == 0)
#define ATK_MC2640_VSYNC_GPIO_PORT GPIOB
#define ATK_MC2640_VSYNC_GPIO_PIN GPIO_PIN_7
#define ATK_MC2640_VSYNC_GPIO_CLK_ENABLE() \
    do                                     \
    {                                      \
        __HAL_RCC_GPIOB_CLK_ENABLE();      \
    } while (0)
#define ATK_MC2640_HREF_GPIO_PORT GPIOH
#define ATK_MC2640_HREF_GPIO_PIN GPIO_PIN_8
#define ATK_MC2640_HREF_GPIO_CLK_ENABLE() \
    do                                    \
    {                                     \
        __HAL_RCC_GPIOH_CLK_ENABLE();     \
    } while (0)
#define ATK_MC2640_D0_GPIO_PORT GPIOC
#define ATK_MC2640_D0_GPIO_PIN GPIO_PIN_6
#define ATK_MC2640_D0_GPIO_CLK_ENABLE() \
    do                                  \
    {                                   \
        __HAL_RCC_GPIOC_CLK_ENABLE();   \
    } while (0)
#define ATK_MC2640_D1_GPIO_PORT GPIOC
#define ATK_MC2640_D1_GPIO_PIN GPIO_PIN_7
#define ATK_MC2640_D1_GPIO_CLK_ENABLE() \
    do                                  \
    {                                   \
        __HAL_RCC_GPIOC_CLK_ENABLE();   \
    } while (0)
#define ATK_MC2640_D2_GPIO_PORT GPIOC
#define ATK_MC2640_D2_GPIO_PIN GPIO_PIN_8
#define ATK_MC2640_D2_GPIO_CLK_ENABLE() \
    do                                  \
    {                                   \
        __HAL_RCC_GPIOC_CLK_ENABLE();   \
    } while (0)
#define ATK_MC2640_D3_GPIO_PORT GPIOC
#define ATK_MC2640_D3_GPIO_PIN GPIO_PIN_9
#define ATK_MC2640_D3_GPIO_CLK_ENABLE() \
    do                                  \
    {                                   \
        __HAL_RCC_GPIOC_CLK_ENABLE();   \
    } while (0)
#define ATK_MC2640_D4_GPIO_PORT GPIOC
#define ATK_MC2640_D4_GPIO_PIN GPIO_PIN_11
#define ATK_MC2640_D4_GPIO_CLK_ENABLE() \
    do                                  \
    {                                   \
        __HAL_RCC_GPIOC_CLK_ENABLE();   \
    } while (0)
#define ATK_MC2640_D5_GPIO_PORT GPIOD
#define ATK_MC2640_D5_GPIO_PIN GPIO_PIN_3
#define ATK_MC2640_D5_GPIO_CLK_ENABLE() \
    do                                  \
    {                                   \
        __HAL_RCC_GPIOD_CLK_ENABLE();   \
    } while (0)
#define ATK_MC2640_D6_GPIO_PORT GPIOB
#define ATK_MC2640_D6_GPIO_PIN GPIO_PIN_8
#define ATK_MC2640_D6_GPIO_CLK_ENABLE() \
    do                                  \
    {                                   \
        __HAL_RCC_GPIOB_CLK_ENABLE();   \
    } while (0)
#define ATK_MC2640_D7_GPIO_PORT GPIOB
#define ATK_MC2640_D7_GPIO_PIN GPIO_PIN_9
#define ATK_MC2640_D7_GPIO_CLK_ENABLE() \
    do                                  \
    {                                   \
        __HAL_RCC_GPIOB_CLK_ENABLE();   \
    } while (0)
#define ATK_MC2640_PCLK_GPIO_PORT GPIOA
#define ATK_MC2640_PCLK_GPIO_PIN GPIO_PIN_6
#define ATK_MC2640_PCLK_GPIO_CLK_ENABLE() \
    do                                    \
    {                                     \
        __HAL_RCC_GPIOA_CLK_ENABLE();     \
    } while (0)
#endif
#define ATK_MC2640_RST_GPIO_PORT GPIOA
#define ATK_MC2640_RST_GPIO_PIN GPIO_PIN_15
#define ATK_MC2640_RST_GPIO_CLK_ENABLE() \
    do                                   \
    {                                    \
        __HAL_RCC_GPIOA_CLK_ENABLE();    \
    } while (0)
#if (ATK_MC2640_LED_CTL_BY_OV2640 == 0)
#define ATK_MC2640_FLASH_GPIO_PORT GPIOA
#define ATK_MC2640_FLASH_GPIO_PIN GPIO_PIN_8
#define ATK_MC2640_FLASH_GPIO_CLK_ENABLE() \
    do                                     \
    {                                      \
        __HAL_RCC_GPIOA_CLK_ENABLE();      \
    } while (0)
#endif

#define ATK_MC2640_RST(x)                                                                                                                                                              \
    do                                                                                                                                                                                 \
    {                                                                                                                                                                                  \
        x ? HAL_GPIO_WritePin(ATK_MC2640_RST_GPIO_PORT, ATK_MC2640_RST_GPIO_PIN, GPIO_PIN_SET) : HAL_GPIO_WritePin(ATK_MC2640_RST_GPIO_PORT, ATK_MC2640_RST_GPIO_PIN, GPIO_PIN_RESET); \
    } while (0)
#define ATK_MC2640_PWDN(x)                                                           \
    do                                                                               \
    {                                                                                \
        x ? pcf8574_write_bit(DCMI_PWDN_IO, 1) : pcf8574_write_bit(DCMI_PWDN_IO, 0); \
    } while (0)
#if (ATK_MC2640_LED_CTL_BY_OV2640 == 0)
#define ATK_MC2640_FLASH(x)                                                                                                                                                                    \
    do                                                                                                                                                                                         \
    {                                                                                                                                                                                          \
        x ? HAL_GPIO_WritePin(ATK_MC2640_FLASH_GPIO_PORT, ATK_MC2640_FLASH_GPIO_PIN, GPIO_PIN_SET) : HAL_GPIO_WritePin(ATK_MC2640_FLASH_GPIO_PORT, ATK_MC2640_FLASH_GPIO_PIN, GPIO_PIN_RESET); \
    } while (0)
#endif
#if (ATK_MC2640_USING_DCMI == 0)
#define ATK_MC2640_READ_VSYNC() (ATK_MC2640_VSYNC_GPIO_PORT->IDR & ATK_MC2640_VSYNC_GPIO_PIN)
#define ATK_MC2640_READ_HREF() (ATK_MC2640_HREF_GPIO_PORT->IDR & ATK_MC2640_HREF_GPIO_PIN)
#define ATK_MC2640_READ_PCLK() (ATK_MC2640_PCLK_GPIO_PORT->IDR & ATK_MC2640_PCLK_GPIO_PIN)
#endif

#define ATK_MC2640_SCCB_ADDR 0x30

typedef enum
{
    ATK_MC2640_LIGHT_MODE_AUTO = 0x00, /* Auto */
    ATK_MC2640_LIGHT_MODE_SUNNY,       /* Sunny */
    ATK_MC2640_LIGHT_MODE_CLOUDY,      /* Cloudy */
    ATK_MC2640_LIGHT_MODE_OFFICE,      /* Office */
    ATK_MC2640_LIGHT_MODE_HOME,        /* Home */
} atk_mc2640_light_mode_t;

typedef enum
{
    ATK_MC2640_COLOR_SATURATION_0 = 0x00, /* +2 */
    ATK_MC2640_COLOR_SATURATION_1,        /* +1 */
    ATK_MC2640_COLOR_SATURATION_2,        /* 0 */
    ATK_MC2640_COLOR_SATURATION_3,        /* -1 */
    ATK_MC2640_COLOR_SATURATION_4,        /* -2 */
} atk_mc2640_color_saturation_t;

typedef enum
{
    ATK_MC2640_BRIGHTNESS_0 = 0x00, /* +2 */
    ATK_MC2640_BRIGHTNESS_1,        /* +1 */
    ATK_MC2640_BRIGHTNESS_2,        /* 0 */
    ATK_MC2640_BRIGHTNESS_3,        /* -1 */
    ATK_MC2640_BRIGHTNESS_4,        /* -2 */
} atk_mc2640_brightness_t;

typedef enum
{
    ATK_MC2640_CONTRAST_0 = 0x00, /* +2 */
    ATK_MC2640_CONTRAST_1,        /* +1 */
    ATK_MC2640_CONTRAST_2,        /* 0 */
    ATK_MC2640_CONTRAST_3,        /* -1 */
    ATK_MC2640_CONTRAST_4,        /* -2 */
} atk_mc2640_contrast_t;

typedef enum
{
    ATK_MC2640_SPECIAL_EFFECT_ANTIQUE = 0x00, /* Antique */
    ATK_MC2640_SPECIAL_EFFECT_BLUISH,         /* Bluish */
    ATK_MC2640_SPECIAL_EFFECT_GREENISH,       /* Greenish */
    ATK_MC2640_SPECIAL_EFFECT_REDISH,         /* Redish */
    ATK_MC2640_SPECIAL_EFFECT_BW,             /* B&W */
    ATK_MC2640_SPECIAL_EFFECT_NEGATIVE,       /* Negative */
    ATK_MC2640_SPECIAL_EFFECT_BW_NEGATIVE,    /* B&W Negative */
    ATK_MC2640_SPECIAL_EFFECT_NORMAL,         /* Normal */
} atk_mc2640_special_effect_t;

typedef enum
{
    ATK_MC2640_OUTPUT_FORMAT_RGB565 = 0x00, /* RGB565 */
    ATK_MC2640_OUTPUT_FORMAT_JPEG,          /* JPEG */
} atk_mc2640_output_format_t;

typedef enum
{
    ATK_MC2640_GET_TYPE_DTS_8B_NOINC = 0x00,
    ATK_MC2640_GET_TYPE_DTS_8B_INC,
    ATK_MC2640_GET_TYPE_DTS_16B_NOINC,
    ATK_MC2640_GET_TYPE_DTS_16B_INC,
    ATK_MC2640_GET_TYPE_DTS_32B_NOINC,
    ATK_MC2640_GET_TYPE_DTS_32B_INC,
} atk_mc2640_get_type_t;

#define ATK_MC2640_EOK 0
#define ATK_MC2640_ERROR 1
#define ATK_MC2640_EINVAL 2
#define ATK_MC2640_ENOMEM 3
#define ATK_MC2640_EEMPTY 4

uint8_t atk_mc2640_init(void);
#if (ATK_MC2640_LED_CTL_BY_OV2640 == 0)
void atk_mc2640_led_on(void);
void atk_mc2640_led_off(void);
#else
void atk_mc2640_led_enable(void);
#endif
uint8_t atk_mc2640_set_light_mode(atk_mc2640_light_mode_t mode);
uint8_t atk_mc2640_set_color_saturation(atk_mc2640_color_saturation_t saturation);
uint8_t atk_mc2640_set_brightness(atk_mc2640_brightness_t brightness);
uint8_t atk_mc2640_set_contrast(atk_mc2640_contrast_t contrast);
uint8_t atk_mc2640_set_special_effect(atk_mc2640_special_effect_t effect);
uint8_t atk_mc2640_set_output_format(atk_mc2640_output_format_t format);
uint8_t atk_mc2640_set_output_size(uint16_t width, uint16_t height);
void atk_mc2640_set_sensor_window(uint16_t start_x, uint16_t start_y, uint16_t width, uint16_t height);
uint8_t atk_mc2640_set_image_window(uint16_t off_x, uint16_t off_y, uint16_t width, uint16_t height);
void atk_mc2640_set_image_size(uint16_t width, uint16_t height);
uint8_t atk_mc2640_set_output_speed(uint8_t clk_dev, uint8_t pclk_dev);
void atk_mc2640_colorbar_enable(void);
void atk_mc2640_colorbar_disable(void);
uint8_t atk_mc2640_get_frame(uint32_t dts_addr, atk_mc2640_get_type_t type, void (*before_transfer)(void));

#endif /* __OV2640_H__ */
