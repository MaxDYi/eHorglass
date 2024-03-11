# 电子沙漏

# 0 目录

1. 简介
2. 原理图
3. PCB
4. 外壳
5. 物料清单
6. 成本核算
7. 代码实现
8. AT指令

# 1 简介

电子沙漏使用STM32F103C8T6作为主控，利用MPU6050感知当前重力方向。

- 支持使用AT指令对运行参数进行配置。
- 支持更换点阵颜色（更换LED8x8点阵屏）。
- 支持Typec接口充电（内置900mAh锂电池）。

![image-20240218105633731](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202402181056795.png)



# 2 原理图

![eHorglass-SCH-V0.0](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202403111732414.png)

# 3 PCB

![image-20240218110747864](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202402181107907.png)

![image-20240218110751804](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202402181107850.png)

PCB使用4层板设计，面积4.6x9.2cm，主要元器件位于背面，正面仅有LED8x8点阵屏的圆形排母座。

# 4 外壳

外壳设计详见github库中的**4.Component**部分，共设计**外壳-上**与**外壳-上**两部分，使用3D打印进行实现，利用M3铜柱进行连接。

|  元件   |        尺寸        |   体积   |  表面积   |
| :-----: | :----------------: | :------: | :-------: |
| 外壳-上 | 3.2 * 5.2 * 9.8cm  | 17.72cm³ | 245.49cm² |
| 外壳-下 | 3.45 * 5.2 * 9.8cm | 24.72cm³ | 289.86cm² |

# 5 物料清单

| Comment          | Description                 | Designator                                                   | Footprint       | Quantity |
| ---------------- | --------------------------- | ------------------------------------------------------------ | --------------- | -------- |
| 10uF             | 贴片电容/MLCC电容           | C1, C2, C10, C12, C13                                        | C0603_M         | 5        |
| 100nF            | 贴片电容/MLCC电容           | C3, C4, C5, C6, C7,  C8, C9, C11, C14, C15, C16, C17, C18, C19 | C0603_M         | 14       |
| 20pF             | 贴片电容/MLCC电容           | C20, C21                                                     | C0603_M         | 2        |
| 1N5819           | 肖特基二极管                | D1, D2                                                       | SOD-323         | 2        |
| TP4056           | 锂电池充电管理              | IC1                                                          | SOIC-8_EP       | 1        |
| Header 5X2       | 5*2P接插件                  | JP1                                                          | HDR2.54-LI-2x5P | 1        |
| HDR-1X2          | 2P接插件                    | JP2                                                          | XH2.54-LI-2P    | 1        |
| 1588A            | 共阴单色LED8*8点阵屏        | LD1, LD2                                                     | LED 8*8-32-FH   | 2        |
| RED              | 贴片LED                     | LED1, LED3                                                   | LED0603_R       | 2        |
| GREEN            | 贴片LED                     | LED2                                                         | LED0603_G       | 1        |
| AO3401           | P沟道 30V/4.2A              | Q1                                                           | SOT23-3N        | 1        |
| 1K               | 贴片电阻                    | R1, R3, R11                                                  | R0603_M         | 3        |
| 2K               | 贴片电阻                    | R2                                                           | R0603_M         | 1        |
| 10K              | 贴片电阻                    | R4, R9, R10, R14                                             | R0603_M         | 4        |
| 20K              | 贴片电阻                    | R5, R6                                                       | R0603_M         | 2        |
| 5.1K             | 贴片电阻                    | R7, R8                                                       | R0603_M         | 2        |
| 4.7K             | 贴片电阻                    | R12, R13                                                     | R0603_M         | 2        |
| KCD1-101         | 1路单刀船型开关             | S1                                                           | HDR2.54-LI-2P   | 1        |
| M3铜柱           | 铜柱                        | SP1, SP2, SP3, SP4                                           | M3x20+6_N       | 4        |
| 3x6x5            | 3x6轻触开关                 | SW1                                                          | SW SMD-3*6*2.5  | 1        |
| STM32F103C8T6    | STM32 ARM-based  32-bit MCU | U1                                                           | LQFP48_N        | 1        |
| MAX7219          | 8位 LED驱动器               | U2, U3                                                       | SOIC-24W        | 2        |
| MPU6050          | 三轴加速度+三轴陀螺仪       | U4                                                           | QFN24-P50       | 1        |
| HT7533           | LDO线性稳压芯片             | U5                                                           | SOT89_N         | 1        |
| TYPE-C 2.0  -16P | USB2.0_Type-C_16Pin母座     | USBC1                                                        | USB-C-SMD_16P   | 1        |
| 8MHz             | 2脚无源晶振(谐振器）        | X1                                                           | OSC-5032-2P     | 1        |

# 6 成本核算

|   类目   |       型号       | 采购总价 | 采购数量 | 采购单价 | 使用数量 |    小计    |
| :------: | :--------------: | :------: | :------: | :------: | :------: | :--------: |
|   PCB    |  四层板1.6mm厚   | ¥100.44  |    10    | ¥10.0440 |    1     |   ¥10.04   |
|   SMT    |      经济型      | ¥133.06  |    10    | ¥13.3060 |    1     |   ¥13.31   |
|  元器件  | STM32F103C8T6等  |  ¥8.69   |    1     | ¥8.6900  |    1     |   ¥46.1    |
|   外壳   | 外壳（黑色树脂） |  ¥9.21   |    1     | ¥9.2100  |    1     |   ¥18.50   |
|  固定件  |   尼龙M3固定件   |  ¥6.43   |   100    | ¥0.0643  |    4     |   ¥0.67    |
|  锂电池  | 900mAh单节锂电池 |  ¥11.00  |    1     | ¥11.0000 |    1     |   ¥11.00   |
| **合计** |                  |          |          |          |          | **¥99.63** |

# 7 代码实现

## 7.1 软件环境

IAR 9.30

STM32CubeMX 6.5.0

## 7.2 主要库

使用到的库位于**\eHorglass\Drivers**路径下。

| 库        | 功能                 |
| --------- | -------------------- |
| AT        | AT指令控制与应答     |
| MAX7219   | 点阵屏驱动库         |
| MPU6050   | MPU6050陀螺仪驱动    |
| parameter | 运行参数配置库       |
| Runtime   | 获取代码段运行时间   |
| SandMove  | 砂砾运动控制核心算法 |

## 7.3 砂砾运动控制核心算法

算法流程图如下：

![流程图](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202403111706001.png)

## 7.4 Flash使用

STM32F103C8T6共64KB内部FLASH，分为64Page，每Page为1KB。

![image-20240218112618059](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202402181126115.png)

使用前63个FLASH烧录App，最后一个FLash区域用于记录参数。

|   用途    |          地址           | 大小 |
| :-------: | :---------------------: | :--: |
|    App    | 0x08000000 - 0x0800FBFF | 63KB |
| Parameter | 0x0800FC00 - 0x0800FFFF | 1KB  |

最后一个FLash区域记录的参数表如下：

|   参数    | 字节数 |  格式  |    备注    |
| :-------: | :----: | :----: | :--------: |
| initFlag  |   4    | uint32 | 初始化标志 |
|  sandNum  |   4    | uint32 |  砂砾个数  |
| frameTime |   4    | uint32 | 帧间隔时间 |

# 8 AT指令

支持使用AT指令修改运行参数，可以修改与砂砾个数（SANDNUM）显示帧间隔（FRAMETIME）。

指令分为查询指令与写入指令，均以“**\r\n**”结尾。

## 8.1 使用说明

使用的是STM32的USB虚拟串口实现AT指令，无需设置波特率、数据位、校验位和停止位。

使用时先打开电源开关，再将USB线插入电脑USB口，可以在串口调试助手中读取到“**STMicroelectronics Virtual COM Port**”的串口，如无法打开则尝试重新插拔。

## 8.1 查询指令

查询指令共有3条。

- AT+INFO=?
- AT+SANDNUM=?
- AT+FRAMETIME=?

这3条指令分别返回系统信息、砂砾个数与帧间隔时间。

## 8.2 写入指令

写入指令共有2条。

- AT+SANDNUM=num（AT+SANDNUM=64）
- AT+FRAMETIME=num（AT+FRAMETIME=150）

其中，num为正整数。对于AT+SANDNUM，num的限定值为1-64；对于AT+FRAMETIME，num的限定值为20-1000。
