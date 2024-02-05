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
#include "common.h"
#include "SandMove.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t gDirection = 1;
uint8_t sandNum = 64;
uint8_t ledScreen1[LED_WIDTH][LED_WIDTH];
uint8_t ledScreen2[LED_WIDTH][LED_WIDTH];
uint8_t ledScreenData1[LED_WIDTH];
uint8_t ledScreenData2[LED_WIDTH];
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId taskDefaultHandle;
osThreadId taskMPU6050Handle;
osThreadId taskShowFrameHandle;
osThreadId taskUpdateHandle;
osSemaphoreId BinSem_RefreshHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void TaskDefault(void const* argument);
void TaskMPU6050(void const* argument);
void TaskShowFrame(void const* argument);
void TaskUpdate(void const* argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer, StackType_t** ppxIdleTaskStackBuffer, uint32_t* pulIdleTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer, StackType_t** ppxIdleTaskStackBuffer, uint32_t* pulIdleTaskStackSize)
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

    /* Create the semaphores(s) */
    /* definition and creation of BinSem_Refresh */
    osSemaphoreDef(BinSem_Refresh);
    BinSem_RefreshHandle = osSemaphoreCreate(osSemaphore(BinSem_Refresh), 1);

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

    /* definition and creation of taskShowFrame */
    osThreadDef(taskShowFrame, TaskShowFrame, osPriorityIdle, 0, 512);
    taskShowFrameHandle = osThreadCreate(osThread(taskShowFrame), (void*)BinSem_RefreshHandle);

    /* definition and creation of taskUpdate */
    osThreadDef(taskUpdate, TaskUpdate, osPriorityIdle, 0, 512);
    taskUpdateHandle = osThreadCreate(osThread(taskUpdate), NULL);

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
void TaskDefault(void const* argument)
{
    /* init code for USB_DEVICE */
    MX_USB_DEVICE_Init();
    /* USER CODE BEGIN TaskDefault */
            /* Infinite loop */
    for (;;)
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
void TaskMPU6050(void const* argument)
{
    /* USER CODE BEGIN TaskMPU6050 */
    MPU6050_Init();
    //MPU6050ReadID();

    osDelay(50);
    /* Infinite loop */
    for (;;)
    {
        short aData[3];
        short gData[3];
        MPU6050ReadAcc(aData);
        MPU6050ReadGyro(gData);
        float ax, ay;
        ax = (float)aData[0] / (0xffff / 4);
        ay = (float)aData[1] / (0xffff / 4);
        //az = (float)aData[2] / (0xffff / 4);
        //float x, y, z;
        //x = ax * cos(135 / 180.0 * PI) + ay * cos(45 / 180.0 * PI);
        //y = ax * sin(135 / 180.0 * PI) + ay * sin(45 / 180.0 * PI);
        //z = -az;
        float radian = atan2(ax, ay);
        float angle = radian * 180.0 / PI + MPU6050_ANGEL_OFFSET;
        gDirection = GetDirection(angle);

        //printf("direction:%d\tangle:%1.3f\tradian:%1.3f\r\n", gDirection, angle, radian);
        //float g = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        /*
        printf("----------------------------------------\r\n");
        printf("x:%1.3f g\r\n", x);
        printf("y:%1.3f g\r\n", y);
        printf("z:%1.3f g\r\n", z);
        printf("g:%1.3f\r\n", g);
        printf("----------------------------------------\r\n");
        */
        osDelay(100);
    }
    /* USER CODE END TaskMPU6050 */
}

/* USER CODE BEGIN Header_TaskShowFrame */
/**
* @brief Function implementing the taskShowFrame thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskShowFrame */
void TaskShowFrame(void const* argument)
{
    /* USER CODE BEGIN TaskShowFrame */
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
    /* Infinite loop */
    for (;;)
    {
        //if (osSemaphoreWait(BinSem_RefreshHandle, 0) == osOK) {
        for (uint8_t i = 0;i < LED_WIDTH;i++) {
            uint8_t ledBuf1 = 0;
            uint8_t ledBuf2 = 0;
            for (uint8_t j = 0;j < LED_WIDTH;j++) {
                ledBuf1 = ledBuf1 + (ledScreen1[i][j] << j);
                ledBuf2 = ledBuf2 + (ledScreen2[i][j] << j);
            }
            ledScreenData1[i] = ledBuf1;
            ledScreenData2[i] = ledBuf2;
        }
        Max7219_Display(led1_handle, 0, ledScreenData1);
        Max7219_Display(led2_handle, 0, ledScreenData2);
        //}

        osDelay(100);
    }
    /* USER CODE END TaskShowFrame */
}

/* USER CODE BEGIN Header_TaskUpdate */
/**
* @brief Function implementing the taskUpdate thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskUpdate */
void TaskUpdate(void const* argument)
{
    /* USER CODE BEGIN TaskUpdate */
    sandInfo_s sandInfos[SAND_MAX_NUM];
    //TODO:初始化位置错误
    Sand_InfoInit(sandInfos, sandNum);
    osSemaphoreRelease(BinSem_RefreshHandle);
    uint8_t loopDirection = 0;
    uint8_t index = 0;
    /* Infinite loop */
    for (;;)
    {
        while (1) {

            uint8_t LeftOrRight = 0;
            //printf("index=%d\r\n", index);
            for (index = 0; index < sandNum; ) {
                //printf("index = %d\r\n", index);
                if (sandInfos[index].isMoved == 0) {    //如果没有移动过
                    int target_x = sandInfos[index].x;
                    int target_y = sandInfos[index].y;
                    Sand_GetMajorTarget(&target_x, &target_y, gDirection);
                    if (Sand_Move(target_x, target_y, sandInfos, sandNum, index) == TRUE)   //如果向正下移动成功
                    {
                        index = 0;
                    }
                    else if (Sand_TargetIsConnectDot(target_x, target_y, sandInfos[index].ledScreen) == TRUE) {  //如果向正下移动失败，检查是否连接点
                        Sand_MoveToConnectDot(target_x, target_y, sandInfos, sandNum, index);   //如果是连接点，移动到连接点
                        index = 0;
                    }
                    else {
                        LeftOrRight = 1 - LeftOrRight;
                        target_x = sandInfos[index].x;
                        target_y = sandInfos[index].y;
                        Sand_GetMinorTarget(&target_x, &target_y, gDirection, LeftOrRight);
                        if (Sand_Move(target_x, target_y, sandInfos, sandNum, index) == TRUE) //如果向斜下移动成功
                        {
                            index = 0;
                        }
                        else {
                            LeftOrRight = 1 - LeftOrRight;  //如果向斜下移动失败，选择另一个方向
                            target_x = sandInfos[index].x;
                            target_y = sandInfos[index].y;
                            Sand_GetMinorTarget(&target_x, &target_y, gDirection, LeftOrRight);
                            if (Sand_Move(target_x, target_y, sandInfos, sandNum, index) == TRUE)   //如果向斜下移动成功
                            {
                                index = 0;
                            }
                            else {
                                index++;
                            }
                        }
                    }

                }
                else {  //如果移动过直接跳过
                    index++;
                }
            }
            loopDirection = 1 - loopDirection;
            break;
        }
        //清空显存
        for (uint8_t i = 0;i < LED_WIDTH;i++) {
            for (uint8_t j = 0;j < LED_WIDTH;j++) {
                ledScreen1[i][j] = 0;
                ledScreen2[i][j] = 0;
            }
        }
        //更新显存
        for (uint8_t i = 0;i < sandNum;i++) {
            sandInfos[i].isMoved = 0;
            if (sandInfos[i].ledScreen == 1) {
                ledScreen1[sandInfos[i].x][sandInfos[i].y] = 1;
            }
            else {
                ledScreen2[sandInfos[i].x][sandInfos[i].y] = 1;
            }

        }
        osSemaphoreRelease(BinSem_RefreshHandle);
        osDelay(1000);
    }
    /* USER CODE END TaskUpdate */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

