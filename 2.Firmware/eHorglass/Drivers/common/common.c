#include "common.h"

uint32_t FLASH_ReadWord(uint32_t address)
{
    return *(__IO uint32_t*)address;
}

