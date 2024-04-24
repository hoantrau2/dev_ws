cmake_minimum_required(VERSION 3.8)
project(cpp_srvcli)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
# find_package(example_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2_msgs REQUIRED)

add_executable(data_processing_node src/data_processing_node.cpp)
ament_target_dependencies(data_processing_node rclcpp std_msgs tf2_msgs)

add_executable(straight_line_node src/straight_line_node.cpp)
ament_target_dependencies(straight_line_node rclcpp std_msgs)

install(TARGETS
data_processing_node
straight_line_node
DESTINATION lib/${PROJECT_NAME})
ament_package()
