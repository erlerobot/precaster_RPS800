#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/range.hpp>

void cb_range(const sensor_msgs::msg::Range::SharedPtr msg)
{
  printf("Distance: [%+6.3f]\n", msg->range);
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("precaster_rps800_rangefinder_listener");

  auto sub = node->create_subscription<sensor_msgs::msg::Range>(
    "range", cb_range, rmw_qos_profile_sensor_data);
  rclcpp::spin(node);

  return 0;
}
