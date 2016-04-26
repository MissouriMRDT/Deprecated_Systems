#!/usr/bin/env python
import rospy
import trexjr
from geometry_msgs.msg import Twist

motors = trexjr.TrexJr()

# Receives twist messages and sends them to the motor controller

def callback(twist):
    leftspeed = twist.linear.x - twist.angular.z
    rightspeed = twist.linear.x + twist.angular.z
    motors.move(leftspeed, rightspeed)

# Intializes everything
def start():
    # Subscribe to a twist message
    rospy.Subscriber('turtle1/cmd_vel', Twist, callback)
    # starts the node
    rospy.init_node('MotorController')
    rospy.spin()

if __name__ == '__main__':
    start()
