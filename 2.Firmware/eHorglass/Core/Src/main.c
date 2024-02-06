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
#include "common.h"
#include "SandMove.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t gDirection = 1;
uint8_t sandNum = 64;
uint8_t ledScreen1[LED_WIDTH * LED_WIDTH];
uint8_t ledScreen2[LED_WIDTH * LED_WIDTH];
uint8_t ledScreenData1[LED_WIDTH];
uint8_t ledScreenData2[LED_WIDTH];
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
    MX_USB_DEVICE_Init();
    /* USER CODE BEGIN 2 */
    MPU6050_Init();
    HAL_Delay(100);
    gDirection = MPU6050_GetDirection(1);
    max7219_handle led1_handle;
    max7219_handle led2_handle;
    led1_handle.spiHandle = &hspi1;
    led1_handle.CS_GPIO = LED1_CS_GPIO_Port;
    led1_handle.CS_Pin = LED1_CS_Pin;
    led2_handle.spiHandle = &hspi2;
    led2_handle.CS_GPIO = LED2_CS_GPIO_Port;
    led2_handle.CS_Pin = LED2_CS_Pin;
    Max7219_Init(led1_handle);
    Max7219_Init(led2_handle);
    Max7219_DisplayNromal(led1_handle);
    Max7219_DisplayNromal(led2_handle);

    srand((unsigned)time(NULL));
    for (uint8_t i = 0;i < LED_WIDTH * LED_WIDTH;i++) {
        ledScreen1[i] = EMPTY;
        ledScreen2[i] = EMPTY;
    }
    if (Sand_GetUpLed(gDirection) == LED_SCREEN_1) {
        for (uint8_t i = 0;i < sandNum;i++) {
            coord xy = Sand_GetLoopCoord(i, gDirection, 0);
            ledScreen1[xy.x * LED_WIDTH + xy.y] = FULL;
        }
    }
    else {
        for (uint8_t i = 0;i < sandNum;i++) {
            coord xy = Sand_GetLoopCoord(i, gDirection, 0);
            ledScreen2[xy.x * LED_WIDTH + xy.y] = FULL;
        }
    }
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        gDirection = MPU6050_GetDirection(1);

        uint8_t upLED = Sand_GetUpLed(gDirection);
        uint8_t downLED = Sand_GetDownLed(gDirection);
        uint8_t* nowScreen = NULL;
        uint8_t* nextScreen = NULL;
        uint8_t nowLEDNum = downLED;
        for (uint8_t i = 0;i < LED_WIDTH;i++) {
            for (uint8_t j = 0;j < LED_WIDTH;j++) {
                if (upLED == LED_SCREEN_1) {
                    nowScreen = ledScreen2;
                    nextScreen = ledScreen1;
                }
                else {
                    nowScreen = ledScreen1;
                    nextScreen = ledScreen2;
                }
            }
        }

        Sand_UpdateScreen(nowScreen, nextScreen, nowLEDNum, sandNum, gDirection);
        nowLEDNum = 1 - nowLEDNum;
        Sand_UpdateScreen(nextScreen, nowScreen, nowLEDNum, sandNum, gDirection);

        for (uint8_t i = 0;i < LED_WIDTH;i++) {
            uint8_t ledBuf1 = 0;
            uint8_t ledBuf2 = 0;
            for (uint8_t j = 0;j < LED_WIDTH;j++) {
                ledBuf1 = ledBuf1 + (ledScreen1[i * LED_WIDTH + j] << j);
                ledBuf2 = ledBuf2 + (ledScreen2[i * LED_WIDTH + j] << j);
            }
            ledScreenData1[i] = ledBuf1;
            ledScreenData2[i] = ledBuf2;
        }
        Max7219_Display(led1_handle, 0, ledScreenData1);
        Max7219_Display(led2_handle, 0, ledScreenData2);
        HAL_Delay(100);
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
    RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

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
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
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
void assert_failed(uint8_t* file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
              /* User can add his own implementation to report the file name and line number,
                 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
                 /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
