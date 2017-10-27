#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>

nav_msgs::Odometry current_pose_iRobot;

void pose_cb_iRobot(const nav_msgs::Odometry::ConstPtr& msg){
    current_pose_iRobot = *msg;
}

geometry_msgs::Twist current_vel_iRobot;

void vel_cb_iRobot(const geometry_msgs::Twist::ConstPtr& msg){
    current_vel_iRobot = *msg;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
  ros::init(argc, argv, "distance_iRobot");
  ros::NodeHandle nh;
  
  
 // ros::Subscriber pose_sub_drone = nh.subscribe<geometry_msgs::PoseStamped>
  //         ("mavros/local_position/pose", 10, pose_cb_drone);
  ros::Subscriber pose_sub_iRobot = nh.subscribe<nav_msgs::Odometry>
           ("iRobot/odom", 10, pose_cb_iRobot);
  ros::Subscriber vel_sub_iRobot = nh.subscribe<geometry_msgs::Twist>
           ("iRobot/cmd_vel", 10, vel_cb_iRobot);
  ros::Publisher set_vel_pub = nh.advertise<geometry_msgs::Twist>
            ("iRobot/cmd_vel", 10);
   
 //  ros::Publisher set_pose_pub = nh.advertise<geometry_msgs::PoseStamped>
  //          ("mavros/setpoint_position/local", 10);	
	    
	   
   ros::Rate loop_rate(20);
   
    geometry_msgs::Twist set_vel_iRobot;
    
    
   std::cout << "Definisco il mio primo obiettivo" <<std::endl;

   set_vel_iRobot.linear.x=0.3;
   set_vel_iRobot.linear.y=0.0;
   set_vel_iRobot.linear.z=0.0;
   set_vel_iRobot.angular.x=0.0;
   set_vel_iRobot.angular.y=0.0;
   set_vel_iRobot.angular.z=0.0;
   
   ros::Time last_request = ros::Time::now();
  
while (ros::ok()) // Keep spinning loop until user presses Ctrl+C
 {
 
   
   set_vel_pub.publish(set_vel_iRobot);
  
  //std::cout << "drone_pos x:"<<"\n"<< current_pose_drone.pose.position.x << "\n" << " drone_pos y:"<< "\n"<<current_pose_drone.pose.position.y<<"\n"<< "drone_pos:"<<"\n"<< current_pose_drone.pose.position.z << std::endl;
  std::cout << "iRobot_pos x:"<<"\n"<< current_pose_iRobot.pose.pose.position.x << "\n" << " iRobot_pos y:"<< "\n"<<current_pose_iRobot.pose.pose.position.y<<"\n"<< "iRobot_pos z:"<<"\n"<< current_pose_iRobot.pose.pose.position.z << std::endl;
 
  ros::spinOnce(); // Allow ROS to process incoming messages
 loop_rate.sleep(); // Sleep for the rest of the cycle


  }
  
return 0;


}