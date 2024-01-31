/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "spi.h"
#include "MAX7219.h"
#include "MPU6050.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define PI 3.14159265
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId taskDefaultHandle;
osThreadId taskMPU6050Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void TaskDefault(void const * argument);
void TaskMPU6050(void const * argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of taskDefault */
  osThreadDef(taskDefault, TaskDefault, osPriorityNormal, 0, 128);
  taskDefaultHandle = osThreadCreate(osThread(taskDefault), NULL);

  /* definition and creation of taskMPU6050 */
  osThreadDef(taskMPU6050, TaskMPU6050, osPriorityIdle, 0, 256);
  taskMPU6050Handle = osThreadCreate(osThread(taskMPU6050), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_TaskDefault */
/**
  * @brief  Function implementing the taskDefault thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TaskDefault */
void TaskDefault(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN TaskDefault */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END TaskDefault */
}

/* USER CODE BEGIN Header_TaskMPU6050 */
/**
* @brief Function implementing the taskMPU6050 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskMPU6050 */
void TaskMPU6050(void const * argument)
{
  /* USER CODE BEGIN TaskMPU6050 */
    MPU6050_Init();
    MPU6050ReadID();
  /* Infinite loop */
  for(;;)
  {
        short aData[3];
        short gData[3];
        MPU6050ReadAcc(aData);
        MPU6050ReadGyro(gData);
        float ax,ay,az;
        ax=(float)aData[0] / (0xffff / 4);
        ay=(float)aData[1] / (0xffff / 4);
        az=(float)aData[2] / (0xffff / 4);
        /*
        float gx,gy,gz;
        gx=(float)gData[0] / (0xffff / 500);
        gy=(float)gData[1] / (0xffff / 500);
        gz=(float)gData[2] / (0xffff / 500);
        */
        float x,y,z;
        x=ax*cos(135/180.0*PI)+ay*cos(45/180.0*PI);
        y=ax*sin(135/180.0*PI)+ay*sin(45/180.0*PI);
        z=-az;
        float g=sqrt(pow(x,2)+pow(y,2)+pow(z,2));
        printf("----------------------------------------\r\n");
        printf("x:%1.3f g\r\n", x);
        printf("y:%1.3f g\r\n", y);
        printf("z:%1.3f g\r\n", z);
        printf("g:%1.3f\r\n", g);
        printf("----------------------------------------\r\n");
    osDelay(1000);
  }
  /* USER CODE END TaskMPU6050 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

