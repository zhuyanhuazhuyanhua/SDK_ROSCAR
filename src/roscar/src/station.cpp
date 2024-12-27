#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/PoseStamped.h"
#include "tf/transform_broadcaster.h"

// 定义状态向量和协方差矩阵
struct State {
    double x, y, theta;
    double cov[3][3];
};

State state;

// 发布器
ros::Publisher fused_pub;

// 更新步骤
void update(const sensor_msgs::LaserScan::ConstPtr& scan) {
    // 使用激光扫描数据更新状态向量
    double measured_x = scan->ranges[0] * cos(scan->angle_min);
    double measured_y = scan->ranges[0] * sin(scan->angle_min);

    // 更新状态向量（简单的加权平均）
    state.x = 0.8 * state.x + 0.2 * measured_x;
    state.y = 0.8 * state.y + 0.2 * measured_y;

    // 更新协方差矩阵（示例，实际应根据具体算法更新）
    state.cov[0][0] *= 0.8; // 简单的协方差更新
    state.cov[1][1] *= 0.8;
}

// 预测步骤
void predict(const nav_msgs::Odometry::ConstPtr& odom) {
    // 使用里程计数据更新状态向量
    state.x += odom->pose.pose.position.x;
    state.y += odom->pose.pose.position.y;
    state.theta += odom->pose.pose.orientation.z;
}

// 主函数
int main(int argc, char **argv) {
    ros::init(argc, argv, "station");
    if (!ros::master::check()) {
        ROS_ERROR("ROS master is not running.");
        return 1;
    }

    ros::NodeHandle nh;

    // 初始化状态和协方差矩阵
    state.x = 0.0;
    state.y = 0.0;
    state.theta = 0.0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == j) state.cov[i][j] = 1.0; // 初始协方差对角线设为1
            else state.cov[i][j] = 0.0;
        }
    }

    // 创建一个订阅器来订阅 "scan" 话题，消息类型为 LaserScan
    ros::Subscriber scan_sub = nh.subscribe<sensor_msgs::LaserScan>("scan", 1000, update);

    // 创建一个订阅器来订阅 "odom" 话题，消息类型为 Odometry
    ros::Subscriber odom_sub = nh.subscribe<nav_msgs::Odometry>("odom", 1000, predict);

    // 创建一个发布器来发布融合结果
   
    // ... 现有代码 ...
// 创建一个发布器来发布融合结果
    fused_pub = nh.advertise<nav_msgs::Odometry>("fused_odom", 1000); // 修正为 nav_msgs::Odometry
// ... 现有代码 ...

    ros::Rate loop_rate(10); // 设置循环频率

    while (ros::ok()) {
        // 创建融合后的消息
        nav_msgs::Odometry fused_odom;
        fused_odom.header.stamp = ros::Time::now();
        fused_odom.header.frame_id = "map";
        fused_odom.child_frame_id = "base_footprint";

        // 设置位置和姿态
        fused_odom.pose.pose.position.x = state.x;
        fused_odom.pose.pose.position.y = state.y;
        fused_odom.pose.pose.orientation = tf::createQuaternionMsgFromYaw(state.theta);

        // 发布融合结果
        fused_pub.publish(fused_odom);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
