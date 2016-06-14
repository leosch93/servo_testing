//
//

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

  float min = 9.0;
  float max = 27.0;
  float step_size = 1.5;
  float value = min;
  int i = 0;
    
  trajectory.joint_names.push_back(name1);
  //trajectory.joint_names.push_back(name2);
    
  trajectory.points.resize(1);
  trajectory.points[0].positions.resize(1);
  trajectory.points[0].velocities.resize(1);
  trajectory.points[0].accelerations.resize(1);
  trajectory.points[0].effort.resize(1);


  // While loop to test servo  
  while(value <= max) {	  
	  trajectory.header.stamp = ros::Time::now();
      trajectory.points[0].positions[0] = value;
      //trajectory.points[0].velocities[0] = 0.0;
      //trajectory.points[0].accelerations[0] = 0.0;	
      //trajectory.points[0].effort[0] = 0.0; 
      std::cout << "Position: "  << trajectory.points[0].positions[0] << std::endl;
	  value += step_size;
	  i++;
	  
	  pub.publish(trajectory);
	  ros::Duration(5).sleep();
  }  
  
  //ros::Rate loop_rate(0.01);   // change setpoint every 1/x seconds

  //while (ros::ok())
  //{
    //ros::spinOnce();

    //pub.publish(trajectory);

	//ros::Duration(5).sleep();
    //loop_rate.sleep();
  //}

  // Initialize parameter structure
  //ParameterBag parameter;
  //InitializeParameters(nh, &parameter);

  // Construct class detection_processor with ros::NodeHandle and parameter structure
  //FrameworkProcessor framework(nh, parameter);

  // Relative path to package
  //std::string strimg = ros::package::getPath("catkinpkg_framework") + "/src";

  // Spin
  ros::spin ();
}
