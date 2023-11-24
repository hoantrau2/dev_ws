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

#ifdef PUBLISHER_C
#include <stdio.h> // Include for printf
#include <rcl/rcl.h> 
#include <rcl/error_handling.h> 
#include <rclc/rclc.h> 
#include <rclc/executor.h> 
#include <std_msgs/msg/int32.h> 
#include <std_msgs/msg/float64.h> 
#include <std_msgs/msg/string.h>

rcl_subscription_t subscription;
std_msgs__msg__Float64 msg;

void subscription_callback(const void *msgin) {
  const std_msgs__msg__Float64 *float_msg = (const std_msgs__msg__Float64 *)msgin;
  if (float_msg != NULL) {
    printf("I heard: '%f'\n", float_msg->data);
  } else {
    printf("Received null message\n");
  }
}

int main(int argc, char *argv[]) {

  // Initialize Node
  rcl_node_t node;
  if (rclc_node_init_default(&node, "subscriber_from_pico_node", "", &support) != RCL_RET_OK) {
    printf("Error initializing ROS node\n");
    return -1;
  }

  // Initialize Subscription
  if (rclc_subscription_init_default(
          &subscription, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float64),
          "pico_publisher_topic") != RCL_RET_OK) {
    printf("Error initializing ROS subscription\n");
    return -1;
  }

  // Initialize Executor
  rclc_executor_t executor;
  rclc_executor_init(&executor, &support.context, 1, &allocator);

  if (rclc_executor_add_subscription(
          &executor, &subscription, &msg, subscription_callback, 
          ON_NEW_DATA) != RCL_RET_OK) {
    printf("Error adding subscription to executor\n");
    return -1;
  }

  while (1) {
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
  }

  // Clean up
  rcl_subscription_fini(&subscription, &node);
  rcl_node_fini(&node);

  return 0;
}
#endif



