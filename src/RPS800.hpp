#ifndef RPS800_H
#define RPS800_H

#include <serial/serial.h>
#include <ros/ros.h>
#include <sensor_msgs/Range.h>

#include <string>
#include <iostream>
#include <cstdio>
#include <stdlib.h>     /* atoi */
#include <unistd.h>

class RPS800
{
public:
  RPS800(std::string port, unsigned long baud);
  void read_message();

private:
  ros::Publisher rangefinder_pub;
  serial::Serial my_serial;
};

#endif // RPS800_H
