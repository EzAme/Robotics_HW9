cmake_minimum_required(VERSION 2.8.3)
project(hw9_1)

find_package(catkin REQUIRED
  roscpp
  rospy
  sensor_msgs
  std_msgs
  tf
)
catkin_package()

if(CATKIN_ENABLE_TESTING)
  find_package(roslaunch REQUIRED)
  roslaunch_add_file_check(launch)
endif()

install(DIRECTORY launch rviz urdf
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(tf_publisher tf_publisher.cpp)
target_link_libraries(tf_publisher ${catkin_LIBRARIES})
