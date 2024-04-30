cmake_minimum_required(VERSION 3.8)
project(cpp_interface)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(read_parameters_pi src/read_parameters_pi.cpp)
ament_target_dependencies(read_parameters_pi rclcpp std_msgs)

add_executable(test_cmd_vel src/test_cmd_vel.cpp)
ament_target_dependencies(test_cmd_vel rclcpp std_msgs geometry_msgs)

add_executable(pid_node src/pid_node.cpp)
ament_target_dependencies(pid_node rclcpp std_msgs)

add_executable(fuzzy_longitudinal_controllers src/fuzzy_longitudinal_controllers.cpp)
ament_target_dependencies(fuzzy_longitudinal_controllers rclcpp std_msgs)

add_executable(data_processing_node src/data_processing_node.cpp)
ament_target_dependencies(data_processing_node rclcpp std_msgs tf2_msgs)
add_executable(data_processing_node_straight src/data_processing_node_straight.cpp)
ament_target_dependencies(data_processing_node_straight rclcpp std_msgs tf2_msgs)
add_executable(data_processing_node_zz src/data_processing_node_zz.cpp)
ament_target_dependencies(data_processing_node_zz rclcpp std_msgs tf2_msgs)

add_executable(straight_line_node src/straight_line_node.cpp)
ament_target_dependencies(straight_line_node rclcpp std_msgs)

add_executable(circumference_node src/circumference_node.cpp)
ament_target_dependencies(circumference_node rclcpp std_msgs)

add_executable(sinusoidal_node src/sinusoidal_node.cpp)
ament_target_dependencies(sinusoidal_node rclcpp std_msgs)

add_executable(controllers_node src/controllers_node.cpp)
ament_target_dependencies(controllers_node rclcpp std_msgs)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
  read_parameters_pi
  test_cmd_vel
  pid_node
  fuzzy_longitudinal_controllers
  data_processing_node
  data_processing_node_straight
  data_processing_node_zz
  straight_line_node
  circumference_node
  sinusoidal_node
  controllers_node
  DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME})

ament_package()
