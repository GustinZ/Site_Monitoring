/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_RST_Pin GPIO_PIN_1
#define LCD_RST_GPIO_Port GPIOC
#define LCD_SCL_Pin GPIO_PIN_2
#define LCD_SCL_GPIO_Port GPIOC
#define LCD_DC_Pin GPIO_PIN_3
#define LCD_DC_GPIO_Port GPIOC
#define LCD_CS_Pin GPIO_PIN_0
#define LCD_CS_GPIO_Port GPIOA
#define LCD_SDA_Pin GPIO_PIN_1
#define LCD_SDA_GPIO_Port GPIOA
#define LCD_BL_Pin GPIO_PIN_2
#define LCD_BL_GPIO_Port GPIOA
#define GP2Y10_LED_Pin GPIO_PIN_5
#define GP2Y10_LED_GPIO_Port GPIOA
#define DUST_REMOVAL_Pin GPIO_PIN_5
#define DUST_REMOVAL_GPIO_Port GPIOC
#define W5300_LINK_Pin GPIO_PIN_6
#define W5300_LINK_GPIO_Port GPIOJ
#define DHT11_DQ_Pin GPIO_PIN_4
#define DHT11_DQ_GPIO_Port GPIOG
#define SGP30_SCL_Pin GPIO_PIN_5
#define SGP30_SCL_GPIO_Port GPIOG
#define SGP30_SDA_Pin GPIO_PIN_6
#define SGP30_SDA_GPIO_Port GPIOG
#define SCCB_SDA_Pin GPIO_PIN_3
#define SCCB_SDA_GPIO_Port GPIOB
#define SCCB_SCL_Pin GPIO_PIN_4
#define SCCB_SCL_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

void main_timer(void);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
