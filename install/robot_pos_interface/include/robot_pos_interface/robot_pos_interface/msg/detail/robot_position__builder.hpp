// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_pos_interface:msg/RobotPosition.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_POS_INTERFACE__MSG__DETAIL__ROBOT_POSITION__BUILDER_HPP_
#define ROBOT_POS_INTERFACE__MSG__DETAIL__ROBOT_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_pos_interface/msg/detail/robot_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_pos_interface
{

namespace msg
{

namespace builder
{

class Init_RobotPosition_angle
{
public:
  explicit Init_RobotPosition_angle(::robot_pos_interface::msg::RobotPosition & msg)
  : msg_(msg)
  {}
  ::robot_pos_interface::msg::RobotPosition angle(::robot_pos_interface::msg::RobotPosition::_angle_type arg)
  {
    msg_.angle = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_pos_interface::msg::RobotPosition msg_;
};

class Init_RobotPosition_y
{
public:
  explicit Init_RobotPosition_y(::robot_pos_interface::msg::RobotPosition & msg)
  : msg_(msg)
  {}
  Init_RobotPosition_angle y(::robot_pos_interface::msg::RobotPosition::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_RobotPosition_angle(msg_);
  }

private:
  ::robot_pos_interface::msg::RobotPosition msg_;
};

class Init_RobotPosition_x
{
public:
  explicit Init_RobotPosition_x(::robot_pos_interface::msg::RobotPosition & msg)
  : msg_(msg)
  {}
  Init_RobotPosition_y x(::robot_pos_interface::msg::RobotPosition::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_RobotPosition_y(msg_);
  }

private:
  ::robot_pos_interface::msg::RobotPosition msg_;
};

class Init_RobotPosition_robot_id
{
public:
  explicit Init_RobotPosition_robot_id(::robot_pos_interface::msg::RobotPosition & msg)
  : msg_(msg)
  {}
  Init_RobotPosition_x robot_id(::robot_pos_interface::msg::RobotPosition::_robot_id_type arg)
  {
    msg_.robot_id = std::move(arg);
    return Init_RobotPosition_x(msg_);
  }

private:
  ::robot_pos_interface::msg::RobotPosition msg_;
};

class Init_RobotPosition_frame
{
public:
  Init_RobotPosition_frame()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotPosition_robot_id frame(::robot_pos_interface::msg::RobotPosition::_frame_type arg)
  {
    msg_.frame = std::move(arg);
    return Init_RobotPosition_robot_id(msg_);
  }

private:
  ::robot_pos_interface::msg::RobotPosition msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_pos_interface::msg::RobotPosition>()
{
  return robot_pos_interface::msg::builder::Init_RobotPosition_frame();
}

}  // namespace robot_pos_interface

#endif  // ROBOT_POS_INTERFACE__MSG__DETAIL__ROBOT_POSITION__BUILDER_HPP_
