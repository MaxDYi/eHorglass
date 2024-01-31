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
#include "cmsis_os.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "spi.h"
#include "MAX7219.h"
#include "MPU6050.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define CONFIG_SAND_NUM_DEFAULT 64
#define CONFIG_SCREEN_BRIGHTNESS_DEFAULT 0x08
#define CONFIG_GRAVITY_COEFFICENT_DEFAULT 1500

#define CONFIG_BASE_ADDRESS 0X0800FC00
#define CONFIG_INIT_FLAG_OFFSET_ADDRESS 0x0000
#define CONFIG_SAND_NUM_OFFSET_ADDRESS 0x0004
#define CONFIG_SCREEN_BRIGHTNESS_OFFSET_ADDRESS 0x0008
#define CONFIG_GRAVITY_COEFFICENT_OFFSET_ADDRESS 0x000C

#define CONFIG_INIT_FLAG_ADDRESS (CONFIG_BASE_ADDRESS + CONFIG_INIT_FLAG_OFFSET_ADDRESS)
#define CONFIG_SAND_NUM_ADDRESS (CONFIG_BASE_ADDRESS + CONFIG_SAND_NUM_OFFSET_ADDRESS)
#define CONFIG_SCREEN_BRIGHTNESS_ADDRESS (CONFIG_BASE_ADDRESS + CONFIG_SCREEN_BRIGHTNESS_OFFSET_ADDRESS)
#define CONFIG_GRAVITY_COEFFICENT_ADDRESS (CONFIG_BASE_ADDRESS + CONFIG_GRAVITY_COEFFICENT_OFFSET_ADDRESS)
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint32_t initFlag = 0;
uint32_t sandNum = CONFIG_SAND_NUM_DEFAULT;
uint32_t screenBrightness = CONFIG_SCREEN_BRIGHTNESS_DEFAULT;
uint32_t gravityCoefficent = CONFIG_GRAVITY_COEFFICENT_DEFAULT;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

uint32_t FLASH_ReadWord(uint32_t address)
{
    return *(__IO uint32_t *)address;
}
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
    initFlag = FLASH_ReadWord(CONFIG_INIT_FLAG_ADDRESS);
    if (initFlag == 0x01)
    {
        printf("Init Config\r\n");
        uint32_t err = 0;
        FLASH_EraseInitTypeDef EraseInitStruct = {
            .TypeErase = FLASH_TYPEERASE_PAGES,
            .PageAddress = CONFIG_BASE_ADDRESS,
            .NbPages = 1};
        HAL_FLASH_Unlock();
        HAL_FLASHEx_Erase(&EraseInitStruct, &err);
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, CONFIG_INIT_FLAG_ADDRESS, 0X01);
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, CONFIG_SAND_NUM_ADDRESS, sandNum);
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, CONFIG_SCREEN_BRIGHTNESS_ADDRESS, screenBrightness);
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, CONFIG_GRAVITY_COEFFICENT_ADDRESS, gravityCoefficent);
        HAL_FLASH_Lock();
    }

    sandNum = FLASH_ReadWord(CONFIG_BASE_ADDRESS + CONFIG_SAND_NUM_OFFSET_ADDRESS);
    screenBrightness = FLASH_ReadWord(CONFIG_BASE_ADDRESS + CONFIG_SCREEN_BRIGHTNESS_OFFSET_ADDRESS);
    gravityCoefficent = FLASH_ReadWord(CONFIG_BASE_ADDRESS + CONFIG_GRAVITY_COEFFICENT_OFFSET_ADDRESS);
    printf("sandNum:%d\r\n", sandNum);
    printf("screenBrightness:%d\r\n", screenBrightness);
    printf("gravityCoefficent:%1.3f\r\n", gravityCoefficent / 1000.0);



    max7219_handle led1;
    max7219_handle led2;
    led1.spiHandle = &hspi1;
    led1.CS_GPIO = LED1_CS_GPIO_Port;
    led1.CS_Pin = LED1_CS_Pin;
    led2.spiHandle = &hspi2;
    led2.CS_GPIO = LED2_CS_GPIO_Port;
    led2.CS_Pin = LED2_CS_Pin;
    Max7219_Init(led1);
    Max7219_Init(led2);

    Max7219_DisplayTest(led1);
    Max7219_DisplayTest(led2);

    Max7219_WriteReg(led1, 0x0A, 0x0f);
    Max7219_WriteReg(led2, 0x0A, 0x0f);

    HAL_Delay(100);

    // Max7219_DisplayNromal(led1);
    // Max7219_DisplayNromal(led2);

    // Max7219_Test(led1);
    // Max7219_Test(led2);
    /*
        uint8_t data[8] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};

            Max7219_Display(led1, 0, data);
            HAL_Delay(1000);
            Max7219_Display(led1, 1, data);
            HAL_Delay(1000);
            Max7219_Display(led1, 2, data);
            HAL_Delay(1000);
            Max7219_Display(led1, 3, data);
            HAL_Delay(1000);
            Max7219_Display(led1, 0, data);
            */
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


        HAL_Delay(500);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
