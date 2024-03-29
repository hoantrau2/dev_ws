/**
 * @file stanley_node.cpp
 * @author Hoan Duong & Hien Nguyen
 * @brief the stanley_controller_node of my thesis at my university,
 *  Ho Chi Minh University of Technology.
 * @version 1
 * @date 2024-03-29
 */
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "tf2_msgs/msg/tf_message.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <string>

#define ANGLE_MAX 45 / 180 * 3.14
#define Kp 10
#define Ksoft 10
#define RADIUS 0.03446

class StanleyNode : public rclcpp::Node {
public:
  StanleyNode()
      : Node("stanley_node"), angleIMU(0.0), linear_velocity(1.0),
        currentValuesMotor({4.0, 4.0, 4.0, 4.0}),
        actual_position({0.0, 0.0, 0.0}), desired_positon({1.0, 1.0, 0.5}) {

    subscription_angle_IMU_ =
        this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/angle_IMU", 10,
            std::bind(&StanleyNode::angle_IMU_callback, this,
                      std::placeholders::_1));

    subscription_actual_angle_ =
        this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/actual_angle", 10,
            std::bind(&StanleyNode::actual_angle_callback, this,
                      std::placeholders::_1));

    subscription_tf_ = this->create_subscription<tf2_msgs::msg::TFMessage>(
        "/tf", 10,
        std::bind(&StanleyNode::tf_callback, this, std::placeholders::_1));

    subscription_reference_map_ =
        this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/reference_map", 10,
            std::bind(&StanleyNode::reference_map_callback, this,
                      std::placeholders::_1));

    publisher_delta_angle_ =
        this->create_publisher<std_msgs::msg::Float64MultiArray>("/delta_angle",
                                                                 10);
    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(500),
        std::bind(&StanleyNode::timer_callback,
                  this)); // use create_wall_timer to timer 500ms
  }

private:
  void timer_callback() {
    double error_distace = -(actual_position[0] - desired_positon[0]) *
                               std::cos(actual_position[2]) +
                           (actual_position[1] - desired_positon[1]) *
                               std::sin(actual_position[2]);
    double angle_stenley_output =
        desired_positon[2] -
        std::atan2(Kp * error_distace, Ksoft * linear_velocity);

    if (angle_stenley_output > ANGLE_MAX)
      angle_stenley_output = ANGLE_MAX;
    else if (angle_stenley_output < -ANGLE_MAX)
      angle_stenley_output = ANGLE_MAX;

    // publish message with delta angle
    auto message = std_msgs::msg::Float64MultiArray();
    message.data.resize(1); // Set size of data vector to 4
    message.data[0] = angle_stenley_output;
    message.layout.data_offset = 333;
    publisher_delta_angle_->publish(message);
  }

  void
  actual_angle_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 222 && msg->data.size() == 4) {
      // Handle actual angle data
      for (size_t i = 0; i < 4; ++i) {
        currentValuesMotor[i] = msg->data[i];
      }
    } else {
      RCLCPP_ERROR(this->get_logger(), "Invalid message format or size");
    }
    linear_velocity =
        RADIUS * (currentValuesMotor[0] + currentValuesMotor[1]) / 2;
  }

  void
  angle_IMU_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 222 && msg->data.size() == 1) {
      RCLCPP_INFO(this->get_logger(), "Received angle of IMU");
      // Handle actual angle IMU
      angleIMU = msg->data[0];
    } else {
      RCLCPP_ERROR(this->get_logger(), "Invalid message format or size");
    }
  }

  void reference_map_callback(
      const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    if (msg->layout.data_offset == 222 && msg->data.size() == 3) {
      RCLCPP_INFO(this->get_logger(), "Received a reference map");
      // Handle a reference map
      for (size_t i = 0; i < 3; ++i) {
        desired_positon[i] = msg->data[i];
      }
    } else {
      RCLCPP_ERROR(this->get_logger(), "Invalid message format or size");
    }
  }

  void tf_callback(const tf2_msgs::msg::TFMessage::SharedPtr msg) {
    for (auto transform : msg->transforms) {
      if (transform.child_frame_id == "base_footprint") {
        RCLCPP_INFO(this->get_logger(), "Received a reference map");
        // Handle a reference map
        actual_position[0] = transform.transform.translation.x;
        actual_position[1] = transform.transform.translation.y;
        actual_position[2] = transform.transform.rotation.z;
        break; // Exit loop after finding the desired transform
      }
    }
  }

  double angleIMU;
  double linear_velocity;
  std::vector<double> currentValuesMotor;
  std::vector<double> actual_position;
  std::vector<double> desired_positon;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr
      subscription_angle_IMU_;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr
      subscription_actual_angle_;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr
      subscription_reference_map_;
  rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr subscription_tf_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr
      publisher_delta_angle_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<StanleyNode>());
  rclcpp::shutdown();
  return 0;
}
