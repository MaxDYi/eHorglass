/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2024-02-15 14:22:57
 * @LastEditTime : 2024-02-16 09:55:34
 * @FilePath     : \ArcheryTimer_Appe:\eHorglass\2.Firmware\eHorglass\Drivers\parameter\parameter.h
 */
#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct parameters
{
    uint32_t initFlag;
    uint32_t sandNum;
    uint32_t frameTime;
    float angleOffset;
};

void LoadParameters(struct parameters* para);

uint8_t SaveParameters(struct parameters* para);

#endif // __PARAMETER_H__