#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "w5300_config.h"
#include "socket.h"
#include "w5300.h"
#include "ov2640.h"
#include "malloc.h"

#define DEMO_JPEG_OUTPUT_WIDTH 240
#define DEMO_JPEG_OUTPUT_HEIGHT 320

#define DEMO_JPEG_BUF_SIZE (80 * 1024)

uint8_t remote_ip[4] = {192, 168, 124, 255};
uint16_t remote_port = 1234;
uint16_t local_port = 1234;

uint32_t *jpeg_buf;
uint8_t *p_jpeg_buf;
uint32_t jpeg_len;
uint32_t jpeg_index;

void eth_video_init(void)
{
    my_mem_init(SRAMIN);

    atk_mc2640_init();
    atk_mc2640_set_output_format(ATK_MC2640_OUTPUT_FORMAT_JPEG);
    atk_mc2640_set_output_size(DEMO_JPEG_OUTPUT_WIDTH, DEMO_JPEG_OUTPUT_HEIGHT);
    atk_mc2640_set_light_mode(ATK_MC2640_LIGHT_MODE_SUNNY);
    atk_mc2640_set_color_saturation(ATK_MC2640_COLOR_SATURATION_1);
    atk_mc2640_set_brightness(ATK_MC2640_BRIGHTNESS_1);
    atk_mc2640_set_contrast(ATK_MC2640_CONTRAST_2);
    atk_mc2640_set_special_effect(ATK_MC2640_SPECIAL_EFFECT_NORMAL);

    jpeg_buf = (uint32_t *)mymalloc(SRAMIN, DEMO_JPEG_BUF_SIZE);
}

void eth_video_run(void)
{
    atk_mc2640_set_output_format(ATK_MC2640_OUTPUT_FORMAT_JPEG);
    switch (getSn_SSR(W5300_VIDEO_SOCKET))
    {
    case SOCK_UDP:
        p_jpeg_buf = (uint8_t *)jpeg_buf;
        jpeg_len = DEMO_JPEG_BUF_SIZE / (sizeof(uint32_t));
        memset((void *)jpeg_buf, 0, DEMO_JPEG_BUF_SIZE);

        atk_mc2640_get_frame((uint32_t)jpeg_buf, ATK_MC2640_GET_TYPE_DTS_32B_INC, NULL);

        while (jpeg_len > 0)
        {
            if (jpeg_buf[jpeg_len - 1] != 0)
            {
                break;
            }
            jpeg_len--;
        }
        jpeg_len *= sizeof(uint32_t);

        sendto(W5300_VIDEO_SOCKET, p_jpeg_buf, jpeg_len, remote_ip, remote_port);

        break;

    case SOCK_CLOSED:                                         // CLOSED
        close(W5300_VIDEO_SOCKET);                            // close the SOCKET
        socket(W5300_VIDEO_SOCKET, Sn_MR_UDP, local_port, 0); // open the SOCKET with UDP mode
        break;

    default:
        break;
    }
}

uint16_t *get_video_rgb565(void)
{
    atk_mc2640_set_output_format(ATK_MC2640_OUTPUT_FORMAT_RGB565);

    p_jpeg_buf = (uint8_t *)jpeg_buf;
    jpeg_len = DEMO_JPEG_BUF_SIZE / (sizeof(uint32_t));
    memset((void *)jpeg_buf, 0, DEMO_JPEG_BUF_SIZE);
    atk_mc2640_get_frame((uint32_t)jpeg_buf, ATK_MC2640_GET_TYPE_DTS_32B_INC, NULL);

    return (uint16_t *)p_jpeg_buf;
}

void demo_run(void)
{
    atk_mc2640_set_output_format(ATK_MC2640_OUTPUT_FORMAT_JPEG);

    p_jpeg_buf = (uint8_t *)jpeg_buf;
    jpeg_len = DEMO_JPEG_BUF_SIZE / (sizeof(uint32_t));
    memset((void *)jpeg_buf, 0, DEMO_JPEG_BUF_SIZE);

    atk_mc2640_get_frame((uint32_t)jpeg_buf, ATK_MC2640_GET_TYPE_DTS_32B_INC, NULL);

    while (jpeg_len > 0)
    {
        if (jpeg_buf[jpeg_len - 1] != 0)
        {
            break;
        }
        jpeg_len--;
    }
    jpeg_len *= sizeof(uint32_t);

    for (jpeg_index = 0; jpeg_index < jpeg_len; jpeg_index++)
    {
        USART3->DR = p_jpeg_buf[jpeg_index];
        while ((USART3->SR & 0x40) == 0)
            ;
    }
}
