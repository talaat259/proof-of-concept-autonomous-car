#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float32MultiArray.h>
ros::NodeHandle nh;


#define motor1A 3  // IN1
#define motor1B 5  // IN2
#define motor2A 9  // IN3
#define motor2B 10  //

#define motor1Enable 6
#define motor2Enable 11

float motor1 =0;
float motor2=0;

void message_Cb_S(const std_msgs::Float32MultiArray& vectoring) {

  motor1=vectoring.data[0];
  motor2=vectoring.data[1];
}

ros::Subscriber<std_msgs::Float32MultiArray> sub1("MMC", &message_Cb_S);

void setup() {
  nh.initNode();
  nh.subscribe(sub1);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

}


void loop() {  

  nh.spinOnce();
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  analogWrite(motor1Enable, motor1);  // Adjust PWM value for desired speed (0-255)//left

  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  analogWrite(motor2Enable, motor2);  // Adjust PWM value for desired speed (0-255)//right

  // Motor 1 forward
  // Adjust PWM value for desired speed (0-255)

}