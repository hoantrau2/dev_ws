#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/num.hpp"

using namespace std::chrono_literals; // std::chrono::milliseconds
                                      // duration(500);

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */
class MinimalPublisher : public rclcpp::Node {
public:
  MinimalPublisher() : Node("minimal_publisher"), count_(0) {
    publisher_ = this->create_publisher<tutorial_interfaces::msg::Num>(
        "topic", 10); // use create_publisher to create publisher
    timer_ = this->create_wall_timer(
        500ms, std::bind(&MinimalPublisher::timer_callback,
                         this)); // use create_wall_timer to timer, timer 500ms
                                 // call timer_callback
  }

private:
  void timer_callback() {
    auto message = tutorial_interfaces::msg::Num();
    message.num = this->count_++; 
    RCLCPP_INFO(this->get_logger(), "Publishing: '%ld'", message.num);
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<tutorial_interfaces::msg::Num>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
