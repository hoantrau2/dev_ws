/**
 * @file pid_node.cpp
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

#define UK_MAX 0.8
#define SAMPLE_TIME 100 // in milliseconds

using namespace std::chrono_literals;

// Complete definition of PID_t structure
typedef struct {
  float Kp;
  float Ki;
  float Kd;
  float ek_1;
  float ek_2;
  float uk_1;
} PID_t;

// Function prototypes
void init_pid(PID_t *pid, float kp, float ki, float kd);
float PID_controller(float sp, float pv, PID_t *pid);

// Define a class for controlling motors using PID controllers
class MotorController {
public:
  MotorController() {
    // Initialize PID controllers for each motor
    for (int i = 0; i < 4; ++i) {
      PID_t pid;
      init_pid(&pid, Kp[i], Ki[i], Kd[i]);
      pid_controllers.push_back(pid);
    }
  }

  // Method to update motor speeds based on setpoints and current values
  std::vector<float> updateMotors(const std::vector<float> &setpoints,
                                  const std::vector<float> &currentValues) {
    std::vector<float> outputs;
    for (int i = 0; i < 4; ++i) {
      outputs.push_back(
          PID_controller(setpoints[i], currentValues[i], &pid_controllers[i]));
    }
    return outputs;
  }

private:
  // Define PID parameters for each motor
  const float Kp[4] = {0.2, 0.2, 0.2, 0.2};
  const float Ki[4] = {0.7, 0.7, 0.7, 0.7};
  const float Kd[4] = {0.0, 0.0, 0.0, 0.0};

  // Vector to store PID controllers for each motor
  std::vector<PID_t> pid_controllers;
};

// Function to calculate PID control signal
float PID_controller(float sp, float pv, PID_t *pid) {
  float ek, uk; // uk: - UK_MAX->UK_MAX
  ek = sp - pv;
  uk = pid->uk_1 + pid->Kp * (ek - pid->ek_1) +
       pid->Ki * SAMPLE_TIME * 1e-3 * (ek + pid->ek_1) * 0.5 +
       pid->Kd * (ek - 2 * pid->ek_1 + pid->ek_2) / (SAMPLE_TIME * 1e-3);

  if (uk > UK_MAX)
    uk = UK_MAX;
  else if (uk < -UK_MAX)
    uk = -UK_MAX;

  pid->uk_1 = uk;
  pid->ek_1 = ek;
  pid->ek_2 = pid->ek_1;

  return uk;
}

// Function to initialize PID controller parameters
void init_pid(PID_t *pid, float kp, float ki, float kd) {
  pid->Kp = kp;
  pid->Ki = ki;
  pid->Kd = kd;
  pid->uk_1 = 0;
  pid->ek_1 = 0;
  pid->ek_2 = 0;
}

class PIDNode : public rclcpp::Node {
public:
  PIDNode() : Node("pid_node"), currentValues({4.0, 4.0, 4.0, 4.0}) {
    subscription_actual_angle_ =
        this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/actual_angle", 10,
            std::bind(&PIDNode::actual_angle_callback, this,
                      std::placeholders::_1));

    subscription_velocity_fuzzy_ =
        this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/velocity_fuzzy", 10,
            std::bind(&PIDNode::velocity_fuzzy_callback, this,
                      std::placeholders::_1));

    publisher_desired_angle_ =
        this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/desired_angle", 10);
    timer_ = this->create_wall_timer(
        500ms, std::bind(&PIDNode::timer_callback,
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
  rclcpp::spin(std::make_shared<PIDNode>());
  rclcpp::shutdown();
  return 0;
}
