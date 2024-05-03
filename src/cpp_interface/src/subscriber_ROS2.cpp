#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
 public:
  MinimalSubscriber()
    : Node("QT_subscriber") {
    // Ensure that the necessary header is included
    subscription_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/QT_publisher_topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));

    if (subscription_ == nullptr) {
      // Check if subscription creation failed
      RCLCPP_ERROR(this->get_logger(), "Failed to create subscription.");
    }
  }

 private:
  void topic_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) const {
    if (msg != nullptr) {
      // Check if the data vector contains at least two elements
      if (msg->data.size() >= 2) {
        double value1 = msg->data[0];
        double value2 = msg->data[1];
        RCLCPP_INFO(this->get_logger(), "Received values: %lf, %lf", value1, value2);
      } else {
        RCLCPP_ERROR(this->get_logger(), "Received data vector does not contain enough elements");
      }
    } else {
      RCLCPP_ERROR(this->get_logger(), "Received null message");
    }
  }
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_;
};

int main(int argc, char* argv[]) {
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
