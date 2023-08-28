/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dcmi.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "delay.h"
#include "w5300_config.h"
#include "w5300_aliyun.h"
#include "eth_video.h"
#include "lcd.h"
#include "sgp30.h"
#include "gp2y10.h"
#include "light_check.h"
#include "dht11.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint8_t parms_update_count = 0;
uint8_t image_update_count = 0;
uint8_t aliyun_auto_up_count = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void demo_run(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  uint8_t lcd_buff[64] = {0};
  uint32_t sgp30_dat = 0;
  uint32_t CO2Data = 0;
  uint32_t TVOCData = 0;
  uint16_t AQI = 0;
  uint16_t PM25 = 0;
  uint16_t Light = 0;
  uint8_t Temperature = 0;
  uint8_t Humidity = 0;
  uint8_t bust_removal_flag = 0;

  uint8_t payload[128] = {0};

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DCMI_Init();
  MX_USART1_UART_Init();
  MX_FMC_Init();
  MX_ADC1_Init();
  MX_TIM6_Init();
  MX_ADC2_Init();
  /* USER CODE BEGIN 2 */

  delay_init(180);

  printf("STM32F429BIT6  WizNET W5300.\r\n");

  w5300_init();
  aliyun_init();
  eth_video_init();
  LCD_Init();
  SGP30_Init();
  dht11_init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  LCD_Clear(BLACK);
  POINT_COLOR = RED;
  BACK_COLOR = BLACK;
  LCD_ShowString(0, 0, 240, 16, 16, "Initializing...");

  do
  {
    SGP30_Write(0x20, 0x08);
    sgp30_dat = SGP30_Read();
    CO2Data = (sgp30_dat & 0xffff0000) >> 16;
    TVOCData = sgp30_dat & 0x0000ffff;
    HAL_Delay(100);
  } while (CO2Data == 400 && TVOCData == 0);

  LCD_Clear(WHITE);

  while (1)
  {
    do_aliyun_run();
    eth_video_run();

    SGP30_Write(0x20, 0x08);
    sgp30_dat = SGP30_Read();
    CO2Data = (sgp30_dat & 0xffff0000) >> 16;
    TVOCData = sgp30_dat & 0x0000ffff;

    get_gp2y10_value(&AQI, &PM25);

    get_light_value(&Light);

    dht11_read_data(&Temperature, &Humidity);

    if ((AQI >= 50) || (Temperature > 40))
    {
      HAL_GPIO_WritePin(DUST_REMOVAL_GPIO_Port, DUST_REMOVAL_Pin, GPIO_PIN_RESET);
      bust_removal_flag = 1;
    }
    else
    {
      HAL_GPIO_WritePin(DUST_REMOVAL_GPIO_Port, DUST_REMOVAL_Pin, GPIO_PIN_SET);
      bust_removal_flag = 0;
    }

    if (parms_update_count >= 1)
    {
      parms_update_count = 0;
      POINT_COLOR = BLUE;
      BACK_COLOR = WHITE;

      memset(lcd_buff, 0, sizeof(lcd_buff));
      sprintf((char *)lcd_buff, "CO2:%dppm    ", CO2Data);
      LCD_ShowString(0, 160 + 16, 120, 16, 16, lcd_buff);

      memset(lcd_buff, 0, sizeof(lcd_buff));
      sprintf((char *)lcd_buff, "TVOC:%dppd    ", TVOCData);
      LCD_ShowString(120, 160 + 16, 120, 16, 16, lcd_buff);

      memset(lcd_buff, 0, sizeof(lcd_buff));
      sprintf((char *)lcd_buff, "AQI:%d    ", AQI);
      LCD_ShowString(0, 160 + 32, 120, 16, 16, lcd_buff);

      memset(lcd_buff, 0, sizeof(lcd_buff));
      sprintf((char *)lcd_buff, "PM2.5:%dmg/m3    ", PM25);
      LCD_ShowString(120, 160 + 32, 120, 16, 16, lcd_buff);

      memset(lcd_buff, 0, sizeof(lcd_buff));
      sprintf((char *)lcd_buff, "TEMP:%d    ", Temperature);
      LCD_ShowString(0, 160 + 48, 120, 16, 16, lcd_buff);

      memset(lcd_buff, 0, sizeof(lcd_buff));
      sprintf((char *)lcd_buff, "HUMI:%d%%    ", Humidity);
      LCD_ShowString(120, 160 + 48, 120, 16, 16, lcd_buff);

      memset(lcd_buff, 0, sizeof(lcd_buff));
      sprintf((char *)lcd_buff, "Light:%d%%    ", Light);
      LCD_ShowString(0, 160 + 64, 120, 16, 16, lcd_buff);

      memset(lcd_buff, 0, sizeof(lcd_buff));
      sprintf((char *)lcd_buff, "DUST:%d    ", bust_removal_flag);
      LCD_ShowString(120, 160 + 64, 120, 16, 16, lcd_buff);
    }

    if (image_update_count >= 10)
    {
      image_update_count = 0;
      LCD_ShowImage(get_video_rgb565(), 0, 0);
    }

    if (aliyun_auto_up_count >= 1)
    {
      aliyun_auto_up_count = 0;
      sprintf((char*)payload, "{\"params\":{\
\"co2\":{\"value\":%d},\
\"TVOC\":{\"value\":%d},\
\"PM25\":{\"value\":%d},\
\"mtemp\":{\"value\":%d},\
\"mhumi\":{\"value\":%d},\
\"mlux\":{\"value\":%d}\
},\"method\":\"thing.event.property.post\"}", CO2Data, TVOCData, PM25, Temperature, Humidity, Light);
      aliyun_publish(payload);
    }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void main_timer(void)
{
  parms_update_count++;
  image_update_count++;
  aliyun_auto_up_count++;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
