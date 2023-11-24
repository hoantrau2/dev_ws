#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"

typedef struct StdMsgsMsgFloat64
{
  double data;
} StdMsgsMsgFloat64;

typedef struct StdMsgsMsgFloat64Sequence
{
  StdMsgsMsgFloat64 *data;
  uint32_t size;
  uint32_t capacity;
} StdMsgsMsgFloat64Sequence;

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("subscriber_from_pico")
  {
    // Create subscription
    subscription_ = this->create_subscription<StdMsgsMsgFloat64Sequence>(
      "pico_publisher_topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));

    if (subscription_ == nullptr) {
      // Check if subscription creation failed
      RCLCPP_ERROR(this->get_logger(), "Failed to create subscription.");
    }
  }

private:
  // Fix the type and add a default value for msg.data
  void topic_callback(const StdMsgsMsgFloat64Sequence &msg) const
  {
   
      RCLCPP_INFO(this->get_logger(), "Received sequence with size %u", msg.size);

      for (uint32_t i = 0; i < msg.size; ++i) {
        RCLCPP_INFO(this->get_logger(), "  Item: %f", msg.data[i].data);
      }
  
  }

  rclcpp::Subscription<StdMsgsMsgFloat64Sequence>::SharedPtr subscription_;
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
