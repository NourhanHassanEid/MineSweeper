#!/usr/bin/env python
import rospy
from std_msgs.msg import Int16
distance=Int16()
angle=Int16() #angle_state
motion=Int16()
x=Int16()
prev_x=Int16()
x=0
prev_x=0
y=Int16()
data1=Int16()
data2=Int16()
data3=Int16()
def callback_distance(data1):
        global distance
	distance.data=data1.data
	rospy.loginfo(rospy.get_caller_id() + "I heard %s", data1)
	
def callback_angle(data2):
        global angle
	angle.data=data2.data
	rospy.loginfo(rospy.get_caller_id() + "I heard %s", data2)

def callback_motion(data3):
        global motion
	motion.data=data3.data
	rospy.loginfo(rospy.get_caller_id() + "I heard %s", data3)


	


	
def main():
	global x, y, motion, angle, distance ,prev_x 
        x = 0 #if i take it 
	prev_x =0
	rospy.init_node('encoder', anonymous=True)
	pub1 = rospy.Publisher('sure', Int16 ,queue_size=1)
	sub1= rospy.Subscriber("distance", Int16, callback_distance)
	sub2= rospy.Subscriber("angle_state", Int16, callback_angle)
	sub3= rospy.Subscriber("control_topic", Int16, callback_motion)
	pub2 = rospy.Publisher('prev_x', Int16 ,queue_size=1)
	pub3 = rospy.Publisher('y', Int16 ,queue_size=1)
	pub4 = rospy.Publisher('x', Int16 ,queue_size=1)
	r=rospy.Rate(1)
	while not rospy.is_shutdown():
		pub1.publish(angle) 
		
		
	
		
		if ((angle.data==8) and ((motion.data == 8) or (motion.data == 2))):#up
			y=distance.data
			#x=prev_x
			
			pub3.publish(y)

			pub4.publish(x)
		elif ((angle.data ==2 ) and ((motion.data == 8 ) or (motion.data == 2))):#down
			y=0
			y=19-distance.data
			x = prev_x
			pub3.publish(y)
			pub4.publish(x)
		if (((angle.data == 6) or (angle.data ==4)) and ((motion.data == 8 ) or (motion.data == 2))) :#right or left
			
			
			x= prev_x + distance.data
			prev_x = x
			pub2.publish(prev_x)
			pub4.publish(x)
			pub3.publish(y)
			pass
		elif angle.data== 0 :
			
			pass 
		
		#pub3.publish( y)
		#pub2.publish( x)
		r.sleep()
	rospy.spin()

if __name__ == '__main__':
	try:
		x=0
		main()
	except rospy.ROSInterruptException:

		pass

