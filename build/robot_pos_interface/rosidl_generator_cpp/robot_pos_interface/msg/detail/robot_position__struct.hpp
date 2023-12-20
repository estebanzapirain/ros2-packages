// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_pos_interface:msg/RobotPosition.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_POS_INTERFACE__MSG__DETAIL__ROBOT_POSITION__STRUCT_HPP_
#define ROBOT_POS_INTERFACE__MSG__DETAIL__ROBOT_POSITION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robot_pos_interface__msg__RobotPosition __attribute__((deprecated))
#else
# define DEPRECATED__robot_pos_interface__msg__RobotPosition __declspec(deprecated)
#endif

namespace robot_pos_interface
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RobotPosition_
{
  using Type = RobotPosition_<ContainerAllocator>;

  explicit RobotPosition_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->frame = 0ll;
      this->robot_id = 0ll;
      this->x = 0ll;
      this->y = 0ll;
      this->angle = 0ll;
    }
  }

  explicit RobotPosition_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->frame = 0ll;
      this->robot_id = 0ll;
      this->x = 0ll;
      this->y = 0ll;
      this->angle = 0ll;
    }
  }

  // field types and members
  using _frame_type =
    int64_t;
  _frame_type frame;
  using _robot_id_type =
    int64_t;
  _robot_id_type robot_id;
  using _x_type =
    int64_t;
  _x_type x;
  using _y_type =
    int64_t;
  _y_type y;
  using _angle_type =
    int64_t;
  _angle_type angle;

  // setters for named parameter idiom
  Type & set__frame(
    const int64_t & _arg)
  {
    this->frame = _arg;
    return *this;
  }
  Type & set__robot_id(
    const int64_t & _arg)
  {
    this->robot_id = _arg;
    return *this;
  }
  Type & set__x(
    const int64_t & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const int64_t & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__angle(
    const int64_t & _arg)
  {
    this->angle = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_pos_interface::msg::RobotPosition_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_pos_interface::msg::RobotPosition_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_pos_interface::msg::RobotPosition_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_pos_interface::msg::RobotPosition_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_pos_interface::msg::RobotPosition_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_pos_interface::msg::RobotPosition_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_pos_interface::msg::RobotPosition_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_pos_interface::msg::RobotPosition_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_pos_interface::msg::RobotPosition_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_pos_interface::msg::RobotPosition_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_pos_interface__msg__RobotPosition
    std::shared_ptr<robot_pos_interface::msg::RobotPosition_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_pos_interface__msg__RobotPosition
    std::shared_ptr<robot_pos_interface::msg::RobotPosition_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotPosition_ & other) const
  {
    if (this->frame != other.frame) {
      return false;
    }
    if (this->robot_id != other.robot_id) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->angle != other.angle) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotPosition_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotPosition_

// alias to use template instance with default allocator
using RobotPosition =
  robot_pos_interface::msg::RobotPosition_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_pos_interface

#endif  // ROBOT_POS_INTERFACE__MSG__DETAIL__ROBOT_POSITION__STRUCT_HPP_
