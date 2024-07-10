# PD快充风扇
特性：
- 供电支持Type-C PD快充协议和DC 12V直流供电。
- 可调转速，可自选高风速和静音模式，转速调节精度为300档，按下旋钮即可满速。
- 核心主控使用STM8，Release界面有编译完成的二进制文件，无需配置IDE即可刷入

## 实物图
TODO

## 电路图
26Pin版本电路图如下：  
![](./Images/电路原理图(26Pin).png)
PCB工程文件见目录[PCB](https://github.com/h13-0/Fan/tree/master/PCB)：
- 26Pin版本工程文件为[FAN_PCB(26Pin).PrjPcb](https://github.com/h13-0/Fan/blob/master/PCB/FAN_PCB(26Pin).PrjPcb)，PCB文件为[PCB1(26Pin).PcbDoc](https://github.com/h13-0/Fan/blob/master/PCB/PCB1(26Pin).PcbDoc)
- 28Pin版本工程文件为[FAN_PCB(28Pin).PrjPcb](https://github.com/h13-0/Fan/blob/master/PCB/FAN_PCB(28Pin).PrjPcb)，PCB文件为[PCB1(28Pin).PcbDoc](https://github.com/h13-0/Fan/blob/master/PCB/PCB1(28Pin).PcbDoc)
PCB尺寸统一为74mm\*25mm，孔位见PCB丝印。

## 外壳模型
外壳模型使用SolidWorks2024建模，有导出[STL文件](./Shell/外壳.STL)，使用3D打印即可完成制作。  
如需适配其他型号的80mm风扇，可基于上述建模修改或根据PCB丝印所标识的尺寸信息重新绘制。  

## 注意事项
市售的STM8S103FxP6的最小系统板有两个版本，分别为26Pin和28Pin，推荐使用26Pin版本，该版本较为常用。  
两个版本区别如下图所示：  
![](./Images/STM8S103F2F3%20Module区别.jpg)
（上为26Pin，下为28Pin）

## BOM

| 物料名称               | 参数/型号             | 数量 | 购买链接                                                                                         |
| --------------------- | --------------------- | ---- | ----------------------------------------------------------------------------------------------- |
| 80mm服务器风扇         | 8038 三洋 12V 1.8A    | 1    | https://item.taobao.com/item.htm?spm=a1z09.2.0.0.3a172e8dN2QdaD&id=12923471278&_u=a2ncf4788bf0  |
| STM8S103F3P6最小系统板 | 26Pin版本             | 1    | https://item.taobao.com/item.htm?spm=a1z09.2.0.0.3a172e8drIuggJ&id=524863693731&_u=a2ncf4783ec0 |
| PD诱骗器               | 12V                  | 1    | https://item.taobao.com/item.htm?spm=a1z09.2.0.0.3a172e8drIuggJ&id=639940641909&_u=a2ncf478ed00 |
| DC降压模块             | 12V转5V               | 1    | https://item.taobao.com/item.htm?spm=a1z09.2.0.0.67002e8dtGKmA8&id=560178970252&_u=a2ncf478929c |
| 3脚DC母座              |                      | 1    | https://item.taobao.com/item.htm?spm=a1z09.2.0.0.67002e8dtGKmA8&id=521786520463&_u=a2ncf478625b |
| EC11卧式编码器，带按钮  | 20脉冲/圈             | 1    | https://item.taobao.com/item.htm?spm=a1z09.2.0.0.67002e8dtGKmA8&id=7872903968&_u=a2ncf478e268   |
| 10K直插电阻            | AXIAL-0.4            | 3    | 略                                                                                              |
| xh2.54 弯头座          | 4Pin                 | 1    | https://item.taobao.com/item.htm?spm=a1z09.2.0.0.67002e8d309Yz2&id=587341434964&_u=a2ncf478175b |
| 4Pin风扇座             |                      | 1    | 任选，可用排针代替                                                                               |

