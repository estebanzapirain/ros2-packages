// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from map_interface:msg/Block.idl
// generated code does not contain a copyright notice

#ifndef MAP_INTERFACE__MSG__DETAIL__BLOCK__TRAITS_HPP_
#define MAP_INTERFACE__MSG__DETAIL__BLOCK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "map_interface/msg/detail/block__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace map_interface
{

namespace msg
{

inline void to_flow_style_yaml(
  const Block & msg,
  std::ostream & out)
{
  out << "{";
  // member: frame
  {
    out << "frame: ";
    rosidl_generator_traits::value_to_yaml(msg.frame, out);
    out << ", ";
  }

  // member: sig
  {
    out << "sig: ";
    rosidl_generator_traits::value_to_yaml(msg.sig, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: width
  {
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << ", ";
  }

  // member: height
  {
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Block & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: frame
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frame: ";
    rosidl_generator_traits::value_to_yaml(msg.frame, out);
    out << "\n";
  }

  // member: sig
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sig: ";
    rosidl_generator_traits::value_to_yaml(msg.sig, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << "\n";
  }

  // member: height
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Block & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace map_interface

namespace rosidl_generator_traits
{

[[deprecated("use map_interface::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const map_interface::msg::Block & msg,
  std::ostream & out, size_t indentation = 0)
{
  map_interface::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use map_interface::msg::to_yaml() instead")]]
inline std::string to_yaml(const map_interface::msg::Block & msg)
{
  return map_interface::msg::to_yaml(msg);
}

template<>
inline const char * data_type<map_interface::msg::Block>()
{
  return "map_interface::msg::Block";
}

template<>
inline const char * name<map_interface::msg::Block>()
{
  return "map_interface/msg/Block";
}

template<>
struct has_fixed_size<map_interface::msg::Block>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<map_interface::msg::Block>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<map_interface::msg::Block>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MAP_INTERFACE__MSG__DETAIL__BLOCK__TRAITS_HPP_
