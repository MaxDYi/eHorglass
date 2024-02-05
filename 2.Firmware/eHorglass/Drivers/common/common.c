#include "common.h"

uint8_t DataInRange(float data, float mid, float range)
{
    if (data >= mid - range && data <= mid + range)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t GetDirection(float angle)
{
    if (DataInRange(angle, 90, 22.5)) {
        return 0;
    }
    else if (DataInRange(angle, 45, 22.5)) {
        return 1;
    }
    else if (DataInRange(angle, 0, 22.5)) {
        return 2;
    }
    else if (DataInRange(angle, -45, 22.5)) {
        return 3;
    }
    else if (DataInRange(angle, -90, 22.5)) {
        return 4;
    }
    else if (DataInRange(angle, -135, 22.5)) {
        return 5;
    }
    else if (DataInRange(angle, 180, 22.5)) {
        return 6;
    }
    else if (DataInRange(angle, 135, 22.5)) {
        return 7;
    }
    else {
        return 8;
    }
}



uint32_t FLASH_ReadWord(uint32_t address)
{
    return *(__IO uint32_t*)address;
}

