#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

#include <memory>

void add(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request>
             request, // receive request from client
         std::shared_ptr<example_interfaces::srv::AddTwoInts::Response>
             response) // tranffer response to client
{
  response->sum = request->a + request->b;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
              "Incoming request\na: %ld"
              " b: %ld",
              request->a, request->b);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]",
              (long int)response->sum);
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node =
      rclcpp::Node::make_shared("add_two_ints_server"); //create node with name "add_two_ints_server"

  rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service = // example_interfaces::srv::AddTwoInts: type of service 
      node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", //name of service if "add_two_ints"
                                                                &add);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}