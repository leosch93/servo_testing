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

  float minalpha = 9.0;
  float minbeta = 9.0;
  float maxalpha = 27.0;
  float maxbeta = 27.0;

  float step_size_alpha = 0.3;
  float step_size_beta = 0.3;

  float valuealpha = minalpha;
  float valuebeta = minbeta;
  int i = 0;
  int j = 0;
    
  trajectory.joint_names.resize(1);  
  //trajectory.joint_names.push_back(name2);
    
  trajectory.points.resize(1);
  trajectory.points[0].positions.resize(1);
  trajectory.points[0].velocities.resize(1);
  trajectory.points[0].accelerations.resize(1);
  trajectory.points[0].effort.resize(1);

	
  // While loop to run servo  
  while(valuealpha <= maxalpha) {	  
	  trajectory.joint_names[0] = name1;
	  trajectory.header.stamp = ros::Time::now();
      trajectory.points[0].positions[0] = valuealpha;
      
	  std::cout << "Position command "  << trajectory.points[0].positions[0] << "\t" << " Angle of attack " << "\t" << trajectory.points[0].positions[0]*150/45-60 << " deg" << std::endl;
	  valuealpha += step_size_alpha;
	  i++;
	  pub.publish(trajectory);
	  
	  ros::Duration(1).sleep();
      while(valuebeta <= maxbeta){
		 
			trajectory.joint_names[0] = name2;
			trajectory.header.stamp = ros::Time::now();
			trajectory.points[0].positions[0] = valuebeta;

			std::cout << "Position command "  << trajectory.points[0].positions[0] << "\t" << " Angle of sideslip " << "\t" << trajectory.points[0].positions[0]*150/45-60 << " deg" << std::endl;
			valuebeta += step_size_beta;
			j++;
			pub.publish(trajectory);
			ros::Duration(1).sleep();
	  }
      //trajectory.points[0].velocities[0] = 0.0;
      //trajectory.points[0].accelerations[0] = 0.0;	
      //trajectory.points[0].effort[0] = 0.0; 
      
	  valuebeta = minbeta;
	  //pub.publish(trajectory);
	  //ros::Duration(3).sleep();
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
