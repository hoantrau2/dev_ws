// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from tutorial_interfaces:msg/Float64.idl
// generated code does not contain a copyright notice

#ifndef TUTORIAL_INTERFACES__MSG__DETAIL__FLOAT64__BUILDER_HPP_
#define TUTORIAL_INTERFACES__MSG__DETAIL__FLOAT64__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "tutorial_interfaces/msg/detail/float64__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace tutorial_interfaces
{

namespace msg
{

namespace builder
{

class Init_Float64_size
{
public:
  explicit Init_Float64_size(::tutorial_interfaces::msg::Float64 & msg)
  : msg_(msg)
  {}
  ::tutorial_interfaces::msg::Float64 size(::tutorial_interfaces::msg::Float64::_size_type arg)
  {
    msg_.size = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tutorial_interfaces::msg::Float64 msg_;
};

class Init_Float64_data
{
public:
  Init_Float64_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Float64_size data(::tutorial_interfaces::msg::Float64::_data_type arg)
  {
    msg_.data = std::move(arg);
    return Init_Float64_size(msg_);
  }

private:
  ::tutorial_interfaces::msg::Float64 msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::tutorial_interfaces::msg::Float64>()
{
  return tutorial_interfaces::msg::builder::Init_Float64_data();
}

}  // namespace tutorial_interfaces

#endif  // TUTORIAL_INTERFACES__MSG__DETAIL__FLOAT64__BUILDER_HPP_
