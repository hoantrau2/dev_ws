#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
public:
  MinimalSubscriber() : Node("minimal_subscriber") {
    subscription_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
        "transfer_to_pico_topic", 10,
        std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void
  topic_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) const {

     RCLCPP_INFO(this->get_logger(), "voltage: %lf",msg->data[0]);
     RCLCPP_INFO(this->get_logger(), "angular_pich: %lf",msg->data[1]);
     RCLCPP_INFO(this->get_logger(), "encoder: %lf",msg->data[2]);
     RCLCPP_INFO(this->get_logger(), "error: %lf",msg->data[3]);

  }
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}