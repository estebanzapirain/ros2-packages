// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from pwm_interface:srv/SetSpeeds.idl
// generated code does not contain a copyright notice

#ifndef PWM_INTERFACE__SRV__DETAIL__SET_SPEEDS__BUILDER_HPP_
#define PWM_INTERFACE__SRV__DETAIL__SET_SPEEDS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "pwm_interface/srv/detail/set_speeds__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace pwm_interface
{

namespace srv
{

namespace builder
{

class Init_SetSpeeds_Request_right
{
public:
  explicit Init_SetSpeeds_Request_right(::pwm_interface::srv::SetSpeeds_Request & msg)
  : msg_(msg)
  {}
  ::pwm_interface::srv::SetSpeeds_Request right(::pwm_interface::srv::SetSpeeds_Request::_right_type arg)
  {
    msg_.right = std::move(arg);
    return std::move(msg_);
  }

private:
  ::pwm_interface::srv::SetSpeeds_Request msg_;
};

class Init_SetSpeeds_Request_left
{
public:
  explicit Init_SetSpeeds_Request_left(::pwm_interface::srv::SetSpeeds_Request & msg)
  : msg_(msg)
  {}
  Init_SetSpeeds_Request_right left(::pwm_interface::srv::SetSpeeds_Request::_left_type arg)
  {
    msg_.left = std::move(arg);
    return Init_SetSpeeds_Request_right(msg_);
  }

private:
  ::pwm_interface::srv::SetSpeeds_Request msg_;
};

class Init_SetSpeeds_Request_id
{
public:
  Init_SetSpeeds_Request_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetSpeeds_Request_left id(::pwm_interface::srv::SetSpeeds_Request::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_SetSpeeds_Request_left(msg_);
  }

private:
  ::pwm_interface::srv::SetSpeeds_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::pwm_interface::srv::SetSpeeds_Request>()
{
  return pwm_interface::srv::builder::Init_SetSpeeds_Request_id();
}

}  // namespace pwm_interface


namespace pwm_interface
{

namespace srv
{

namespace builder
{

class Init_SetSpeeds_Response_ok
{
public:
  Init_SetSpeeds_Response_ok()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::pwm_interface::srv::SetSpeeds_Response ok(::pwm_interface::srv::SetSpeeds_Response::_ok_type arg)
  {
    msg_.ok = std::move(arg);
    return std::move(msg_);
  }

private:
  ::pwm_interface::srv::SetSpeeds_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::pwm_interface::srv::SetSpeeds_Response>()
{
  return pwm_interface::srv::builder::Init_SetSpeeds_Response_ok();
}

}  // namespace pwm_interface

#endif  // PWM_INTERFACE__SRV__DETAIL__SET_SPEEDS__BUILDER_HPP_
