#!/usr/bin/env python3

import rospy
from std_msgs.msg import Float64

def talker():
    rospy.init_node('Steering_tt', anonymous=True)  # Initialize the node with a name

    pub = rospy.Publisher('Vectoring_steering', Float64, queue_size=10)  # Create a publisher object

    rate = rospy.Rate(1)  # 1 Hz
    while not rospy.is_shutdown():
        hello_str = 1.1
        rospy.loginfo(hello_str)
        pub.publish(hello_str)  # Publish the message
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
    rospy.spin()
