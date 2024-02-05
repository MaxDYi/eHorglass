/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2024-02-04 20:48:28
 * @LastEditTime : 2024-02-05 14:24:50
 * @FilePath     : \ArcheryTimer_Appe:\eHorglass\2.Firmware\eHorglass\Drivers\SandMove\SandMove.c
 */
#include "SandMove.h"

void Sand_InfoInit(sandInfo_s* sandInfos, uint8_t sandNum)
{
    if (sandNum >= SAND_MAX_NUM)
    {
        sandNum = SAND_MAX_NUM;
        for (uint8_t i = 0; i < SAND_MAX_NUM; i++)
        {
            sandInfos[i].x = i / LED_WIDTH;
            sandInfos[i].y = i % LED_WIDTH;
            sandInfos[i].isMoved = 0;
            sandInfos[i].ledScreen = LED_SCREEN_2;

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
                    sandInfos[i].ledScreen = LED_SCREEN_2;
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
                    sandInfos[i].ledScreen = LED_SCREEN_2;
                }
            }
        }
    }
}

uint8_t Sand_TargetIsEmpty(int target_x, int target_y, uint8_t ledScreeNum, sandInfo_s* sandInfo, uint8_t sandNum) {
    for (uint8_t i = 0; i < sandNum; i++) {
        if (sandInfo[i].ledScreen == ledScreeNum && sandInfo[i].x == target_x && sandInfo[i].y == target_y) {
            return FALSE;
        }
    }
    return TRUE;
}

uint8_t Sand_TargetIsBorder(int target_x, int target_y) {
    if (target_x < 0 || target_x >= LED_WIDTH || target_y < 0 || target_y >= LED_WIDTH) {
        return TRUE;
    }
    return FALSE;
}

void Sand_GetMajorTarget(int* x, int* y, uint8_t direction)
{
    int operandsX[DIRECTION_NUM] = { 1,1,0,-1,-1,-1,0,1 };
    int operandsY[DIRECTION_NUM] = { 0,1,1,1,0,-1,-1,-1 };
    *x = *x + operandsX[direction];
    *y = *y + operandsY[direction];
}

void Sand_GetMinorTarget(int* x, int* y, uint8_t direction, uint8_t flag) {
    if (flag == LEFT) {
        uint8_t newDirection = (direction + 1) % 8;
        Sand_GetMajorTarget(x, y, newDirection);
    }
    else {
        uint8_t newDirection = (direction - 1) % 8;
        Sand_GetMajorTarget(x, y, newDirection);
    }
}

uint8_t Sand_Move(int target_x, int target_y, sandInfo_s* sandInfos, uint8_t sandNum, uint8_t currentSandIndex) {
    uint8_t emptyFlag = Sand_TargetIsEmpty(target_x, target_y, sandInfos[currentSandIndex].ledScreen, sandInfos, sandNum);
    uint8_t borderFlag = Sand_TargetIsBorder(target_x, target_y);
    if (emptyFlag == TRUE && borderFlag == FALSE) {
        sandInfos[currentSandIndex].isMoved = 1;
        sandInfos[currentSandIndex].x = target_x;
        sandInfos[currentSandIndex].y = target_y;
        return TRUE;
    }
    return FALSE;
}

uint8_t Sand_TargetIsConnectDot( int target_x, int target_y, uint8_t ledScreenNum) {
    if (ledScreenNum == LED_SCREEN_2) {
        if (target_x == LED_WIDTH && target_y == LED_WIDTH) {
            return TRUE;
        }
    }
    else {
        if (target_x == -1 && target_y == -1) {
            return TRUE;
        }
    }
    return FALSE;
}

void Sand_MoveToConnectDot(int target_x, int target_y, sandInfo_s* sandInfos, uint8_t sandNum, uint8_t currentSandIndex) {
    if (target_x == LED_WIDTH && target_y == LED_WIDTH) {
        sandInfos[currentSandIndex].isMoved = 1;
        sandInfos[currentSandIndex].x = 0;
        sandInfos[currentSandIndex].y = 0;
        sandInfos[currentSandIndex].ledScreen = LED_SCREEN_1;
    }
    else if (target_x == -1 && target_y == -1) {
        sandInfos[currentSandIndex].isMoved = 1;
        sandInfos[currentSandIndex].x = LED_WIDTH - 1;
        sandInfos[currentSandIndex].y = LED_WIDTH - 1;
        sandInfos[currentSandIndex].ledScreen = LED_SCREEN_2;
    }
}
