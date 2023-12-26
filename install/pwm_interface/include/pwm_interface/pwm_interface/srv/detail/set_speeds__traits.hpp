// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from pwm_interface:srv/SetSpeeds.idl
// generated code does not contain a copyright notice

#ifndef PWM_INTERFACE__SRV__DETAIL__SET_SPEEDS__TRAITS_HPP_
#define PWM_INTERFACE__SRV__DETAIL__SET_SPEEDS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "pwm_interface/srv/detail/set_speeds__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace pwm_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetSpeeds_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: left
  {
    out << "left: ";
    rosidl_generator_traits::value_to_yaml(msg.left, out);
    out << ", ";
  }

  // member: right
  {
    out << "right: ";
    rosidl_generator_traits::value_to_yaml(msg.right, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetSpeeds_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: left
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left: ";
    rosidl_generator_traits::value_to_yaml(msg.left, out);
    out << "\n";
  }

  // member: right
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right: ";
    rosidl_generator_traits::value_to_yaml(msg.right, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetSpeeds_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace pwm_interface

namespace rosidl_generator_traits
{

[[deprecated("use pwm_interface::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const pwm_interface::srv::SetSpeeds_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  pwm_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use pwm_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const pwm_interface::srv::SetSpeeds_Request & msg)
{
  return pwm_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<pwm_interface::srv::SetSpeeds_Request>()
{
  return "pwm_interface::srv::SetSpeeds_Request";
}

template<>
inline const char * name<pwm_interface::srv::SetSpeeds_Request>()
{
  return "pwm_interface/srv/SetSpeeds_Request";
}

template<>
struct has_fixed_size<pwm_interface::srv::SetSpeeds_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<pwm_interface::srv::SetSpeeds_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<pwm_interface::srv::SetSpeeds_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace pwm_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetSpeeds_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: ok
  {
    out << "ok: ";
    rosidl_generator_traits::value_to_yaml(msg.ok, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetSpeeds_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: ok
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ok: ";
    rosidl_generator_traits::value_to_yaml(msg.ok, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetSpeeds_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace pwm_interface

namespace rosidl_generator_traits
{

[[deprecated("use pwm_interface::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const pwm_interface::srv::SetSpeeds_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  pwm_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use pwm_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const pwm_interface::srv::SetSpeeds_Response & msg)
{
  return pwm_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<pwm_interface::srv::SetSpeeds_Response>()
{
  return "pwm_interface::srv::SetSpeeds_Response";
}

template<>
inline const char * name<pwm_interface::srv::SetSpeeds_Response>()
{
  return "pwm_interface/srv/SetSpeeds_Response";
}

template<>
struct has_fixed_size<pwm_interface::srv::SetSpeeds_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<pwm_interface::srv::SetSpeeds_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<pwm_interface::srv::SetSpeeds_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<pwm_interface::srv::SetSpeeds>()
{
  return "pwm_interface::srv::SetSpeeds";
}

template<>
inline const char * name<pwm_interface::srv::SetSpeeds>()
{
  return "pwm_interface/srv/SetSpeeds";
}

template<>
struct has_fixed_size<pwm_interface::srv::SetSpeeds>
  : std::integral_constant<
    bool,
    has_fixed_size<pwm_interface::srv::SetSpeeds_Request>::value &&
    has_fixed_size<pwm_interface::srv::SetSpeeds_Response>::value
  >
{
};

template<>
struct has_bounded_size<pwm_interface::srv::SetSpeeds>
  : std::integral_constant<
    bool,
    has_bounded_size<pwm_interface::srv::SetSpeeds_Request>::value &&
    has_bounded_size<pwm_interface::srv::SetSpeeds_Response>::value
  >
{
};

template<>
struct is_service<pwm_interface::srv::SetSpeeds>
  : std::true_type
{
};

template<>
struct is_service_request<pwm_interface::srv::SetSpeeds_Request>
  : std::true_type
{
};

template<>
struct is_service_response<pwm_interface::srv::SetSpeeds_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // PWM_INTERFACE__SRV__DETAIL__SET_SPEEDS__TRAITS_HPP_
