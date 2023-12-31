/*
 * @Description  : LED点阵驱动
 * @Author       : MaxDYi
 * @Date         : 2023-12-30 17:17:09
 * @LastEditTime : 2023-12-31 10:09:28
 * @FilePath     : \STM32F411CE_MAX7219\Drivers\MAX7219\MAX7219.c
 */

#include "MAX7219.h"
#include "stdio.h"
#include "string.h"

void Max7219_WriteReg(max7219_handle handle, uint8_t addr, uint8_t data)
{
    uint8_t tx_data[2] = { addr ,data };
    HAL_GPIO_WritePin(handle.CS_GPIO, handle.CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, tx_data, 2, 0xff);
    HAL_GPIO_WritePin(handle.CS_GPIO, handle.CS_Pin, GPIO_PIN_SET);
}

void Max7219_Init(max7219_handle handle)
{
    Max7219_WriteReg(handle, 0x09, 0x00);
    Max7219_WriteReg(handle, 0x0a, 0x03);
    Max7219_WriteReg(handle, 0x0b, 0x07);
    Max7219_WriteReg(handle, 0x0c, 0x01);
    Max7219_WriteReg(handle, 0x0f, 0x00);
    Max7219_TurnOffAll(handle);
}

void Max7219_TurnOffAll(max7219_handle handle)
{
    for (uint8_t i = 0;i < 8;i++)
    {
        Max7219_WriteReg(handle, i + 1, 0x00);
    }
}

void Max7219_TurnOnAll(max7219_handle handle)
{
    for (uint8_t i = 0;i < 8;i++)
    {
        Max7219_WriteReg(handle, i + 1, 0xff);
    }
}

void Max7219_RotateData(uint8_t direction, uint8_t* data) {
    uint8_t temp[8];

    switch (direction) {
    case 1:  // 90度旋转
        for (int i = 0; i < 8; ++i) {
            temp[i] = 0;
            for (int j = 0; j < 8; ++j) {
                temp[i] |= ((data[j] >> (7 - i)) & 1) << j;
            }
        }
        break;

    case 2:  // 180度旋转
        for (int i = 0; i < 8; ++i) {
            temp[7 - i] = 0;
            for (int j = 0; j < 8; ++j) {
                temp[7 - i] |= ((data[i] >> j) & 1) << (7 - j);
            }
        }
        break;

    case 3:  // 270度旋转
        for (int i = 0; i < 8; ++i) {
            temp[i] = 0;
            for (int j = 0; j < 8; ++j) {
                temp[i] |= ((data[7 - j] >> i) & 1) << j;
            }
        }
        break;

    default:  // 0度旋转（无变化）
        return;
    }

    // 复制旋转后的数据回原数组
    for (int i = 0; i < 8; ++i) {
        data[i] = temp[i];
    }
}

void Max7219_Display(max7219_handle handle, uint8_t direction, uint8_t* data)
{
    Max7219_TurnOffAll(handle);
    if (direction > 3) {
        direction = 0;
    }
    uint8_t temp[8];
    for (uint8_t i = 0; i < 8; i++)
    {
        temp[i] = data[i];
    }
    Max7219_RotateData(direction, temp);
    for (uint8_t i = 0; i < 8; i++) {
        Max7219_WriteReg(handle, i + 1, temp[i]);
    }

}

void Max7219_Test(max7219_handle handle)
{
    Max7219_TurnOnAll(handle);
    HAL_Delay(500);
    Max7219_TurnOffAll(handle);
    HAL_Delay(500);
    for (uint8_t i = 0;i < 8;i++)
    {
        if (i > 0) {
            Max7219_WriteReg(handle, i, 0x00);
        }
        Max7219_WriteReg(handle, i + 1, 0xff);
        HAL_Delay(500);
    }
    Max7219_TurnOffAll(handle);
}