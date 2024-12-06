## 一、环境配置
***Ubuntu20.04  ROS1-noetic***

### 1.编译
##### 1.首先在一个合适的位置打开终端，执行命令
```git clone https://github.com/iamgod-king/SDK_roscar.git```
##### 2.随后编译
```catkin_make```

### 2.运行launch
#####  1.source工作空间环境(每次在新的终端窗口都要source一下)
```source path/to/your/workspace/SDK_roscar/devel/setup.bash```
  **例如**
  ```source ~/SDK_roscar/devel/setup.bash```
##### 2.启动地图和机器人的gazebo
```roslaunch roscar roscar_gazebo.launch```
##### 3.启动rviz和雷达点云图
```roslaunch roscar roscar_move.launch```
##### 4.启动camera和imu的订阅节点
```roslaunch roscar camera_imu.launch```

### 完毕

#### 注：
##### 1.可能会需要安装 Arbotix，Arbotix 是一款控制电机、舵机的控制板，并提供相应的 ros 功能包
```sudo apt-get install ros-noetic-arbotix```
##### 2.可能会需要安装键盘控制机器人的ROS包
```sudo apt install ros-noetic-teleop-twist-keyboard```

## 二、任务描述

该SDK制作耗时7天，从机器人xacro模型、世界gazebo模型到传感器的纯手搓ROS1小车仿真。由左右两个驱动轮、一个万向轮、一个2D激光雷达、一个普通单目摄像头、一个imu构成。
<img src="小车简图.png" alt="alt text" width="400"/>
<img src="1.png" alt="alt text" width="400"/>

### 本次考核概述

本次考核主要面对无人机的二维定点问题，随着光流技术日益成熟，电赛主办方更倾向于选择难以分辨的地面来干扰光流定点效果，而雷达方案则更加稳定。

在室内定位中，以 IMU 为主，同时雷达点云数据辅助融合。

---

#### 系统组件

- **摄像头节点**：`camera_subscriber`
- **IMU 节点**：`imu_subscriber`
- **机器人控制**：接收 `/cmd_vel` 消息，控制底盘的线速度和角速度来进行运动。

---

#### 参数设置

##### 摄像头
- **帧率**：30 Hz
- **分辨率**：640x480

##### 雷达
- **频率**：10 Hz
- **测量范围**：0.1 m 至 10 m
- **测量弧度**：-1 至 1 弧度

##### IMU
- **频率**：100 Hz


##### 任务一：键盘控制机器人平移与旋转，并运动至能够看到橙蓝柱子的位置

1. 请用键盘发布 `/cmd_vel` 消息，控制机器人平移与旋转。
2. 运动至能够看到橙蓝柱子的位置。
3. 请简单录制并提交一个键盘控制视频。
<img src="橙蓝柱.png" alt="alt text" width="400"/>
---

##### 任务二：使用 OpenCV 实时显示转化成 HSV 格式后的视频，并保存

1. 使用 OpenCV，在 `camera_subscriber.cpp` 中编写代码，实时显示转化为 HSV 格式后的视频。
2. 保存任务一中从原点移动至看到橙蓝柱子的 HSV 视频。
3. 提交 OpenCV 保存的视频。

---

##### 任务三（难）：融合 IMU 和雷达点云数据，并在终端发布自己位置

1. 融合 IMU 和雷达点云数据。
2. 在终端发布自己位置。
3. 请在网上认真搜集资料并移植一个适合的算法。
4. 请简单录制运行过程的视频。

---

## 提交要求

1. 提交视频与整个 `roscar` 包代码，并发送至邮箱：`yinzhe23@bupt.edu.cn`。
2. 提示：
   - SDK 已配好 `rviz.config`、`map.world`、`xacro`、`model`，主要在 `camera_subscriber.cpp`、`imu_subscriber.cpp` 编写代码，并编写新的 CPP 与 Launch 文件。
   - 由于 Gazebo 问题，可能会出现障碍物悬浮在空中的情况，请在 QQ 群中提问或私信解决。
