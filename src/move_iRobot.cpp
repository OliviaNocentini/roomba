#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>

nav_msgs::Odometry current_pose_iRobot;

void pose_cb_iRobot(const nav_msgs::Odometry::ConstPtr& msg){
    current_pose_iRobot = *msg;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_iRobot");
  ros::NodeHandle nh;
  
 
  ros::Subscriber pose_sub_iRobot = nh.subscribe<nav_msgs::Odometry>
           ("iRobot/odom", 10, pose_cb_iRobot);
  ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>
            ("iRobot/cmd_vel", 10);

	  
    std::cout << "Type a command and then press enter.  "
      "Use '+' to move forward, 'l' to turn left, "
      "'r' to turn right, '.' to exit.\n";
    
     ros::Rate loop_rate(20);

    //we will be sending commands of type "twist"
    geometry_msgs::Twist base_cmd;
    
     ros::Time last_request = ros::Time::now();

    char cmd[50];
    while(nh.ok()){

      std::cin.getline(cmd, 50);
      if(cmd[0]!='+' && cmd[0]!='l' && cmd[0]!='r' && cmd[0]!='.')
      {
        std::cout << "unknown command:" << cmd << "\n";
        continue;
      }

      base_cmd.linear.x = base_cmd.linear.y = base_cmd.angular.z = 0;
      //move forward
      if(cmd[0]=='+'){
        base_cmd.linear.x = 0.1;
      }
      //turn left (yaw) and drive forward at the same time
      else if(cmd[0]=='l'){
        base_cmd.angular.z = 0.75;
        base_cmd.linear.x = 0.25;
      }
      //turn right (yaw) and drive forward at the same time
      else if(cmd[0]=='r'){
        base_cmd.angular.z = -0.75;
        base_cmd.linear.x = 0.25;
      }
      //quit
      else if(cmd[0]=='.'){
        break;
      }

      //publish the assembled command
      cmd_vel_pub.publish(base_cmd);
      std::cout << "iRobot_pos x:"<<"\n"<< current_pose_iRobot.pose.pose.position.x << "\n" << " iRobot_pos y:"<< "\n"<<current_pose_iRobot.pose.pose.position.y<<"\n"<< "iRobot_pos z:"<<"\n"<< current_pose_iRobot.pose.pose.position.z << std::endl;
 
    ros::spinOnce(); // Allow ROS to process incoming messages
 loop_rate.sleep(); // Sleep for the rest of the cycle

    }
    return 0;
  
}	    
