#include "parameter.h"

#define PARAMETER_ADDRESS 0x0800FC00
#define PARAMETER_LEN 0x100

/**
 * @description: Flash参数结构体
 * @return {*}
 */
struct parameters defaultParameters = {
    .initFlag = 0x01,
    .sandNum = 64,
    .frameTime = 200,
};

/**
 * @description: 加载参数
 * @param {parameters*} para
 * @return {*}
 */
void LoadParameters(struct parameters *para)
{
    uint32_t readBuffer[PARAMETER_LEN / 4];
    uint32_t address = PARAMETER_ADDRESS;
    memset(readBuffer, 0xFF, sizeof(readBuffer));
    for (uint16_t i = 0; i < PARAMETER_LEN / 4; i++)
    {
        readBuffer[i] = (*(__IO uint32_t *)address);
        address = address + 4;
    }
    memcpy(para, readBuffer, sizeof(struct parameters));
    if (para->initFlag != 0x01)
    {
        memcpy(para, &defaultParameters, sizeof(struct parameters));
        SaveParameters(para);
    }
    else
    {
        memcpy(para, readBuffer, sizeof(struct parameters));
    }
}

/**
 * @description: 保存参数
 * @param {parameters*} para
 * @return {*}
 */
uint8_t SaveParameters(struct parameters *para)
{
    uint32_t writeBuffer[PARAMETER_LEN / 4];
    uint32_t address = PARAMETER_ADDRESS;
    static FLASH_EraseInitTypeDef EraseInitStruct;
    HAL_FLASH_Unlock();
    uint32_t NbrOfPage = 1;
    uint32_t SECTORError = 0;
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.NbPages = NbrOfPage;
    EraseInitStruct.PageAddress = PARAMETER_ADDRESS;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
    {
        return -1;
    }
    memset(writeBuffer, 0xFF, sizeof(writeBuffer));
    memcpy(writeBuffer, para, sizeof(struct parameters));
    for (uint16_t i = 0; i < PARAMETER_LEN / 4; i++)
    {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, writeBuffer[i]) == HAL_OK)
        {
            address = address + 4;
        }
        else
        {
            return -1;
        }
    }
    HAL_FLASH_Lock();
    return 1;
}
