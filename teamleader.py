#!/usr/bin/env python
#-----------------------------------------------
import rospy
from std_msgs.msg import Int16
from std_msgs.msg import String
from math import fabs

x_dem = Int16()
y_dem = Int16()
x_tem = Int16()
y_tem = Int16()

x_tem_prev = Int16()
y_tem_prev = Int16()
detected = String()
team_leader_angle = Int16()
current_distance = Int16()
motion_state = Int16() 
target= Int16()
#----------------------------------------------- get the deminer x coordinate
def callback_x(data1):
	global x_dem
	x_dem.data=data1.data
	rospy.loginfo(rospy.get_caller_id() + "I heard %s",data1)
#----------------------------------------------get the deminer y coordinate
def callback_y(data2):
	global y_dem
	y_dem.data=data2.data
	rospy.loginfo(rospy.get_caller_id() + "I heard %s",data2)
#----------------------------------------------get the metal_detector reading
def callback_mine(data3):
	global detected
	detected.data=data3.data
	rospy.loginfo(rospy.get_caller_id() + "I heard %s",data3)
#---------------------------------------------
def callback_angle(data4):

	global team_leader_angle
	team_leader_angle.data=data4.data
	rospy.loginfo(rospy.get_caller_id() + "I heard %s",data4)
#--------------------------------------------
def callback_current_distance(data5):

	global current_distance
	current_distance.data=data4.data
	rospy.loginfo(rospy.get_caller_id() + "I heard %s",data5)

def main ():
	global x,y,detected,team_leader_angle,current_distance
	rospy.init_node('team_leader', anonymous=True)
	sub1= rospy.Subscriber("x", Int16, callback_x)
	sub2= rospy.Subscriber("y", Int16, callback_y)
	sub3= rospy.Subscriber("metal_detected	", Int16, callback_motion)
	sub4= rospy.Subscriber("team_leader_angle ", Int16, callback_motion)
	sub5= rospy.Subscriber("current_distance", Int16, callback_motion)
	pub1 = rospy.Publisher('x_teamleader', Int16 ,queue_size=1)	
	pub2 = rospy.Publisher('y_teamleader', Int16 ,queue_size=1)
	pub3 = rospy.Publisher('target', Int16 ,queue_size=1)
	pub4 = rospy.Publisher('motion_state', Int16 ,queue_size=1)
	r=rospy.Rate(1)
	while not rospy.is_shutdown():
		if ((detected.data=='S') or (detected.data=='B') :
			y_tem= y_dem - y_tem_prev 
			x_tem= x_dem - x_tem_prev
			if(y_tem < 0):
				motion_state= 2
				pub4.publish(motion_state)
			elif(y_tem > 0):
				motion_state= 8
				pub4.publish(motion_state)
				
			if (angle.data == 8) or (angle.data == 2):
				target = fabs(x_tem)
				pub3.publish(target)
				
				if (angle.data == 8):
					motion_state= 6
					pub4.publish(motion_state)
				elif (angle.data == 2):
					motion_state= 4
					pub4.publish(motion_state)
				elif (angle.data == 6) :
					target = x_tem
					pub3.publish(target)
					if (current_distance != target ):
						motion_state= 8
						pub4.publish(motion_state)
					else
						

				
						
		

					


					
				

	
		

		
		
