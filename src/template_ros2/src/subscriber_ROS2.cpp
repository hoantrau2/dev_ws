// #define SUBCRIBER_ROS2

#ifdef SUBCRIBER_ROS2_TWIST
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <string>

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
public:
  MinimalSubscriber() : Node("subscriber_ROS2") {
    subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
        "/cmd_vel", 10,
        std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const geometry_msgs::msg::Twist::SharedPtr msg) const {
    RCLCPP_INFO(this->get_logger(), "linear_x: %lf", msg->linear.x);
    RCLCPP_INFO(this->get_logger(), "angular_z: %lf", msg->angular.z);
  }
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
#endif

#ifdef SUBSCRIBER_INT32
#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("subscriber_from_pico")
  {
    // Ensure that the necessary header is included
    subscription_ = this->create_subscription<std_msgs::msg::Int32>(
      "pico_publisher_topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));

    if (subscription_ == nullptr) {
      // Check if subscription creation failed
      RCLCPP_ERROR(this->get_logger(), "Failed to create subscription.");
    }
  }

private:
  // Fix the type and add a default value for msg.data
  void topic_callback(const std_msgs::msg::Int32::SharedPtr msg) const
  {
    if (msg != nullptr) {
      // Use msg->data instead of msg.data
      RCLCPP_INFO(this->get_logger(), "I heard: '%d'", msg->data);
    } else {
      RCLCPP_ERROR(this->get_logger(), "Received null message");
    }
  }
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<MinimalSubscriber>();

  // Check if the node is successfully created
  if (node != nullptr) {
    rclcpp::spin(node);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("main"), "Failed to create node");
  }

  rclcpp::shutdown();
  return 0;
}
#endif