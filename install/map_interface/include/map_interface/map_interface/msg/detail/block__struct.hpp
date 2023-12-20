// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from map_interface:msg/Block.idl
// generated code does not contain a copyright notice

#ifndef MAP_INTERFACE__MSG__DETAIL__BLOCK__STRUCT_HPP_
#define MAP_INTERFACE__MSG__DETAIL__BLOCK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__map_interface__msg__Block __attribute__((deprecated))
#else
# define DEPRECATED__map_interface__msg__Block __declspec(deprecated)
#endif

namespace map_interface
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Block_
{
  using Type = Block_<ContainerAllocator>;

  explicit Block_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->frame = 0ll;
      this->sig = 0ll;
      this->x = 0ll;
      this->y = 0ll;
      this->width = 0ll;
      this->height = 0ll;
    }
  }

  explicit Block_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->frame = 0ll;
      this->sig = 0ll;
      this->x = 0ll;
      this->y = 0ll;
      this->width = 0ll;
      this->height = 0ll;
    }
  }

  // field types and members
  using _frame_type =
    int64_t;
  _frame_type frame;
  using _sig_type =
    int64_t;
  _sig_type sig;
  using _x_type =
    int64_t;
  _x_type x;
  using _y_type =
    int64_t;
  _y_type y;
  using _width_type =
    int64_t;
  _width_type width;
  using _height_type =
    int64_t;
  _height_type height;

  // setters for named parameter idiom
  Type & set__frame(
    const int64_t & _arg)
  {
    this->frame = _arg;
    return *this;
  }
  Type & set__sig(
    const int64_t & _arg)
  {
    this->sig = _arg;
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
  Type & set__width(
    const int64_t & _arg)
  {
    this->width = _arg;
    return *this;
  }
  Type & set__height(
    const int64_t & _arg)
  {
    this->height = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    map_interface::msg::Block_<ContainerAllocator> *;
  using ConstRawPtr =
    const map_interface::msg::Block_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<map_interface::msg::Block_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<map_interface::msg::Block_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      map_interface::msg::Block_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<map_interface::msg::Block_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      map_interface::msg::Block_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<map_interface::msg::Block_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<map_interface::msg::Block_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<map_interface::msg::Block_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__map_interface__msg__Block
    std::shared_ptr<map_interface::msg::Block_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__map_interface__msg__Block
    std::shared_ptr<map_interface::msg::Block_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Block_ & other) const
  {
    if (this->frame != other.frame) {
      return false;
    }
    if (this->sig != other.sig) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->width != other.width) {
      return false;
    }
    if (this->height != other.height) {
      return false;
    }
    return true;
  }
  bool operator!=(const Block_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Block_

// alias to use template instance with default allocator
using Block =
  map_interface::msg::Block_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace map_interface

#endif  // MAP_INTERFACE__MSG__DETAIL__BLOCK__STRUCT_HPP_
