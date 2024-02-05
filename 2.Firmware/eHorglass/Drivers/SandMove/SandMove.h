/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2024-02-04 20:48:36
 * @LastEditTime : 2024-02-05 22:10:12
 * @FilePath     : \ArcheryTimer_Appe:\eHorglass\2.Firmware\eHorglass\Drivers\SandMove\SandMove.h
 */
#ifndef __SANDMOVE_H__
#define __SANDMOVE_H__

#include "common.h"
#include "time.h"

#define LED_WIDTH 8
#define SAND_MAX_NUM (LED_WIDTH*LED_WIDTH)

#define LED_SCREEN_1 0
#define LED_SCREEN_2 1

#define EMPTY 0
#define FULL 1

#define OUT 0
#define IN 1

#define MID 0
#define LEFT 1
#define RIGHT 2

typedef struct
{
    int x;
    int y;
}coord;

coord Sand_GetLoopCoord(uint8_t index, uint8_t direction, uint8_t randNum);

void Sand_GetTarget(coord now_xy, coord* target_xy, uint8_t direction);

uint8_t Sand_GetUpLed(uint8_t gDirection);

uint8_t Sand_GetDownLed(uint8_t gDirection);

uint8_t Sand_IsBorder(int x);

uint8_t Sand_IsVertex(coord target_xy, uint8_t direction);

uint8_t Sand_IsDownVertex(coord target_xy, uint8_t direction);

uint8_t Sand_IsUpVertex(coord target_xy, uint8_t direction);

uint8_t Sand_TargetIsEmpty(coord target_xy, uint8_t nowLEDNum, uint8_t direction, uint8_t* now_screen, uint8_t* next_screen);

void Sand_MoveToTarget(coord now_xy, coord target_xy, uint8_t direction, uint8_t nowLEDNum, uint8_t* now_screen, uint8_t* next_screen);

void Sand_UpdateScreen(uint8_t* nowScreen, uint8_t* nextScreen, uint8_t nowLEDNum, uint8_t sandNum, uint8_t gDirection);

#endif