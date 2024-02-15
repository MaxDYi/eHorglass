/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2024-02-15 14:08:18
 * @LastEditTime : 2024-02-15 14:17:09
 * @FilePath     : \ArcheryTimer_Appe:\eHorglass\2.Firmware\eHorglass\Drivers\Runtime\Runtime.c
 */
#include "Runtime.h"

#define RUNTIME_TIMER htim3

void Runtime_Init(void)
{
    Runtime_Clear();
}

void Runtime_Clear(void)
{
    __HAL_TIM_SET_COUNTER(&RUNTIME_TIMER, 0);
}

void Runtime_Start(void)
{
    Runtime_Clear();
    HAL_TIM_Base_Start(&RUNTIME_TIMER);
}

uint32_t Runtime_Stop(void)
{
    HAL_TIM_Base_Stop(&RUNTIME_TIMER);
    return __HAL_TIM_GET_COUNTER(&RUNTIME_TIMER);
}