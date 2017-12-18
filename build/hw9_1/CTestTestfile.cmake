# CMake generated Testfile for 
# Source directory: /home/ros-industrial/HW9/src/hw9_1
# Build directory: /home/ros-industrial/HW9/build/hw9_1
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_hw9_1_roslaunch-check_launch "/home/ros-industrial/HW9/build/hw9_1/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/ros-industrial/HW9/build/hw9_1/test_results/hw9_1/roslaunch-check_launch.xml" "--return-code" "/usr/bin/cmake -E make_directory /home/ros-industrial/HW9/build/hw9_1/test_results/hw9_1" "/opt/ros/kinetic/share/roslaunch/cmake/../scripts/roslaunch-check -o '/home/ros-industrial/HW9/build/hw9_1/test_results/hw9_1/roslaunch-check_launch.xml' '/home/ros-industrial/HW9/src/hw9_1/launch' ")
subdirs(gtest)
