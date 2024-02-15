#ifndef __AT_H__
#define __AT_H__

#include "main.h"
#include "parameter.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void AT_Init(struct parameters* para);

void AT_ResponseOK(void);

void AT_ResponseError(void);

void AT_ResponseInfo(void);

void AT_RecevieReInit(void);

void AT_ResponseSandNum(uint32_t sandNum);

void AT_ResponseFrameTime(uint32_t time);

void AT_RecevieSandNum(uint32_t sandNum);

void AT_RecevieFrameTime(uint32_t time);

void AT_ParseCommand(uint8_t* buffer);

#endif // __AT_H__