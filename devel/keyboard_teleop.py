#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist

def move():
    pub = rospy.Publisher('/cmd_vel', Twist, queue_size=1)
    rospy.init_node('keyboard_teleop', anonymous=True)
    rate = rospy.Rate(10) # 10hz

    while not rospy.is_shutdown():
        # 等待用户输入
        move_cmd = input("Enter your move (format: linear_x linear_y angular_z): ")
        try:
            linear_x, linear_y, angular_z = move_cmd.split()
            linear_x, linear_y, angular_z = float(linear_x), float(linear_y), float(angular_z)
            
            # 创建Twist消息
            twist = Twist()
            twist.linear.x = linear_x
            twist.linear.y = linear_y
            twist.angular.z = angular_z
            
            # 发布消息
            pub.publish(twist)
            rate.sleep()
            
        except ValueError:
            print("Invalid message format. Correct format is: linear_x linear_y angular_z")

if __name__ == '__main__':
    try:
        move()
    except rospy.ROSInterruptException:
        pass
