// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from tutorial_interfaces:msg/MyInterface.idl
// generated code does not contain a copyright notice

#ifndef TUTORIAL_INTERFACES__MSG__DETAIL__MY_INTERFACE__BUILDER_HPP_
#define TUTORIAL_INTERFACES__MSG__DETAIL__MY_INTERFACE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "tutorial_interfaces/msg/detail/my_interface__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace tutorial_interfaces
{

namespace msg
{

namespace builder
{

class Init_MyInterface_data
{
public:
  explicit Init_MyInterface_data(::tutorial_interfaces::msg::MyInterface & msg)
  : msg_(msg)
  {}
  ::tutorial_interfaces::msg::MyInterface data(::tutorial_interfaces::msg::MyInterface::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tutorial_interfaces::msg::MyInterface msg_;
};

class Init_MyInterface_first_data
{
public:
  Init_MyInterface_first_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MyInterface_data first_data(::tutorial_interfaces::msg::MyInterface::_first_data_type arg)
  {
    msg_.first_data = std::move(arg);
    return Init_MyInterface_data(msg_);
  }

private:
  ::tutorial_interfaces::msg::MyInterface msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::tutorial_interfaces::msg::MyInterface>()
{
  return tutorial_interfaces::msg::builder::Init_MyInterface_first_data();
}

}  // namespace tutorial_interfaces

#endif  // TUTORIAL_INTERFACES__MSG__DETAIL__MY_INTERFACE__BUILDER_HPP_
