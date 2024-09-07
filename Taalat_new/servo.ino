#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;
std_msgs::Int32 int_msg;
ros::Publisher angle("angle", &int_msg);

int minPotValue = 150;
int maxPotValue = 450;

int reading(){
  delay(100);
  
  int sensorValue = analogRead(A0);
  if(sensorValue < minPotValue){
    minPotValue = sensorValue;
  }
  if(sensorValue > maxPotValue){
    maxPotValue = sensorValue;
  }
  
  const int minOutput = 0;
  const int maxOutput = 180;

  int mappedValue = map(sensorValue, minPotValue, maxPotValue, minOutput, maxOutput);
  //  Serial.println(sensorValue);


  return mappedValue;

 

}

void setup() {
  // Serial.begin(9600);
  nh.initNode();
  nh.advertise(angle);
}
void loop() {
  int_msg.data=reading();

  angle.publish( &int_msg );
  nh.spinOnce();
  //int sensorValue = analogRead(A0);
  
  //const int minPotValue = 117;
 // const int maxPotValue = 495;

  //const int minOutput = 0;
  //const int maxOutput = 180;

  //int mappedValue = map(sensorValue, minPotValue, maxPotValue, minOutput, maxOutput);

  //Serial.println(mappedValue);
  //delay(1);
}
