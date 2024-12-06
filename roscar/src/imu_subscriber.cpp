#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

void imuCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
    // 获取加速度计数据 (单位: m/s²)
    double acc_x = msg->linear_acceleration.x;
    double acc_y = msg->linear_acceleration.y;
    double acc_z = msg->linear_acceleration.z;

    // 获取角速度数据 (单位: rad/s)
    double gyro_x = msg->angular_velocity.x;
    double gyro_y = msg->angular_velocity.y;
    double gyro_z = msg->angular_velocity.z;

    // 获取方向数据 (单位: 四元数)
    double orientation_x = msg->orientation.x;
    double orientation_y = msg->orientation.y;
    double orientation_z = msg->orientation.z;
    double orientation_w = msg->orientation.w;

    // 打印数据
    ROS_INFO("Acceleration (m/s^2): x=%.2f, y=%.2f, z=%.2f", acc_x, acc_y, acc_z);
    ROS_INFO("Gyroscope (rad/s): x=%.2f, y=%.2f, z=%.2f", gyro_x, gyro_y, gyro_z);
    ROS_INFO("Orientation (Quaternion): x=%.2f, y=%.2f, z=%.2f, w=%.2f", orientation_x, orientation_y, orientation_z, orientation_w);
}

int main(int argc, char** argv)
{
    // 初始化 ROS 节点
    ros::init(argc, argv, "imu_subscriber");
    ros::NodeHandle nh;

    // 订阅 IMU 数据
    ros::Subscriber sub = nh.subscribe("/imu", 1000, imuCallback);

    // 保持节点运行
    ros::spin();

    return 0;
}
