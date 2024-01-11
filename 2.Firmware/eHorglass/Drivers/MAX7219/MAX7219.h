/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2023-12-30 17:17:20
 * @LastEditTime : 2023-12-31 10:02:15
 * @FilePath     : \STM32F411CE_MAX7219\Drivers\MAX7219\MAX7219.h
 */
#ifndef __MAX7219_H__
#define __MAX7219_H__

#include "main.h"
#include "spi.h"

typedef struct MAX7219_Handle
{
    SPI_HandleTypeDef *spiHandle;
    GPIO_TypeDef *CS_GPIO;
    uint16_t CS_Pin;
} max7219_handle;

void Max7219_WriteReg(max7219_handle handle, uint8_t addr, uint8_t data);

void Max7219_Init(max7219_handle handle);

void Max7219_TurnOffAll(max7219_handle handle);

void Max7219_TurnOnAll(max7219_handle handle);

void Max7219_RotateData(uint8_t direction, uint8_t *data);

void Max7219_Display(max7219_handle handle, uint8_t direction, uint8_t *data);

void Max7219_DisplayNromal(max7219_handle handle);

void Max7219_DisplayTest(max7219_handle handle);

void Max7219_Test(max7219_handle handle);

#endif
