/**
 ******************************************************************************
 * @file    bsp_mpu6050.c
 * @author  STMicroelectronics
 * @version V1.0
 * @date    2013-xx-xx
 * @brief    mpu6050����
 ******************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:Ұ�� �Ե� ������
 * ��̳    :http://www.firebbs.cn
 * �Ա�    :https://fire-stm32.taobao.com
 *
 ******************************************************************************
 */

#include "MPU6050.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define I2C_MPU6050 hi2c1
#define MPU6050_ADDRESS 0x68
#define MPU6050_WRITE 0xD0
#define MPU6050_READ 0xD1

 /**
  * @brief   д���ݵ�MPU6050�Ĵ���
  * @param
  * @retval
  */
void MPU6050_WriteReg(uint8_t reg_add, uint8_t reg_dat)
{
    // I2C_ByteWrite(reg_dat, reg_add);
    HAL_I2C_Mem_Write(&I2C_MPU6050, MPU6050_WRITE,
        reg_add, I2C_MEMADD_SIZE_8BIT, &reg_dat, 1, 0x1f);
}

/**
 * @brief   ��MPU6050�Ĵ�����ȡ����
 * @param
 * @retval
 */
void MPU6050_ReadData(uint8_t reg_add, uint8_t* Read, uint8_t num)
{
    // I2C_BufferRead(Read, reg_add, num);
    HAL_I2C_Mem_Read(&I2C_MPU6050, MPU6050_READ,
        reg_add, I2C_MEMADD_SIZE_8BIT, Read, num, 0xff);
}

/**
 * @brief   ��ʼ��MPU6050оƬ
 * @param
 * @retval
 */
void MPU6050_Init(void)
{
    // HAL_Delay(1000);
    MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x80);
    HAL_Delay(100);
    MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00); // �������״̬
    MPU6050_WriteReg(MPU6050_RA_USER_CTRL, 0x00);  // I2C��ģʽ�ر�
    MPU6050_WriteReg(MPU6050_RA_FIFO_EN, 0x00);    // �ر�FIFO
    MPU6050_WriteReg(MPU6050_RA_SMPLRT_DIV, 0x07); // �����ǲ�����
    MPU6050_WriteReg(MPU6050_RA_CONFIG, 0x06);
    MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG, 0x01); // ���ü��ٶȴ�����������4Gģʽ
    MPU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);  // �������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
}

/**
 * @brief   ��ȡMPU6050��ID
 * @param
 * @retval  ��������1���쳣����0
 */
uint8_t MPU6050ReadID(void)
{
    unsigned char Re = 0;
    MPU6050_ReadData(MPU6050_RA_WHO_AM_I, &Re, 1); // ��������ַ
    if (Re != 0x68)
    {
        printf("MPU6050 dectected error!\r\n");
        return 0;
    }
    else
    {
        printf("MPU6050 ID = 0x%02X\r\n", Re);
        return 1;
    }
}

/**
 * @brief   ��ȡMPU6050�ļ��ٶ�����
 * @param
 * @retval
 */
void MPU6050ReadAcc(short* accData)
{
    uint8_t buf[6];
    MPU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
    accData[0] = (buf[0] << 8) + buf[1];
    accData[1] = (buf[2] << 8) + buf[3];
    accData[2] = (buf[4] << 8) + buf[5];
}

/**
 * @brief   ��ȡMPU6050�ĽǼ��ٶ�����
 * @param
 * @retval
 */
void MPU6050ReadGyro(short* gyroData)
{
    uint8_t buf[6];
    MPU6050_ReadData(MPU6050_GYRO_OUT, buf, 6);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}

/**
 * @brief   ��ȡMPU6050��ԭʼ�¶�����
 * @param
 * @retval
 */
void MPU6050ReadTemp(short* tempData)
{
    uint8_t buf[2];
    MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H, buf, 2); // ��ȡ�¶�ֵ
    *tempData = (buf[0] << 8) | buf[1];
}

/**
 * @brief   ��ȡMPU6050���¶����ݣ�ת�������϶�
 * @param
 * @retval
 */
void MPU6050_ReturnTemp(float* Temperature)
{
    short temp3;
    uint8_t buf[2];

    MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H, buf, 2); // ��ȡ�¶�ֵ
    temp3 = (buf[0] << 8) | buf[1];
    *Temperature = ((double)temp3 / 340.0) + 36.53;
}

/**
 * @brief   ��ȡMPU6050�Ƕȷ�ʽ������z�ᣩ
 * @param
 * @retval
 */
uint8_t MPU6050_GetDirection(float angelOffset) {
    short aData[3];
    MPU6050ReadAcc(aData);
    float ax, ay;
    ax = (float)aData[0] / (0xffff / 4);
    ay = (float)aData[1] / (0xffff / 4);
    float radian = atan2(ax, ay);
    float angle = radian * 180.0 / 3.14159265 + angelOffset;
    uint8_t gDirection = 0;
    if (DataInRange(angle, 90, 22.5)) {
        gDirection = 0;
    }
    else if (DataInRange(angle, 45, 22.5)) {
        gDirection = 1;
    }
    else if (DataInRange(angle, 0, 22.5)) {
        gDirection = 2;
    }
    else if (DataInRange(angle, -45, 22.5)) {
        gDirection = 3;
    }
    else if (DataInRange(angle, -90, 22.5)) {
        gDirection = 4;
    }
    else if (DataInRange(angle, -135, 22.5)) {
        gDirection = 5;
    }
    else if (DataInRange(angle, 180, 22.5)) {
        gDirection = 6;
    }
    else if (DataInRange(angle, 135, 22.5)) {
        gDirection = 7;
    }
    else {
        gDirection = 8;
    }
    return gDirection;
}

/**
 * @brief   �����Ƿ��ڷ�Χ��
 * @param
 * @retval
 */
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
