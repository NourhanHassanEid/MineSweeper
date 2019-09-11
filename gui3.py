#!/usr/bin/env python
#-----------------------------------------------
import rospy
from std_msgs.msg import Int16
from std_msgs.msg import String
#-----------------------------------------------
import Tkinter
from Tkinter import *
import ttk
import time

#------------------------------------------------
X = Int16()
Y = Int16()
COLOR = String()
x = Int16()
y = Int16()
color = String()
#-----------------------------------------------
def callback_x(data1):
	global X
	X.data=data1.data
	rospy.loginfo(rospy.get_caller_id() + "I heard %s",data1)
	
def callback_y(data2):
	global Y
	Y.data=data2.data
	rospy.loginfo(rospy.get_caller_id() + "I heard %s",data2)

def callback_mine(data3):
	global COLOR
	COLOR.data=data3.data
	rospy.loginfo(rospy.get_caller_id() + "I heard %s",data3)
#----------------------------------------------


#------------------------------------------------
root = Tk()
w = Label(root, text="THE STARKS",font='TkFixedFont 24 bold')
w.pack(side=TOP)

btn=  [[0 for x in range(20)] for y in range(20)]     #initializing mapping variable


def map_buttons():
	#global x,y,X,Y
    x_modified = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T']
#entering 20*20 array of disabled buttons
    for x in range(20):
         for y in range(20):
            btn[x][y] = Button(frame_map,height =1, width = 3,state=DISABLED,text=("(",x_modified[x],",",20-y,")"))
            btn[x][y].grid(column=x, row=y)

def color_change(x,y):             #color changing function
	#global x,y,X,Y
    if (color=='S'):
        btn[x][y].configure(bg = "red")
    elif(color=='B'):
        btn[x][y].configure(bg="blue")

def mapping(x,y):                #placing point on the map
	#global x,y,X,Y
    if((int(x)<=20 and int(x)>0) and (int(y)<21 and int(y)>=1) ):
        color_change((int(x)-1),(20-int(y)))


def indication ():
    btn1 = Button(frame_ind,height =1, width = 4,state=DISABLED,bg="red")
    btn2=Button(frame_ind,height =1, width = 4,state=DISABLED,bg="blue")
    label1=Label(frame_ind,text="Surface Mines")
    label2=Label(frame_ind,text="Buried Mines")
    btn1.grid(column=0,row=1)
    btn2.grid(column=0,row=2)
    label1.grid(column=1,row=1)
    label2.grid(column=1,row=2)
#--------------------------------------------------
def main():
	global x,y,X,Y,COLOR,color
	x=1
	rospy.init_node('gui2', anonymous=True)
	sub1= rospy.Subscriber("x", Int16, callback_x)
	sub2= rospy.Subscriber("y", Int16, callback_y)
	sub3= rospy.Subscriber("metal_detection_topic", String, callback_mine)
	pub1= rospy.Publisher ('sure_reading_x', Int16 ,queue_size=1)

	r=rospy.Rate(1)
	while not rospy.is_shutdown():
		
		x=X.data
		y=Y.data
		color=COLOR.data
		#color='B'
		pub1.publish(color)
		#x=6
		#y=7
		mapping(x,y)
		r.sleep()
	
	#x=X.data
	#y=Y.data
	#pub1.publish(X)
	#x=6
	#y=7
	#mapping(x,y)
	#r.sleep()

	rospy.spin()
#--------------------------------------------------
root.title("Minesweaper")
frame_map=Frame(root,height=100,width=100,relief=RIDGE)
frame_map.pack()
map_buttons()

frame_ind=Frame(root,height=100,width=100,relief=RIDGE)
frame_ind.pack(side=BOTTOM)

#indication()
#----------------------------------------------------------------
#color='B'



#----------------------------------------------------------------
if __name__ == '__main__':
	try:
		indication()
		main()
	except rospy.ROSInterruptException:

		pass

root.mainloop()
