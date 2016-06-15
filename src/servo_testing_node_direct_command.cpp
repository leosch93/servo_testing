//#include "servo_testing/parameter/parameter_bag.h"
//#include "servo_testing/servo_testing.h"

#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/Header.h>

#include <iostream>
#include <vector>

#include <trajectory_msgs/JointTrajectory.h>

//void InitializeParameters(const ros::NodeHandle& nh, ParameterBag* parameter) {
  // Retrieve all parameters or set to default
  //nh.param("subscribed_rostopic_img", parameter->subscribed_rostopic_img, kDefaultImageSubTopic);
//}

int main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "servo_testing_node");
  ros::NodeHandle nh;
  
  ros::Publisher pub = nh.advertise<trajectory_msgs::JointTrajectory>("/firefly/command_trajectory", 10);
  //ros::Publisher pub_point = nh.advertise<trajectory::JointTrajectoryPoint>("/firefly/command_trajectory",1);
  // Create messages
  trajectory_msgs::JointTrajectory trajectory;

  std::string name1 = "joint_1";
  std::string name2 = "joint_2";

    
  trajectory.joint_names.resize(1);  
  //trajectory.joint_names.push_back(name2);
    
  trajectory.points.resize(1);
  trajectory.points[0].positions.resize(1);
  trajectory.points[0].velocities.resize(1);
  trajectory.points[0].accelerations.resize(1);
  trajectory.points[0].effort.resize(1);

// Directly command Servo
bool a = true;
while (a == true)
{
double num, deg;
std::cout << "Choose servo" << std::endl;
std::cin >> num;
std::cout << "Choose an angle";
std::cout << std::endl << "Attention !!! Angles lower than -30 deg can cause a crash";
std::cout << std::endl;
std::cin >> deg;
double commandangle;
commandangle = (deg+60)*45.0/150.0;
std::cout << commandangle << std::endl;


if(num==1)
{
trajectory.joint_names[0] = name1;
trajectory.header.stamp = ros::Time::now();
trajectory.points[0].positions[0] = commandangle;
std::cout << "Position command "  << trajectory.points[0].positions[0] << " Angle of attack " << trajectory.points[0].positions[0]*150/45-60 << " deg" << std::endl;
pub.publish(trajectory);

a = false;
}
else if(num==2)
{
trajectory.joint_names[0] = name2;
trajectory.header.stamp = ros::Time::now();
trajectory.points[0].positions[0] = commandangle;
std::cout << "Position command "  << trajectory.points[0].positions[0] << " Angle of sideslip " << trajectory.points[0].positions[0]*150/45-60 << " deg" << std::endl;
pub.publish(trajectory);


a = false;
}
else
{
	std::cout << "There is no servo number " << num <<" servo" << std::endl;
	a = true;
}
}

ros::spin();
}



