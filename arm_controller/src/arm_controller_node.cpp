#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>


void printJointStates(const sensor_msgs::JointState::ConstPtr& joint_states)
{
    // Print the current joint positions
    ROS_INFO("Current Joint Positions:");
    for (size_t i = 0; i < joint_states->name.size(); i++) 
    {
        ROS_INFO("Joint Name: %s, Position: %f", joint_states->name[i].c_str(), joint_states->position[i]);
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "arm_controller_node");
    ros::NodeHandle nh;   

    ros::Subscriber joint_states_sub = nh.subscribe("/arm/joint_states", 10, printJointStates);

    ros::Publisher j0_pub = nh.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J0_controller/command", 10);
    ros::Publisher j1_pub = nh.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J1_controller/command", 10);
    ros::Publisher j2_pub = nh.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J2_controller/command", 10);
    ros::Publisher j3_pub = nh.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J3_controller/command", 10);

    ros::Rate loop_rate(10);

    while (ros::ok()) {
        // Publish commands to the controllers' /command topics
        std_msgs::Float64 j0_command;
        j0_command.data = 1;
        j0_pub.publish(j0_command);

        std_msgs::Float64 j1_command;
        j1_command.data = 0.5;
        j1_pub.publish(j1_command);

        std_msgs::Float64 j2_command;
        j2_command.data = -0.7;
        j2_pub.publish(j2_command);

        std_msgs::Float64 j3_command;
        j3_command.data = 0.4;
        j3_pub.publish(j3_command); 

        ros::spinOnce();
        loop_rate.sleep();

    }

    return 0;
}
