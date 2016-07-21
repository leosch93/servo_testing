cmake_minimum_required(VERSION 2.8.3)
project(servo_testing)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  trajectory_msgs
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Ofast") 

###################################
## catkin specific configuration ##
###################################
catkin_package(
 INCLUDE_DIRS include
 LIBRARIES servo_testing
 CATKIN_DEPENDS roscpp std_msgs trajectory_msgs
 DEPENDS system_lib
)

###########
## Build ##
###########
include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${roscpp_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(servo_testing_input 
	src/servo_testing_node_direct_command.cpp
)

add_executable(servo_testing_loop 
	src/servo_testing_node_whileloop.cpp
)

## Specify libraries to link a library or executable target against
target_link_libraries(servo_testing_input
  ${catkin_LIBRARIES}
)

target_link_libraries(servo_testing_loop
  ${catkin_LIBRARIES}
)
