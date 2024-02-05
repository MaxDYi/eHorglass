/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2024-02-04 20:48:36
 * @LastEditTime : 2024-02-05 14:21:01
 * @FilePath     : \ArcheryTimer_Appe:\eHorglass\2.Firmware\eHorglass\Drivers\SandMove\SandMove.h
 */
#ifndef __SANDMOVE_H__
#define __SANDMOVE_H__

#include "common.h"

#define LEFT 0
#define RIGHT 1

#define LED_SCREEN_1 0
#define LED_SCREEN_2 1

typedef struct
{
    int x;
    int y;
    uint8_t isMoved;
    uint8_t ledScreen;
}sandInfo_s;

void Sand_InfoInit(sandInfo_s* sandInfo, uint8_t sandNum);

uint8_t Sand_TargetIsEmpty(int target_x, int target_y, uint8_t ledScreeNum, sandInfo_s* sandInfo, uint8_t sandNum);

uint8_t Sand_TargetIsBorder(int target_x, int target_y);

void Sand_GetMajorTarget(int* x, int* y, uint8_t direction);

void Sand_GetMinorTarget(int* x, int* y, uint8_t direction, uint8_t flag);

uint8_t Sand_Move(int target_x, int target_y, sandInfo_s* sandInfos, uint8_t sandNum, uint8_t currentSandIndex);

uint8_t Sand_TargetIsConnectDot(int target_x, int target_y, uint8_t ledScreenNum);

void Sand_MoveToConnectDot(int target_x, int target_y, sandInfo_s* sandInfos, uint8_t sandNum, uint8_t currentSandIndex);

#endif