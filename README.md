# 电子沙漏

外壳设计

开关大小8.0x14.0mm

3D打印厚度1.5mm

| 内容     | 高度   |
| -------- | ------ |
| 底面     | 4.0mm  |
| 铜柱     | 15.0mm |
| 板厚     | 1.6mm  |
| 点阵     | 13mm   |
| 合计33.6 | 33.6mm |

点阵屏外形尺寸

![image-20240127191458166](https://raw.githubusercontent.com/MaxDYi/PicGo/main/img/202401271914271.png)





FLASH

STM32F103C8T6共64KB内部FLASH，分为64个Page，每Page为1KB。

![image-20240111133508131](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202401111335204.png)

使用前63个FLASH烧录App，最后一个FLash用于记录参数，参数表如下。

|        参数        | 字节数 | 格式  | 偏移地址 |  绝对地址   |    备注    |
| :----------------: | :----: | :---: | :------: | :---------: | :--------: |
|      InitFlag      |   4    | uint8 |  0x0000  | 0x0800_FC00 | 初始化标志 |
|      SandNum       |   4    | uint8 |  0x0004  | 0x0800_FC04 |  砂砾个数  |
|  ScreenBrightness  |   4    | uint8 |  0x0008  | 0x0800_FC08 |  屏幕亮度  |
| GravityCoefficient |   4    | float |  0x000C  | 0x0800_FC0C |  重力系数  |

