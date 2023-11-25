#ifdef TEST
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/Float64MultiArray.h"
#include <functional>
#include <memory>
#include <rcl/error_handling.h>
#include <rcl/rcl.h>
#include <rclc/executor.h>
#include <rclc/rclc.h>
#include <stdio.h>

#ifdef C
rcl_subscription_t subscription;
tutorial_interfaces__msg__Float64__Sequence msgh;

void subscription_callback(const void *msgin) {
  const tutorial_interfaces__msg__Float64__Sequence *msgh =
      (const tutorial_interfaces__msg__Float64__Sequence *)msgin;
  printf("%ld", msgh->size);
  // RCLCPP_INFO(" ", "I heard: '%lf'", msgh->data[0].data);
  // RCLCPP_INFO(" ", "I heard: '%lf'", msgh->data[1].data);
  // RCLCPP_INFO(" ", "I heard: '%lf'", msgh->data[2].data);
  // RCLCPP_INFO(" ", "I heard: '%lf'", msgh->data[3].data);
}

int main(int argc, char *argv[]) {
  printf("hoan");
  rclcpp::init(argc, argv);

  rcl_node_t node;
  rcl_allocator_t allocator;
  rclc_support_t support;
  rclc_executor_t executor;
  allocator = rcl_get_default_allocator();

  rclc_support_init(&support, 0, NULL, &allocator);
  rclc_node_init_default(&node, "pico_subscriber_node", "", &support);
  rclc_subscription_init_default(
      &subscription, &node,
      ROSIDL_GET_MSG_TYPE_SUPPORT(tutorial_interfaces, msg, Float64),
      "transfer_to_pico_topic");
  rclc_executor_init(&executor, &support.context, 1, &allocator);
  rclc_executor_add_subscription(&executor, &subscription, &msgh,
                                 &subscription_callback, ON_NEW_DATA);
  while (true) {
    //    rclc_spin_node_once(&node, 1000000);
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
    // sleep_us(100000);
  }

  return 0;
}
#endif

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
public:
  MinimalSubscriber() : Node("read_data_picoW_node") {
    // Ensure that the necessary header is included
    subscription_ = this->create_subscription<std_msgs::Float64MultiArray>(
        "transfer_to_pico_topic", 10,
        std::bind(&MinimalSubscriber::topic_callback, this, _1));

    if (subscription_ == nullptr) {
      // Check if subscription creation failed
      RCLCPP_ERROR(this->get_logger(), "Failed to create subscription.");
    }
  }

private:
  // Fix the type and add a default value for msg.data
  void topic_callback(const std_msgs::Float64MultiArray::ConstPtr &msg) const {
    if (msg) {
      // Use msg->data instead of msg.data;

      // RCLCPP_INFO(this->get_logger(), "voltage: '%lf'", msg->data.data[0]);
      // RCLCPP_INFO(this->get_logger(), "angular_pich: '%lf'",
      // msg->data.data[1]); RCLCPP_INFO(this->get_logger(), "encoder: '%lf'",
      // msg->data.data[2]); RCLCPP_INFO(this->get_logger(), "error: '%lf'",
      // msg->data.data[3]);

    } else {
      RCLCPP_ERROR(this->get_logger(), "Received null message");
    }
  }
  rclcpp::Subscription<std_msgs::Float64MultiArray>::SharedPtr subscription_;
};

int main(int argc, char *argv[]) {
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
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node {
public:
  MinimalPublisher() : Node("minimal_publisher"), count_(0) {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    timer_ = this->create_wall_timer(
        500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback() {
    auto message = std_msgs::msg::String();
    message.data = "Hello, world! " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}