#include "sgp30.h"
#include "delay.h"

void SDA_OUT(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};

    gpio_init_struct.Pin = SGP30_SDA_Pin;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SGP30_SDA_GPIO_Port, &gpio_init_struct);
}

void SDA_IN(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};

    gpio_init_struct.Pin = SGP30_SDA_Pin;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(SGP30_SDA_GPIO_Port, &gpio_init_struct);
}

void SGP30_IIC_Start(void)
{
    SDA_OUT();
    SGP30_SDA_H;
    SGP30_SCL_H;
    delay_us(20);

    SGP30_SDA_L;
    delay_us(20);
    SGP30_SCL_L;
}

void SGP30_IIC_Stop(void)
{
    SDA_OUT();
    SGP30_SCL_L;
    SGP30_SDA_L;
    delay_us(20);
    SGP30_SCL_H;
    SGP30_SDA_H;
    delay_us(20);
}

uint8_t SGP30_IIC_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    SDA_IN();
    SGP30_SDA_H;
    delay_us(10);
    SGP30_SCL_H;
    delay_us(10);
    while (SGP30_SDA_READ())
    {
        ucErrTime++;
        if (ucErrTime > 250)
        {
            SGP30_IIC_Stop();
            return 1;
        }
    }
    SGP30_SCL_L;
    return 0;
}

void SGP30_IIC_Ack(void)
{
    SGP30_SCL_L;
    SDA_OUT();
    SGP30_SDA_L;
    delay_us(20);
    SGP30_SCL_H;
    delay_us(20);
    SGP30_SCL_L;
}

void SGP30_IIC_NAck(void)
{
    SGP30_SCL_L;
    SDA_OUT();
    SGP30_SDA_H;
    delay_us(20);
    SGP30_SCL_H;
    delay_us(20);
    SGP30_SCL_L;
}

void SGP30_IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    SGP30_SCL_L;
    for (t = 0; t < 8; t++)
    {
        if ((txd & 0x80) >> 7)
            SGP30_SDA_H;
        else
            SGP30_SDA_L;
        txd <<= 1;
        delay_us(20);
        SGP30_SCL_H;
        delay_us(20);
        SGP30_SCL_L;
        delay_us(20);
    }
    delay_us(20);
}

uint16_t SGP30_IIC_Read_Byte(uint8_t ack)
{
    uint8_t i;
    uint16_t receive = 0;
    SDA_IN();
    for (i = 0; i < 8; i++)
    {
        SGP30_SCL_L;
        delay_us(20);
        SGP30_SCL_H;
        receive <<= 1;
        if (SGP30_SDA_READ())
            receive++;
        delay_us(20);
    }
    if (!ack)
        SGP30_IIC_NAck();
    else
        SGP30_IIC_Ack();
    return receive;
}

void SGP30_Init(void)
{
    SGP30_Write(0x20, 0x03);
    //  SGP30_ad_write(0x20,0x61);
    //  SGP30_ad_write(0x01,0x00);
}

void SGP30_Write(uint8_t a, uint8_t b)
{
    SGP30_IIC_Start();
    SGP30_IIC_Send_Byte(SGP30_write);
    SGP30_IIC_Wait_Ack();
    SGP30_IIC_Send_Byte(a);
    SGP30_IIC_Wait_Ack();
    SGP30_IIC_Send_Byte(b);
    SGP30_IIC_Wait_Ack();
    SGP30_IIC_Stop();
    delay_ms(100);
}

uint32_t SGP30_Read(void)
{
    uint32_t dat;
    uint8_t crc;
    SGP30_IIC_Start();
    SGP30_IIC_Send_Byte(SGP30_read);
    SGP30_IIC_Wait_Ack();
    dat = SGP30_IIC_Read_Byte(1);
    dat <<= 8;
    dat += SGP30_IIC_Read_Byte(1);
    crc = SGP30_IIC_Read_Byte(1);
    crc = crc;
    dat <<= 8;
    dat += SGP30_IIC_Read_Byte(1);
    dat <<= 8;
    dat += SGP30_IIC_Read_Byte(0);
    SGP30_IIC_Stop();
    return (dat);
}
