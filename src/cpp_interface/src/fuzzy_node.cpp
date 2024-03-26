/**
 * @file fuzzy_node.cpp
 * @author Hoan Duong & Hien Nguyen
 * @brief the pid_node of my thesis at my university, Ho Chi Minh University of
 * Technology.
 * @version 1
 * @date 2024-03-27
 */
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#define UK_MAX 0.87
#define SAMPLE_TIME 100 // in milliseconds

using namespace std::chrono_literals;

class FuzzyNode : public rclcpp::Node {
public:
  FuzzyNode() : Node("pid_node"), currentValues({4.0, 4.0, 4.0, 4.0}) {
    subscription_actual_angle_ =
        this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/actual_angle", 10,
            std::bind(&FuzzyNode::actual_angle_callback, this,
                      std::placeholders::_1));

    subscription_velocity_fuzzy_ =
        this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/velocity_fuzzy", 10,
            std::bind(&FuzzyNode::velocity_fuzzy_callback, this,
                      std::placeholders::_1));

    publisher_desired_angle_ =
        this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/desired_angle", 10);
    timer_ = this->create_wall_timer(
        500ms, std::bind(&FuzzyNode::timer_callback,
                         this)); // use create_wall_timer to timer 500ms
  }

private:
  void timer_callback() {
    // Assume you have some way to get setpoints for each motor
    std::vector<float> setpoints = {12.3, 14.3, 19.3, 30.3};
    MotorController motorController;
    std::vector<float> desiredAngles =
        motorController.updateMotors(setpoints, currentValues);
    // publish message with desired angles
    auto message = std_msgs::msg::Float64MultiArray();
    message.data.resize(4); // Set size of data vector to 4
    for (size_t i = 0; i < 4; ++i) {
      message.data[i] = desiredAngles[i];
    }
    message.layout.data_offset = 333;
    publisher_desired_angle_->publish(message);
  }

  void
  actual_angle_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 222 && msg->data.size() == 4) {
      // Handle actual angle data
      for (size_t i = 0; i < 4; ++i) {
        currentValues[i] = msg->data[i];
      }
    } else {
      RCLCPP_ERROR(this->get_logger(), "Invalid message format or size");
    }
  }

  void velocity_fuzzy_callback(
      const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    // Handle fuzzy velocity data
    RCLCPP_INFO(this->get_logger(), "Received fuzzy velocity");
    // Your logic here
    RCLCPP_INFO(this->get_logger(), "velocity fuzzy %f", msg->data[0]);
  }
  std::vector<float> currentValues;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr
      subscription_actual_angle_;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr
      subscription_velocity_fuzzy_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr
      publisher_desired_angle_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FuzzyNode>());
  rclcpp::shutdown();
  return 0;
}