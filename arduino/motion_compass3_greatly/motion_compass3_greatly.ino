#include <ros.h>
#include <std_msgs/Int16.h>
//--------------------------------------------------------------------------------------------------------------------------------
#include <QMC5883L.h>
#include <Wire.h>
QMC5883L compass;
//----------------------------------------------------------------------------------------------------------------
#define rate 200
#define l1in1_motor 3
#define l1in2_motor 4
#define l1enb_motor 5

#define r1in1_motor 11
#define r1in2_motor 9
#define r1enb_motor 10
//-----------------------------------------------------------------------------------------------------------------
ros::NodeHandle ros_node;
std_msgs::Int16 angle_reading;
std_msgs::Int16 angleState_reading;
std_msgs::Int16 str_msg;
//-----------------------------------------------------------------------------------------------------------------
void motion(const std_msgs::Int16& control_char);


//-----------------------------------------------------------------------------------------------------------------
ros::Subscriber<std_msgs::Int16> control_sub("control_topic", &motion);
ros::Publisher reading1("angle", &angle_reading);
ros::Publisher reading2("angle_State", &angleState_reading); //here is the topic that publishes to another node which is called (test2) to another topic called (angle_state)with small 's'
//-------------------------------------------------------------------------------------------------------------------
const int min_up=290;
const int max_up=320;
const int min_down=125;
const int max_down=140;
const int min_right=65;
const int max_right=75;
const int min_left=220;
const int max_left=230;
int angle_state;
//--------------------------------------------------------------------------------------------------------------------

void setup ()
{
    ros_node.initNode();
  ros_node.subscribe(control_sub);
  ros_node.advertise(reading1);
  ros_node.advertise(reading2);
  //-------------------------------
  pinMode(l1in1_motor, OUTPUT);
  pinMode(l1in2_motor, OUTPUT);
  pinMode(l1enb_motor, OUTPUT);
  pinMode(r1in1_motor, OUTPUT);
  pinMode(r1in2_motor, OUTPUT);
  pinMode(r1enb_motor, OUTPUT);
  //----------------------------------------------------------------------------------------------------

  
  //------------------------------------------------------------------------------------------------------------------
  Wire.begin();
  compass.init();
  compass.setSamplingRate(50);
  //--------------------------------------------------------------------------------------------------------------------------------------------------

  //-----------------------------------------------------------------------------------------------------------------
}

void loop ()
{
  //-------------------------------------------------------------------------------------------------------------------------------------------
  int heading = compass.readHeading();

  if (heading == 0) {
    /* Still calibrating, so measure but don't print */
    
    
  } else {
      angle_reading.data = heading ;
      
      reading1.publish( &angle_reading);
      angleState_reading.data = angle_state ;}
      
      if ((heading >= min_up) && (heading <= max_up)) {
        angle_state = 8;
        reading2.publish( &angleState_reading);
      }

      else if ((heading >= min_down ) && (heading <= max_down)) {

        angle_state = 2;
        reading2.publish( &angleState_reading);
      }
      else if ((heading >= min_right ) && (heading <= max_right)) {

        angle_state = 6;
        reading2.publish( &angleState_reading);
      }
      else if ((heading >= min_left ) && (heading <= max_left)) {
        angle_state = 4;
        reading2.publish( &angleState_reading);
      }
      else {
        angle_state = 0;
        reading2.publish( &angleState_reading);
        }
        }

  ros_node.spinOnce();

}

void motion(const std_msgs::Int16& control_char)
{

  int n = control_char.data;
  if (n == 8) //forward
  {
    digitalWrite(l1in1_motor, 1);
    digitalWrite(l1in2_motor, 0);
    analogWrite(l1enb_motor, rate);
    digitalWrite(r1in1_motor, 0);
    digitalWrite(r1in2_motor, 1);
    analogWrite(r1enb_motor, rate);
  }
  else if (n == 2) //backward
  {
    digitalWrite(l1in1_motor, 0);
    digitalWrite(l1in2_motor, 1);
    analogWrite(l1enb_motor, rate);
    digitalWrite(r1in1_motor, 1);
    digitalWrite(r1in2_motor, 0);
    analogWrite(r1enb_motor, rate);

  }
  else if ( n == 6) //right
  {
    digitalWrite(l1in1_motor, 1);
    digitalWrite(l1in2_motor, 0);
    analogWrite(l1enb_motor, rate);
    digitalWrite(r1in1_motor, 1);
    digitalWrite(r1in2_motor, 0);
    analogWrite(r1enb_motor, rate);

  }
  else if (n == 4) //left
  {
    digitalWrite(l1in1_motor, 0);
    digitalWrite(l1in2_motor, 1);
    analogWrite(l1enb_motor, rate);
    digitalWrite(r1in1_motor, 0);
    digitalWrite(r1in2_motor, 1);
    analogWrite(r1enb_motor, rate);
  }
  else if ( n == 5) //left
  {
    digitalWrite(l1in1_motor, 0);
    digitalWrite(l1in2_motor, 0);
    analogWrite(l1enb_motor, 0);
    digitalWrite(r1in1_motor, 0);
    digitalWrite(r1in2_motor, 0);
    analogWrite(r1enb_motor, 0);

  }
  else  //stop
  {
     digitalWrite(l1in1_motor, 0);
    digitalWrite(l1in2_motor, 0);
    analogWrite(l1enb_motor, 0);
    digitalWrite(r1in1_motor, 0);
    digitalWrite(r1in2_motor, 0);
    analogWrite(r1enb_motor, 0);
  }

}
