#!/usr/bin/python3
import rospy
from std_msgs.msg import String

from std_msgs.msg import Float32MultiArray, Float64
import math

# Constants
trackwidth2 = 0.3  # Replace with actual value
x = 0.75  # wheelbase

# Global variables
rs = 0
s_angle = 0

def output(motor1, motor2):
    pub = rospy.Publisher('MMC', Float32MultiArray, queue_size=10)
    mtg = Float32MultiArray()
    mtg.data = [min(motor1,255),min(motor2,255)]

    pub.publish(mtg)
    rospy.loginfo("Published motor values: %f, %f", min(motor1,255), min(motor2,255))

def mapped(velocity):
    mapped_velocity = math.exp(0.034 * velocity) - 1
    x = (mapped_velocity * 255) / 1.4524
    return math.ceil(x)



def velocity_output(velocity,radius,inner):
    if inner:
        v = ((radius - (1/2) * trackwidth2) * velocity) / radius
    else:
        v = ((radius + (1/2) * trackwidth2) * velocity) / radius
    return v


def r_s(s_angle):
    if(s_angle != 0):
        r=x/math.tan(s_angle)
    else:
        r = 1000
    return r

def callback_v(Velocity):
    Velocity=Velocity.data
    right_left(s_angle,rs,Velocity)

def callback_S(Stearing):
    global s_angle
    s_angle = Stearing.data
    global rs
    rs = r_s(s_angle)
    
def right_left(angle,r,v):
    degree_angle=angle*(180/math.pi) 
    if(degree_angle>0):
        
        inner=velocity_output(v,r,True)
        outer=velocity_output(v,r,False)
        
        mapped1=mapped(inner)
        mapped2=mapped(outer)
        
        output(mapped1,mapped2)

    elif(degree_angle<0):
        
        inner=velocity_output(v,r,True)
        outer=velocity_output(v,r,False)
        
        mapped1=mapped(inner)
        mapped2=mapped(outer)
        
        output(mapped2,mapped1)

    else: 
        
        map1=mapped(v)
        
        output(map1,map1)



def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("Vectoring_velocity",Float64, callback_v)
    rospy.Subscriber("Vectoring_steering",Float64,callback_S)
    

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
