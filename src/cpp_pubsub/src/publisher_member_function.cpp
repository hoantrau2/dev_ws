#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
// #include "tutorial_interfaces/msg/num.hpp"

using namespace std::chrono_literals; // std::chrono::milliseconds
                                      // duration(500);

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */
class MinimalPublisher : public rclcpp::Node 
{
  public:
    MinimalPublisher() 
        : Node("minimal_publisher"), count_(0) 
        {
          publisher_ = this->create_publisher<std_msgs::msg::Float64>("transfer_to_pico_topic", 10); // use create_publisher to create publisher
          timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this)); // use create_wall_timer to timer, timer 500ms
                                 // call timer_callback
        }

  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::Float64();
      message.data = this->count_++; 
      RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
      publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}

