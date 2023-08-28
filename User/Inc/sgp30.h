#ifndef __SGP30_H__
#define __SGP30_H__

#include "stm32f4xx_hal.h"
#include "main.h"

#define SGP30_SCL_H HAL_GPIO_WritePin(SGP30_SCL_GPIO_Port, SGP30_SCL_Pin, GPIO_PIN_SET)
#define SGP30_SCL_L HAL_GPIO_WritePin(SGP30_SCL_GPIO_Port, SGP30_SCL_Pin, GPIO_PIN_RESET)
#define SGP30_SDA_H HAL_GPIO_WritePin(SGP30_SDA_GPIO_Port, SGP30_SDA_Pin, GPIO_PIN_SET)
#define SGP30_SDA_L HAL_GPIO_WritePin(SGP30_SDA_GPIO_Port, SGP30_SDA_Pin, GPIO_PIN_RESET)

#define SGP30_SDA_READ() HAL_GPIO_ReadPin(SGP30_SDA_GPIO_Port, SGP30_SDA_Pin)

#define SGP30_read 0xb1
#define SGP30_write 0xb0

void SGP30_IIC_Start(void);
void SGP30_IIC_Stop(void);
void SGP30_IIC_Send_Byte(uint8_t txd);
uint16_t SGP30_IIC_Read_Byte(unsigned char ack);
uint8_t SGP30_IIC_Wait_Ack(void);
void SGP30_IIC_Ack(void);
void SGP30_IIC_NAck(void);
void SGP30_IIC_Write_One_Byte(uint8_t daddr, uint8_t addr, uint8_t data);
uint8_t SGP30_IIC_Read_One_Byte(uint8_t daddr, uint8_t addr);
void SGP30_Init(void);
void SGP30_Write(uint8_t a, uint8_t b);
uint32_t SGP30_Read(void);

#endif /* __SGP30_H__ */
