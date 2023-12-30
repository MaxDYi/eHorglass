
#include "MAX7219.h"

void Max7219_Write(max7219_handle handle, uint8_t addr, uint8_t data)
{
    uint8_t tx_data[2] = { addr ,data };
    HAL_GPIO_WritePin(handle.CS_GPIO, handle.CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, tx_data, 2, 0x10);
    HAL_GPIO_WritePin(handle.CS_GPIO, handle.CS_Pin, GPIO_PIN_SET);
}

void Max7219_Init(max7219_handle handle)
{
    Max7219_Write(handle, 0x09, 0x00);
    Max7219_Write(handle, 0x0a, 0x03);
    Max7219_Write(handle, 0x0b, 0x07);
    Max7219_Write(handle, 0x0c, 0x01);
    Max7219_Write(handle, 0x0f, 0x00);
}

void Max7219_TurnOffAll(max7219_handle handle)
{
    for (uint8_t i = 0;i < 8;i++)
    {
        Max7219_Write(handle, i + 1, 0x00);
    }
}

void Max7219_TurnOnAll(max7219_handle handle)
{
    for (uint8_t i = 0;i < 8;i++)
    {
        Max7219_Write(handle, i + 1, 0xff);
    }
}

void Max7219_Display(max7219_handle handle, uint8_t* data)
{
    Max7219_TurnOffAll(handle);
    for (uint8_t i = 0;i < 8;i++)
    {
        Max7219_Write(handle, i + 1, data[i]);
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
            Max7219_Write(handle, i, 0x00);
        }
        Max7219_Write(handle, i + 1, 0xff);
        HAL_Delay(500);
    }
    Max7219_TurnOffAll(handle);
}
