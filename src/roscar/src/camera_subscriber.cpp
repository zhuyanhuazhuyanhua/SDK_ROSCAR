#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>

class CameraSubscriber
{
public:
    CameraSubscriber()
    {
        // 初始化图像订阅器
        image_transport::ImageTransport it(nh_);
        image_sub_ = it.subscribe("/camera/image_raw", 1, &CameraSubscriber::imageCallback, this);

        // 初始化摄像头信息订阅器
        camera_info_sub_ = nh_.subscribe("/camera/camera_info", 1, &CameraSubscriber::cameraInfoCallback, this);
    }

    // 回调函数：处理图像消息
    void imageCallback(const sensor_msgs::ImageConstPtr& msg)
    {
        try
        {
            // 使用 cv_bridge 将 ROS 图像消息转换为 OpenCV 图像
            cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
            
            // 在窗口中显示图像
            cv::imshow("Camera Image", cv_ptr->image);
            cv::waitKey(30);  // 等待30ms，显示图像
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
        }
    }

    // 回调函数：处理摄像头信息消息
    void cameraInfoCallback(const sensor_msgs::CameraInfoConstPtr& msg)
    {
        //ROS_INFO("Camera Info: Width: %d, Height: %d", msg->width, msg->height);
    }

private:
    ros::NodeHandle nh_;
    image_transport::Subscriber image_sub_;
    ros::Subscriber camera_info_sub_;
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "camera_subscriber");

    CameraSubscriber camera_subscriber;

    // 循环处理ROS消息
    ros::spin();

    return 0;
}
