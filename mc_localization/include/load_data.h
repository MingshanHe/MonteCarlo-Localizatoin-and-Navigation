#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/Float32.h"
#include <math.h>
#include <iostream>
using namespace std;
typedef struct 
{
	float x_robot,y_robot,theta_robot; 		// 机器人位姿
}Odom_Data;

class LoadData
{
	public:
	
        LoadData(ros::NodeHandle node)
        {
            node_ = node;
            laser_sub = node_.subscribe("/scan", 1000, &LoadData::Load_Laser,this);
            odom_sub  = node_.subscribe("/odom", 1000, &LoadData::Load_Odom,this);
            flag = true;
        };
        ~LoadData(){};

    private:
        ros::NodeHandle node_;
        ros::Subscriber odom_sub;
        ros::Subscriber laser_sub;
        bool flag;

    public:
        void Load_Laser(const sensor_msgs::LaserScan::ConstPtr& msg){
            ROS_INFO("I heard scan: ");
            // data.clear();
            for (int i = 0; i < msg->ranges.size(); i++) {
                cout<<msg->ranges[i]<<endl;
                data.push_back(msg->ranges[i]);
            }
        };

        void Load_Odom(const nav_msgs::Odometry::ConstPtr& msg){
            
            ROS_INFO("I heard odom: ");
            if (flag)
            {
                old_odom_data.x_robot = msg->pose.pose.position.x;
                old_odom_data.y_robot = msg->pose.pose.position.y;
                float x = msg->pose.pose.orientation.x;
                float y = msg->pose.pose.orientation.y;
                float z = msg->pose.pose.orientation.z;
                float w = msg->pose.pose.orientation.w;
                old_odom_data.theta_robot = atan2(2*(w*z+x*y),1-2*(y*y+z*z));
                new_odom_data.x_robot = old_odom_data.x_robot;
                new_odom_data.y_robot = old_odom_data.y_robot;
                new_odom_data.theta_robot = old_odom_data.theta_robot;
                flag = false;
            }
            else{
                old_odom_data.x_robot = new_odom_data.x_robot;
                old_odom_data.y_robot = new_odom_data.y_robot;
                old_odom_data.theta_robot = new_odom_data.theta_robot;

                new_odom_data.x_robot     = msg->pose.pose.position.x;
                new_odom_data.y_robot     = msg->pose.pose.position.y;
                float x = msg->pose.pose.orientation.x;
                float y = msg->pose.pose.orientation.y;
                float z = msg->pose.pose.orientation.z;
                float w = msg->pose.pose.orientation.w;
                new_odom_data.theta_robot = atan2(2*(w*z+x*y),1-2*(y*y+z*z));
            }
        };
    public:
        vector<double> data;
        Odom_Data new_odom_data;
        Odom_Data old_odom_data;
        
};
#endif