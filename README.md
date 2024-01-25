# 电子沙漏

外壳设计

开关大小8x14mm

3D打印厚度1.2mm

| 内容 | 高度   |
| ---- | ------ |
| 铜柱 | 10.0mm |
| 板厚 | 1.6mm  |
| 排母 | 8.5mm  |
| 点阵 | 6.5mm  |
| 冗余 | 0.2mm  |
| 合计 | 26.8mm |



![LED点阵](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202401081244703.jpg)





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

