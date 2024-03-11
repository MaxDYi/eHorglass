/*
 * @Description  : LED点阵驱动
 * @Author       : MaxDYi
 * @Date         : 2023-12-30 17:17:09
 * @LastEditTime: 2024-03-11 16:03:47
 * @FilePath: \ArcheryTimer_Appe:\eHorglass\2.Firmware\eHorglass\Drivers\MAX7219\MAX7219.c
 */

#include "MAX7219.h"
#include "stdio.h"
#include "string.h"

#define MAX7219_MODE_DECODE_ADDR 0X09
#define MAX7219_MODE_NODECODE 0X00
#define MAX7219_MODE_DECODE 0XFF
#define MAX7219_MODE_INTENSITY_ADDR 0X0A
#define MAX7219_MODE_INTENSITY_1 0X00
#define MAX7219_MODE_INTENSITY_3 0X01
#define MAX7219_MODE_INTENSITY_5 0X02
#define MAX7219_MODE_INTENSITY_7 0X03
#define MAX7219_MODE_INTENSITY_9 0X04
#define MAX7219_MODE_INTENSITY_11 0X05
#define MAX7219_MODE_INTENSITY_13 0X06
#define MAX7219_MODE_INTENSITY_15 0X07
#define MAX7219_MODE_INTENSITY_17 0X08
#define MAX7219_MODE_INTENSITY_19 0X09
#define MAX7219_MODE_INTENSITY_21 0X0A
#define MAX7219_MODE_INTENSITY_23 0X0B
#define MAX7219_MODE_INTENSITY_25 0X0C
#define MAX7219_MODE_INTENSITY_27 0X0D
#define MAX7219_MODE_INTENSITY_29 0X0E
#define MAX7219_MODE_INTENSITY_31 0X0F
#define MAX7219_MODE_SCAN_LIMIT_ADDR 0X0B
#define MAX7219_MODE_SCAN_0 0X00
#define MAX7219_MODE_SCAN_1 0X01
#define MAX7219_MODE_SCAN_2 0X02
#define MAX7219_MODE_SCAN_3 0X03
#define MAX7219_MODE_SCAN_4 0X04
#define MAX7219_MODE_SCAN_5 0X05
#define MAX7219_MODE_SCAN_6 0X06
#define MAX7219_MODE_SCAN_7 0X07
#define MAX7219_MODE_SHUTDOWN_ADDR 0X0C
#define MAX7219_MODE_SHUTDOWN 0X00
#define MAX7219_MODE_WORK 0X01
#define MAX7219_MODE_DISPALY_ADDR 0X0F
#define MAX7219_MODE_TEST 0X01
#define MAX7219_MODE_NORMAL 0X00

/**
 * @description: 写MAX7219寄存器
 * @param {max7219_handle} handle
 * @param {uint8_t} addr
 * @param {uint8_t} data
 * @return {*}
 */
void Max7219_WriteReg(max7219_handle handle, uint8_t addr, uint8_t data)
{
    uint8_t tx_data[2] = {addr, data};
    HAL_GPIO_WritePin(handle.CS_GPIO, handle.CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(handle.spiHandle, tx_data, 2, 0xff);
    HAL_GPIO_WritePin(handle.CS_GPIO, handle.CS_Pin, GPIO_PIN_SET);
}

/**
 * @description: MAX7219初始化
 * @param {max7219_handle} handle
 * @return {*}
 */
void Max7219_Init(max7219_handle handle)
{
    Max7219_WriteReg(handle, MAX7219_MODE_SHUTDOWN_ADDR, MAX7219_MODE_SHUTDOWN);
    Max7219_WriteReg(handle, MAX7219_MODE_DECODE_ADDR, MAX7219_MODE_NODECODE);
    Max7219_WriteReg(handle, MAX7219_MODE_INTENSITY_ADDR, MAX7219_MODE_INTENSITY_17);
    Max7219_WriteReg(handle, MAX7219_MODE_SCAN_LIMIT_ADDR, MAX7219_MODE_SCAN_7);
    Max7219_WriteReg(handle, MAX7219_MODE_DISPALY_ADDR, MAX7219_MODE_NORMAL);
    Max7219_WriteReg(handle, MAX7219_MODE_SHUTDOWN_ADDR, MAX7219_MODE_WORK);
    Max7219_TurnOffAll(handle);
}

/**
 * @description: 关闭所有LED
 * @param {max7219_handle} handle
 * @return {*}
 */
void Max7219_TurnOffAll(max7219_handle handle)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        Max7219_WriteReg(handle, i + 1, 0x00);
    }
}

/**
 * @description: 打开所有LED
 * @param {max7219_handle} handle
 * @return {*}
 */
void Max7219_TurnOnAll(max7219_handle handle)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        Max7219_WriteReg(handle, i + 1, 0xff);
    }
}

/**
 * @description: 旋转数据方向
 * @param {uint8_t} direction
 * @param {uint8_t} *data
 * @return {*}
 */
void Max7219_RotateData(uint8_t direction, uint8_t *data)
{
    uint8_t temp[8];

    switch (direction)
    {
    case 1: // 90度旋转
        for (int i = 0; i < 8; ++i)
        {
            temp[i] = 0;
            for (int j = 0; j < 8; ++j)
            {
                temp[i] |= ((data[j] >> (7 - i)) & 1) << j;
            }
        }
        break;

    case 2: // 180度旋转
        for (int i = 0; i < 8; ++i)
        {
            temp[7 - i] = 0;
            for (int j = 0; j < 8; ++j)
            {
                temp[7 - i] |= ((data[i] >> j) & 1) << (7 - j);
            }
        }
        break;

    case 3: // 270度旋转
        for (int i = 0; i < 8; ++i)
        {
            temp[i] = 0;
            for (int j = 0; j < 8; ++j)
            {
                temp[i] |= ((data[7 - j] >> i) & 1) << j;
            }
        }
        break;

    default: // 0度旋转（无变化）
        return;
    }

    // 复制旋转后的数据回原数组
    for (int i = 0; i < 8; ++i)
    {
        data[i] = temp[i];
    }
}

/**
 * @description: 显示LED数据
 * @param {max7219_handle} handle
 * @param {uint8_t} direction
 * @param {uint8_t} *data
 * @return {*}
 */
void Max7219_Display(max7219_handle handle, uint8_t direction, uint8_t *data)
{
    Max7219_TurnOffAll(handle);
    if (direction > 3)
    {
        direction = 0;
    }
    uint8_t temp[8];
    for (uint8_t i = 0; i < 8; i++)
    {
        temp[i] = data[i];
    }
    Max7219_RotateData(direction, temp);
    for (uint8_t i = 0; i < 8; i++)
    {
        Max7219_WriteReg(handle, i + 1, temp[i]);
    }
}

/**
 * @description: MAX7219普通显示模式
 * @param {max7219_handle} handle
 * @return {*}
 */
void Max7219_DisplayNromal(max7219_handle handle)
{
    Max7219_WriteReg(handle, 0x0F, MAX7219_MODE_NORMAL);
}

/**
 * @description: MAX7219测试显示模式
 * @param {max7219_handle} handle
 * @return {*}
 */
void Max7219_DisplayTest(max7219_handle handle)
{
    Max7219_WriteReg(handle, 0x0F, MAX7219_MODE_TEST);
}

/**
 * @description: MAX7219测试
 * @param {max7219_handle} handle
 * @return {*}
 */
void Max7219_Test(max7219_handle handle)
{
    Max7219_TurnOnAll(handle);
    HAL_Delay(500);
    Max7219_TurnOffAll(handle);
    HAL_Delay(500);
    for (uint8_t i = 0; i < 8; i++)
    {
        if (i > 0)
        {
            Max7219_WriteReg(handle, i, 0x00);
        }
        Max7219_WriteReg(handle, i + 1, 0xff);
        HAL_Delay(500);
    }
    Max7219_TurnOffAll(handle);
}