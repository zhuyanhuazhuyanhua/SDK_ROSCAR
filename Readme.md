## 一、环境配置
Ubuntu20.04  ROS1-noetic

### 1.编译
##### 1.首先在一个合适的位置打开终端，执行命令
```git clone https://github.com/iamgod-king/SDK_roscar.git```
##### 2.随后编译
```catkin_make```

### 2.运行launch
#####  1.source工作空间环境(每次在新的终端窗户都要source一下)
```source path/to/your/workspace/SDK_roscar/devel/setup.bash```
  例如
  ```source ~/SDK_roscar/devel/setup.bash```
##### 2.启动地图和机器人的gazebo
```roslaunch roscar roscar_gazebo.launch```
##### 3.启动rviz和雷达点云图
```roslaunch roscar roscar_move.launch```
##### 4.启动camera和imu的订阅节点
```roslaunch roscar camera_imu.launch```

完毕

注：
1.ros1大概的架构默认你一定了解的一些，所以这里并未细致地讲在哪个目录下
2.可能会安装 Arbotix，Arbotix 是一款控制电机、舵机的控制板，并提供相应的 ros 功能包
```sudo apt-get install ros-noetic-arbotix```
3.可能会安装键盘控制机器人的ROS包
```sudo apt install ros-noetic-teleop-twist-keyboard```

## 二、任务描述

![alt text](1.png)
该SDK耗时7天，从机器人xacro模型、世界gazebo模型到传感器的纯手搓ROS1小车仿真。由左右两个驱动轮、一个万向轮、一个2D激光雷达、一个普通单目摄像头、一个imu构成。
![alt text](小车简图.png)

本次考核主要面对无人机的二维定点问题，随着光流技术日益成熟，电赛主办方更倾向于选择难以分辨的地面来干扰光流定点效果，雷达方案更加稳定。
在室内定位中，以imu为主，同时雷达点云数据辅助融合。

摄像头的camera_subscriber节点
imu的imu_subscriber节点
机器人接收/cmd_vel消息控制底盘的 线速度、角速度 来进行运动。
摄像头帧率30，像素640*480
雷达频率10，范围0.1m~10m，弧度-1~1
imu频率100

![alt text](橙蓝柱.png)
##### 任务一：键盘控制机器人平移与旋转，并运动至能够看到橙蓝柱子的位置

1. 请用键盘发布 `/cmd_vel` 消息，控制机器人平移与旋转。
2. 运动至能够看到橙蓝柱子的位置。
3. 请简单录制并提交一个键盘控制视频。

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
