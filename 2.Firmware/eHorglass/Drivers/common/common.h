/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2024-02-04 16:37:57
 * @LastEditTime : 2024-02-04 19:56:04
 * @FilePath     : \ArcheryTimer_Appe:\eHorglass\2.Firmware\eHorglass\Drivers\common\common.h
 */
#ifndef __COMMON_H__
#define __COMMON_H__

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

#define LED_WIDTH 8
#define SAND_MAX_NUM (LED_WIDTH*LED_WIDTH)

#define DIRECTION_NUM 8

#define PI 3.14159265

#define MPU6050_ANGEL_OFFSET 1.0

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

typedef struct
{
    uint8_t x;
    uint8_t y;
    uint8_t isMoved;
    uint8_t ledScreen;
}sandInfo_s;

uint8_t DataInRange(float data, float mid, float range);

uint8_t GetDirection(float angle);

uint8_t LocationIsEmpty(uint8_t x, uint8_t y, uint8_t ledScreeNum, sandInfo_s* sandInfo, uint8_t sandNum);

uint32_t FLASH_ReadWord(uint32_t address);


#endif
