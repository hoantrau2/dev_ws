// #include <memory>
// #include <functional>
// #include "rclcpp/rclcpp.hpp"
// #include "tutorial_interfaces/msg/my_interface.hpp"
// #include "std_msgs/msg/string.hpp"

// using std::placeholders::_1;

// class MinimalSubscriber : public rclcpp::Node
// {
// public:
//   MinimalSubscriber()  : Node("read_data_picoW_node")
//   {
//     // Ensure that the necessary header is included
//     subscription_ = this->create_subscription<tutorial_interfaces::msg::MyInterface>(
//       "pico_publisher_topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));

//     if (subscription_ == nullptr) {
//       // Check if subscription creation failed
//       RCLCPP_ERROR(this->get_logger(), "Failed to create subscription.");
//     }
//   }

// private:
//   // Fix the type and add a default value for msg.data
//   void topic_callback(const tutorial_interfaces::msg::MyInterface::SharedPtr msg) const
//   {
//     if (msg != nullptr) {
//       // Use msg->data instead of msg.data
//       RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg->data);

//     } else {
//       RCLCPP_ERROR(this->get_logger(), "Received null message");
//     }
//   }
//   rclcpp::Subscription<tutorial_interfaces::msg::MyInterface>::SharedPtr subscription_;
// };

// int main(int argc, char * argv[])
// {
//   rclcpp::init(argc, argv);

//   auto node = std::make_shared<MinimalSubscriber>();

//   // Check if the node is successfully created
//   if (node != nullptr) {
//     rclcpp::spin(node);
//   } else {
//     RCLCPP_ERROR(rclcpp::get_logger("main"), "Failed to create node");
//   }

//   rclcpp::shutdown();
//   return 0;
// }

#include <memory>
#include <functional>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber() : Node("read_data_picoW_node")
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "pico_publisher_topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));

    if (subscription_ == nullptr) {
      RCLCPP_ERROR(this->get_logger(), "Failed to create subscription.");
    }
  }

private:
  void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
  {
    if (msg != nullptr) {
      RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
    } else {
      RCLCPP_ERROR(this->get_logger(), "Received null message");
    }
  }

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<MinimalSubscriber>();

  if (node != nullptr) {
    rclcpp::spin(node);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("main"), "Failed to create node");
  }

  rclcpp::shutdown();
  return 0;
}