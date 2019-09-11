//motion 15/7/2019  well
#include <ros.h>
#include <std_msgs/Int16.h>



#define rate 200

#define l1in1_motor 3
#define l1in2_motor 4
#define l1enb_motor 5

#define r1in1_motor 11
#define r1in2_motor 9
#define r1enb_motor 10


ros::NodeHandle nh;
std_msgs::Int16 str_msg;

void motion(const std_msgs::Int16& control_char);
ros::Subscriber<std_msgs::Int16> control_sub("control_topic", &motion);


void setup ()
{
  pinMode(l1in1_motor, OUTPUT);
  pinMode(l1in2_motor, OUTPUT);
  pinMode(l1enb_motor, OUTPUT);
  pinMode(r1in1_motor, OUTPUT);
  pinMode(r1in2_motor, OUTPUT);
  pinMode(r1enb_motor, OUTPUT);

  nh.initNode();
  nh.subscribe(control_sub);
}

void loop ()
{

  nh.spinOnce();
  //delay(100);

}

void motion(const std_msgs::Int16& control_char)
{
  int n = control_char.data;
  if (n == 8) //forward
  { digitalWrite(l1in1_motor, 1);
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
  else if ( n == 4) //left    
  {
    digitalWrite(l1in1_motor, 0);
    digitalWrite(l1in2_motor, 1);
    analogWrite(l1enb_motor, rate);
    digitalWrite(r1in1_motor, 0);
    digitalWrite(r1in2_motor, 1);
    analogWrite(r1enb_motor, rate);
  }
  else if ( n == 5) //stop
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
