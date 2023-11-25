#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()  : Node("subscriber_from_pico_node")
  {
    // Ensure that the necessary header is included
    subscription_ = this->create_subscription<std_msgs::msg::Float64>(
      "pico_publisher_topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));

    if (subscription_ == nullptr) {
      // Check if subscription creation failed
      RCLCPP_ERROR(this->get_logger(), "Failed to create subscription.");
    }
  }

private:
  // Fix the type and add a default value for msg.data
  void topic_callback(const std_msgs::msg::Float64::SharedPtr msg) const
  {
    if (msg != nullptr) {
      // Use msg->data instead of msg.data
      RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg->data);

    } else {
      RCLCPP_ERROR(this->get_logger(), "Received null message");
    }
  }
  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
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




