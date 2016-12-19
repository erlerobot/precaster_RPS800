#include <ros/ros.h>
#include <sensor_msgs/Range.h>

void chatterCallback(const sensor_msgs::Range::ConstPtr& msg)
{
	ROS_INFO("I heard: [%.2f]", msg->range);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "precaster_rps800_listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("range", 1, chatterCallback);

  ros::spin();

  return 0;
}
