#define metal_detector_digital 6
#define mine_detection A0
#define min_value 320
#define max_value 800
//---------------------------------------------------------
#include <ros.h>
#include <std_msgs/String.h>
//---------------------------------------------------------
//----------------------------------------------------
ros::NodeHandle ros_node;

std_msgs::String metal_detection_value;

ros::Publisher metal_pub ("metal_detection_topic", &metal_detection_value);
//------------------------------------------------------
int metal_detection_reading = 0;
int digital_detection_reading = 0;

void setup() 
{
  ros_node.initNode();
  ros_node.advertise(metal_pub);
//-------------------------------------------------------  
  pinMode(metal_detector_digital, INPUT);
  pinMode(mine_detection, INPUT);
  
}

void loop() 
{
digital_detection_reading = digitalRead(metal_detector_digital);
metal_detection_reading = analogRead(mine_detection);

  if(metal_detection_reading < min_value){
  metal_detection_value.data = "No" ;
    metal_pub.publish( &metal_detection_value);}
  else if(metal_detection_reading > min_value && metal_detection_reading < 540){
    metal_detection_value.data = "B" ;
    metal_pub.publish( &metal_detection_value);}
  else if(metal_detection_reading > 540){
   metal_detection_value.data = "S" ;
    metal_pub.publish( &metal_detection_value);}
  
  ros_node.spinOnce();
}
