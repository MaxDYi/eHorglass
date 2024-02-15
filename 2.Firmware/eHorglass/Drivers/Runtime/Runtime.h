#ifndef __RUNTIME_H__
#define __RUNTIME_H__

#include "main.h"
#include "tim.h"

void Runtime_Init(void);

void Runtime_Clear(void);

void Runtime_Start(void);

uint32_t Runtime_Stop(void);

#endif // __AT_H__