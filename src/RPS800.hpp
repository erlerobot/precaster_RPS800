#ifndef RPS800_H
#define RPS800_H

#include <serial/serial.h>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/range.hpp>

#include <string>
#include <iostream>
#include <cstdio>
#include <stdlib.h>     /* atoi */
#include <unistd.h>

class RPS800
{
public:
  RPS800(std::string port,
         unsigned long baud,
         std::shared_ptr<rclcpp::node::Node> node);

  void read_and_send_message();

private:
  rclcpp::publisher::Publisher<sensor_msgs::msg::Range>::SharedPtr rangefinder_pub;
  serial::Serial my_serial;
};

#endif // RPS800_H
