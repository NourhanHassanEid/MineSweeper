#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy
from std_msgs.msg import Int16
from std_msgs.msg import String

def callback(data):
         twist = Twist()
	 motion = 0
	 movement = "no button pressed"
         twist.linear.x = data.axes[1]
         twist.angular.z = data.axes[0]
	 twist.linear.y = data.buttons[4]
	 if twist.linear.x==1:
		movement = "forward"
		motion = 8
	 elif twist.linear.x==-1:
		movement = "Stop"
		motion = 2
	 elif twist.angular.z==1:
		movement = "Left"
		motion = 4
	 elif twist.angular.z==-1:
		movement = "right"
		motion = 6
	 elif twist.linear.y==1:
		movement = "Stop"
		motion = 5
	 print movement

         pub.publish(motion)
def start():
         global pub
         pub = rospy.Publisher('control_topic', Int16, queue_size=1)
        
         rospy.Subscriber("joy", Joy, callback)
         rospy.init_node('joystick')
         rospy.spin()
   
if __name__ == '__main__':
         start()
