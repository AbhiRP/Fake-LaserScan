//Author: Abhi Ravikumar
//Reference 1: http://wiki.ros.org/navigation/Tutorials/RobotSetup/Sensors
//Reference 2: http://answers.ros.org/question/198843/need-explanation-on-sensor_msgslaserscanmsg/ 


#include <ros/ros.h>
#include <stdlib.h>
#include <sensor_msgs/LaserScan.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "laserscan_publisher");
  ros::NodeHandle n;
  ros::Publisher scan_pub = n.advertise<sensor_msgs::LaserScan>("scan", 50);

  //Using Hokuyo UST-20LX laser scanner parameters
  
  unsigned int num_readings = 1081;
  double laser_frequency = 50;
  double ranges[num_readings];
  double intensities[num_readings];

  int count = 0;
  srand(time(0));
  ros::Rate r(1.0);
  while(n.ok())
  {
  //generate some fake data for our laser scan
    for(unsigned int i = 0; i < num_readings; ++i)
    {
      ranges[i] = count;
      intensities[i] = 100 + count;
    }
    ros::Time scan_time = ros::Time::now();
    
    //Assuming a lidar with 1081 measurement steps, detection angle of 270 Degrees and angular resolution of 0.25 Degrees
    //populate the LaserScan message
    sensor_msgs::LaserScan scan;
    scan.header.stamp = scan_time;
    scan.header.frame_id = "laser_frame";
    scan.angle_min = -135 * (3.14/180);
    scan.angle_max = 135 * (3.14/180);
    scan.angle_increment = 0.25 * (3.14/180);
    scan.time_increment = (1 / laser_frequency) / (num_readings);
    scan.range_min = 0.02;
    scan.range_max = 20.0;
    
    scan.ranges.resize(num_readings);
    scan.intensities.resize(num_readings);
    for(unsigned int i = 0; i < num_readings; ++i)
    {
      scan.ranges[i] = ranges[i];
      scan.intensities[i] = intensities[i];
    }

    scan_pub.publish(scan);
    ++count;
    r.sleep();
  }
}

