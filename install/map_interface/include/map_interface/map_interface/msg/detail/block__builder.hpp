// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from map_interface:msg/Block.idl
// generated code does not contain a copyright notice

#ifndef MAP_INTERFACE__MSG__DETAIL__BLOCK__BUILDER_HPP_
#define MAP_INTERFACE__MSG__DETAIL__BLOCK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "map_interface/msg/detail/block__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace map_interface
{

namespace msg
{

namespace builder
{

class Init_Block_height
{
public:
  explicit Init_Block_height(::map_interface::msg::Block & msg)
  : msg_(msg)
  {}
  ::map_interface::msg::Block height(::map_interface::msg::Block::_height_type arg)
  {
    msg_.height = std::move(arg);
    return std::move(msg_);
  }

private:
  ::map_interface::msg::Block msg_;
};

class Init_Block_width
{
public:
  explicit Init_Block_width(::map_interface::msg::Block & msg)
  : msg_(msg)
  {}
  Init_Block_height width(::map_interface::msg::Block::_width_type arg)
  {
    msg_.width = std::move(arg);
    return Init_Block_height(msg_);
  }

private:
  ::map_interface::msg::Block msg_;
};

class Init_Block_y
{
public:
  explicit Init_Block_y(::map_interface::msg::Block & msg)
  : msg_(msg)
  {}
  Init_Block_width y(::map_interface::msg::Block::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Block_width(msg_);
  }

private:
  ::map_interface::msg::Block msg_;
};

class Init_Block_x
{
public:
  explicit Init_Block_x(::map_interface::msg::Block & msg)
  : msg_(msg)
  {}
  Init_Block_y x(::map_interface::msg::Block::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Block_y(msg_);
  }

private:
  ::map_interface::msg::Block msg_;
};

class Init_Block_sig
{
public:
  explicit Init_Block_sig(::map_interface::msg::Block & msg)
  : msg_(msg)
  {}
  Init_Block_x sig(::map_interface::msg::Block::_sig_type arg)
  {
    msg_.sig = std::move(arg);
    return Init_Block_x(msg_);
  }

private:
  ::map_interface::msg::Block msg_;
};

class Init_Block_frame
{
public:
  Init_Block_frame()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Block_sig frame(::map_interface::msg::Block::_frame_type arg)
  {
    msg_.frame = std::move(arg);
    return Init_Block_sig(msg_);
  }

private:
  ::map_interface::msg::Block msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::map_interface::msg::Block>()
{
  return map_interface::msg::builder::Init_Block_frame();
}

}  // namespace map_interface

#endif  // MAP_INTERFACE__MSG__DETAIL__BLOCK__BUILDER_HPP_
