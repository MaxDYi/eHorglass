/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2024-02-04 20:48:28
 * @LastEditTime : 2024-02-04 20:53:53
 * @FilePath     : \ArcheryTimer_Appe:\eHorglass\2.Firmware\eHorglass\Drivers\LED8x8\LED8x8.c
 */
#include "LED8x8.h"

void SandInfoInit(sandInfo_s* sandInfos, uint8_t sandNum)
{
    if (sandNum > SAND_MAX_NUM)
    {
        sandNum = SAND_MAX_NUM;
        for (uint8_t i = 0; i < LED_WIDTH; i++)
        {
            for (uint8_t j = 0; j < LED_WIDTH; j++) {
                sandInfos[i].x = 0;
                sandInfos[i].y = 0;
                sandInfos[i].isMoved = 0;
                sandInfos[i].ledScreen = 1;
            }
        }
    }
    else {
        if (sandNum > (SAND_MAX_NUM / 2 + LED_WIDTH / 2)) {
            uint8_t row = 0;
            for (uint8_t i = 0; i < sandNum;row++)
            {
                for (uint8_t j = 0;j < row + 1;i++, j++) {
                    sandInfos[i].x = j;
                    sandInfos[i].y = row - j;
                    sandInfos[i].isMoved = 0;
                    sandInfos[i].ledScreen = 1;
                }
            }
        }
        else {
            uint8_t row = 0;
            for (uint8_t i = 0; i < sandNum;row++)
            {
                for (uint8_t j = 0;j < row + 1;i++, j++) {
                    sandInfos[i].x = j;
                    sandInfos[i].y = row - j;
                    sandInfos[i].isMoved = 0;
                    sandInfos[i].ledScreen = 1;
                }
            }
        }
    }
}