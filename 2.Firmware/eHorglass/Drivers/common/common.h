/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2024-02-04 16:37:57
 * @LastEditTime : 2024-02-05 18:50:42
 * @FilePath     : \ArcheryTimer_Appe:\eHorglass\2.Firmware\eHorglass\Drivers\common\common.h
 */
#ifndef __COMMON_H__
#define __COMMON_H__

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "time.h"

#define TRUE 1
#define FALSE 0
#define true 1
#define false 0

#define PI 3.14159265

#define DIRECTION_NUM 8

#define MPU6050_ANGEL_OFFSET 1.0

uint8_t DataInRange(float data, float mid, float range);

uint8_t GetDirection(float angle);

uint32_t FLASH_ReadWord(uint32_t address);


#endif
