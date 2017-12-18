#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_listener.h>

void printTransform(const std::string &name, const tf::StampedTransform &transform)
{
  // For some reason the logger level is set to errors so I am just going to print error.
  // Normally you would use ROS_INFO_STREAM
  ROS_ERROR_STREAM(name << " (Translation): " << "x: " << transform.getOrigin().getX() 
    << ", y: " << transform.getOrigin().getY() << ", z: " << transform.getOrigin().getZ());
  
  // Get RPY representation
  double roll, pitch, yaw;
  tf::Matrix3x3 rotation(transform.getRotation());
  rotation.getRPY(roll, pitch ,yaw);

  ROS_ERROR_STREAM(name << " (Rotation RPY): " << "r: " << roll << ", p: " << pitch
    << ", y: " << yaw);
}

int main(int argc, char** argv) 
{
  ros::init(argc, argv, "state_publisher");
  ros::NodeHandle n;
  ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1); //publish to node sensor_msgs
  ros::Rate loop_rate(30);



  // initialize robot state
  double theta1 = 0.785, theta2 = 0.1, theta3 =1.57;
//  double theta1_inc = 0.01, theta2_inc = 0.025;

  // message declarations
  sensor_msgs::JointState joint_state;

  tf::TransformListener listener;
    
  while (ros::ok()) 
  {
//    // Get transform between base_link and link2 and base_link to tool0
    tf::StampedTransform base_link_to_link2;
    tf::StampedTransform BASE_to_EE;
    tf::StampedTransform link1_to_link2;

    try
    {
      listener.lookupTransform("BASE", "link2", ros::Time(0), base_link_to_link2);
      listener.lookupTransform("BASE", "EE", ros::Time(0), BASE_to_EE);
      listener.lookupTransform("link2", "link3", ros::Time(0), link1_to_link2);
    }
    catch (tf::TransformException &ex)
    {
      ROS_ERROR_STREAM(ex.what());
    }
    //ROS_INFO_STREAM("Hello");

    // Print out transforms
    printTransform("base_link_to_link2", base_link_to_link2);
    printTransform("BASE_to_EE", BASE_to_EE);
    printTransform("link1_to_link2", link1_to_link2);

    // update joint_state
    joint_state.header.stamp = ros::Time::now();
    joint_state.name.resize(3);
    joint_state.position.resize(3);
    joint_state.name[0] ="base_to_link1";
    joint_state.position[0] = theta1;
    joint_state.name[1] ="link1_to_link2";
    joint_state.position[1] = theta2;
    joint_state.name[2]="link2_to_link3";
    joint_state.position[2] = theta3;
    // Theta1
    theta1 = 0.785;
//    theta2= 0.1;
    theta3=1.57;

    // send the joint state and transform
    joint_pub.publish(joint_state);

    // This will adjust as needed per iteration
    loop_rate.sleep();
  }

  return 0;
}

