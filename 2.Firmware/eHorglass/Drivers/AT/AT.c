#include "AT.h"

#define AT_CMD_LEN 32

#define PARA_SAND_NUM_MAX 64
#define PARA_FRAME_TIME_MIN 20
#define PARA_FRAME_TIME_MAX 1000

struct parameters *flashPara;

/**
 * @description: usb虚拟串口输出
 * @param {uint8_t} *str
 * @return {*}
 */
void usb_printf(uint8_t *str)
{
    uint8_t len = strlen((char *)str);
    CDC_Transmit_FS(str, len);
}

/**
 * @description: 串口1输出
 * @param {uint8_t} *str
 * @return {*}
 */
void com_printf(uint8_t *str)
{
    uint8_t len = strlen((char *)str);
    HAL_UART_Transmit(&huart1, str, len, 0xFFFF);
}

/**
 * @description:AT指令初始化
 * @param {parameters} *para
 * @return {*}
 */
void AT_Init(struct parameters *para)
{
    flashPara = para;
}

/**
 * @description: AT指令回复OK
 * @return {*}
 */
void AT_ResponseOK(void)
{
    com_printf("OK\r\n");
    usb_printf("OK\r\n");
}

/**
 * @description: AT指令回复ERROR
 * @return {*}
 */
void AT_ResponseError(void)
{
    com_printf("ERROR\r\n");
    usb_printf("ERROR\r\n");
}

/**
 * @description: AT指令回复系统信息
 * @return {*}
 */
void AT_ResponseInfo(void)
{
    com_printf("Designed By MaxDYi\r\n2024/02\r\n");
    usb_printf("Designed By MaxDYi\r\n2024/02\r\n");
}

/**
 * @description: AT指令回复砂砾数量
 * @param {uint32_t} sandNum
 * @return {*}
 */
void AT_ResponseSandNum(uint32_t sandNum)
{
    uint8_t buffer[64];
    sprintf((char *)buffer, "AT+SANDNUM=%d\r\n", sandNum);
    com_printf(buffer);
    usb_printf(buffer);
}

/**
 * @description: AT指令回复帧时间
 * @param {uint32_t} time
 * @return {*}
 */
void AT_ResponseFrameTime(uint32_t time)
{
    uint8_t buffer[64];
    sprintf((char *)buffer, "AT+FRAMETIME=%d\r\n", time);
    com_printf(buffer);
    usb_printf(buffer);
}

/**
 * @description: AT指令接收重置
 * @return {*}
 */
void AT_RecevieReInit(void)
{
    flashPara->initFlag = 0;
    SaveParameters(flashPara);
    NVIC_SystemReset();
}

/**
 * @description: AT指令接收砂砾数量
 * @param {uint32_t} sandNum
 * @return {*}
 */
void AT_RecevieSandNum(uint32_t sandNum)
{
    if (sandNum <= PARA_SAND_NUM_MAX)
    {
        flashPara->sandNum = sandNum;
        SaveParameters(flashPara);
        AT_ResponseSandNum(sandNum);
        //AT_ResponseOK();
        //NVIC_SystemReset();
    }
    else
    {
        AT_ResponseError();
    }
}

/**
 * @description: AT指令接收帧时间
 * @param {uint32_t} time
 * @return {*}
 */
void AT_RecevieFrameTime(uint32_t time)
{
    if ((time >= PARA_FRAME_TIME_MIN) && (time <= PARA_FRAME_TIME_MAX))
    {
        flashPara->frameTime = time;
        SaveParameters(flashPara);
        AT_ResponseFrameTime(time);
        //AT_ResponseOK();
        //HAL_Delay(10); 
        //NVIC_SystemReset();
    }
    else
    {
        AT_ResponseError();
    }
}

/**
 * @description: AT指令解析
 * @param {uint8_t} *buffer
 * @return {*}
 */
void AT_ParseCommand(uint8_t *buffer)
{
    char command[AT_CMD_LEN];
    char questionMark;
    int number;
    memset(command, 0, AT_CMD_LEN);

    // 首先检查是否以"AT+"开头，并提取CMD部分
    if (sscanf((char *)buffer, "AT+%[^=]=%c", command, &questionMark) == 2)
    {
        // 检查"?"位置的字符是'?'还是数字
        if (questionMark == '?')
        {
            if (strcmp(command, "INFO") == 0)
            {
                AT_ResponseInfo();
            }
            else if (strcmp(command, "SANDNUM") == 0)
            {
                AT_ResponseSandNum(flashPara->sandNum);
            }
            else if (strcmp(command, "FRAMETIME") == 0)
            {
                AT_ResponseFrameTime(flashPara->frameTime);
            }
        }
        else
        {
            // 如果不是'?'，假设是数字，尝试解析整个字符串
            int result = sscanf((char *)buffer, "AT+%[^=]=%d", command, &number);
            if (result == 2)
            {
                // 解析成功，处理数字情况
                if (strcmp(command, "REINIT") == 0)
                {
                    if (number == 1)
                    {
                        AT_RecevieReInit();
                    }
                    else
                    {
                        AT_ResponseError();
                    }
                }
                else if (strcmp(command, "SANDNUM") == 0)
                {
                    AT_RecevieSandNum(number);
                }
                else if (strcmp(command, "FRAMETIME") == 0)
                {
                    AT_RecevieFrameTime(number);
                }
            }
            else
            {
                AT_ResponseError();
            }
        }
    }
    else
    {
        AT_ResponseError();
    }
}
