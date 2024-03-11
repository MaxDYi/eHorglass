/*
 * @Description  : 代码段运行时间计算库
 * @Author       : MaxDYi
 * @Date         : 2024-02-15 14:08:18
 * @LastEditTime : 2024-02-15 14:17:09
 * @FilePath     : \ArcheryTimer_Appe:\eHorglass\2.Firmware\eHorglass\Drivers\Runtime\Runtime.c
 */
#include "Runtime.h"

#define RUNTIME_TIMER htim3

/**
 * @description: 运行时间计数器初始化
 * @return {*}
 */
void Runtime_Init(void)
{
    Runtime_Clear();
}

/**
 * @description: 清零运行计数器
 * @return {*}
 */
void Runtime_Clear(void)
{
    __HAL_TIM_SET_COUNTER(&RUNTIME_TIMER, 0);
}

/**
 * @description: 运行时间计数器开始
 * @return {*}
 */
void Runtime_Start(void)
{
    Runtime_Clear();
    HAL_TIM_Base_Start(&RUNTIME_TIMER);
}

/**
 * @description: 运行时间计数器停止
 * @return {*}
 */
uint32_t Runtime_Stop(void)
{
    HAL_TIM_Base_Stop(&RUNTIME_TIMER);
    return __HAL_TIM_GET_COUNTER(&RUNTIME_TIMER);
}