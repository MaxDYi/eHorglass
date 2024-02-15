#include "AT.h"

#define AT_CMD_LEN 32

#define PARA_SAND_NUM_MAX 64
#define PARA_FRAME_TIME_MIN 20
#define PARA_FRAME_TIME_MAX 1000

struct parameters* flashPara;

void AT_Init(struct parameters* para)
{
    flashPara = para;
}

void AT_ResponseOK(void)
{
    printf("OK\r\n");
}

void AT_ResponseError(void)
{
    printf("ERROR\r\n");
}

void AT_ResponseInfo(void)
{
    printf("Designed By MaxDYi\r\n");
    printf("2024/02\r\n");
}

void AT_RecevieReInit(void)
{
    flashPara->initFlag = 0;
    SaveParameters(flashPara);
    NVIC_SystemReset();
}

void AT_ResponseSandNum(uint32_t sandNum)
{
    printf("AT+SANDNUM=%d\r\n", sandNum);
}

void AT_ResponseFrameTime(uint32_t time)
{
    printf("AT+FRAMETIME=%d\r\n", time);
}

void AT_RecevieSandNum(uint32_t sandNum)
{
    if (sandNum <= PARA_SAND_NUM_MAX) {
        flashPara->sandNum = sandNum;
        SaveParameters(flashPara);
        NVIC_SystemReset();
    }
    else {
        AT_ResponseError();
    }
}

void AT_RecevieFrameTime(uint32_t time)
{
    if (time >= PARA_FRAME_TIME_MIN && time <= PARA_FRAME_TIME_MAX) {
        flashPara->frameTime = time;
        SaveParameters(flashPara);
        NVIC_SystemReset();
    }
    else {
        AT_ResponseError();
    }
}

void AT_ParseCommand(uint8_t* buffer)
{
    char command[AT_CMD_LEN];
    char questionMark;
    int number;
    memset(command, 0, AT_CMD_LEN);

    // 首先检查是否以"AT+"开头，并提取CMD部分
    if (sscanf((char*)buffer, "AT+%[^=]=%c", command, &questionMark) == 2) {
        // 检查"?"位置的字符是'?'还是数字
        if (questionMark == '?') {
            if (strcmp(command, "INFO") == 0) {
                AT_ResponseInfo();
            }
            else if (strcmp(command, "SANDNUM") == 0) {
                AT_ResponseSandNum(flashPara->sandNum);
            }
            else if (strcmp(command, "FRAMETIME") == 0) {
                AT_ResponseFrameTime(flashPara->frameTime);
            }
        }
        else {
            // 如果不是'?'，假设是数字，尝试解析整个字符串
            int result = sscanf((char*)buffer, "AT+%[^=]=%d", command, &number);
            if (result == 2) {
                // 解析成功，处理数字情况
                if (strcmp(command, "REINIT") == 0) {
                    AT_RecevieReInit();
                }
                else if (strcmp(command, "SANDNUM") == 0) {
                    AT_RecevieSandNum(number);
                }
                else if (strcmp(command, "FRAMETIME") == 0) {
                    AT_RecevieFrameTime(number);
                }
            }
            else {
                // 解析失败，输入格式不符合预期
                printf("Invalid format.\n");
            }
        }
    }
    else {
        // 输入格式不符合预期
        printf("Invalid format.\n");
    }

}

