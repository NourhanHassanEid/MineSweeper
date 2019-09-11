#include <ros.h>

#include <std_msgs/Int16.h>
//--------------------------------------------------------------------------------------------------------------------------------
#include <QMC5883L.h>
#include <Wire.h>
QMC5883L compass;
//-------------------------------------------------------------------------------------------------------------------------------------
#define ld1_motor 4
#define le1_motor 5
#define ld2_motor 7
#define le2_motor 6
#define rd1_motor 8
#define re1_motor 9
#define rd2_motor 12
#define re2_motor 11 
//-----------------------------------------------------------------------------------------------------------------
ros::NodeHandle ros_node;
std_msgs::Int16 angle_reading;
std_msgs::Int16 angleState_reading;
std_msgs::Int16 str_msg;
//------------------------------------------------------------------------------------------------------------------------------
void motion(const std_msgs::Int16& control_char);
ros::Subscriber<std_msgs::Int16> control_sub("motion_topic", &motion);
//----------------------------------------------------------------------------------------------------------
ros::Publisher reading1("angle_teamleader", &angle_reading);
ros::Publisher reading2("angle_state_teamleader", &angleState_reading);
//-------------------------------------------------------------------------------------------------------------------
const int min_up=200;
const int max_up=215;
const int min_down=20;
const int max_down=35;
const int min_right=285;
const int max_right=305;
const int min_left=110;
const int max_left=225;
int angle_state;
//--------------------------------------------------------------------------------------------------------------------

void setup ()
{
  pinMode(ld1_motor, OUTPUT);
  pinMode(le1_motor, OUTPUT);
  pinMode(ld2_motor, OUTPUT);
  pinMode(le2_motor, OUTPUT);
  pinMode(rd1_motor, OUTPUT);
  pinMode(re1_motor, OUTPUT);
  pinMode(rd2_motor, OUTPUT);
  pinMode(re2_motor, OUTPUT);
//----------------------------------------------------------------------------------------------------
  ros_node.initNode();
  ros_node.subscribe(control_sub);
//------------------------------------------------------------------------------------------------------------------
  Wire.begin();

  compass.init();
  compass.setSamplingRate(50);
//-------------------------------------------------------------------------------------------------------------------------------------------------- 
  ros_node.initNode();
  ros_node.advertise(reading1);
  ros_node.advertise(reading2);
//-----------------------------------------------------------------------------------------------------------------    
}

void loop ()
{
  //-------------------------------------------------------------------------------------------------------------------------------------------
  int heading = compass.readHeading();
  
  if(heading==0) {
    /* Still calibrating, so measure but don't print */
  } else {
     angle_reading.data = heading ;
     reading1.publish( &angle_reading);
        if ((heading>=min_up)&&(heading<=max_up)) {
            angle_state=8;}

         else if ((heading>=min_down )&&(heading<=max_down)){
          
             angle_state=2;}
          else if ((heading>=min_right )&&(heading<=max_right)){
          
             angle_state=6;}
           else if ((heading>=min_left )&&(heading<=max_left)){
               angle_state=4;}
            
     }
     angleState_reading.data = angle_state ;
     reading2.publish( &angleState_reading); 
     ros_node.spinOnce();
      
  //---------------------------------------------------------------------------------------------------------------------------------------------

  
}

void motion(const std_msgs::Int16& control_char)
{

  int n = control_char.data;;
  if (n == 8) //forward
  {
    digitalWrite(ld1_motor, 0);
    analogWrite(le1_motor, 150);
    digitalWrite(ld2_motor, 0);
    analogWrite(le2_motor, 150);
    digitalWrite(rd1_motor, 0);
    analogWrite(re1_motor, 150);
    digitalWrite(rd2_motor, 0);
    analogWrite(re2_motor, 150);
  }
  else if(n == 2) //backward
  {
    digitalWrite(ld1_motor, 1);
    analogWrite(le1_motor, 150);
    digitalWrite(ld2_motor, 1);
    analogWrite(le2_motor, 150);
    digitalWrite(rd1_motor, 1);
    analogWrite(re1_motor, 150);
    digitalWrite(rd2_motor, 1);
    analogWrite(re2_motor, 150);
    
  }
  else if( n == 6) //right
  {
    digitalWrite(ld1_motor, 0);
    analogWrite(le1_motor, 100);
    digitalWrite(ld2_motor, 0);
    analogWrite(le2_motor, 100);
    digitalWrite(rd1_motor, 1);
    analogWrite(re1_motor, 100);
    digitalWrite(rd2_motor, 1);
    analogWrite(re2_motor, 100);
    
  }
  else if(n == 4) //left
  {
    digitalWrite(ld1_motor, 1);
    analogWrite(le1_motor, 100);
    digitalWrite(ld2_motor, 1);
    analogWrite(le2_motor, 100);
    digitalWrite(rd1_motor, 0);
    analogWrite(re1_motor, 100);
    digitalWrite(rd2_motor, 0);
    analogWrite(re2_motor, 100);
  
  }  
  else if( n == 5) //left
  {
    digitalWrite(ld1_motor, 0);
    analogWrite(le1_motor, 0);
    digitalWrite(ld2_motor, 0);
    analogWrite(le2_motor, 0);
    digitalWrite(rd1_motor, 0);
    analogWrite(re1_motor, 0);
    digitalWrite(rd2_motor, 0);
    analogWrite(re2_motor, 0);
  
  }  
else  //stop
  {
    digitalWrite(ld1_motor, 0);
    analogWrite(le1_motor, 0);
    digitalWrite(ld2_motor, 0);
    analogWrite(le2_motor, 0);
    digitalWrite(rd1_motor, 0);
    analogWrite(re1_motor, 0);
    digitalWrite(rd2_motor, 0);
    analogWrite(re2_motor, 0);
    
  }  
  
}
