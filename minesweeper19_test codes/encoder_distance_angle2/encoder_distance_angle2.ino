/*this is the current encoder code which take the angle state to set the encoder reading to zero
  give us the distance which well be either to X or Y
  then puplish both distance and angle state
*/
#include <ros.h>
#include <std_msgs/Int16.h>
//--------------------------------------------------------encoder1
int encoder1Pin1 = 2;
int encoder1Pin2 = 3;
//--------------------------------------------------------encoder2
int encoder2Pin1 = 18;
int encoder2Pin2 = 19;
//--------------------------------------------------------both
int lastMSB = 0;
int lastLSB = 0;
volatile int encoder1 = 0;
volatile int encoder2 = 0;
volatile int lastEncoded1 = 0;
volatile int lastEncoded2 = 0;

//---------------------------------------rover
float DIAMETER  = 0.15  ;         // wheel diameter (in m)
float distanceLeftWheel, distanceRightWheel, Dc, Orientation_change;
int distance ;
float calibration = 0.5; //error value
float ENCODER_RESOLUTION = 1700.0;
float CIRCUMSTANCE = 3.141592654 * DIAMETER ; //wheel circumfrance
int angle_state ;
int motion_state ;
int prev_state = 8;
//---------------------------------------
ros::NodeHandle ros_node;
//std_msgs::Int16 motion_reading;
std_msgs::Int16 distance_reading;
std_msgs::Int16 angleState_reading;
//-----------------------------------------------------
/*subscribe angle state*/
void messageCb1( const std_msgs::Int16& angleState_msg) {
  angle_state = angleState_msg.data;
}
//-----------------------------------------------------
/*subscribe motion state*/
/*void messageCb2( const std_msgs::Int16& motionState_msg){
  motion_state = motionState_msg.data;
  }*/
//-----------------------------------------------------
ros::Subscriber<std_msgs::Int16> sub1("angle_state", &messageCb1 );
//ros::Subscriber<std_msgs::Int16> sub2("control_topic", &messageCb2 );
ros::Publisher reading1("distance", &distance_reading);
ros::Publisher reading2("angle_state_sure", &angleState_reading); //to make sure then delete it

void setup() {
  ros_node.initNode();
  ros_node.advertise(reading1);
  ros_node.subscribe(sub1);
  //ros_node.subscribe(sub2);
  ros_node.advertise(reading2);
  //--------------------------------------------------------------------------
  attachInterrupt(digitalPinToInterrupt(2), updateEncoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), updateEncoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(18), updateEncoder2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), updateEncoder2, CHANGE);
  //-----------------------------------------encoder1

  pinMode(encoder1Pin1, INPUT_PULLUP);
  pinMode(encoder1Pin2, INPUT_PULLUP);

  digitalWrite(encoder1Pin1, HIGH);
  digitalWrite(encoder1Pin2, HIGH);
  //-----------------------------------------encoder2
  pinMode(encoder2Pin1, INPUT_PULLUP);
  pinMode(encoder2Pin2, INPUT_PULLUP);

  digitalWrite(encoder2Pin1, HIGH);
  digitalWrite(encoder2Pin2, HIGH);


}

void loop() {
  //---------------------------------------------------------------

  //---------------------------------------------------------------
  distanceLeftWheel  = CIRCUMSTANCE * ( encoder1 / ENCODER_RESOLUTION);       //  travel distance for the left and right wheel respectively
  distanceRightWheel = CIRCUMSTANCE * ( encoder2 / ENCODER_RESOLUTION);     // which equal to pi * diameter of wheel * (encoder counts / encoder resolution )
  Dc = (distanceLeftWheel + distanceRightWheel) / 2 ;
  distance = (int)Dc;


if  ( prev_state != angle_state) {

  /*encoder1 =0;
    encoder2= 0;
    distance= 0;*/
  encoder1 = 0;
  encoder2 = 0;
  distanceLeftWheel = 0;
  distanceRightWheel = 0;
  prev_state = angle_state;
}

distance_reading.data = distance ;
//------------------------------------------------
angleState_reading.data = angle_state;

reading1.publish( &distance_reading);
reading2.publish( &angleState_reading);//to make sure


//-------------------------------------- or here
/*encoder1 =0;
  encoder2= 0;
  distanceLeftWheel =0;
  distanceRightWheel=0;
  d= 0;*/


ros_node.spinOnce();
delay(100);
}

void updateEncoder1() {
  int MSB = digitalRead(encoder1Pin1);
  int LSB = digitalRead(encoder1Pin2);

  int encoded1 = (MSB << 1) | LSB;
  int sum  = (lastEncoded1 << 2) | encoded1;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoder1 ++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoder1 --;

  lastEncoded1 = encoded1;
}

void updateEncoder2() {
  int MSB = digitalRead(encoder2Pin1);
  int LSB = digitalRead(encoder2Pin2);

  int encoded2 = (MSB << 1) | LSB;
  int sum  = (lastEncoded2 << 2) | encoded2;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoder2 ++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoder2 --;
  lastEncoded2 = encoded2;
}
//---------------------------------------------------------------------------distance calculatin function
/*int distanceCalculation( int state) {
  int prev_state = 8;
  int d = 0;
  if  ( prev_state != state) {
    //---------------------------------------------------------------
    distanceLeftWheel  = CIRCUMSTANCE * ( encoder1 / ENCODER_RESOLUTION);       //  travel distance for the left and right wheel respectively
    distanceRightWheel = CIRCUMSTANCE * ( encoder2 / ENCODER_RESOLUTION);     // which equal to pi * diameter of wheel * (encoder counts / encoder resolution )
    Dc = calibration + ((distanceLeftWheel + distanceRightWheel) / 2 );
    d = (int)Dc;
  }
  encoder1 = 0;
  encoder2 = 0;
  distanceLeftWheel = 0;
  distanceRightWheel = 0;
  prev_state = state;
  return d;
}*/
