#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>

#define motor1A 3   // IN1 pin for motor 1
#define motor1B 5   // IN2 pin for motor 1
#define motor2A 9   // IN3 pin for motor 2
#define motor2B 10  // IN4 pin for motor 2

#define motor1Enable 6   // Enable A pin for motor 1 (PWM for speed control)
#define motor2Enable 11  // Enable B pin for motor 2 (PWM for speed control)

double maxrpm = 73;
double wheel_radius = 0.19;
double s_angle = 0;
double rs = 0;
const int x = 0.75;  // wheelbase
const int trackwidth2 = 0.30;

ros::NodeHandle nh;

std_msgs::Float64 Vel;
std_msgs::Float64 Str;
std_msgs::Float64 debug_msg;

ros::Publisher LEDVelocity("state_velocity", &Vel);
ros::Publisher LEDSteering("state_steering", &Str);
ros::Publisher debugPub("debug_info", &debug_msg);

void doubleToString(char *buffer, size_t bufferSize, double value) {
  dtostrf(value, 6, 2, buffer);  // Convert double to string with 2 decimal places
}


void output(int motor1, int motor2) {
  digitalWrite(motor2A, LOW);  // 2A high == forward
  digitalWrite(motor2B, HIGH);

  // Set motor 1 speed using PWM (0-255 for duty cycle)
  analogWrite(motor2Enable, motor2);  // Adjust value for desired speed

  digitalWrite(motor1A, HIGH);   // 2A high == forward
  digitalWrite(motor1B, LOW);

  // Set motor 1 speed using PWM (0-255 for duty cycle)
  analogWrite(motor1Enable, motor1);
}

double r_s(double s_angle) {
  double r_dash = x / sin(s_angle);
  double r = x / tan(s_angle);

  debug_msg.data = (double)(x / tan(s_angle));
  debugPub.publish(&debug_msg);
  return x / tan(s_angle);
}

double mapped(double velocity) {
  double mapped_velocity = exp(0.034 * velocity) - 1;
  double x = mapped_velocity * 255 / 1.4524;
  return ceil(x);
}

double velocity_output(double velocity,double radius,bool inner){
  double v=0;
  
  if(inner){
     v=((radius-((1/2)*trackwidth2))*velocity)/radius;
    return v;
    
    
    }
  else{
    v=((radius+((1/2)*trackwidth2))*velocity)/radius;
    return v;
    
    } 
  
  }

void right_left(double angle, double r, double v) {
  double degree_angle=angle*(3.14/180);
  if(degree_angle>0){
    double inner=velocity_output(v,r,true);
    double outer=velocity_output(v,r,false);
    double mapped1=mapped(inner);
    double mapped2=mapped(outer);

    
    output(mapped1,mapped2);
    
    
    }
   else if(degree_angle<0){
    double inner=velocity_output(v,r,true);
    double outer=velocity_output(v,r,false);

    double mapped1=mapped(inner);
    double mapped2=mapped(outer);
    output(mapped2,mapped1);
    
    
    
    
    }
   else{
    double mapped1=mapped(v);
    
    
    output(mapped1,mapped1);
    }
  
}

void message_Cb_S(const std_msgs::Float64& stearing) {
  s_angle = stearing.data;  // Use incoming steering data
  rs = r_s(s_angle);
  Str.data = stearing.data;

  // debug_msg.data = s_angle;
  // debugPub.publish(&debug_msg);
}

void message_Cb_v(const std_msgs::Float64& velocity) {
  double Velocity = velocity.data;
  right_left(s_angle, rs, Velocity);

}

ros::Subscriber<std_msgs::Float64> sub1("Vectoring_steering", &message_Cb_S);
ros::Subscriber<std_msgs::Float64> sub2("Vectoring_velocity", &message_Cb_v);

void setup() {
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.advertise(LEDVelocity);
  nh.advertise(LEDSteering);
  nh.advertise(debugPub);
}

void loop() {
  LEDVelocity.publish(&Vel);
  LEDSteering.publish(&Str);
  nh.spinOnce();
  delay(1);
}
